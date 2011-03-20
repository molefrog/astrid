#ifndef MODEL_OBJECT
#define MODEL_OBJECT

#include <GL/glu.h>
#include <math.h>
#include <QList>
#include <QFileDialog>

typedef struct
{
	float ambient [4];
	float diffuse [4];
	float specular[4];
	float emission[4];
	
	float shininess;	
}material_struct;

typedef struct
{
	float x;
	float y;
	float z;	
}pos_struct;

struct vertex_2d
{
	float x;
	float y;	
};

class modelObject
{
public:
	modelObject();
	material_struct material;
 	pos_struct 	position;
	pos_struct	rotation;
	pos_struct 	scale;
	
	void draw();
protected:
	virtual void own_draw(){};
};

class block : public modelObject
{
public:	
	block();
	block(float,float,float);
protected:	
	void own_draw();	
};

class sphere : public modelObject
{
public:
	sphere();
	sphere(float);		
	float radius;
	int stacks;
protected:
	void own_draw();
};

class figure : public modelObject
{
public:
	QList<vertex_2d> lst;
protected:
	void own_draw();
};

class points : public modelObject
{
public:
	points(int,int);
	~points();	
	float **data;
	int height,width;
	void newsize(int,int);
	void del();
	void fromImage();
protected:
	void own_draw();
};


#endif
