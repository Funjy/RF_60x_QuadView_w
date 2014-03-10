#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>
#include "ui_PlotWidget.h"
//Qt
#include <qmap.h>
#include <qstring.h>
//Qwt
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_series_data.h>
#include <qwt_legend.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_zoomer.h>
#include <qwt_symbol.h>

#include <qwheelzoomsvc.h>
#include <qaxiszoomsvc.h>


class PlotWidget : public QWidget
{
	Q_OBJECT

public:	
	PlotWidget(QWidget *parent = 0);
	
	~PlotWidget();
	void AddPlotData(QString title, float* plotData, int size, bool showMarkers = false);
	void AddPlotData(QString title, float plotData);
	void RemovePlotData(QString title);
	void SetAutoUpdatePlot(bool autoUpdatePlot);
	void SetShowLegend(bool showLegend);
	void SetShowMarkers(bool showMarkers);
	void ChangeSeriesTitle(QString oldTitle, QString newTitle);
	bool ExportPNG(QString fileName, int preferedWidth = -1, int preferedHeight = -1);
	void Replot();

private:
	//Funcs
	void CheckNReplot();
	QwtPointSeriesData * CreatePointSeriesFromArray(float* plotData, int size);
	QRectF CreateRectForCurve(QwtPlotCurve *curve);
	//Members
	bool _autoUpdatePlot;
	bool _showLegend;
	bool _showMarkers;
	QwtPlot *_plot;
	QwtLegend *_leg;
	QwtPlotGrid *_grid;
	//QwtPlotZoomer *_zoom;
	QwtChartZoom *_zoom;
	QWheelZoomSvc *_wheelZoom;
	QAxisZoomSvc *_axisZoom;
	QMap<QString, QwtPlotCurve*> _curves;	
	Ui::PlotWidget ui;

	QwtSymbol* GetDefaultMarker();
};

#endif // PLOTWIDGET_H
