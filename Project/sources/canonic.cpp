#include <canonic.hpp>
#include <tools.hpp>
#include <cmath>
#include <cstdlib>

bool isInSphere(float x, float y, float z) {
	return x * x + y * y + z * z <= .9 * .9;
}

ObjCanonique* getCanonicSphere() {
	ObjCanonique* sphere = (ObjCanonique*) malloc(sizeof(ObjCanonique));
	sphere->nb_vertices = NB_VERTICES;
	sphere->isIn = isInSphere;
	float theta, phi;
	float ray = .9;

	for (int i = 0; i < NB_VERTICES; i++) {
		theta = randomFloat(0., 360.);
		phi = randomFloat(0., 180.);

		sphere->vertices[i][0] = ray * cos(theta) * sin(phi);
		sphere->vertices[i][1] = ray * sin(theta) * sin(phi);
		sphere->vertices[i][2] = ray * cos(phi);
	}
	return sphere;
}

bool isInCylindre(float x, float y, float z) {
	return x * x + y * y <= 0.5 * 0.5 && (-.5 <= z && z <= .5);
}

ObjCanonique* getCanonicCylindre() {
	ObjCanonique* cylindre = (ObjCanonique*) malloc(sizeof(ObjCanonique));
	cylindre->nb_vertices = NB_VERTICES;
	cylindre->isIn = isInCylindre;
	float rayon = 0.5;
	for (int i = 0; i < 3 * NB_VERTICES / 4; i++) {
		float u = randomFloat(0., 360.);
		float v = randomFloat(-.5, .5);

		cylindre->vertices[i][0] = rayon * cos(u);
		cylindre->vertices[i][1] = rayon * sin(u);
		cylindre->vertices[i][2] = v;
	}
	for (int i = 3 * NB_VERTICES / 4; i < NB_VERTICES; i++) {
		float theta = randomFloat(0., 180.);
		float u = randomFloat(-rayon, rayon);
		float v = randomFloat(-rayon, rayon);
		switch (rand() % 2) {
		case 0:
			cylindre->vertices[i][0] = u * cos(theta);
			cylindre->vertices[i][1] = v * sin(theta);
			cylindre->vertices[i][2] = -.5;
			break;
		case 1:
			cylindre->vertices[i][0] = u * cos(theta);
			cylindre->vertices[i][1] = v * sin(theta);
			cylindre->vertices[i][2] = 0.5;
			break;
		}
	}
	return cylindre;
}

bool isInCone(float x, float y, float z) {
	return x * x + y * y <= z * z && (-.5 <= z && z <= 0.);
}

ObjCanonique* getCanonicCone() {
	ObjCanonique* cone = (ObjCanonique*) malloc(sizeof(ObjCanonique));
	cone->nb_vertices = NB_VERTICES;
	cone->isIn = isInCone;
	float theta, r;

	for (int i = 0; i < 2 * NB_VERTICES / 3; i++) {
		theta = randomFloat(0., 180.);
		r = randomFloat(-.5, 0.);

		cone->vertices[i][0] = r * cos(theta);
		cone->vertices[i][1] = r * sin(theta);
		cone->vertices[i][2] = r;
	}
	for (int i = 2 * NB_VERTICES / 3; i < NB_VERTICES; i++) {
		theta = randomFloat(0., 180.);
		r = randomFloat(-.5, 0.);

		cone->vertices[i][0] = r * cos(theta);
		cone->vertices[i][1] = r * sin(theta);
		cone->vertices[i][2] = -.5;
	}
	return cone;
}

bool isInToroid(float x, float y, float z) {
	return (x * x + y * y + z * z + 0.5 * .5 - .2 * .2)
			* (x * x + y * y + z * z + 0.5 * .5 - .2 * .2)
			<= 4 * .5 * .5 * (x * x + y * y);
}

ObjCanonique* getCanonicToroid() {
	ObjCanonique* tore = (ObjCanonique*) malloc(sizeof(ObjCanonique));
	tore->nb_vertices = NB_VERTICES;
	tore->isIn = isInToroid;
	float theta, phi;
	float R = .5, r = 0.2;

	for (int i = 0; i < NB_VERTICES; i++) {
		theta = randomFloat(0., 360.);
		phi = randomFloat(0., 360.);

		tore->vertices[i][0] = (R + r * cos(phi)) * cos(theta);
		tore->vertices[i][1] = (R + r * cos(phi)) * sin(theta);
		tore->vertices[i][2] = r * sin(phi);
	}
	return tore;
}

bool isInCube(float x, float y, float z) {
	return (-.5 <= x && x <= .5) && (-.5 <= y && y <= .5)
			&& (-.5 <= z && z <= .5);
}

ObjCanonique* getCanonicCube() {
	ObjCanonique* cube = (ObjCanonique*) malloc(sizeof(ObjCanonique));
	cube->nb_vertices = NB_VERTICES;
	cube->isIn = isInCube;
	for (int i = 0; i < NB_VERTICES; i++) {
		int face = rand() % 6;
		switch (face) {
		case 0:
			cube->vertices[i][0] = -.5;
			cube->vertices[i][1] = randomFloat(-.5, .5);
			cube->vertices[i][2] = randomFloat(-.5, .5);
			break;
		case 1:
			cube->vertices[i][0] = .5;
			cube->vertices[i][1] = randomFloat(-.5, .5);
			cube->vertices[i][2] = randomFloat(-.5, .5);
			break;
		case 2:
			cube->vertices[i][0] = randomFloat(-.5, .5);
			cube->vertices[i][1] = -.5;
			cube->vertices[i][2] = randomFloat(-.5, .5);
			break;
		case 3:
			cube->vertices[i][0] = randomFloat(-.5, .5);
			cube->vertices[i][1] = .5;
			cube->vertices[i][2] = randomFloat(-.5, .5);
			break;
		case 4:
			cube->vertices[i][0] = randomFloat(-.5, .5);
			cube->vertices[i][1] = randomFloat(-.5, .5);
			cube->vertices[i][2] = -.5;
			break;
		case 5:
			cube->vertices[i][0] = randomFloat(-.5, .5);
			cube->vertices[i][1] = randomFloat(-.5, .5);
			cube->vertices[i][2] = .5;
			break;
		}
	}
	return cube;
}

void initCanonicObjects() {
}
