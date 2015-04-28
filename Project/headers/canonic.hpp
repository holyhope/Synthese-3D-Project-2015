/*
 * canonic.hpp
 *
 *  Created on: 28 avr. 2015
 *      Author: pperonne
 */

#ifndef CANONIC_HPP_
#define CANONIC_HPP_

#ifndef NB_VERTICES
#define NB_VERTICES_ADDED
#define NB_VERTICES 1000000
#endif

struct ObjCanonique {
	int nb_vertices;
	float vertices[NB_VERTICES][3];
	bool (*isIn)(float, float, float);
};

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


#ifndef NB_VERTICES_ADDED
#undef NB_VERTICES
#endif
#undef NB_VERTICES_ADDED

#endif /* CANONIC_HPP_ */
