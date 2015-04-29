/*
 * advanced.hpp
 *
 *  Created on: 29 avr. 2015
 *      Author: pperonne
 */

#ifndef ADVANCED_HPP_
#define ADVANCED_HPP_

#include <matrix.hpp>
#include <canonic.hpp>

struct transformedObj {
	ObjCanonique* oc;
	Matrix* transf;
	Matrix* inv;
	float color[3];
};

struct CSGTree {
	int type;
	transformedObj* obj;
	CSGTree* fg;
	CSGTree* fd;
};

void AddTranslation(transformedObj* obj, float x, float y, float z);
void AddHomo(transformedObj* obj, float rx, float ry, float rz);
void AddRotationZ(transformedObj* obj, float theta);
void AddRotationX(transformedObj* obj, float theta);
void AddRotationY(transformedObj* obj, float theta);

transformedObj* Cube();
transformedObj* Tore();
transformedObj* Cone();
transformedObj* Sphere();
transformedObj* Cylindre();

void SetColor(transformedObj* obj, float r, float g, float b);

CSGTree* NewCSGTree(transformedObj* obj, int type, CSGTree* fg, CSGTree* fd);

#endif /* ADVANCED_HPP_ */
