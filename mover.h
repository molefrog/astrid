#ifndef MOVER
#define MOVER

#include <QWidget>
#include <QImage>
#include <QMouseEvent>
#include "drawerwidget.h"

class mover : public QWidget
{
	Q_OBJECT
public:
	mover(QWidget*, drawerWidget*);
private:
	drawerWidget* drawer;
	int mode;
	float x,y,z;
	bool  tracking;
	float lightx,lighty,lightz;
	QImage lightImage, cameraImage;
	int k;
	void circle(int,int,int,QPainter*);
 	void refresh();
private slots:
	void changeViewerPosition(float,float,float);
	void changeLightPosition(float,float,float);
protected:
	void paintEvent(QPaintEvent *);
	void mouseMoveEvent(QMouseEvent *);
 	void mousePressEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *);
};

#endif
