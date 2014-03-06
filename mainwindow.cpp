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
	current_column	= 0;
	current_row		= 0;

	

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

	QQuickItem* root = _view->rootObject();
	QMetaObject::Connection con1 = connect(root, SIGNAL(deviceIdentificationRequested()), this, SLOT(IdentifyButtonPressed()));

	/*QStringList list;
	list.append("228");
	list.append("1337");
	bool chk = QQmlProperty::write(root, "comPortsModel", QVariant::fromValue(list));*/
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
	const int comPortIndex = 0;
	const int comSpeedIndex = 1;
	QVariant ret;	
	bool chk = QMetaObject::invokeMethod(_view->rootObject(), "getConnectParameters", Q_RETURN_ARG(QVariant, ret));		
	QStringList sl = ret.toStringList();
	if(_isConnected)
		_sensor->ClosePort();
	chk = _sensor->OpenPort(sl[comPortIndex].toUtf8().constData(), sl[comSpeedIndex].toULong());
	_isConnected = chk;
	if(!chk)
	{
		return;
	}

	DeviceDataWidget* dev;
	foreach(dev, _devWidgets)
	{
		dev->DevWorker()->Sensor(_sensor);
		chk = dev->DevWorker()->ReceiveInfo(dev->NetworkAddress().toUShort());
		if(!chk)
		{
			dev->SerialNumber("N/A");
			dev->BaseDistance("N/A");
			dev->Range("N/A");
			continue;
		}
		dev->SerialNumber(QString::number(dev->DevWorker()->Serial()));
		dev->BaseDistance(QString::number(dev->DevWorker()->MaxDistance()));
		dev->Range(QString::number(dev->DevWorker()->Range()));
		dev->DevWorker()->ReceiveNewValues();
	}


	/*DeviceDataWidget* dev;
	foreach(dev, _devWidgets)
	{
		bool chk = dev->DevWorker()->ConnectToDevice(sl[0], sl[1].toULong(), dev->NetworkAddress().toUShort());		
	}*/
}
