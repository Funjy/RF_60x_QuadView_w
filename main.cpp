#include "mainwindow.h"
#include <QApplication>
#include <QtQml>
#include <QDesktopWidget>
#include <QDir>
#include <QLibraryInfo>
#include <QMessageBox>
//local
//#include <ComDeviceWorker.h>
//#include <RFDevice.h>

void setCenterOfApplication(QWidget* widget);

int main(int argc, char *argv[])
{	
	QString path = QDir::current().absolutePath();
	QStringList paths = QCoreApplication::libraryPaths();		
	//paths[0] = path + "/plugins";
	//paths.removeAt(0);
	paths.append(".");
	paths.append(path + "/plugins");
	paths.append(path + "/platforms");
	QCoreApplication::setLibraryPaths(paths);
    QApplication a(argc, argv);		
	//list.append(".");		
	/*QStringList list = a.libraryPaths();
	QMessageBox::information(NULL, "", list[0] + "\r\n" + list[1] + "\r\n" + list[2]);*/
    MainWindow w;
    w.show();
	setCenterOfApplication(&w);
    return a.exec();
}

void setCenterOfApplication(QWidget* widget)
{
	QSize size = widget->sizeHint();
	QDesktopWidget* desktop = QApplication::desktop();
	int width = desktop->width();
	int height = desktop->height();
	int mw = size.width();
	int mh = size.height();
	int centerW = (width/2) - (mw/2);
	int centerH = (height/2) - (mh/2);
	widget->move(centerW, centerH);
}