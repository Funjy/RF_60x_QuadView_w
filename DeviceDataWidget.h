#ifndef DEVICEDATAWIDGET_H
#define DEVICEDATAWIDGET_H

#include <QWidget>
#include "ui_DeviceDataWidget.h"
#include <PlotWidget.h>

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

	QString	NetworkAddress() const {return ui.addressBox->text();}
	void	NetworkAddress(QString var) {ui.addressBox->setText(var);}

	QString	SerialNumber() const {return ui.snBox->text();}
	void	SerialNumber(QString var) {ui.snBox->setText(var);}

	QString	BaseDistance() const {return ui.baseDistBox->text();}
	void	BaseDistance(QString var) {ui.baseDistBox->setText(var);}

	QString	Range() const {return ui.rangeBox->text();}
	void	Range(QString var) {ui.rangeBox->setText(var);}


private:
	bool _onTop;	
	PlotWidget* _plot;
	Ui::DeviceDataWidget ui;
};

#endif // DEVICEDATAWIDGET_H
