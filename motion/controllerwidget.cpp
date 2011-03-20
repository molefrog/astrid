/**************************************
 controllerWidget 
класс настроек движения источника света
***************************************/
#include "controllerwidget.h"

controllerWidget::controllerWidget(QWidget* parent, drawerWidget* dr, graphWidget* gr, graphInspector* ins,mover* m,drawerSettings* set,QList<graphObject*>* list) : QWidget(parent)
{
	/*Настроим интерфейс*/
	setupUi(this);	
	/*Присвоим значения*/
	drawer 		= dr;
	graph		= gr;
	graphinspector  = ins;
	settings 	= set;
	graphs 		= list;
	mov		= m;
	steps		= 360;
	count 		= 1;
	/*Создаем генераторы движения*/
	circleMotion    = new circleMotionGenerator(this);
	/*Настроим лэйауты*/
	hboxLayout->addWidget(circleMotion);
	/*Создаем таймер*/
	timer  = new QTimer(this);
	QObject::connect(timer, 	SIGNAL(timeout()), 	   this, SLOT(timerStep()));
	QObject::connect(buildButton, 	SIGNAL(clicked()), 	   this, SLOT(start()));
	QObject::connect(stepEdit, 	SIGNAL(valueChanged(int)),this, SLOT(changeStep(int)));
	QObject::connect(countEdit,	SIGNAL(valueChanged(int)),this, SLOT(changeCount(int)));
}

controllerWidget::~controllerWidget()
{
	delete timer;
	delete circleMotion;
}

void controllerWidget::changeStep(int newstep)
{
	steps  =  newstep;	
}

void controllerWidget::start()
{
	iterator = 0;
	/*Инициализируем график*/
	currentgraph = graphinspector->getCurrentIndex();
	if(graphs->at(currentgraph)->data != NULL) free(graphs->at(currentgraph)->data);
	graphs->at(currentgraph)->data 	    = (float*) malloc(sizeof(float)*steps*count);
	graphs->at(currentgraph)->dataCount = 0;
	
	circleMotion->init(drawer,steps,count);
	
	/*Отключаем управление*/
	stepEdit->setEnabled(false);
	buildButton->setEnabled(false);
	progressIndicator->setEnabled(true);
	graphinspector->setEnabled(false);
	settings->setEnabled(false);
	mov->setEnabled(false);
	circleMotion->setEnabled(false);
	countEdit->setEnabled(false);
	/*Запускаем таймер*/
	timer->start(TIMER_INTERVAL);
}

void controllerWidget::timerStep()
{
	if(iterator >= steps*count)
	{
	/*Отключаем таймер*/
		timer->stop(); 
	/*Включаем управление*/
		stepEdit->setEnabled(true);
		buildButton->setEnabled(true);
		progressIndicator->setEnabled(false);
		progressIndicator->setValue(0);
		graphinspector->setEnabled(true);
		settings->setEnabled(true);
		mov->setEnabled(true);
		circleMotion->setEnabled(true);
		countEdit->setEnabled(true);
		return;
	}
	
	circleMotion->generate(iterator);
	
	graphs->at(currentgraph)->data[iterator] = drawer->getBright();	
	graphs->at(currentgraph)->dataCount = iterator + 1;
	if(iterator == 1) graphs->at(currentgraph)->data[0] = graphs->at(currentgraph)->data[1];
	
	graph->update();
	progressIndicator->setValue(100*iterator/(steps*count));
	iterator++;
}

void controllerWidget::changeCount(int a)
{
	count = a;
}
