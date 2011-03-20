#include "modelobject.h"

modelObject::modelObject()
{
	/*Установки по умолчанию*/	
	material.ambient [0] = 0.2;
	material.ambient [1] = 0.2;
	material.ambient [2] = 0.2;
	material.ambient [3] = 1.0;
	
	material.diffuse [0] = 0.8;
	material.diffuse [1] = 0.8;
	material.diffuse [2] = 0.8;
	material.diffuse [3] = 1.0;
	
	material.specular[0] = 0.0;
	material.specular[1] = 0.0;
	material.specular[2] = 0.0;
	material.specular[3] = 1.0;
	
	material.emission[0] = 0.0;
	material.emission[1] = 0.0;
	material.emission[2] = 0.0;
	material.emission[3] = 1.0;
	
	material.shininess   = 0.0;
	
	position.x 	     = 0.0;
	position.y 	     = 0.0;
	position.z	     = 0.0;
	
	rotation.x	     = 0.0;
	rotation.y	     = 0.0;
	rotation.z	     = 0.0;
	
	scale.x		     = 1.0;
	scale.y		     = 1.0;
	scale.z		     = 1.0;
}

void modelObject::draw()
{	
	glPushMatrix();
	if(position.x || position.y || position.z) glTranslatef(position.x,position.y,position.z);
	
	if(rotation.x) glRotatef(rotation.x,1.0,0.0,0.0);
	if(rotation.y) glRotatef(rotation.y,0.0,1.0,0.0);
	if(rotation.z) glRotatef(rotation.z,0.0,0.0,1.0);
	
	glScalef(scale.x,scale.y,scale.z);
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   material.ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   material.diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  material.specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,  material.emission);
	glMaterialf(GL_FRONT_AND_BACK,  GL_SHININESS, material.shininess);
	
	own_draw();
		
	glPopMatrix();
}

block::block()
{
}

block::block(float x, float y, float z)
{
	scale.x = x;
	scale.y = y;
	scale.z = z;	
}

void block::own_draw()
{
	glBegin(GL_QUADS);
	/*Нижняя грань*/
	glNormal3f( 0.0,-1.0, 0.0);
	glVertex3f(-0.5,-0.5, 0.5);
	glVertex3f(-0.5,-0.5,-0.5);
	glVertex3f( 0.5,-0.5,-0.5);
	glVertex3f( 0.5,-0.5, 0.5);
	/*Верхняя грань*/
	glNormal3f(0.0,1.0,0.0);
	glVertex3f(-0.5,0.5,0.5);
	glVertex3f(0.5,0.5,0.5);
	glVertex3f(0.5,0.5,-0.5);
	glVertex3f(-0.5,0.5,-0.5);
	/*Задняя грань*/
	glNormal3f(0.0,0.0,-1.0);
	glVertex3f(-0.5,-0.5,-0.5);
	glVertex3f(-0.5,0.5,-0.5);
	glVertex3f(0.5,0.5,-0.5);
	glVertex3f(0.5,-0.5,-0.5);
	/*Передняя грань*/
	glNormal3f(0.0,0.0,1.0);
	glVertex3f(-0.5,-0.5,0.5);
	glVertex3f(0.5,-0.5,0.5);
	glVertex3f(0.5,0.5,0.5);
	glVertex3f(-0.5,0.5,0.5);
	/*Левая грань*/
	glNormal3f(-1.0,0.0,0.0);
	glVertex3f(-0.5,-0.5,-0.5);
	glVertex3f(-0.5,-0.5,0.5);
	glVertex3f(-0.5,0.5,0.5);
	glVertex3f(-0.5,0.5,-0.5);
	/*Правая грань*/
	glNormal3f(1.0,0.0,0.0);
	glVertex3f(0.5,-0.5,0.5);
	glVertex3f(0.5,-0.5,-0.5);
	glVertex3f(0.5,0.5,-0.5);
	glVertex3f(0.5,0.5,0.5);
	glEnd();
}	

