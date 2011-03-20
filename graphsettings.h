#ifndef GRAPH_SETTINGS
#define GRAPH_SETTINGS

#include <QWidget>
#include <QObject>
#include <QColorDialog>

#include "graphwidget.h"
#include "ui_graphsettings.h"

class graphSettings : public QWidget, private Ui::graphSettings
{
	Q_OBJECT
public:
	graphSettings(QWidget*,graphWidget*);
private:
	graphWidget  *graph; /*Виджет для настройки*/
private slots:
/*Настройки сетки*/
	void switch_grid();
	void minus_grid();
	void plus_grid();
	void zoom(int);
	void setzoom(float);
/*Цвета*/
	void fore_color();
	void grid_color();
};

#endif
