#ifndef COMDEVICEWORKER_H
#define COMDEVICEWORKER_H

#include <QObject>
#include <QStringList>
#include <RFComDevice.h>
#include <RF603Device.h>

using namespace RFDevice;

class DeviceWorker : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QStringList ComPorts READ ComPorts WRITE setComPorts NOTIFY ComPortsChanged)
	

public:
	DeviceWorker(QObject *parent = NULL);
	~DeviceWorker();

	QStringList ComPorts() const { return _comPorts; }
	void setComPorts(QStringList val) { _comPorts = val; }

	Q_INVOKABLE void FindActiveComPorts();

signals:
	void ComPortsChanged();

private:
	QStringList _comPorts;
	RF603Device* _sensor;

};

#endif // COMDEVICEWORKER_H
