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
#include <tools.hpp>
#include <cmath>
#include <cstdio>

#define COLOR_COEFF .8

void addTranslation(TransformedObject* obj, float x, float y, float z) {
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

/**
 * rx > 0, ry > 0, rz > 0
 */
void addHomothety(TransformedObject* obj, float rx, float ry, float rz) {
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

	freeNewMatrix(oldInv);
	freeNewMatrix(inv);
	freeNewMatrix(old);
	freeNewMatrix(h);
}

void addRotationZ(TransformedObject* obj, float theta) {
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

	freeNewMatrix(oldInv);
	freeNewMatrix(inv);
	freeNewMatrix(old);
	freeNewMatrix(rz);
}

void addRotationX(TransformedObject* obj, float theta) {
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

	freeNewMatrix(oldInv);
	freeNewMatrix(inv);
	freeNewMatrix(old);
	freeNewMatrix(rx);
}

void addRotationY(TransformedObject* obj, float theta) {
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

	freeNewMatrix(oldInv);
	freeNewMatrix(inv);
	freeNewMatrix(old);
	freeNewMatrix(ry);
}

void freeTransformedObject(TransformedObject *object) {
	free(object);
}

TransformedObject* Cube() {
	TransformedObject* cube = (TransformedObject*) malloc(
			sizeof(TransformedObject));
	cube->oc = getCanonicCube();
	cube->transf = allocNewMatrix();
	cube->inv = allocNewMatrix();
	cube->color[0] = randomColorCoeff(COLOR_COEFF);
	cube->color[1] = randomColorCoeff(COLOR_COEFF);
	cube->color[2] = randomColorCoeff(COLOR_COEFF);
	return cube;
}

TransformedObject* Tore() {
	TransformedObject* tore = (TransformedObject*) malloc(
			sizeof(TransformedObject));
	tore->oc = getCanonicToroid();
	tore->transf = allocNewMatrix();
	tore->inv = allocNewMatrix();
	tore->color[0] = randomColorCoeff(COLOR_COEFF);
	tore->color[1] = randomColorCoeff(COLOR_COEFF);
	tore->color[2] = randomColorCoeff(COLOR_COEFF);
	return tore;
}

TransformedObject* Cone() {
	TransformedObject* cone = (TransformedObject*) malloc(
			sizeof(TransformedObject));
	cone->oc = getCanonicCone();
	cone->transf = allocNewMatrix();
	cone->inv = allocNewMatrix();
	cone->color[0] = randomColorCoeff(COLOR_COEFF);
	cone->color[1] = randomColorCoeff(COLOR_COEFF);
	cone->color[2] = randomColorCoeff(COLOR_COEFF);
	return cone;
}

TransformedObject* Sphere() {
	TransformedObject* sphere = (TransformedObject*) malloc(
			sizeof(TransformedObject));
	sphere->oc = getCanonicSphere();
	sphere->transf = allocNewMatrix();
	sphere->inv = allocNewMatrix();
	sphere->color[0] = randomColorCoeff(COLOR_COEFF);
	sphere->color[1] = randomColorCoeff(COLOR_COEFF);
	sphere->color[2] = randomColorCoeff(COLOR_COEFF);
	return sphere;
}

TransformedObject* Cylindre() {
	TransformedObject* cylindre = (TransformedObject*) malloc(
			sizeof(TransformedObject));
	cylindre->oc = getCanonicCylindre();
	cylindre->transf = allocNewMatrix();
	cylindre->inv = allocNewMatrix();
	cylindre->color[0] = randomColorCoeff(COLOR_COEFF);
	cylindre->color[1] = randomColorCoeff(COLOR_COEFF);
	cylindre->color[2] = randomColorCoeff(COLOR_COEFF);
	return cylindre;
}

void setColor(TransformedObject* obj, float r, float g, float b) {
	obj->color[0] = r;
	obj->color[1] = g;
	obj->color[2] = b;
}

CSGTree* allocCSGTree(TransformedObject* obj, TreeType type, CSGTree* fg,
		CSGTree* fd) {
	CSGTree* tree = (CSGTree*) malloc(sizeof(CSGTree));
	tree->type = type;
	tree->obj = obj;
	tree->fg = fg;
	tree->fd = fd;
	return tree;
}
