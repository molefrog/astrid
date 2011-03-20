/******************************
graphInspector
Инспектор графиков
Позволяет изменять лист из графиков.
Особенности:
-В листе должен быть как минимум 1 график
-Следит за распределением памяти
-Довавление/удаление графиков
-Взаимодействует с внешним миром при помощи:
1)сигнала needToRedraw(перерисовать графики)
2)функции getCurrentIndex(чтобы узнать текущий
график)

+удаление всех графиков при выходе сделать из вне
(mainWindow).

******************************/
#include "graphinspector.h"

graphInspector::graphInspector(QWidget *parent, QList<graphObject*>* list) : QWidget(parent)
{
	int i;
	setupUi(this);

	styleEdit->addItem(QString::fromUtf8("Сплошной"));
	styleEdit->addItem(QString::fromUtf8("Штрих"));
	styleEdit->addItem(QString::fromUtf8("Точка"));
	styleEdit->addItem(QString::fromUtf8("Штрих-точка"));

	graphs = list;
	for(i=0;i<graphs->count();i++) graphBox->addItem(graphs->at(i)->description );
	
	QObject::connect(graphBox,        SIGNAL(activated(int)),	  this, SLOT(changeSelection(int)));
 	QObject::connect(widthEdit,       SIGNAL(valueChanged(int)),  this, SLOT(changeWidth(int)));
 	QObject::connect(colorEdit,       SIGNAL(clicked()),		  this, SLOT(changeColor()));
 	QObject::connect(descriptionEdit, SIGNAL(textEdited(QString)),this, SLOT(changeDescription(QString)));
 	QObject::connect(drawableEdit,    SIGNAL(stateChanged(int)),  this, SLOT(changeDrawable(int)));
	QObject::connect(addEdit,	      SIGNAL(clicked()),		  this, SLOT(add()));
	QObject::connect(removeEdit,	  SIGNAL(clicked()),		  this, SLOT(remove()));
	QObject::connect(styleEdit,		  SIGNAL(activated(int)),     this, SLOT(changeStyle(int)));
	
	graphBox->setCurrentIndex(0);
	changeSelection(0);
}

void graphInspector::changeSelection(int a)
{
	descriptionEdit->setText(graphs->at(a)->description);
	widthEdit->setValue(graphs->at(a)->pen.width());
	drawableEdit->setCheckState(graphs->at(a)->drawable? Qt::Checked : Qt::Unchecked);
	colorEdit->setPalette(QPalette(graphs->at(a)->pen.color()));
	styleEdit->setCurrentIndex(graphs->at(a)->pen.style()-1);
}

void graphInspector::changeWidth(int width)
{
	graphs->at(graphBox->currentIndex())->pen.setWidth(width);
	
	emit needToRedraw();
}

void graphInspector::changeColor()
{
	QPen* pen = &(graphs->at(graphBox->currentIndex())->pen);
	pen->setColor(QColorDialog::getColor(pen->color(),parentWidget()));
	colorEdit->setPalette(pen->color());
	
	emit needToRedraw();
}

void graphInspector::changeDescription(QString string)
{
	graphs->at(graphBox->currentIndex())->description = string;
	graphBox->setItemText(graphBox->currentIndex(), string);
	emit needToRedraw();
}

void graphInspector::changeDrawable(int a)
{
	graphs->at(graphBox->currentIndex())->drawable = !a ? false : true;
	
	emit needToRedraw();
}

void graphInspector::changeStyle(int a)
{
	Qt::PenStyle b = Qt::SolidLine;
	switch(a)
	{
	case 0:
	b = Qt::SolidLine;
	break;

	case 1:
	b = Qt::DashLine;
	break;

	case 2:
	b = Qt::DotLine;
	break;

	case 3:
	b = Qt::DashDotLine;
	break;
	}
	graphs->at(graphBox->currentIndex())->pen.setStyle(b);
	
	emit needToRedraw();
}

void graphInspector::add()
{
	int i = graphs->count();
	graphObject* obj = new graphObject;
	obj->description = QString::fromUtf8("Новая кривая ") + QString::number(i+1); 
	/*Небольшой бонус ;)*/
	if(graphs->count() < 12) obj->pen.setColor(Qt::GlobalColor(graphs->count()+6)); /*Автоматически устанавливается цвет*/
	/*Конец*/
	graphs->append(obj);
	graphBox->addItem(graphs->at(i)->description);
	graphBox->setCurrentIndex(i);
	changeSelection(i);
	descriptionEdit->setFocus();	
}

void graphInspector::remove()
{
	int i = graphBox->currentIndex();
	/*Чтобы не удалили все*/
	if(graphs->count() == 1) return;
	
	if(graphs->at(i)->data != NULL) free(graphs->at(i)->data);
	delete graphs->at(i);
	graphs->removeAt(i);
	graphBox->removeItem(i);
	
	if(i == graphs->count()) i--;
	graphBox->setCurrentIndex(i);
	changeSelection(i);
		
	emit needToRedraw();
}

int graphInspector::getCurrentIndex()
{
	return graphBox->currentIndex();
}
