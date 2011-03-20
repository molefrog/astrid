#include "motiongenerator.h"

/*Генератор движения по окружности(или эллипсу)*/
circleMotionGenerator::circleMotionGenerator(QWidget *parent) : motionGenerator(parent)
{
	setupUi(this);
	
	mode        =   OXZ;
	motion_type =   LIGHT_MOTION;
	
	motionSelect->addItem(QString::fromUtf8("Движение источника"));
	motionSelect->addItem(QString::fromUtf8("Движение наблюдателя"));
	
	radius1 = 10.0;
	radius2 = 10.0;
	
	radius1Edit->setValue(radius1);
	radius2Edit->setValue(radius2);
	
	QObject::connect(radius1Edit, SIGNAL(valueChanged(double)), 	  this, SLOT(setRadius1(double)));
	QObject::connect(radius2Edit, SIGNAL(valueChanged(double)), 	  this, SLOT(setRadius2(double)));
	QObject::connect(motionSelect,SIGNAL(currentIndexChanged(int)), this, SLOT(selectMotionType(int)));
	QObject::connect(oxzButton,   SIGNAL(clicked()), 		  this, SLOT(changeToOXZ()));
	QObject::connect(oyzButton,   SIGNAL(clicked()), 		  this, SLOT(changeToOYZ()));
	QObject::connect(oxyButton,   SIGNAL(clicked()), 		  this, SLOT(changeToOXY()));
}

void circleMotionGenerator::init(drawerWidget* dr, int st, int c)
{	
	drawer   = dr;
	steps    = st;
	count    = c;	
	
	a = 3.1415 * 2 / steps;
}

void circleMotionGenerator::generate(int i)
{
	float x = 0.0;
	float y = 0.0;
	float z = 0.0;
	
	float b1;
	float b2;
	
	b1 = radius1*cos((float)a*i);
	b2 = radius2*sin((float)a*i);
	
	switch(mode)
		{
			case OXZ:
			x = b1;
			z = b2;	
			break;
			
			case OYZ:
			y = b1;
			z = b2;
			break;
			
			case OXY:
			x = b1;
			y = b2;
			break;
		}
	switch(motion_type)
		{
			case LIGHT_MOTION:
			drawer-> setLightPosition(x,y,z);	
			break;
			
			case VIEWER_MOTION:
			drawer->setViewerPosition(x,y,z);	
			break;
		}
}


void circleMotionGenerator::changeToOXZ()
{
	mode = OXZ;
}

void circleMotionGenerator::changeToOYZ()
{
	mode = OYZ;	
}

void circleMotionGenerator::changeToOXY()
{
	mode = OXY;	
}

void circleMotionGenerator::selectMotionType(int a)
{
	motion_type = a;	
}

void circleMotionGenerator::setRadius1(double a)
{
	radius1 = a;
}

void circleMotionGenerator::setRadius2(double a)
{
	radius2 = a;	
}
