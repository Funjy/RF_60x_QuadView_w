#include "mainwindow.h"
#include "ui_mainwindow.h"



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
