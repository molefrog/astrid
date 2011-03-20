/**********************************************
Класс graphWidget отвечает за вывод графика.
Плюсы:
-Сделан на qt
-Много настроек
-Прорисовка графика с помощью GL

TODO
-Оптимизация прорисовки самого графика (100%)
-Сделать деления (75%)
-Осуществить zoom (100%)
-Передвижение графика (0%)
**********************************************/

#include "graphwidget.h"

float maximum(float* data, int count)
{
	int i;
	float temp = -20000.0;

	for(i=0;i<count;i++)
	{
		if(data[i] > temp) temp = data[i];
	}
	return temp;
}	

graphWidget::graphWidget(QWidget* parent) : QWidget(parent)
{
	graphs 		= NULL;
	gridState 	= true;
	space 			= 10;
	gridInterval	= 10.0;
	
	gridColor = QColor::fromRgbF(0.9,0.9,0.9);
	backColor = QColor::fromRgbF(1.0,1.0,1.0);
	
	zoom		= 1.0;
	setWindowFlags(Qt::MSWindowsOwnDC);
	setupSize();
}


/*Функция рисования сетки*/
void graphWidget::drawGrid(QPainter* painter)
{
	if(!gridState) return;
	float 	 x;
	float 	 y;
	const float sp = space*zoom;

	painter->begin(this);

	painter->setPen(QPen(gridColor));
	
	for(x=sp; x<width()-sp;  x+= gridInterval*zoom) painter->drawLine(QLineF(x,  sp, x, height()-sp));
	for(y=height()-sp; y>sp; y-= gridInterval*zoom) painter->drawLine(QLineF(sp, y,  width()-sp, y ));
	
	painter->drawLine(QLineF(sp,sp,width()-sp,sp));
	painter->drawLine(QLineF(width()-sp,sp,width()-sp,height()-sp));

	painter->end();
}

/*Функция рисования осей*/
void graphWidget::drawAxis(QPainter* painter)
{
	const float sp = space*zoom;
	QPolygonF polygon;
	float i;	

	painter->begin(this);
	painter->setPen(QPen(Qt::black));
	/*Оси*/
	painter->translate(sp,height()-sp);
	painter->drawLine(QLineF(0.0, 0.0, 0.0,         -height()+2*sp));
	painter->drawLine(QLineF(0.0, 0.0, width()-2*sp, 0.0		  ));

	for(i=0.0;i < width()-2*sp; i += gridInterval*4*zoom) painter->drawLine(QLineF(i,-2*zoom,i,0.0));
	for(i=0.0;i > -height()+2*sp; i -= gridInterval*4*zoom) painter->drawLine(QLineF(0.0,i,2*zoom,i));
	/*Стрелки*/
	polygon << QPointF(0.0,0.0) << QPointF(3.0*zoom, 12.0*zoom) << QPointF(0.0, 10.0*zoom) << QPointF(-3.0*zoom, 12.0*zoom); 
	painter->save();	
	painter->setRenderHint(QPainter::Antialiasing, true);
	painter->translate(0.0,-height()+2*sp);
	painter->setBrush(QBrush(Qt::black));
	painter->drawPolygon(polygon);

	painter->translate(width()-2*sp,height()-2*sp);
	painter->rotate(90.0);
	painter->drawPolygon(polygon);
	painter->restore();

	painter->end();
}

/*Функция рисования графиков*/
void graphWidget::drawData(QPainter *painter)
{	
/*Здесь рисуем сам график, считывая данные
* из массива(в массиве только координаты, их преобразование
* происходит из вне, так что нам незачем беспокоиться)  
*/
	int i;
	int ii;
	const float sp = space*zoom;
	graphObject* current;
	for(i=0; i<graphs->count(); i++)
	{
		current = graphs->at(i);
		if(current->drawable)
		{
			QPainterPath path;
			if(current->dataCount) path.moveTo(QPointF(0.0,-current->data[0]*400*zoom));
			for(ii=1; ii<current->dataCount; ii++) path.lineTo(QPointF(ii*zoom, -current->data[ii]*400*zoom));
			painter->begin(this);
			painter->setRenderHint(QPainter::Antialiasing,true);
			painter->setPen(current->pen);
			painter->translate(sp,height()-sp);
			painter->drawPath(path);
			painter->end();
		}
	}
}

/*Функция рисования фона*/
void graphWidget::drawBackground(QPainter* painter)
{
	painter->begin(this);
	painter->setBrush(QBrush(backColor));
	painter->setPen(QPen(backColor));
	painter->drawRect(QRect(0,0,width(),height()));	
	painter->end();
}

void graphWidget::drawLegend(QPainter* painter)
{
	const int   boxwidth = 40;
	painter->begin(this);

	painter->end();
}

/**********************
paintEvent() главная функция рисования
**********************/
void graphWidget::paintEvent(QPaintEvent *)
{
	 setupSize();
	 QPainter painter;
	 drawBackground(&painter);
	 drawGrid(&painter);
	 drawAxis(&painter);
	 drawData(&painter);
	 drawLegend(&painter);
}

void graphWidget::wheelEvent(QWheelEvent* we)
{
	setZoom(zoom +(float)we->delta()/1000);
	emit zoomChanged(zoom);
	update();
}

/************************************
Слоты установок
************************************/

void graphWidget::setBackColor(QColor color)
{
	backColor = color;
	
	update();	
}

void graphWidget::setGridColor(QColor color)
{
	gridColor = color;
	
	update();	
}

void graphWidget::enableGrid(bool state)
{
	gridState = state;

	update();
}

void graphWidget::setGridInterval(float interval)
{
	if(interval < 0.01) return;
	gridInterval = interval;

	update();
}
void graphWidget::setData(QList<graphObject*> *newgraphs)
{
	graphs = newgraphs;
	update();
}

void graphWidget::setZoom(float zoom)
{
	if(zoom < 0.2) return;
	this->zoom = zoom;

	update();
}
/*Расчет измерений окна*/
void graphWidget::setupSize()
{
	if(!graphs) 
	{
		setFixedHeight(200);
		setFixedWidth(400);
		return;
	}
	int   height,width,i,temp;
	float temp2,maxtemp;
	/*Рассчитываем необходимую ширину*/
	for(i=0, temp=0; i < graphs->count(); i++) 
	{	
		if(graphs->at(i)->drawable && graphs->at(i)->dataCount > temp)
		{
			temp = graphs->at(i)->dataCount;
		}
	}
	if(temp > (400-2*space)) width = temp + 3*space;
	else width = 400;
	/*Рассчитываем необходимую высоту*/
	for(i=0,maxtemp=0.0; i< graphs->count(); i++)
	{
		if(graphs->at(i)->drawable)
		{
			temp2 = maximum(graphs->at(i)->data,graphs->at(i)->dataCount);
			if(temp2 > maxtemp) maxtemp = temp2;
		}
	}

	if(maxtemp*400 > (200-2*space)) height = maxtemp*400 + 3*space;
	else height = 200;

	setFixedWidth (width*zoom);
	setFixedHeight(height*zoom);
}

/**********************************
Слоты параметров
**********************************/

bool graphWidget::gridEnabled()
{
	return  gridState;
}

float graphWidget::getGridInterval()
{
	return gridInterval;
}

float graphWidget::getZoom()
{
	return zoom;
}

QColor graphWidget::getBackColor()
{
	return backColor;
}

QColor graphWidget::getGridColor()
{
	return gridColor;
}
