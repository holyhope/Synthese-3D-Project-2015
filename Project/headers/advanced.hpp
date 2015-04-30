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

typedef struct {
	ObjCanonique* oc;
	Matrix* transf;
	Matrix* inv;
	float color[3];
} TransformedObject;

typedef enum {
	NONE, UNION, INTER, SUBSTRACT
} TreeType;

typedef struct struct_CSGTree {
	TreeType type;
	TransformedObject* obj;
	struct_CSGTree* fg;
	struct_CSGTree* fd;
} CSGTree;

void addTranslation(TransformedObject* obj, float x, float y, float z);
void addHomothety(TransformedObject* obj, float rx, float ry, float rz);
void addRotationZ(TransformedObject* obj, float theta);
void addRotationX(TransformedObject* obj, float theta);
void addRotationY(TransformedObject* obj, float theta);

TransformedObject* Cube();
TransformedObject* Tore();
TransformedObject* Cone();
TransformedObject* Sphere();
TransformedObject* Cylindre();
void freeTransformedObject(TransformedObject *object);

void setColor(TransformedObject* obj, float r, float g, float b);

CSGTree* allocCSGTree(TransformedObject* obj, TreeType type, CSGTree* fg,
		CSGTree* fd);

#endif /* ADVANCED_HPP_ */
