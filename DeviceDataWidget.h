#ifndef DEVICEDATAWIDGET_H
#define DEVICEDATAWIDGET_H

#define CONNECTED_STATUS "Connected"
#define NOT_CONNECTED_STATUS "Not connected"

#include <QWidget>
#include "ui_DeviceDataWidget.h"
#include <PlotWidget.h>
#include <DeviceWorker.h>

class DeviceDataWidget : public QWidget
{
	Q_OBJECT

public:
	DeviceDataWidget(QWidget *parent = 0);
	~DeviceDataWidget();

	bool OnTop() const { return _onTop; }
	void OnTop(bool val) { _onTop = val; }

	void SetPlotWidget(PlotWidget* widget, bool top);
	void SetPlotWidget(PlotWidget* widget);
	PlotWidget* GetPlotWidget() const { return _plot; }

	DeviceWorker* DevWorker() const { return _devWorker; }
	void DevWorker(DeviceWorker* val) { 
		QMetaObject::Connection con = connect(val, &DeviceWorker::NewValueReceived, this, &DeviceDataWidget::onNewPlotValue);
		_devWorker = val; 
	}

	/*QString ConnectionStatus() const {return ui.statusBox->text();}
	void	ConnectionStatus(QString var) {ui.statusBox->setText(var);}*/

	bool ConnectionStatus() const {
			return ui.statusBox->text().compare(CONNECTED_STATUS) == 0;		
	}
	void	ConnectionStatus(bool var) {
		if(var)
		{
			ui.statusBox->setText(CONNECTED_STATUS);
			ui.statusBox->setStyleSheet("QLabel { color : green; }");			
		}
		else
		{
			ui.statusBox->setText(NOT_CONNECTED_STATUS);
			ui.statusBox->setStyleSheet("QLabel { color : red; }");
		}
		
	}

	QString	NetworkAddress() const {return ui.addressBox->text();}
	void	NetworkAddress(QString var) {ui.addressBox->setText(var);}

	bool	IsNetworkAddressEnabled() const {return ui.addressBox->isEnabled();}
	void	IsNetworkAddressEnabled(bool var) {ui.addressBox->setEnabled(var);}

	QString	SerialNumber() const {return ui.snBox->text();}
	void	SerialNumber(QString var) {ui.snBox->setText(var);}

	QString	BaseDistance() const {return ui.baseDistBox->text();}
	void	BaseDistance(QString var) {ui.baseDistBox->setText(var);}

	QString	Range() const {return ui.rangeBox->text();}
	void	Range(QString var) {ui.rangeBox->setText(var);}

	void ClearPlot();

public slots:
	void onNewPlotValue(float value);

private:
	bool _onTop;
	QString _plotTitle;
	PlotWidget* _plot;
	DeviceWorker* _devWorker;	
	Ui::DeviceDataWidget ui;
};

#endif // DEVICEDATAWIDGET_H
