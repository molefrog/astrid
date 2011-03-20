#include "drawersettings.h"

drawerSettings::drawerSettings(QWidget* parent, drawerWidget* dr) : QWidget(parent)
{
	drawer = dr;
	float *pos;
	setupUi(this);
	
	ambientEdit ->setPalette(QPalette(drawer->getLightAmbient()));
	diffuseEdit ->setPalette(QPalette(drawer->getLightDiffuse()));
	specularEdit->setPalette(QPalette(drawer->getLightSpecular()));

	QObject::connect(ambientEdit,  SIGNAL(clicked()), this, SLOT(ambient()));
	QObject::connect(diffuseEdit,  SIGNAL(clicked()), this, SLOT(diffuse()));
	QObject::connect(specularEdit, SIGNAL(clicked()), this, SLOT(specular()));
	
	pos = drawer->getLightPosition();
	lightPosition(pos[0],pos[1],pos[2]);
}

void drawerSettings::ambient()
{
	QColor color = QColorDialog::getColor(drawer->getLightAmbient(),parentWidget());
	drawer->setLightAmbient(color);
	ambientEdit->setPalette(QPalette(color));	
}

void drawerSettings::diffuse()
{
	QColor color = QColorDialog::getColor(drawer->getLightDiffuse(), parentWidget());
	drawer->setLightDiffuse(color);
	diffuseEdit->setPalette(QPalette(color));	
}

void drawerSettings::specular()
{
	QColor color = QColorDialog::getColor(drawer->getLightSpecular(), parentWidget());
	drawer->setLightSpecular(color);
	specularEdit->setPalette(QPalette(color));	
}

void drawerSettings::lightPosition(float x, float y, float z)
{
	xEdit->setText(QString::number((double)x));
	yEdit->setText(QString::number((double)y));
	zEdit->setText(QString::number((double)z));	
}
