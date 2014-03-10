#include "mainwindow.h"
#include "ui_mainwindow.h"

const char* GET_CONNECT_PARAMETERS_FUNCTION = "getConnectParameters";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	qmlRegisterType<DeviceWorker>("com.ComDeviceWorker.rf", 1, 0, "ComDeviceWorker");
	
	RFDevice::Initialize();

	//QML container
    _view = new QQuickView();
    _container = QWidget::createWindowContainer(_view, this);
    _container->setMinimumSize(180, 60);
    _container->setMaximumSize(400, 1080);
    _container->setFocusPolicy(Qt::TabFocus);
	_container->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    _view->setSource(QUrl("main.qml"));
	_view->setResizeMode(QQuickView::SizeRootObjectToView);	
	ui->ParametersLayout->addWidget(_container);

	_sensor = new RF603Device();
	_isConnected = false;
	_isStreaming = false;
	current_column	= 0;
	current_row		= 0;
	_connectedDevices = 0;

	_statusLabel = new QLabel(this);
	_statusLabel->setMargin(4);
	_statusLabel->setText(READY_STATUS);
	ui->statusBar->addWidget(_statusLabel);

	DeviceDataWidget* ddw = new DeviceDataWidget();
	ddw->NetworkAddress("1");
	PlotWidget* pw = new PlotWidget();
	pw->SetShowLegend(false);
	ddw->SetPlotWidget(pw);
	DeviceWorker* dw = new DeviceWorker();
	ddw->DevWorker(dw);
	ui->graphsLayout->addWidget(ddw);
	_devWidgets.append(ddw);
	//////////////////////////////////////////////////////////////////////////
	DeviceDataWidget* ddw1 = new DeviceDataWidget();
	ddw1->NetworkAddress("2");
	PlotWidget* pw1 = new PlotWidget();
	pw1->SetShowLegend(false);
	ddw1->SetPlotWidget(pw1, true);
	DeviceWorker* dw1 = new DeviceWorker();
	ddw1->DevWorker(dw1);
	ui->graphsLayout->addWidget(ddw1);
	_devWidgets.append(ddw1);
	//////////////////////////////////////////////////////////////////////////

	QQuickItem* root = _view->rootObject();
	QMetaObject::Connection con1 = connect(root, SIGNAL(deviceIdentificationRequested()), this, SLOT(IdentifyButtonPressed()));
	QMetaObject::Connection con2 = connect(root, SIGNAL(scanPortsRequested()), this, SLOT(Reconnect()));
	QMetaObject::Connection con3 = connect(root, SIGNAL(beforeScanPortsRequested()), this, SLOT(BeforeScanRequested()));
	connect(root, SIGNAL(streamButtonClicked()), this, SLOT(onStreamButtonPressed()));
	connect(this, &MainWindow::StatusChanged, this, &MainWindow::SetStatus);
	connect(this, &MainWindow::IdentificationCompleteSignal, this, &MainWindow::IdentificationComplete);
	connect(&_streamTimer, &QTimer::timeout, this, &MainWindow::onTimerTick);

	_appDir = QCoreApplication::applicationDirPath();
	_iniFilePath = _appDir + "\\file.ini";
	ReadParametersFromFile();
}

MainWindow::~MainWindow()
{
	//delete _view;
	RFDevice::Cleanup();
	delete _container;
    delete ui;
}

void MainWindow::AddWidgetToGrid(QWidget* widget)
{
	const int maxRows = 2;
	
	if(current_row == maxRows - 1)
	{
		current_row = 0;
		current_column++;
	}
	else
	{
		current_row++;
	}

}

