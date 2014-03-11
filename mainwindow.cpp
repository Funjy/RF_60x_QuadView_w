#include "mainwindow.h"
#include "ui_mainwindow.h"

const char* GET_CONNECT_PARAMETERS_FUNCTION = "getConnectParameters";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	//qmlRegisterType<DeviceWorker>("com.ComDeviceWorker.rf", 1, 0, "ComDeviceWorker");

	_appDir = QCoreApplication::applicationDirPath();
	RFDevice::Initialize();

	//QML container
	/*_view = new QQuickView();
	_container = QWidget::createWindowContainer(_view, this);
	_container->setMinimumSize(160, 60);
	_container->setMaximumSize(380, 1600);
	_container->setFocusPolicy(Qt::TabFocus);
	_container->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);*/
	//_view->setSource(QUrl::fromLocalFile("main.qml"));
	/*_view->setResizeMode(QQuickView::SizeRootObjectToView);	
	ui->ParametersLayout->addWidget(_container);*/
	//////////////////////////////////////////////////////////////////////////
//	QUrl url(_appDir + "/main.qml");
//    _view->setSource(QUrl(_appDir + "\\main.qml"));
	/*QUrl qu = QUrl::fromLocalFile("main.qml");
	QString str = qu.toString();
	str = qu.path();
	str = qu.fileName();*/
	
	//QFile file(":/new/prefix1/main.qml");	
	//qint64 s = file.size();
    //_view->setSource(QUrl("qrc:/new/prefix1/main.qml"));

	

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
	QStringList speeds;
	speeds.append("9600");
	speeds.append("115200");
	speeds.append("230400");
	speeds.append("460800");
	speeds.append("921600");
	ui->comSpeedBox->addItems(speeds);	
	ui->streamButton->setEnabled(false);
	//DeviceDataWidget* ddw = new DeviceDataWidget();
	//ddw->NetworkAddress("1");
	//PlotWidget* pw = new PlotWidget();
	//pw->SetShowLegend(false);
	//ddw->SetPlotWidget(pw);
	//DeviceWorker* dw = new DeviceWorker();
	//ddw->DevWorker(dw);
	//ui->graphsLayout->addWidget(ddw);
	//_devWidgets.append(ddw);
	////////////////////////////////////////////////////////////////////////////
	//DeviceDataWidget* ddw1 = new DeviceDataWidget();
	//ddw1->NetworkAddress("2");
	//PlotWidget* pw1 = new PlotWidget();
	//pw1->SetShowLegend(false);
	//ddw1->SetPlotWidget(pw1, true);
	//DeviceWorker* dw1 = new DeviceWorker();
	//ddw1->DevWorker(dw1);
	//ui->graphsLayout->addWidget(ddw1);
	//_devWidgets.append(ddw1);
	//////////////////////////////////////////////////////////////////////////
	AddWidgetToGrid();
	AddWidgetToGrid();
	AddWidgetToGrid();
	AddWidgetToGrid();

	//QQuickItem* root = _view->rootObject();

	/*QMetaObject::Connection con2 = connect(root, SIGNAL(scanPortsRequested()), this, SLOT(Reconnect()));
	QMetaObject::Connection con3 = connect(root, SIGNAL(beforeScanPortsRequested()), this, SLOT(BeforeScanRequested()));
	QMetaObject::Connection con1 = connect(root, SIGNAL(deviceIdentificationRequested()), this, SLOT(IdentifyButtonPressed()));
	connect(root, SIGNAL(streamButtonClicked()), this, SLOT(onStreamButtonPressed()));*/
	QMetaObject::Connection con1 = connect(ui->scanPortsButton, &QPushButton::clicked, this, &MainWindow::BeforeScanRequested);
	QMetaObject::Connection con2 = connect(&_aloneDevWorker, &DeviceWorker::ComPortsScanned, this, &MainWindow::onPortsScanned);
	QMetaObject::Connection con3 = connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(IdentifyButtonPressed()));
	QMetaObject::Connection con4 = connect(ui->streamButton, &QPushButton::clicked, this, &MainWindow::onStreamButtonPressed);

	connect(this, &MainWindow::StatusChanged, this, &MainWindow::SetStatus);
	connect(this, &MainWindow::IdentificationCompleteSignal, this, &MainWindow::IdentificationComplete);
	connect(this, &MainWindow::StreamPeriodCompleteSignal, this, &MainWindow::onStreamPeriodComplete);
	connect(&_streamTimer, &QTimer::timeout, this, &MainWindow::onTimerTick);

	
	_iniFilePath = _appDir + "\\file.ini";
	ReadParametersFromFile();
}

