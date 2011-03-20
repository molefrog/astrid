/***********************************
mover класс настройки положения наблюдателя

with best wishes....de
************************************/
#include "mover.h"
#include <math.h>

mover::mover(QWidget* parent, drawerWidget* dw):QWidget(parent)
{	
	drawer    = dw;
	mode      = 0;
	tracking  = false;
	refresh();
	/*Загружаем изображения камеры и света*/
	lightImage.load("light.png");
	cameraImage.load("camera.png");
	/*Коэффициент оконных координат и координат GL*/
	k = 10;
	/*Если положение меняется из вне*/
	QObject::connect(drawer,SIGNAL(viewerPositionChanged(float,float,float)), this, SLOT(changeViewerPosition(float,float,float)));
	QObject::connect(drawer,SIGNAL(lightPositionChanged(float,float,float)),  this, SLOT(changeLightPosition(float,float,float)));
}

void mover::paintEvent(QPaintEvent*)
{
	QPainter painter;
	refresh();
	
	int a = z*k;
	int b = mode?-y*k:-x*k;
	int len = sqrt(a*a  + b*b);	
	
	painter.begin(this);
	painter.setRenderHints(QPainter::Antialiasing);
	/*Рисуем фон*/
	painter.setBrush(QBrush(Qt::black));
	painter.drawRect(0,0,width(),height());
	/*Рисуем окружность*/
	painter.setPen(QPen(Qt::white));
	painter.translate(width()/2,height()/2);
	if(!mode)
	{
		circle(0,0,len,&painter);
		painter.drawLine(0,0,a*1.2,b*1.2);
		
	}
	else
	{
		painter.drawLine(a,-height()/2,a,height()/2);	
	}
	painter.setPen(QPen(Qt::yellow));
	painter.setBrush(QBrush(Qt::red));
	circle(a,b,6,&painter);
	//circle(lightz*k,mode?-lighty*k:-lightx*k,5,&painter);
	painter.drawImage(lightz*k - lightImage.width()/2,(mode?-lighty*k:-lightx*k)-lightImage.height()/2,lightImage);
	painter.end();
}

void mover::circle(int x,int y, int radius, QPainter* painter)
{
	painter->drawEllipse(x-radius,y-radius,radius*2,radius*2);	
}

void mover::mouseMoveEvent(QMouseEvent* me)
{
	if(!tracking) return;
	refresh();
	float a;	
	float b;
	
	if(me->x()<30 && me->y()<20) return;
	if(!mode)
	{
		a = (float) (me->x() - width()/2)/k;
		b = (float) -(me->y() - height()/2)/k;
		drawer->setViewerPosition(b,y,a);
	}
	else
	{
		a = (float) -(me->y() - height()/2)/k;
		drawer->setViewerPosition(x,a,z);
	}
	update();
}

void mover::mousePressEvent(QMouseEvent* me)
{
	switch(me->button())
	{
		case Qt::LeftButton:
		tracking = true;
		break;	
		
		case Qt::RightButton:
		mode = !mode;
		update();
		break;
	
		default:
		break;
	}
	
}

void mover::mouseReleaseEvent(QMouseEvent *)
{
	tracking = false;
}

void mover::refresh()
{
	float *buf;
	buf = drawer->getViewerPosition();
	
	x      = buf[0];
	y      = buf[1];
	z      = buf[2];
	
	buf = drawer->getLightPosition();
	
	lightx = buf[0];
	lighty = buf[1];
	lightz = buf[2];
}

void mover::changeViewerPosition(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	
	update();
}

void mover::changeLightPosition(float x, float y, float z)
{
	lightx = x;
	lighty = y;
	lightz = z;
	
	update();
}
