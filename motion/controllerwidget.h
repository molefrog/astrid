#ifndef CONTROLLER_WIDGET
#define CONTROLLER_WIDGET

#include <QWidget>
#include <QList>
#include <QTimer>
#include <QGridLayout>
#include <QSpacerItem>
#include <string.h>

#include "../ui_controllerwidget.h"
#include "../graphwidget.h"
#include "../drawerwidget.h"
#include "../graphinspector.h"
#include "../drawersettings.h"
#include "../graphobject.h"
#include "../mover.h"
#include "../globals.h"
#include "motiongenerator.h"

class controllerWidget : public QWidget, private Ui::controllerWidget
{
	Q_OBJECT
public:
	controllerWidget(QWidget*, drawerWidget*,graphWidget*,graphInspector*,mover*,drawerSettings*,QList<graphObject*>*);	
	~controllerWidget();
private:
	drawerWidget    	*drawer;
	graphWidget		*graph;
	graphInspector		*graphinspector;
	drawerSettings		*settings;
	mover			*mov;
	QList<graphObject*> 	*graphs;

	QGridLayout		*layout;
	QSpacerItem		*hspacer;
	QSpacerItem		*vspacer;
	
	QTimer			*timer;
	int currentgraph;
	int steps;
	int count;
	int iterator;
	float a;
	circleMotionGenerator   *circleMotion;
private slots:
	void changeStep(int);
	void changeCount(int);
	void start();
	void timerStep();
};

#endif
