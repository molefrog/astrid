#ifndef MOTION_GENERATOR
#define MOTION_GENERATOR

#define OXZ 1
#define OYZ 2
#define OXY 3

#define LIGHT_MOTION  0x0
#define VIEWER_MOTION 0x1

#include <QWidget>
#include <math.h>
#include "../drawerwidget.h"
#include "../ui_circlemotiongenerator.h"

class motionGenerator : public QWidget
{
public: 
	motionGenerator(QWidget*){};
	virtual void 	init(drawerWidget*,int,int){};
	virtual void   generate(int){};
protected:
	int 		steps, count;
	drawerWidget*   drawer;
};

/*Генератор движения по окружности(или эллипсу)*/
class circleMotionGenerator : public motionGenerator, private Ui::circleMotionGenerator
{
	Q_OBJECT
public:
	circleMotionGenerator(QWidget*);
	void init(drawerWidget*, int, int);
	void generate(int);	
private:
	float   a;	
	float   radius1;
	float   radius2;
	int     mode;
	int	motion_type;
private slots:
	void changeToOXZ();
	void changeToOYZ();
	void changeToOXY();
	void selectMotionType(int);
	void setRadius1(double);
	void setRadius2(double);
};

#endif
