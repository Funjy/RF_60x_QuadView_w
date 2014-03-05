#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <PlotWidget.h>
#include <DeviceDataWidget.h>

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

	current_column	= 0;
	current_row		= 0;

	DeviceDataWidget* ddw = new DeviceDataWidget();
	PlotWidget* pw = new PlotWidget();
	ddw->SetPlotWidget(pw);
	ui->graphsLayout->addWidget(ddw);

	DeviceDataWidget* ddw1 = new DeviceDataWidget();
	PlotWidget* pw1 = new PlotWidget();
	ddw1->SetPlotWidget(pw1, true);
	ui->graphsLayout->addWidget(ddw1);

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
