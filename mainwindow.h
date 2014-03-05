#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QQuickView>
#include <QSizePolicy>
#include <QQuickItem>
#include <QQmlProperty>
#include <QtQml>

#include <ComDeviceWorker.h>
#include <RFDevice.h>
#include <RF603Device.h>

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

private:
	//variables
	int current_column;
	int current_row;
	//members
	QQuickView * _view;
	QWidget *_container;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
