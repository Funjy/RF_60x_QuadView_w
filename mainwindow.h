#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QQuickView>
#include <QSizePolicy>
//#include <QQuickItem>
//#include <QQmlProperty>
//#include <QtQml>
#include <QtConcurrent/QtConcurrent>
#include <QMessageBox>
#include <QTimer>

#include <RFDevice.h>
#include <RF603Device.h>

#include <PlotWidget.h>
#include <DeviceDataWidget.h>
#include <DeviceWorker.h>
#include <TextFileWorker.h>

//QML functions
#define STREAM_BUTTON_IsSTREAMING_QML_FUNCTION "setStreamButtonState"
#define STREAM_BUTTON_ENABLED_QML_FUNCTION "setStreamButtonEnabled"
#define CONNECT_BUTTON_CONNECTED_QML_FUNCTION "setConnectButtonState"
#define CONNECT_BUTTON_ENABLED_QML_FUNCTION "setConnectButtonEnabled"
#define GET_CONNECT_PARAMETERS_QML_FUNCTION "getConnectParameters"

//Status list
#define READY_STATUS "Ready"
#define IDENTIFY_STATUS "Identification..."
#define STREAMING_STATUS "Streaming"

#define IDENTIFY_BUTTON_CONNECTED "Disconnect"
#define IDENTIFY_BUTTON_NOT_CONNECTED "Device identification"

#define STREAM_BUTTON_STREAMING "Stop stream"
#define STREAM_BUTTON_NOT_STREAMING "Start stream"

//..
#define CONNECTED_STATUS "Connected"
#define NOT_CONNECTED_STATUS "Not connected"

//Ui parameters indexes in _uiParameters
#define INDEX_COM_NUMBER 0
#define INDEX_COM_SPEED 1
#define INDEX_INTERVAL 2
#define INDEX_DUMP_FILENAME 3

//Ui parameters keys in ini file
#define COM_NUMBER_KEY "Com_port_number"
#define COM_SPEED_KEY "Com_speed"
#define STREAM_INTERVAL_KEY "Stream_Interval"
#define DUMP_FILE_KEY "Dump_File_Name"
#define NETWORK_ADDRESS_KEY_PREFFIX "Network_Address_"

using namespace RFDevice;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	
	void ReadParametersFromFile();
	//called on identify
	void WriteParametersToFile();

	//not implemented
	void AddWidgetToGrid();

	//read parameters from left column of main window (qml part of GUI). Indexes of parameters in define block. Parameters container: "_uiParameters" variable.
	bool ReadUiParameters();	
	void IdentifyDevices(QStringList sl);
	void ClearGraphs();
	//Called on every timer tick and timer restarts here
	void UpdateMeasures();
	void StopStreaming();
	//Next to plot address box state
	void SwitchConnectBoxexState(bool enabled);
	//Next to plot status
	void SwitchConnectedStatus(bool connected);
	//Set info if device connected ("N/A" if not connected)
	void SetInfos();

	void SwitchConnectState(bool state);
	void SwitchStreamState(bool state);

signals:
	void StatusChanged(QString status);
	void IdentificationCompleteSignal();
	void StreamPeriodCompleteSignal(QStringList valuesList);

public slots:
	//Before identification
	void IdentifyButtonPressed();
	//on Identification complete
	void IdentificationComplete();
	void BeforeScanRequested();	
	//used after ports scanning
	void Reconnect();
	void onStreamButtonPressed();

	void SetStatus(QString status)
	{
		_statusLabel->setText(status);
	}
	void onTimerTick();

	void onStreamPeriodComplete(QStringList valuesList);

	void onPortsScanned();

private:
	//const
	const char* GET_CONNECT_PARAMETERS_FUNCTION;	
	//variables
	int current_column;
	int current_row;
	bool _isConnected;
	bool _isStreaming;
	int _connectedDevices;
	QString _lastOpenedPort;
	QString _appDir;
	QString _iniFilePath;
	QMutex _identifyMutex;
	QMutex _streamMutex;
	QTimer _streamTimer;
	QStringList _uiParameters;
	//members
	TextFileWorker _iniParametersWorker;
	TextFileWorker _streamSaver;
	DeviceWorker _aloneDevWorker;
	RF603Device * _sensor;
	//QQuickView * _view;
	//QWidget *_container;
	QLabel* _statusLabel;
	QList<DeviceDataWidget*> _devWidgets;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
