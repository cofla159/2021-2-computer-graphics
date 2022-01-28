#include "shader.h"
#include <math.h>
#include <stdio.h>

using namespace raytraceData;

void norm(point* p);

shader::shader()
{
}

shader::~shader()
{
}

material* shader::makeMaterial(GLfloat r, GLfloat g, GLfloat b, GLfloat amb, GLfloat dif, GLfloat spe) {
	material* m;

	/* allocate memory */
	m = new material();

	/* put stuff in it */
	m->c.r = r;
	m->c.g = g;
	m->c.b = b;
	m->amb = amb;
	m->dif = dif;
	m->spe = spe;

	return(m);
}

/* LIGHTING CALCULATIONS */

/* shade */
/* color of point p with normal vector n and material m returned in c */
void shader::shade(point* p, vector* n, material* m, color* c) {

	light l;
	l.c.r = 0.5;
	l.c.g = 0.5;
	l.c.b = 0.5;

	/* so far, just finds ambient component of color */
	point ambient;
	ambient.x = m->amb * m->c.r;
	ambient.y = m->amb * m->c.g;
	ambient.z = m->amb * m->c.b;

	/*diffuse*/
	norm(n);
	l.pos.x = 5.0;
	l.pos.y = 0.0;
	l.pos.z = 0.0;
	l.pos.w = 0.0;
	point lightdir = { (l.pos.x - p->x), (l.pos.y - p->y) , (l.pos.z - p->z), (l.pos.w - p->w) };
	norm(&lightdir);
	GLfloat dot = n->x * lightdir.x + n->y * lightdir.y + n->z * lightdir.z;
	GLfloat diff = fmax(dot, 0.0);
	point diffuse;
	diffuse.x = l.c.r * diff * m->dif;
	diffuse.y = l.c.g * diff * m->dif;
	diffuse.z = l.c.b * diff * m->dif;

	/*specular*/
	l.shine = 2.0;
	point viewdir = { -1 * p->x, -1 * p->y, -1 * p->z, -1 * p->w };
	norm(&viewdir);
	GLfloat reflectdot = n->x * lightdir.x + n->y * lightdir.y + n->z * lightdir.z;
	point reflectdir = { 2 * reflectdot * n->x - lightdir.x, 2 * reflectdot * n->y - lightdir.y , 2 * reflectdot * n->z - lightdir.z };
	GLfloat specdot = viewdir.x * reflectdir.x + viewdir.y * reflectdir.y + viewdir.z * reflectdir.z;
	GLfloat specmax = fmax(specdot, 0.0);
	GLfloat spec = pow(specmax, l.shine);
	point specular;
	specular.x = l.c.r * spec * m->spe;
	specular.y = l.c.g * spec * m->spe;
	specular.z = l.c.b * spec * m->spe;
	
	c->r = (ambient.x + diffuse.x + specular.x);
	c->g = (ambient.y + diffuse.y + specular.y);
	c->b = (ambient.z + diffuse.z + specular.z);
	
	/* clamp color values to 1.0 */
	if (c->r > 1.0) c->r = 1.0;
	if (c->g > 1.0) c->g = 1.0;
	if (c->b > 1.0) c->b = 1.0;

}

void norm(point* p) {
	GLfloat size = sqrt(powf(p->w, 2) + powf(p->x, 2) + powf(p->y, 2) + powf(p->z, 2));
	p->x = p->x / size;
	p->y = p->y / size;
	p->z = p->z / size;
	p->w = p->w / size;
}
