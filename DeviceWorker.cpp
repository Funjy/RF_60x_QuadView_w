#include "DeviceWorker.h"

DeviceWorker::DeviceWorker(QObject *parent)
	: QObject(parent)
{
	
	_sensor = 0;
	DevAddress(1);
}

DeviceWorker::~DeviceWorker()
{
	delete _sensor;
}

void DeviceWorker::findActiveComPorts()
{
	_sensor = new RF603Device();
	QStringList ql;
	for(int i=0; i<10; i++)
	{
		QString str = "COM" + QString::number(i);
		if(_sensor->OpenPort(str.toUtf8().constData(), 2400))
		{
			//port opened may work with it
			ql.append(str);
		}
		_sensor->ClosePort();
	}
	delete _sensor;
	_sensor = 0;
	_comPorts = ql;
}

void DeviceWorker::ReceiveNewValues()
{
	if(!_sensor)
		return;
	float val = _sensor->GetSingleMeasure();
	emit NewValueReceived(val);
}

bool DeviceWorker::ConnectToDevice(QString port, DWORD speed, BYTE address)
{	
	//open port
	bool chk = _sensor->OpenPort(port.toUtf8().constData(), speed);
	if(!chk)
		return chk;
	RF60xHELLOANSWER answer;
	//bind	
	_sensor->BindNetworkAddress(address);
	//get info
	chk = _sensor->HelloCmd(address, &answer);
	if(!chk)
	{
		_sensor->ClosePort();
		return chk;
	}
	_maxDistance = answer.wDeviceMaxDistance;
	_range = answer.wDeviceRange;
	_serial = answer.wDeviceSerial;	
	/*w->BaseDistance(QString::number(_maxDistance));
	w->Range(QString::number(_range));
	w->SerialNumber(QString::number(sn));*/
	//set info
	_isConnected = true;
	return true;
}

bool DeviceWorker::LockResult(BYTE address)
{
	if(!_sensor)
		return false;
	return _sensor->LockResult(address);
}

bool DeviceWorker::DisconnectFromDevice()
{
	if(!_sensor)
		return false;
	if(!_isConnected)
		return false;
	bool ret = _sensor->ClosePort();
	_isConnected = !ret;
	return ret;
}

bool DeviceWorker::ReceiveInfo(BYTE address)
{
	if(!_sensor)
		return false;
	RF60xHELLOANSWER answer;
	//_sensor->BindNetworkAddress(address);
	bool chk = _sensor->HelloCmd(address, &answer);
	if(!chk)
	{
		return chk;
	}
	_maxDistance = answer.wDeviceMaxDistance;
	_range = answer.wDeviceRange;
	_serial = answer.wDeviceSerial;	
}

bool DeviceWorker::ReceiveInfo()
{
	return ReceiveInfo(DevAddress());
}
