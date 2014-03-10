#ifndef COMDEVICEWORKER_H
#define COMDEVICEWORKER_H

#include <QObject>
#include <QStringList>
#include <QMutex>

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
	void setComPorts(QStringList val) { 
		_comPorts = val;
		emit ComPortsChanged();
	}

	RF603Device* Sensor() const { return _sensor; }
	void Sensor(RF603Device* val) { _sensor = val; }

	WORD MaxDistance() const { return _maxDistance; }
	//void MaxDistance(WORD val) { _maxDistance = val; }
	
	WORD Range() const { return _range; }
	//void Range(WORD val) { _range = val; }

	WORD Serial() const { return _serial; }
	//void Serial(WORD val) { _serial = val; }

	bool IsConnected() const { return _isConnected; }
	void IsConnected(bool val) { _isConnected = val; }

	BYTE DevAddress() const { return _devAddress; }
	void DevAddress(BYTE val) { _devAddress = val; }

	bool ConnectToDevice(QString port, DWORD speed, BYTE address);
	bool DisconnectFromDevice();

	bool ReceiveInfo(BYTE address);
	bool ReceiveInfo();
	void ReceiveNewValues(BYTE address);
	void ReceiveNewValues();

	bool LockResult(BYTE address);

	Q_INVOKABLE void findActiveComPorts();

	static QList<QString> OpenedPorts;
	static QMutex CheckOpenedPortsMutex;
	static float RecalcValue(USHORT value, USHORT range);

signals:
	void ComPortsChanged();
	void NewValueReceived(float newValue);
	void ComPortsScanned();

private:
	//variables
	WORD _maxDistance;	
	WORD _range;	
	WORD _serial;	
	bool _isConnected;	
	BYTE _devAddress;
	//members
	QStringList _comPorts;
	RF603Device* _sensor;
	
};

#endif // COMDEVICEWORKER_H
