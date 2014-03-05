#include "DeviceDataWidget.h"

DeviceDataWidget::DeviceDataWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	OnTop(false);
	_plot = 0;
}

DeviceDataWidget::~DeviceDataWidget()
{
	delete _plot;
}

void DeviceDataWidget::SetPlotWidget(PlotWidget* widget, bool top)
{
	if(!widget)
		return;
	if(top)
		ui.topLayout->addWidget(widget);
	else
		ui.bottomLayout->addWidget(widget);
}

void DeviceDataWidget::SetPlotWidget(PlotWidget* widget)
{
	SetPlotWidget(widget, OnTop());
}
