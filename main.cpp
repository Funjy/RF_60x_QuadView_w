#include "mainwindow.h"
#include <QApplication>
#include <QtQml>

//local
//#include <ComDeviceWorker.h>
//#include <RFDevice.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	

	//qmlRegisterType<ComDeviceWorker>("com.ComDeviceWorker.rf", 1, 0, "ComDeviceWorker");	

    MainWindow w;
    w.show();
    return a.exec();
}