MainWindow::~MainWindow()
{
	//delete _view;
	_sensor->ClosePort();
	delete _sensor;
	RFDevice::Cleanup();
	//delete _container;
    delete ui;
}

void MainWindow::AddWidgetToGrid()
{
	const int maxRows = 2;
	//const int widgetsCount = 4;
	
	DeviceDataWidget* ddw = new DeviceDataWidget();
	//ddw->NetworkAddress(QString::number(i));
	PlotWidget* pw = new PlotWidget();
	pw->SetShowLegend(false);
	bool onTop = current_row == maxRows - 1;
	ddw->SetPlotWidget(pw, onTop);
	DeviceWorker* dw = new DeviceWorker();
	ddw->DevWorker(dw);
	ui->graphsLayout->addWidget(ddw, current_row, current_column);
	_devWidgets.append(ddw);

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
		SwitchConnectBoxexState(true);
		par = QVariant::fromValue(false);
		/*QMetaObject::invokeMethod(_view->rootObject(), CONNECT_BUTTON_CONNECTED_QML_FUNCTION, Q_ARG(QVariant, par));
		QMetaObject::invokeMethod(_view->rootObject(), STREAM_BUTTON_IsSTREAMING_QML_FUNCTION, Q_ARG(QVariant, par));
		QMetaObject::invokeMethod(_view->rootObject(), STREAM_BUTTON_ENABLED_QML_FUNCTION, Q_ARG(QVariant, par));	*/
		ui->connectButton->setEnabled(true);
		SwitchConnectState(false);
		_identifyMutex.unlock();
	}
	else
	{
		//Connecting		
		par = QVariant::fromValue(false);
		WriteParametersToFile();
		ReadUiParameters();
		QFuture<void> future = QtConcurrent::run(this, &MainWindow::IdentifyDevices, _uiParameters);
		SwitchConnectBoxexState(false);
		par = QVariant::fromValue(true);
		/*QMetaObject::invokeMethod(_view->rootObject(), CONNECT_BUTTON_CONNECTED_QML_FUNCTION, Q_ARG(QVariant, par));
		QMetaObject::invokeMethod(_view->rootObject(), CONNECT_BUTTON_ENABLED_QML_FUNCTION, Q_ARG(QVariant, false));*/
		ui->connectButton->setEnabled(false);
		//SwitchConnectState(true);
	}
}

void MainWindow::IdentificationComplete()
{
	bool chk = false;
	SetInfos();
	bool enabled = _connectedDevices > 0;
	//QVariant par = enabled;
	/*chk = QMetaObject::invokeMethod(_view->rootObject(), STREAM_BUTTON_ENABLED_QML_FUNCTION, Q_ARG(QVariant, par));
	QMetaObject::invokeMethod(_view->rootObject(), CONNECT_BUTTON_ENABLED_QML_FUNCTION, Q_ARG(QVariant, true));*/
	ui->connectButton->setEnabled(true);
	//ui->streamButton->setEnabled(enabled);
	SwitchConnectState(enabled);
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
	_aloneDevWorker.findActiveComPorts();
	//Reconnect();
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
		if(_uiParameters[INDEX_DUMP_FILENAME].compare("") != 0)
		{
			_streamSaver.OpenFile(_appDir + "\\" + _uiParameters[INDEX_DUMP_FILENAME]);
		}
		QString timeout = _uiParameters[INDEX_INTERVAL];
		WriteParametersToFile();
		_streamTimer.setInterval(timeout.toInt());
		_streamTimer.setSingleShot(true);
		ClearGraphs();
		emit StatusChanged(STREAMING_STATUS);
		UpdateMeasures();
		QVariant par = QVariant::fromValue(false);
		//par = QVariant::fromValue(true);
		//QMetaObject::invokeMethod(_view->rootObject(), STREAM_BUTTON_IsSTREAMING_QML_FUNCTION, Q_ARG(QVariant, par));
		SwitchStreamState(true);
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
	QStringList vals;
	DeviceDataWidget* dev;
	foreach (dev, _devWidgets)
	{
		float val = dev->DevWorker()->ReceiveNewValues();
		vals.append(QString::number(val));
	}
	//_streamSaver.WriteCSVLine(vals);
	emit StreamPeriodCompleteSignal(vals);
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
	//bool chk = QMetaObject::invokeMethod(_view->rootObject(), GET_CONNECT_PARAMETERS_QML_FUNCTION, Q_RETURN_ARG(QVariant, ret));
	/*if(!chk)
		return chk;*/
	bool chk = true;
	QStringList sl;
	sl.append(ui->comPortsBox->currentText());
	sl.append(ui->comSpeedBox->currentText());
	sl.append(ui->periodBox->text());
	sl.append(ui->dumpFileBox->text());
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
	_streamSaver.CloseFile();
	QVariant par = QVariant::fromValue(true);	
	//par = QVariant::fromValue(false);
	//QMetaObject::invokeMethod(_view->rootObject(), STREAM_BUTTON_IsSTREAMING_QML_FUNCTION, Q_ARG(QVariant, par));
	SwitchStreamState(false);
	emit StatusChanged(READY_STATUS);
	_isStreaming = false;
}

