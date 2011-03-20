#ifndef GRAPH_WIDGET
#define GRAPH_WIDGET

#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QGLFormat>
#include <QColor>
#include <QPaintEvent>
#include <QPainter>
#include <QList>

#include "graphobject.h"
#include "globals.h"

/*Функция нахождения индекса элемента с наибольшим значением*/
float maximum(float*, int);

class graphWidget : public QWidget
{
Q_OBJECT
public:
	graphWidget(QWidget*);
/*Параметры*/
	bool    gridEnabled();
	float   getGridInterval();
	float	getZoom();
	QColor	getBackColor();
	QColor	getGridColor();
private:
/*Функции рисования*/
	void drawGrid(QPainter*);
	void drawAxis(QPainter*);
	void drawData(QPainter*);
	void drawLegend(QPainter*);
	void drawBackground(QPainter*);
/*Параметры сетки*/
 	bool   gridState;
 	float  gridInterval;
 	QColor gridColor;
/*Параметры графиков*/
	float  zoom;
	int	   space;
	QColor backColor;
	
	QList<graphObject*>* graphs; 
	void   setupSize();
protected:
	void paintEvent(QPaintEvent*);
	void wheelEvent(QWheelEvent*);
public slots:
/*Слоты установок*/
	void setBackColor(QColor);
	void setGridColor(QColor);
	void enableGrid(bool);
	void setGridInterval(float);
	void setData(QList<graphObject*>*);
	void setZoom(float);
signals:
    void zoomChanged(float);
};

#endif
