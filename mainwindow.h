#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QQuickView>
#include <QSizePolicy>
#include <QQuickItem>
#include <QQmlProperty>
#include <QtQml>

#include <RFDevice.h>
#include <RF603Device.h>

#include <PlotWidget.h>
#include <DeviceDataWidget.h>
#include <DeviceWorker.h>

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

	void AddWidgetToGrid(QWidget* widget);

public slots:
	void IdentifyButtonPressed();

private:
	//const
	const char* GET_CONNECT_PARAMETERS_FUNCTION;
	//variables
	int current_column;
	int current_row;
	bool _isConnected;	
	//members
	RF603Device * _sensor;
	QQuickView * _view;
	QWidget *_container;
	QList<DeviceDataWidget*> _devWidgets;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