sphere::sphere()
{
	radius = 1.0;
	stacks = 64;	
}

sphere::sphere(float rad)
{
	radius = rad;
	stacks = 64;
}

void sphere::own_draw()
{
	gluSphere(gluNewQuadric(), radius, stacks, stacks);
}

/*Фунция работает, но медленно*/
void figure::own_draw()
{
	int i;
	vertex_2d temp;
	pos_struct a1, a2, a3, a4, normal;
	float step = 3.141592*2/128;
	
	for(i = 0; i < (lst.size() - 1); i++)
	{
		for(float angle = 0.0; angle < 3.141592*2; angle += step)
		{
			glBegin(GL_POLYGON);
			temp = lst.at(i);
			
			a1.x = temp.x;a1.y = temp.y * sin(3.141592/2 - angle);a1.z=temp.y*cos(3.141592/2 - angle);
			a2.x = temp.x;a2.y = temp.y * sin(3.141592/2 - (angle+step));a2.z= temp.y * cos(3.141592/2 - (angle+step));	
			
			temp = lst.at(i+1);
			a3.x = temp.x;a3.y= temp.y * sin(3.141592/2 - (angle+step));a3.z=temp.y*cos(3.141592/2 - (angle+step));	
			a4.x = temp.x;a4.y= temp.y * sin(3.141592/2 - angle);a4.z=temp.y*cos(3.141592/2 - angle);
			
			
			normal.x = a1.y*(a2.z-a3.z)  + a2.y*(a3.z-a1.z) + a3.y*(a1.z-a2.z);
			normal.y = a1.z*(a2.x-a3.x)  + a2.z*(a3.x-a1.x) + a3.z*(a1.x-a2.x);
			normal.z = a1.x*(a2.y-a3.y)  + a2.x*(a3.y-a1.y) + a3.z*(a1.y-a2.y);
			
			glNormal3f(normal.x,normal.y,normal.z);
			glVertex3f(a1.x,a1.y,a1.z);
			glVertex3f(a2.x,a2.y,a2.z);
			glVertex3f(a3.x,a3.y,a3.z);
			glVertex3f(a4.x,a4.y,a4.z);
			glEnd();
		}
		
	}
}
/*Эксперимент*/

points::points(int w, int h)
{
 	data = NULL;
	newsize(w,h);
}

points::~points()
{
	del();
}

void points::own_draw()
{
	int w, h;
	glTranslatef(-((float)width/2)*0.1,0.0, -((float)height/2)*0.1);
	for(w = 0;w< (width - 1);w++)
	{
		for(h = 0; h < (height - 1);h++  )
		{
			glBegin(GL_LINE_LOOP);
			glVertex3f(w*0.1, data[w][h], h*0.1);	
			
			glVertex3f((w+1)*0.1, data[w+1][h], h*0.1);	

			glVertex3f((w+1)*0.1, data[w+1][h+1], (h+1)*0.1);	

			glVertex3f(w*0.1, data[w][h+1], (h+1)*0.1);	

			glEnd();
		}
	}
}

void points::del()
{
	if(!data) return;
	for(int w =0; w< width;w++)
	{
		free(data[w]);
	}
	free(data);
}

void points::newsize(int w, int h)
{
	del();
	width = w;
	height = h;
	data = (float**) malloc(sizeof(float*)*w);
	for(int i = 0; i < w; i++)
	{
		data[i] = (float*)malloc(sizeof(float)*h);
		for(int ii=0; ii < h; ii++) data[i][ii] = 0.0;
	}
}

void points::fromImage()
{
	QString filename = QFileDialog::getOpenFileName(0,"preved","/home","*.*");	
	QImage  image(filename);
	newsize(image.width(),image.width());
	int x, y;
	
	for(x = 0; x < image.width(); x++)
		for(y = 0; y < image.height(); y++)
	{
		QRgb a = image.pixel(x,y);
		data[x][y] = (float)(qRed(a) + qGreen(a) + qBlue(a))/300; 
	}
}	
