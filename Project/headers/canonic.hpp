/*
 * canonic.hpp
 *
 *  Created on: 28 avr. 2015
 *      Author: pperonne
 */

#ifndef CANONIC_HPP_
#define CANONIC_HPP_

#define NB_VERTICES 100000

typedef struct {
	int nb_vertices;
	float vertices[NB_VERTICES][3];
	bool (*isIn)(float, float, float);
} ObjCanonique;

void initCanonicObjects();

bool isInSphere(float x, float y, float z);
ObjCanonique* getCanonicSphere();

bool isInCylindre(float x, float y, float z);
ObjCanonique* getCanonicCylindre();

bool isInCone(float x, float y, float z);
ObjCanonique* getCanonicCone();

bool isInToroid(float x, float y, float z);
ObjCanonique* getCanonicToroid();

bool isInCube(float x, float y, float z);
ObjCanonique* getCanonicCube();

#endif /* CANONIC_HPP_ */
