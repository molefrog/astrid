/****************************
Класс graphObject содержит
информацию о графике:
1. Данные
2. Цвет
3. Описание
4  Остальные опции

*****************************/
#include "graphobject.h"

graphObject::graphObject()
{
	dataCount    = 0;
	data         = NULL;
	pen.setCapStyle(Qt::RoundCap);
	pen.setJoinStyle(Qt::RoundJoin);
	drawable     = true;
	description  = QString(" ");
}