void MainWindow::IdentifyButtonPressed()
{	
	QVariant par;
	bool locked = _identifyMutex.tryLock();
	if(!locked)
		return;
	if(_connectedDevices > 0)
	{
		//Disconnecting
		StopStreaming();
		_sensor->ClosePort();
		_isConnected = false;
		_connectedDevices = 0;
		SwitchConnectedStatus(false);
		SetInfos();
		SwitchNetworkAdressBoxexState(true);
		par = QVariant::fromValue(false);
		QMetaObject::invokeMethod(_view->rootObject(), CONNECT_BUTTON_CONNECTED_QML_FUNCTION, Q_ARG(QVariant, par));
		QMetaObject::invokeMethod(_view->rootObject(), STREAM_BUTTON_IsSTREAMING_QML_FUNCTION, Q_ARG(QVariant, par));
		QMetaObject::invokeMethod(_view->rootObject(), STREAM_BUTTON_ENABLED_QML_FUNCTION, Q_ARG(QVariant, par));	
		//QMetaObject::invokeMethod(_view->rootObject(), "parametersInterfaceIsEnabled", Q_ARG(QVariant, true));
		_identifyMutex.unlock();
	}
	else
	{
		//Connecting		
		par = QVariant::fromValue(false);
		//QMetaObject::invokeMethod(_view->rootObject(), "parametersInterfaceIsEnabled", Q_ARG(QVariant, par));
		/*QVariant ret;
		bool chk = QMetaObject::invokeMethod(_view->rootObject(), GET_CONNECT_PARAMETERS_QML_FUNCTION, Q_RETURN_ARG(QVariant, ret));
		if(!chk)
			return;
		QStringList sl = ret.toStringList();*/
		WriteParametersToFile();
		ReadUiParameters();
		QFuture<void> future = QtConcurrent::run(this, &MainWindow::IdentifyDevices, _uiParameters);
		SwitchNetworkAdressBoxexState(false);
		par = QVariant::fromValue(true);
		QMetaObject::invokeMethod(_view->rootObject(), CONNECT_BUTTON_CONNECTED_QML_FUNCTION, Q_ARG(QVariant, par));
		QMetaObject::invokeMethod(_view->rootObject(), CONNECT_BUTTON_ENABLED_QML_FUNCTION, Q_ARG(QVariant, false));
	}
}

void MainWindow::IdentificationComplete()
{
	bool chk = false;
	SetInfos();
	bool enabled = _connectedDevices > 0;
	QVariant par = enabled;
	chk = QMetaObject::invokeMethod(_view->rootObject(), STREAM_BUTTON_ENABLED_QML_FUNCTION, Q_ARG(QVariant, par));
	QMetaObject::invokeMethod(_view->rootObject(), CONNECT_BUTTON_ENABLED_QML_FUNCTION, Q_ARG(QVariant, true));
	emit StatusChanged(READY_STATUS);
	_identifyMutex.unlock();
	if(!enabled)
	{
		_connectedDevices = 1;
		IdentifyButtonPressed();
	}
}

void MainWindow::Reconnect()
{	
	_sensor = new RF603Device();
	bool retry;
	retry = _isConnected;
	_isConnected = false;
	if(retry)
		IdentifyButtonPressed();	
}

void MainWindow::BeforeScanRequested()
{
	if(!_sensor)
		return;
	bool chk = false;
	if(_isConnected)
		chk = _sensor->ClosePort();
	delete _sensor;
	_sensor = 0;
}

void MainWindow::IdentifyDevices(QStringList sl)
{
	emit StatusChanged(IDENTIFY_STATUS);	
	bool chk = false;
	if(_isConnected)
	{
		_sensor->ClosePort();
	}
	chk = _sensor->OpenPort(sl[INDEX_COM_NUMBER].toUtf8().constData(), sl[INDEX_COM_SPEED].toULong());
	_isConnected = chk;
	if(!chk)
	{
		_lastOpenedPort = "";
		_connectedDevices = 0;
		DeviceDataWidget* dev;
		foreach(dev, _devWidgets)
		{
			dev->DevWorker()->IsConnected(false);
		}
		return;
	}
	_lastOpenedPort = sl[INDEX_COM_NUMBER];

	int found = 0;

	DeviceDataWidget* dev;
	foreach(dev, _devWidgets)
	{
		dev->DevWorker()->Sensor(_sensor);
		chk = dev->DevWorker()->ReceiveInfo(dev->NetworkAddress().toUShort());
		dev->DevWorker()->IsConnected(chk);
		dev->DevWorker()->DevAddress(dev->NetworkAddress().toUShort());
		found += chk ? 1 : 0;
	}
	_connectedDevices = found;
	emit IdentificationCompleteSignal();
}

void MainWindow::onStreamButtonPressed()
{
	if(!_isStreaming)
	{
		//Start stream
		if(!_isConnected)
		{
			QMessageBox::warning(this, "Warning", "No devices identified.");
			return;
		}

		ReadUiParameters();
		if(_uiParameters[INDEX_INTERVAL].compare("") == 0)
		{
			QMessageBox::warning(this, "Warning", "Period not set.");
			return;
		}
		QString timeout = _uiParameters[INDEX_INTERVAL];
		_streamTimer.setInterval(timeout.toInt());
		_streamTimer.setSingleShot(true);
		ClearGraphs();
		emit StatusChanged(STREAMING_STATUS);
		UpdateMeasures();
		QVariant par = QVariant::fromValue(false);
		par = QVariant::fromValue(true);
		QMetaObject::invokeMethod(_view->rootObject(), STREAM_BUTTON_IsSTREAMING_QML_FUNCTION, Q_ARG(QVariant, par));
		_isStreaming = true;
	}
	else
	{
		//Stop stream
		StopStreaming();
	}
}

