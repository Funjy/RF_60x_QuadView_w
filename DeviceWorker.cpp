#include "DeviceWorker.h"

QList<QString> DeviceWorker::OpenedPorts;
QMutex DeviceWorker::CheckOpenedPortsMutex;

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
		//DeviceWorker::CheckOpenedPortsMutex.lock();
		/*if(DeviceWorker::OpenedPorts.contains(str))
		{
			ql.append(str);			
		} else*/
		{
			if(_sensor->OpenPort(str.toUtf8().constData(), 2400))
			{
				//port opened may work with it
				ql.append(str);
			}
			_sensor->ClosePort();
		}
		//DeviceWorker::CheckOpenedPortsMutex.unlock();
	}
	delete _sensor;
	_sensor = 0;
	if(ql.length() < 1)
	{
		ql.append("Not found");
	}
	_comPorts = ql;
	emit ComPortsScanned();
}

void DeviceWorker::ReceiveNewValues()
{
	ReceiveNewValues(_devAddress);
}

void DeviceWorker::ReceiveNewValues(BYTE address)
{
	if(!_sensor)
		return;
	if(!_isConnected)
		return;
	_sensor->BindNetworkAddress(address);
	//float val = _sensor->GetSingleMeasure();
	USHORT measure = 0;
	_sensor->Measure(address, &measure);		
	float retVal = RecalcValue(measure, Range());
	emit NewValueReceived(retVal);
}

//bool DeviceWorker::ConnectToDevice(QString port, DWORD speed, BYTE address)
//{	
//	//open port
//	bool chk = _sensor->OpenPort(port.toUtf8().constData(), speed);
//	if(!chk)
//		return chk;
//	RF60xHELLOANSWER answer;
//	//bind	
//	_sensor->BindNetworkAddress(address);
//	//get info
//	chk = _sensor->HelloCmd(address, &answer);
//	if(!chk)
//	{
//		_sensor->ClosePort();
//		return chk;
//	}
//	_maxDistance = answer.wDeviceMaxDistance;
//	_range = answer.wDeviceRange;
//	_serial = answer.wDeviceSerial;	
//	/*w->BaseDistance(QString::number(_maxDistance));
//	w->Range(QString::number(_range));
//	w->SerialNumber(QString::number(sn));*/
//	//set info
//	_isConnected = true;
//	return true;
//}

bool DeviceWorker::LockResult(BYTE address)
{
	if(!_sensor)
		return false;
	return _sensor->LockResult(address);
}

//bool DeviceWorker::DisconnectFromDevice()
//{
//	if(!_sensor)
//		return false;
//	if(!_isConnected)
//		return false;
//	bool ret = _sensor->ClosePort();
//	_isConnected = !ret;
//	return ret;
//}

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
	return true;
}

bool DeviceWorker::ReceiveInfo()
{
	return ReceiveInfo(DevAddress());
}

float DeviceWorker::RecalcValue(USHORT value, USHORT range)
{
	float maxValue = 16383;
	float coef = range / maxValue;
	float toRet = coef * value;
	return toRet;
}
