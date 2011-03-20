/*************************************
main.cpp
*************************************/
#include <QApplication>
#include "mainwindow.h"

/*Точка входа в программу*/
int main(int argc,char** argv)
{
	QApplication application(argc,argv);
	application.setStyle("plastique");
	
	mainWindow mw(0);
	mw.show();
	
	return application.exec();
}
