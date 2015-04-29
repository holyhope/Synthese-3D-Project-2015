/*
 * advanced.hpp
 *
 *  Created on: 29 avr. 2015
 *      Author: pperonne
 */

#ifndef ADVANCED_HPP_
#define ADVANCED_HPP_

struct Matrix;
struct ObjCanonique;

typedef enum {
	NONE, UNION, INTER, SUBSTRACT
} TreeType;

typedef struct {
	ObjCanonique* oc;
	Matrix* transf;
	Matrix* inv;
	float color[3];
} transformedObj;

typedef struct struct_CSGTree {
	TreeType type;
	transformedObj* obj;
	struct_CSGTree* fg;
	struct_CSGTree* fd;
} CSGTree;

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

CSGTree* allocCSGTree(transformedObj* obj, TreeType type, CSGTree* fg,
		CSGTree* fd);

#endif /* ADVANCED_HPP_ */
