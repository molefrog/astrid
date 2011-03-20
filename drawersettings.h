#ifndef DRAWER_SETTINGS
#define DRAWER_SETTINGS

#include <QWidget>
#include <QColorDialog>
#include "ui_drawersettings.h"
#include "drawerwidget.h"

class drawerSettings : public QWidget, private Ui::drawerSettings 
{
	Q_OBJECT
public:
	drawerSettings(QWidget*, drawerWidget*);
private:	
	drawerWidget* drawer;
private slots:
	void ambient();
	void diffuse();
	void specular();
	void lightPosition(float,float,float);
};

#endif
