#ifndef  GRAPH_OBJECT
#define  GRAPH_OBJECT

#include <QColor>
#include <QString>
#include <QPen>
#include <string.h>

class graphObject
{
public:
	graphObject();	
	float*    data;
	int       dataCount;
	QString   description;
	bool 	  drawable;
	QPen	  pen;
};

#endif
