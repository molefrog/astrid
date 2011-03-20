#ifndef GRAPH_INSPECTOR
#define GRAPH_INSPECTOR

#include <QWidget>
#include <QList>
#include <QColor>
#include <QColorDialog>
#include <string.h>

#include "ui_graphinspector.h"
#include "graphobject.h"

class graphInspector : public QWidget, private Ui::graphInspector
{
	Q_OBJECT
public:
	graphInspector(QWidget*, QList<graphObject*>*);
	int getCurrentIndex();
private:
	QList<graphObject*> *graphs;
	
private slots:
	void changeSelection(int);
	void changeWidth(int);
	void changeColor();
	void changeDescription(QString);
	void changeDrawable(int);
	void changeStyle(int);
	void remove();
	void add();
signals:
	void needToRedraw();
};

#endif
