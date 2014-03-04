#include "ComDeviceWorker.h"

DeviceWorker::DeviceWorker(QObject *parent)
	: QObject(parent)
{
	
	_sensor = new RF603Device();
}

DeviceWorker::~DeviceWorker()
{
	delete _sensor;
}

void DeviceWorker::FindActiveComPorts()
{
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
	_comPorts = ql;
}
