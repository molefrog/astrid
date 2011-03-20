#ifndef DRAWER_WIDGET
#define DRAWER_WIDGET

#include <QtOpenGL/QGLPixelBuffer>
#include <QPainter>
#include <QColor>
#include <GL/glu.h>

#include "globals.h"
#include "model/modelobject.h"

class drawerWidget : public QWidget
{
	Q_OBJECT
public:
	drawerWidget(QGLFormat,QWidget*);
	~drawerWidget();
	float* getLightPosition ();
	float* getViewerPosition();
	QColor getLightAmbient  ();
	QColor getLightDiffuse  ();
	QColor getLightSpecular ();
	float  getBright();
private:
	float lightPosition [4];
	float viewerPosition[3];
	float lightAmbient  [4];
	float lightDiffuse  [4];
	float lightSpecular [4];
	QGLPixelBuffer*     pbuffer;
	QImage 		    buffer;
	bool		    hasbuffers;
protected:
/*Стандартные функции QGLWidget*/
	void paintEvent(QPaintEvent*);
	void initializeGL();
	void paintGL();
	void resizeGL(int,int);
public slots:
/*Слоты настройки источника света*/
	void   setLightAmbient  (QColor);    /*Цвет фонового освещения*/
	void   setLightDiffuse  (QColor);    /*Рассеянное освещение*/
	void   setLightSpecular (QColor);    /*Отраженный свет*/
	void   setLightPosition (float, float, float);
	void   setViewerPosition(float, float, float);

signals:
	void lightPositionChanged(float,float,float);
	void viewerPositionChanged(float,float,float);
};

#endif