void MainWindow::UpdateMeasures()
{
	_streamMutex.lock();

	_sensor->LockResult(0);	

	DeviceDataWidget* dev;
	foreach (dev, _devWidgets)
	{
		dev->DevWorker()->ReceiveNewValues();
	}

	_streamMutex.unlock();

	_streamTimer.start();

}

void MainWindow::onTimerTick()
{
	UpdateMeasures();
}

bool MainWindow::ReadUiParameters()
{
	QVariant ret;
	bool chk = QMetaObject::invokeMethod(_view->rootObject(), GET_CONNECT_PARAMETERS_QML_FUNCTION, Q_RETURN_ARG(QVariant, ret));
	if(!chk)
		return chk;
	QStringList sl = ret.toStringList();
	_uiParameters = sl;
	return chk;
}

void MainWindow::ClearGraphs()
{
	DeviceDataWidget* dev;
	foreach (dev, _devWidgets)
	{
		dev->ClearPlot();
	}
}

void MainWindow::StopStreaming()
{
	if(!_isStreaming)
		return;
	_streamTimer.stop();
	_streamMutex.lock();
	_streamMutex.unlock();
	QVariant par = QVariant::fromValue(true);
	//QMetaObject::invokeMethod(_view->rootObject(), "parametersInterfaceIsEnabled", Q_ARG(QVariant, par));
	par = QVariant::fromValue(false);
	QMetaObject::invokeMethod(_view->rootObject(), STREAM_BUTTON_IsSTREAMING_QML_FUNCTION, Q_ARG(QVariant, par));
	emit StatusChanged(READY_STATUS);
	_isStreaming = false;
}

void MainWindow::SwitchNetworkAdressBoxexState(bool enabled)
{
	DeviceDataWidget* dev;
	foreach (dev, _devWidgets)
	{
		dev->IsNetworkAddressEnabled(enabled);
	}
}

void MainWindow::SwitchConnectedStatus(bool connected)
{
	DeviceDataWidget* dev;
	foreach (dev, _devWidgets)
	{
		dev->DevWorker()->IsConnected(connected);
	}
}

void MainWindow::SetInfos()
{
	DeviceDataWidget* dev;
	foreach(dev, _devWidgets)
	{
		bool chk = dev->DevWorker()->IsConnected();
		if(!chk)
		{
			dev->SerialNumber("N/A");
			dev->BaseDistance("N/A");
			dev->Range("N/A");
			dev->ConnectionStatus(false);
			continue;
		}
		dev->SerialNumber(QString::number(dev->DevWorker()->Serial()));
		dev->BaseDistance(QString::number(dev->DevWorker()->MaxDistance()));
		dev->Range(QString::number(dev->DevWorker()->Range()));
		//dev->DevWorker()->ReceiveNewValues();
		dev->ConnectionStatus(true);
	}
}

void MainWindow::ReadParametersFromFile()
{
	QStringList paramsList;
	bool chk;
	chk = _fileWorker.OpenINIFile(_iniFilePath);
	if(!chk)
		return;	
	QString val;
	chk = _fileWorker.ReadINIValue(COM_NUMBER_KEY, &val);
	if(chk)
		paramsList.append(val);
	chk = _fileWorker.ReadINIValue(COM_SPEED_KEY, &val);
	if(chk)
		paramsList.append(val);
	chk = _fileWorker.ReadINIValue(STREAM_INTERVAL_KEY, &val);
	if(chk)
		paramsList.append(val);
	chk = _fileWorker.ReadINIValue(DUMP_FILE_KEY, &val);
	if(chk)
		paramsList.append(val);
	_fileWorker.CloseFile();
	QVariant toSend = QVariant::fromValue(paramsList);
	chk = QMetaObject::invokeMethod(_view->rootObject(), "setConnectParameters", Q_ARG(QVariant, toSend));	
}

void MainWindow::WriteParametersToFile()
{
	bool chk;
	chk = _fileWorker.OpenINIFile(_iniFilePath);
	if(!chk)
		return;
	ReadUiParameters();
	chk = _fileWorker.WriteINILine(COM_NUMBER_KEY, _uiParameters[INDEX_COM_NUMBER]);
	chk = _fileWorker.WriteINILine(COM_SPEED_KEY, _uiParameters[INDEX_COM_SPEED]);
	chk = _fileWorker.WriteINILine(STREAM_INTERVAL_KEY, _uiParameters[INDEX_INTERVAL]);
	chk = _fileWorker.WriteINILine(DUMP_FILE_KEY, _uiParameters[INDEX_DUMP_FILENAME]);
	_fileWorker.CloseFile();	
}