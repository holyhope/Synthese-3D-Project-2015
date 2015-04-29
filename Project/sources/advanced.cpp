/*
 * advanced.cpp
 *
 *  Created on: 29 avr. 2015
 *      Author: pperonne
 */

#include <advanced.hpp>
#include <canonic.hpp>
#include <matrix.hpp>
#include <stdlib.h>
#include <cmath>
#include <cstdio>

void AddTranslation(transformedObj* obj, float x, float y, float z) {
	// matrice de la transformation
	Matrix* t = allocNewMatrix();
	setMatPoint(t, 0, 3, x);
	setMatPoint(t, 1, 3, y);
	setMatPoint(t, 2, 3, z);

	Matrix* newMat = allocNewMatrix();
	matMulMat(obj->transf, t, newMat);

	Matrix* old = obj->transf;
	obj->transf = newMat;

	// matrice inverse
	Matrix* inv = allocNewMatrix();
	setMatPoint(inv, 0, 3, -x);
	setMatPoint(inv, 1, 3, -y);
	setMatPoint(inv, 2, 3, -z);

	Matrix* newInv = allocNewMatrix();
	matMulMat(inv, obj->inv, newInv);

	Matrix* oldInv = obj->inv;
	obj->inv = newInv;

	freeNewMatrix(oldInv);
	freeNewMatrix(inv);
	freeNewMatrix(old);
	freeNewMatrix(t);
}

void AddHomo(transformedObj* obj, float rx, float ry, float rz) {
	if (rx <= 0. || ry <= 0. || rz <= 0.) {
		fprintf(stderr,
				"Les valeurs de l'homothétie ne peuvent être inférieures ou égalles à 0.\n");
		return;
	}
	// matrice de la transformation
	Matrix* h = allocNewMatrix();
	setMatPoint(h, 0, 0, rx);
	setMatPoint(h, 1, 1, ry);
	setMatPoint(h, 2, 2, rz);

	Matrix* newMat = allocNewMatrix();
	matMulMat(obj->transf, h, newMat);

	Matrix* old = obj->transf;
	obj->transf = newMat;

	// matrice inverse
	Matrix* inv = allocNewMatrix();
	setMatPoint(inv, 0, 0, 1. / rx);
	setMatPoint(inv, 1, 1, 1. / ry);
	setMatPoint(inv, 2, 2, 1. / rz);

	Matrix* newInv = allocNewMatrix();
	matMulMat(inv, obj->inv, newInv);

	Matrix* oldInv = obj->inv;
	obj->inv = newInv;

	free(oldInv);
	free(inv);
	free(old);
	free(h);
}

void AddRotationZ(transformedObj* obj, float theta) {
	// matrice de la transformation
	Matrix* rz = allocNewMatrix();
	setMatPoint(rz, 0, 0, cos(theta));
	setMatPoint(rz, 0, 1, sin(theta));
	setMatPoint(rz, 1, 0, -sin(theta));
	setMatPoint(rz, 1, 1, cos(theta));

	Matrix* newMat = allocNewMatrix();
	matMulMat(obj->transf, rz, newMat);

	Matrix* old = obj->transf;
	obj->transf = newMat;

	// matrice inverse
	Matrix* inv = allocNewMatrix();
	setMatPoint(inv, 0, 0, cos(-theta));
	setMatPoint(inv, 0, 1, sin(-theta));
	setMatPoint(inv, 1, 0, -sin(-theta));
	setMatPoint(inv, 1, 1, cos(-theta));

	Matrix* newInv = allocNewMatrix();
	matMulMat(inv, obj->inv, newInv);

	Matrix* oldInv = obj->inv;
	obj->inv = newInv;

	free(oldInv);
	free(inv);
	free(old);
	free(rz);
}

