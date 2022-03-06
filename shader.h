#pragma once

#include <glad/glad.h>
#include <stdlib.h> 
#include "raytraceData.h"

class shader {
public: 
	shader();
	~shader();

	raytraceData::material* makeMaterial(GLfloat r, GLfloat g, GLfloat b, GLfloat amb, GLfloat dif, GLfloat spe);
	void shade(raytraceData::point* p, raytraceData::vector* n, raytraceData::material* m, raytraceData::color* c);
};