void MainWindow::SwitchConnectBoxexState(bool enabled)
{
	ui->scanPortsButton->setEnabled(enabled);
	ui->comPortsBox->setEnabled(enabled);
	ui->comSpeedBox->setEnabled(enabled);
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
	//QStringList paramsList;
	bool chk;
	chk = _iniParametersWorker.OpenINIFile(_iniFilePath);
	if(!chk)
		return;	
	QString val;
	chk = _iniParametersWorker.ReadINIValue(COM_NUMBER_KEY, &val);
	if(chk)
	{
		QStringList l;
		l.append(val);
		ui->comPortsBox->addItems(l);
		ui->comPortsBox->setCurrentIndex(0);
		//paramsList.append(val);
	}
	chk = _iniParametersWorker.ReadINIValue(COM_SPEED_KEY, &val);
	if(chk)
	{
		int ind = ui->comSpeedBox->findText(val);
		if(ind != -1)
			ui->comSpeedBox->setCurrentIndex(ind);
		//paramsList.append(val);
	}
	chk = _iniParametersWorker.ReadINIValue(STREAM_INTERVAL_KEY, &val);
	if(chk)
	{
		ui->periodBox->setText(val);
		//paramsList.append(val);
	}
	chk = _iniParametersWorker.ReadINIValue(DUMP_FILE_KEY, &val);
	if(chk)
	{
		ui->dumpFileBox->setText(val);
		//paramsList.append(val);
	}
	
	//QVariant toSend = QVariant::fromValue(paramsList);
	//chk = QMetaObject::invokeMethod(_view->rootObject(), "setConnectParameters", Q_ARG(QVariant, toSend));	

	int i = 0;
	DeviceDataWidget* dev;
	foreach(dev, _devWidgets)
	{
		chk = _iniParametersWorker.ReadINIValue(NETWORK_ADDRESS_KEY_PREFFIX + QString::number(i++), &val);
		if(chk)
			dev->NetworkAddress(val);
	}

	_iniParametersWorker.CloseFile();
}

void MainWindow::WriteParametersToFile()
{
	bool chk;
	chk = _iniParametersWorker.OpenINIFile(_iniFilePath);
	if(!chk)
		return;
	ReadUiParameters();
	chk = _iniParametersWorker.WriteINILine(COM_NUMBER_KEY, _uiParameters[INDEX_COM_NUMBER]);
	chk = _iniParametersWorker.WriteINILine(COM_SPEED_KEY, _uiParameters[INDEX_COM_SPEED]);
	chk = _iniParametersWorker.WriteINILine(STREAM_INTERVAL_KEY, _uiParameters[INDEX_INTERVAL]);
	chk = _iniParametersWorker.WriteINILine(DUMP_FILE_KEY, _uiParameters[INDEX_DUMP_FILENAME]);
	int i = 0;
	DeviceDataWidget* dev;
	foreach(dev, _devWidgets)
	{
		_iniParametersWorker.WriteINILine(NETWORK_ADDRESS_KEY_PREFFIX + QString::number(i++), dev->NetworkAddress());
	}
	_iniParametersWorker.CloseFile();
}

void MainWindow::onStreamPeriodComplete(QStringList valuesList)
{
	_streamSaver.WriteCSVLine(valuesList);
}

void MainWindow::onPortsScanned()
{
	QStringList ports = _aloneDevWorker.ComPorts();
	ui->comPortsBox->clear();
	ui->comPortsBox->addItems(ports);	
	Reconnect();
}

void MainWindow::SwitchConnectState(bool state)
{
	if(state)
	{
		ui->connectButton->setText(IDENTIFY_BUTTON_CONNECTED);
		ui->streamButton->setEnabled(true);
		//SwitchConnectBoxexState(false);
	}
	else
	{
		ui->connectButton->setText(IDENTIFY_BUTTON_NOT_CONNECTED);
		ui->streamButton->setEnabled(false);
		//SwitchConnectBoxexState(true);
	}
}

void MainWindow::SwitchStreamState(bool state)
{
	if(state)
	{
		ui->connectButton->setEnabled(false);
		ui->streamButton->setText(STREAM_BUTTON_STREAMING);
	}
	else
	{
		ui->connectButton->setEnabled(true);
		ui->streamButton->setText(STREAM_BUTTON_NOT_STREAMING);
	}
}
