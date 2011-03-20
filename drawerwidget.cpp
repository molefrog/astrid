#include "drawerwidget.h"

/*Конструктор*/
drawerWidget::drawerWidget(QGLFormat fmt, QWidget *parent) : QWidget(parent)
{
	/*Проверка на поддержку пиксельных буферов*/
	if(QGLPixelBuffer::hasOpenGLPbuffers())
		{	
		pbuffer = new QGLPixelBuffer(512,512,fmt);
		hasbuffers = true;
		}
		else hasbuffers = true;
	setFixedHeight(350);
	setFixedWidth(350);
	
	viewerPosition[0] = 0.0;
	viewerPosition[1] = 0.0;
	viewerPosition[2] = 2.0;
	
	lightPosition [0] = 0.0;
	lightPosition [1] = 3.0;
	lightPosition [2] = 3.1;
	lightPosition [3] = 0.0;
	
	lightAmbient  [0] = 0.0;
	lightAmbient  [1] = 0.0;
	lightAmbient  [2] = 0.0;
	lightAmbient  [3] = 1.0;
	
	lightDiffuse  [0] = 1.0;
	lightDiffuse  [1] = 1.0;
	lightDiffuse  [2] = 1.0;
	lightDiffuse  [3] = 1.0;
	
	lightSpecular [0] = 1.0;
	lightSpecular [1] = 1.0;
	lightSpecular [2] = 1.0;
	lightSpecular [3] = 1.0;
}

/*Деструктор*/
drawerWidget::~drawerWidget()
{
	if(hasbuffers) delete pbuffer;
}
/*Стандартные функции QGLWidget*/
void drawerWidget::initializeGL()
{
	glClearColor(0.0,0.0,0.0,0.0);
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT,  lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
}


void drawerWidget::resizeGL(int width, int height)
{
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)width/(float)height, 1.0f, 120.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
/*Функция рисования*/
void drawerWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	gluLookAt(viewerPosition[0],viewerPosition[1],viewerPosition[2],0.0,0.0,0.0,0.0,1.0,0.0);
	glPushMatrix();
	
	block a(3.0,1.0,1.0);
	a.draw();
	a.scale.x = 0.01;
	a.scale.y = 5.0;
	a.scale.z=0.01;
	a.position.x = -1.2;
	a.position.y = 2.0;
	a.draw();
	a.scale.y = 0.01;
	a.scale.x = 1.5;
	a.scale.z = 3.0;
	a.material.specular[2] = 1.0;
	a.material.shininess = 3.0;
	a.position.z = 2.5;
	a.position.y = 0.0;
	a.rotation.z = -30.0;
	a.position.x = 0.0;
	a.draw();
	vertex_2d v1 = {-0.2,0.0};
	vertex_2d v2 = {-0.2,0.5};
	vertex_2d v3 = {0.2,0.5};
	vertex_2d v4 = {0.2,0.0};
	vertex_2d v5 = {1.0,1.0};
	vertex_2d v6 = {1.2,0.8};
	vertex_2d v7 = {1.6,0.0};
	figure b;
	b.lst.append(v1);
	b.lst.append(v2);
	b.lst.append(v3);
	b.lst.append(v4);
	b.position.x = 1.7;
	b.draw();
	glPopMatrix();
	glFlush();
}

void drawerWidget::paintEvent(QPaintEvent*)
{
	/*Если буфферы поддерживаются*/
	QPainter painter;
	if(hasbuffers)
	{
		painter.begin(pbuffer);
		pbuffer->makeCurrent();
		initializeGL();
		resizeGL(width(),height());
		paintGL();	
		painter.end();
	
		buffer = pbuffer->toImage().copy(0,512 - height(),width(), height()).convertToFormat(QImage::Format_RGB32);
	
		painter.begin(this);
		painter.drawImage(0,0,buffer);
		painter.end();
	}
	else
	{
		/*Ничего нет!*/
	}
	
}

void drawerWidget::setLightAmbient(QColor color)
{
	lightAmbient[0] = color.redF();
	lightAmbient[1] = color.greenF();
	lightAmbient[2] = color.blueF();
	
	update();
}

void drawerWidget::setLightDiffuse(QColor color)
{
	lightDiffuse[0] = color.redF();
	lightDiffuse[1] = color.greenF();
	lightDiffuse[2] = color.blueF();
	
	update();
}

void drawerWidget::setLightSpecular(QColor color)
{
	lightSpecular[0] = color.redF();
	lightSpecular[1] = color.greenF();
	lightSpecular[2] = color.blueF();
	
	update();
}

QColor drawerWidget::getLightAmbient()
{
	return QColor::fromRgbF(lightAmbient[0],lightAmbient[1],lightAmbient[2]);	
}

QColor drawerWidget::getLightDiffuse()
{
	return QColor::fromRgbF(lightDiffuse[0],lightDiffuse[1],lightDiffuse[2]);	
}

QColor drawerWidget::getLightSpecular()
{
	return QColor::fromRgbF(lightSpecular[0],lightSpecular[1],lightSpecular[2]);	
}

float* drawerWidget::getLightPosition()
{
	return lightPosition;	
}

void   drawerWidget::setLightPosition(float x, float y, float z)
{
	lightPosition[0] = x;
	lightPosition[1] = y;
	lightPosition[2] = z;
	emit lightPositionChanged(x,y,z);
	
	update();
}

void   drawerWidget::setViewerPosition(float x, float y, float z)
{
	viewerPosition[0] = x;
	viewerPosition[1] = y;
	viewerPosition[2] = z;
	emit viewerPositionChanged(x,y,z);
	
	update();
}

float* drawerWidget::getViewerPosition()
{
	return viewerPosition;	
}

int bright(QRgb rgb)
{
	return (qRed(rgb)+qGreen(rgb)+qBlue(rgb))/3;	
}

float  drawerWidget::getBright()
{
	int x, y;
	int temp = 0;
	for(x = 0; x < buffer.width(); x++)
	for(y = 0; y < buffer.height(); y++)
	{
		temp += bright(buffer.pixel(x,y));
	}
	return (float)temp/(float)(buffer.height()*buffer.width()*255);
}