void AddRotationX(transformedObj* obj, float theta) {
	// matrice de la transformation
	Matrix* rx = allocNewMatrix();
	setMatPoint(rx, 1, 1, cos(theta));
	setMatPoint(rx, 1, 2, sin(theta));
	setMatPoint(rx, 2, 1, -sin(theta));
	setMatPoint(rx, 2, 2, cos(theta));

	Matrix* newMat = allocNewMatrix();
	matMulMat(obj->transf, rx, newMat);

	Matrix* old = obj->transf;
	obj->transf = newMat;

	// matrice inverse
	Matrix* inv = allocNewMatrix();
	setMatPoint(inv, 1, 1, cos(-theta));
	setMatPoint(inv, 1, 2, sin(-theta));
	setMatPoint(inv, 2, 1, -sin(-theta));
	setMatPoint(inv, 2, 2, cos(-theta));

	Matrix* newInv = allocNewMatrix();
	matMulMat(inv, obj->inv, newInv);

	Matrix* oldInv = obj->inv;
	obj->inv = newInv;

	free(oldInv);
	free(inv);
	free(old);
	free(rx);
}

void AddRotationY(transformedObj* obj, float theta) {
	// matrice de la transformation
	Matrix* ry = allocNewMatrix();
	setMatPoint(ry, 0, 0, cos(theta));
	setMatPoint(ry, 0, 2, sin(theta));
	setMatPoint(ry, 2, 0, -sin(theta));
	setMatPoint(ry, 2, 2, cos(theta));

	Matrix* newMat = allocNewMatrix();
	matMulMat(obj->transf, ry, newMat);

	Matrix* old = obj->transf;
	obj->transf = newMat;

	// matrice inverse
	Matrix* inv = allocNewMatrix();
	setMatPoint(inv, 0, 0, cos(-theta));
	setMatPoint(inv, 0, 2, sin(-theta));
	setMatPoint(inv, 2, 0, -sin(-theta));
	setMatPoint(inv, 2, 2, cos(-theta));

	Matrix* newInv = allocNewMatrix();
	matMulMat(inv, obj->inv, newInv);

	Matrix* oldInv = obj->inv;
	obj->inv = newInv;

	free(oldInv);
	free(inv);
	free(old);
	free(ry);
}

transformedObj* Cube() {
	transformedObj* cube = (transformedObj*) malloc(sizeof(transformedObj));
	cube->oc = getCanonicCube();
	cube->transf = allocNewMatrix();
	cube->inv = allocNewMatrix();
	cube->color[0] = 1.;
	cube->color[1] = 0.;
	cube->color[2] = 0.;
	return cube;
}

transformedObj* Tore() {
	transformedObj* tore = (transformedObj*) malloc(sizeof(transformedObj));
	tore->oc = getCanonicToroid();
	tore->transf = allocNewMatrix();
	tore->inv = allocNewMatrix();
	tore->color[0] = 1.;
	tore->color[1] = 0.;
	tore->color[2] = 0.;
	return tore;
}

transformedObj* Cone() {
	transformedObj* cone = (transformedObj*) malloc(sizeof(transformedObj));
	cone->oc = getCanonicCone();
	cone->transf = allocNewMatrix();
	cone->inv = allocNewMatrix();
	cone->color[0] = 1.;
	cone->color[1] = 0.;
	cone->color[2] = 0.;
	return cone;
}

transformedObj* Sphere() {
	transformedObj* sphere = (transformedObj*) malloc(sizeof(transformedObj));
	sphere->oc = getCanonicSphere();
	sphere->transf = allocNewMatrix();
	sphere->inv = allocNewMatrix();
	sphere->color[0] = 1.;
	sphere->color[1] = 0.;
	sphere->color[2] = 0.;
	return sphere;
}

transformedObj* Cylindre() {
	transformedObj* cylindre = (transformedObj*) malloc(sizeof(transformedObj));
	cylindre->oc = getCanonicCylindre();
	cylindre->transf = allocNewMatrix();
	cylindre->inv = allocNewMatrix();
	cylindre->color[0] = 1.;
	cylindre->color[1] = 0.;
	cylindre->color[2] = 0.;
	return cylindre;
}

void SetColor(transformedObj* obj, float r, float g, float b) {
	obj->color[0] = r;
	obj->color[1] = g;
	obj->color[2] = b;
}

CSGTree* allocCSGTree(transformedObj* obj, TreeType type, CSGTree* fg,
		CSGTree* fd) {
	CSGTree* tree = (CSGTree*) malloc(sizeof(CSGTree));
	tree->type = type;
	tree->obj = obj;
	tree->fg = fg;
	tree->fd = fd;
	return tree;
}
