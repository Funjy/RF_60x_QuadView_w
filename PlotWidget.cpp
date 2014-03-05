#include "PlotWidget.h"

PlotWidget::PlotWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);	
	//parameters
	_autoUpdatePlot	= true;
	_showLegend		= true;
	_showMarkers	= true;
	//Plot
	_plot = new QwtPlot();
	//Legend
	_leg = new QwtLegend();	
	_plot->insertLegend(_leg, QwtPlot::TopLegend);
	//Grid
	_grid = new QwtPlotGrid();
	_grid->enableXMin(true);
	_grid->setMajorPen(QPen(Qt::black, 0, Qt::DotLine));
	_grid->setMinorPen(QPen(Qt::gray, 0, Qt::DotLine));
	_grid->attach(_plot);
	//ChartZoom
	_zoom = new QwtChartZoom(_plot);
	_zoom->setRubberBandColor(Qt::blue);	
	_zoom->setLightMode(true);
	_zoom->indicateDragBand(QwtChartZoom::disSimple);
	//WheelZoom
	_wheelZoom = new QWheelZoomSvc();	
	_wheelZoom->attach(_zoom);	
	//AxisZoom
	_axisZoom = new QAxisZoomSvc();
	_axisZoom->setLightMode(true);
	_axisZoom->attach(_zoom);
	
	ui.MainLayout->addWidget(_plot);
}

void PlotWidget::SetAutoUpdatePlot(bool autoUpdatePlot)
{
	_autoUpdatePlot = autoUpdatePlot;
	CheckNReplot();
}

void PlotWidget::AddPlotData(QString title, uint* plotData, int size, bool showMarkers)
{	
	if(_curves.contains(title))
		return;
	QwtPointSeriesData *points = CreatePointSeriesFromArray(plotData, size);
	QwtPlotCurve *curve = new QwtPlotCurve(title);	
	curve->setData(points);
	//Устанавливается цвет
	curve->setPen(QColor(255,0,0), 2.0);
	if(size < 1000)
		curve->setRenderHint(QwtPlotItem::RenderAntialiased);
	//Marker
	if(_showMarkers || showMarkers)
	{
		QwtSymbol *symbol1 = new QwtSymbol();
		symbol1->setStyle(QwtSymbol::Ellipse);
		symbol1->setPen(QColor(Qt::black));	
		symbol1->setSize(4);
		curve->setSymbol(symbol1);
	}
	//Кривая добавляется на график
	curve->attach(_plot);
	//Добавляется в список кривых
	_curves.insert(title, curve);
	//Область рисования перерисовывается, если включен автоматический режим
	CheckNReplot();
}

void PlotWidget::AddPlotData(QString title, uint plotData)
{
	if(!_curves.contains(title))
	{
		//QwtPointSeriesData *points = CreatePointSeriesFromArray(&plotData, 1);
		QwtPlotCurve *curve = new QwtPlotCurve(title);
		curve->setPen(QColor(255,0,0), 2.0);
		
		if(_showMarkers)
		{
			QwtSymbol *symbol1 = new QwtSymbol();
			symbol1->setStyle(QwtSymbol::Ellipse);
			symbol1->setPen(QColor(Qt::black));	
			symbol1->setSize(4);
			curve->setSymbol(symbol1);
		}
		curve->attach(_plot);
		_curves.insert(title, curve);		
	}
	else
	{
		QwtPlotCurve *curve = _curves.take(title);				
		QwtSeriesData<QPointF>* data = curve->data();			
		int s = data->size();		
		QPointF p(s, plotData);		
		QVector<QPointF> nData(s+1);
		for(int i = 0; i < s; i++)
		{			
			QPointF p(data->sample(i).x(), data->sample(i).y());
			nData.append(p);
		}
		nData.append(p);
		curve->setSamples(nData);
	}
	
	CheckNReplot();
	
	
}

//ConvertData
QwtPointSeriesData * PlotWidget::CreatePointSeriesFromArray(uint* plotData, int size)
{
	QVector<QPointF> qv;
	for (int i = 0; i < size; i++)
	{		
		QPointF p(i, plotData[i]);
		qv.append(p);
	}
	QwtPointSeriesData* data = new QwtPointSeriesData(qv);
	return data;
}

QRectF PlotWidget::CreateRectForCurve(QwtPlotCurve *curve)
{
	QRectF rec(curve->minXValue(), curve->minYValue(), curve->maxXValue(), curve->maxYValue());
	return rec;
}

void PlotWidget::RemovePlotData(QString title)
{
	QwtPlotCurve *c = _curves.take(title);
	if(c == NULL)
		return;
	c->detach();
	_curves.remove(title);
	delete c;
	CheckNReplot();
}

void PlotWidget::SetShowLegend(bool showLegend)
{
	_showLegend = showLegend;
	
	if(!showLegend)		
		_leg->contentsWidget()->hide();
	else
		_leg->contentsWidget()->show();
}

void PlotWidget::SetShowMarkers(bool showMarkers)
{
	_showMarkers = showMarkers;
}

void PlotWidget::ChangeSeriesTitle(QString oldTitle, QString newTitle)
{
	QwtPlotCurve *c = _curves.take(oldTitle);
	c->setTitle(newTitle);
	//Replot();
}

bool PlotWidget::ExportPNG(QString fileName, int preferedWidth, int preferedHeight)
{
	if ( !fileName.isEmpty() )
    {
		QPixmap pixmap= QPixmap::grabWidget(this);
		if(preferedWidth != -1)
		{
			if(preferedHeight == -1)
				preferedHeight = preferedWidth;
			pixmap = pixmap.scaled(QSize (preferedWidth,preferedHeight),Qt::KeepAspectRatio, Qt::SmoothTransformation);
		}		
		bool toRet = pixmap.save(fileName, "png");
		return toRet;
	}
	return false;
}

void PlotWidget::Replot()
{
	_plot->replot();	
	_leg->update();
}

void PlotWidget::CheckNReplot()
{
	if(_autoUpdatePlot)
		Replot();
}

PlotWidget::~PlotWidget()
{	
	delete _leg;
	delete _grid;
	delete _axisZoom;
	delete _wheelZoom;
	delete _zoom;
	QwtPlotCurve* c;
	foreach(c, _curves)
	{
		delete c;
	}
	delete _plot;
	
}
