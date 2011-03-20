/**************************************
Класс mainWindow (наследуется от QMainWindow) - 
главное окно программы
Связующее звено между всеми элементами.

with best wishes....de
**************************************/

#include "mainwindow.h"

/*Конструктор*/
mainWindow::mainWindow(QWidget *parent) : QMainWindow(parent)
{
	/*настроим ui*/
	setupUi(this);
	/*Настроим меню*/
	menubar->addAction(QString::fromUtf8("Полноэкранный режим"),this,SLOT(menuFullscreen()));
	/*Создадим лэйауты*/
	centrallayout = new QGridLayout(centralWidget()); 
	centrallayout->setSpacing(0);
	/*Создадим графики*/
	list 		  = new QList<graphObject*>;
	graphObject *obj  = new graphObject;
	obj->description  = QString::fromUtf8("Новая кривая");
	obj->drawable     = true;
	obj->pen.setColor(Qt::magenta);
	list->append(obj);
	/*OpenGL формат*/
	QGLFormat fmt;
	if(!QGLFormat::hasOpenGL())
	{
		fmt.setDoubleBuffer(false);
		fmt.setDirectRendering(false);
	}
	/*Создание элементов окна*/
	graphwidget     = new graphWidget(this);
	graphsettings   = new graphSettings(this,graphwidget);
	graphinspector 	= new graphInspector(this,list);
	drawerwidget	= new drawerWidget(fmt,this);
	drawersettings	= new drawerSettings(this,drawerwidget);
	mv 			    = new mover(this,drawerwidget);
	controllerwidget= new controllerWidget(this,drawerwidget,graphwidget,graphinspector,mv,drawersettings,list);
	
	/*Добавляем виджеты в layout*/
	centrallayout->addWidget(drawerwidget, 0,0,1,1);
	
	/*Настройка доков*/

	/*Док для настройки графера*/
	graphdock      = new QDockWidget(QString::fromUtf8("Построение графиков"),this);
	graphdock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable);
	graphdock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	graphdock->setWidget(graphsettings);
	graphdock->setFixedHeight(graphsettings->height());
	/*Док инспектора графиков*/
	inspectordock	= new QDockWidget(QString::fromUtf8("Инспектор графиков"),this);
	inspectordock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable);
	inspectordock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	inspectordock->setWidget(graphinspector);
	inspectordock->setFixedHeight(graphinspector->height());
	/*Док настроек рисовальщика*/
	drawerdock 	= new QDockWidget(QString::fromUtf8("Источник света"),this);
	drawerdock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable);
	drawerdock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	drawerdock->setWidget(drawersettings);
	drawerdock->setFixedHeight(drawersettings->height());
	/*Док положения камеры*/
	moverdock	= new QDockWidget(QString::fromUtf8("Положение наблюдателя"),this);
	moverdock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable);
	moverdock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	moverdock->setWidget(mv);
	moverdock->setFixedHeight(200);
	/*Док контроллера*/
	controllerdock = new QDockWidget(QString::fromUtf8("Движение источника света"),this);
	controllerdock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable);
	controllerdock->setAllowedAreas(Qt::BottomDockWidgetArea | Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	controllerdock->setWidget(controllerwidget);
	controllerdock->setFixedHeight(controllerwidget->height());
	controllerdock->setFixedWidth(controllerwidget->width());

	area = new QScrollArea;
	area->setWidget(graphwidget);
	centrallayout->addWidget(area,  1,0,1,1);

	addDockWidget(Qt::LeftDockWidgetArea,graphdock);
	addDockWidget(Qt::LeftDockWidgetArea,inspectordock);
	addDockWidget(Qt::LeftDockWidgetArea, controllerdock);
	addDockWidget(Qt::RightDockWidgetArea,moverdock);
	addDockWidget(Qt::RightDockWidgetArea,drawerdock);
	/*Передаем граферу лист с графиками*/
	graphwidget->setData(list);
	/*Чтобы графики были перерисованы*/
	QObject::connect(graphinspector, SIGNAL(needToRedraw()),               	    	  graphwidget,    SLOT(update()));
	QObject::connect(drawerwidget,   SIGNAL(lightPositionChanged(float,float,float)), drawersettings, SLOT(lightPosition(float,float,float)));
}

/*Деструктор*/
mainWindow::~mainWindow()
{
	int i;
	/*Лэйауты*/
	delete centrallayout;
	/*Виджеты*/
	delete mv;
	delete graphwidget;
	delete graphsettings;
	delete drawerwidget;
	delete drawersettings;
	delete controllerwidget;
	delete area;
	/*Доки*/	
	delete controllerdock;
	delete graphdock;
	delete inspectordock;
	delete drawerdock;
	delete moverdock;
	/*Удаление графиков*/	
	for(i = 0; i < list->count(); i++)
		{
			if(list->at(i)->data != NULL) free(list->at(i)->data);
			delete list->at(i);
		}	
	delete list;
}

void mainWindow::menuFullscreen()
{
	setWindowState(windowState() ^ Qt::WindowFullScreen);
}
