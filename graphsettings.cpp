/*******************************
graphSettings виджет для 
настройки графера
********************************/
#include "graphsettings.h"

graphSettings::graphSettings(QWidget* parent, graphWidget* gr) : QWidget(parent)
{
	setupUi(this);
	graph = gr;
	
	forecolor->setPalette(QPalette(gr->getBackColor()));
	gridcolor->setPalette(QPalette(gr->getGridColor()));
	zoomSlider->setValue(gr->getZoom()*1000);
    /*Сигналы и слоты*/
	QObject::connect(gridSwitch, SIGNAL(clicked()), 	    this, SLOT(switch_grid()));
	QObject::connect(gridPlus,   SIGNAL(clicked()), 	    this, SLOT(plus_grid()));
	QObject::connect(gridMinus,  SIGNAL(clicked()), 	    this, SLOT(minus_grid()));
	QObject::connect(forecolor,  SIGNAL(clicked()),         this, SLOT(fore_color()));
	QObject::connect(gridcolor,  SIGNAL(clicked()),	        this, SLOT(grid_color()));
	QObject::connect(zoomSlider, SIGNAL(sliderMoved(int)),  this, SLOT(zoom(int)));
	QObject::connect(graph,      SIGNAL(zoomChanged(float)),this, SLOT(setzoom(float)));
}

void graphSettings::switch_grid()
{
	graph->enableGrid(!graph->gridEnabled());
}

void graphSettings::minus_grid()
{
	graph->setGridInterval(graph->getGridInterval()/2);
}

void graphSettings::plus_grid()
{
	graph->setGridInterval(graph->getGridInterval()*2);
}

void graphSettings::fore_color()
{
	QColor color;
	color = QColorDialog::getColor(graph->getBackColor(), parentWidget());
	graph->setBackColor(color);
	forecolor->setPalette(QPalette(color));
}

void graphSettings::grid_color()
{
	QColor color;
	color = QColorDialog::getColor(graph->getGridColor(), parentWidget());
	graph->setGridColor(color);
	gridcolor->setPalette(QPalette(color));
}

void graphSettings::zoom(int a)
{
     graph->setZoom((float)a/1000);    
}

void graphSettings::setzoom(float a)
{
     zoomSlider->setValue(a*1000);
}
