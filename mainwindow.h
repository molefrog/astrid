#ifndef MAIN_WINDOW
#define MAIN_WINDOW

#include <QWidget>
#include <QDockWidget>
#include <QScrollBar>
#include <QDesktopWidget>
#include <QScrollArea>

#include "ui_mainwindow.h"
#include "graphwidget.h"
#include "graphsettings.h"
#include "graphinspector.h"
#include "drawerwidget.h"
#include "drawersettings.h"
#include "mover.h"
#include "motion/controllerwidget.h"

class mainWindow : public QMainWindow, private Ui::astroMainWindow
{
Q_OBJECT
public:
	mainWindow(QWidget*);
	~mainWindow();
private:
	QDockWidget    *graphdock;
	QDockWidget    *inspectordock;
	QDockWidget    *drawerdock; 
	QDockWidget    *moverdock;
	QDockWidget    *controllerdock;

	graphInspector   *graphinspector;
	graphWidget      *graphwidget;
	graphSettings    *graphsettings;
	drawerWidget     *drawerwidget;
	drawerSettings   *drawersettings;
	controllerWidget *controllerwidget; 
	mover	         *mv;

	QList<graphObject*>  *list;

	QGridLayout    *centrallayout;
	QScrollArea	   *area;
private slots:
	void menuFullscreen();
};

#endif
