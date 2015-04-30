#include <canonic.hpp>
#include <tools.hpp>
#include <cmath>
#include <cstdlib>

#define SPHERE_CANONIC_SIZE .9
#define CUBE_CANONIC_SIZE 1.
#define CONE_CANONIC_SIZE 1.
#define CYLINDRE_CANONIC_SIZE 1.
#define TOROID_CANONIC_SIZE 1.
#define TOROID_CANONIC_HEIGHT .4

bool isInSphere(float x, float y, float z) {
	return x * x + y * y + z * z <= SPHERE_CANONIC_SIZE * SPHERE_CANONIC_SIZE;
}

ObjCanonique* getCanonicSphere() {
	ObjCanonique* sphere = (ObjCanonique*) malloc(sizeof(ObjCanonique));
	sphere->nb_vertices = NB_VERTICES;
	sphere->isIn = isInSphere;
	float theta, phi;

	for (int i = 0; i < NB_VERTICES; i++) {
		theta = randomFloat(0., 360.);
		phi = randomFloat(0., 180.);

		sphere->vertices[i][0] = SPHERE_CANONIC_SIZE * cos(theta) * sin(phi);
		sphere->vertices[i][1] = SPHERE_CANONIC_SIZE * sin(theta) * sin(phi);
		sphere->vertices[i][2] = SPHERE_CANONIC_SIZE * cos(phi);
	}
	return sphere;
}

bool isInCircle(float x, float y, float radius) {
	return x * x + y * y <= radius * radius;
}

bool isInCylindre(float x, float y, float z) {
	static const float halfSize = CYLINDRE_CANONIC_SIZE / 2;
	return isInCircle(x, y, halfSize) && (-halfSize <= z && z <= halfSize);
}

ObjCanonique* getCanonicCylindre() {
	static const float radius = CYLINDRE_CANONIC_SIZE / 2;
	ObjCanonique* cylindre = (ObjCanonique*) malloc(sizeof(ObjCanonique));
	cylindre->nb_vertices = NB_VERTICES;
	cylindre->isIn = isInCylindre;
	for (int i = 0; i < 3 * NB_VERTICES / 4; i++) {
		float u = randomFloat(0., 360.);
		float v = randomFloat(-radius, radius);

		cylindre->vertices[i][0] = radius * cos(u);
		cylindre->vertices[i][1] = radius * sin(u);
		cylindre->vertices[i][2] = v;
	}
	for (int i = 3 * NB_VERTICES / 4; i < NB_VERTICES; i++) {
		float theta = randomFloat(0., 180.);
		float u = randomFloat(-radius, radius);
		float v = randomFloat(-radius, radius);
		switch (rand() % 2) {
		case 0:
			cylindre->vertices[i][0] = u * cos(theta) * CYLINDRE_CANONIC_SIZE;
			cylindre->vertices[i][1] = v * sin(theta) * CYLINDRE_CANONIC_SIZE;
			cylindre->vertices[i][2] = -radius;
			break;
		case 1:
			cylindre->vertices[i][0] = u * cos(theta) * CYLINDRE_CANONIC_SIZE;
			cylindre->vertices[i][1] = v * sin(theta) * CYLINDRE_CANONIC_SIZE;
			cylindre->vertices[i][2] = radius;
			break;
		}
	}
	return cylindre;
}

bool isInCone(float x, float y, float z) {
	static const float halfSize = CONE_CANONIC_SIZE / 2;

	return isInCircle(x, y, z) && (-halfSize <= z && z <= 0.);
}

ObjCanonique* getCanonicCone() {
	static const float halfSize = CONE_CANONIC_SIZE / 2;

	ObjCanonique* cone = (ObjCanonique*) malloc(sizeof(ObjCanonique));
	cone->nb_vertices = NB_VERTICES;
	cone->isIn = isInCone;
	float theta, r;

	for (int i = 0; i < 2 * NB_VERTICES / 3; i++) {
		theta = randomFloat(0., 180.);
		r = randomFloat(-halfSize, 0.);

		cone->vertices[i][0] = r * cos(theta);
		cone->vertices[i][1] = r * sin(theta);
		cone->vertices[i][2] = r;
	}
	for (int i = 2 * NB_VERTICES / 3; i < NB_VERTICES; i++) {
		theta = randomFloat(0., 180.);
		r = randomFloat(-halfSize, 0.);

		cone->vertices[i][0] = r * cos(theta);
		cone->vertices[i][1] = r * sin(theta);
		cone->vertices[i][2] = -halfSize;
	}
	return cone;
}

bool isInToroid(float x, float y, float z) {
	static const float halfSize = TOROID_CANONIC_SIZE / 2;
	static const float halfHeight = TOROID_CANONIC_HEIGHT / 2;
	return (x * x + y * y + z * z + halfSize * halfSize
			- halfHeight * halfHeight)
			* (x * x + y * y + z * z + halfSize * halfSize
					- halfHeight * halfHeight)
			<= 4 * halfSize * halfSize * (x * x + y * y);
}

ObjCanonique* getCanonicToroid() {
	static const float halfSize = TOROID_CANONIC_SIZE / 2;
	static const float halfHeight = TOROID_CANONIC_HEIGHT / 2;
	ObjCanonique* tore = (ObjCanonique*) malloc(sizeof(ObjCanonique));
	tore->nb_vertices = NB_VERTICES;
	tore->isIn = isInToroid;
	float theta, phi;

	for (int i = 0; i < NB_VERTICES; i++) {
		theta = randomFloat(0., 360.);
		phi = randomFloat(0., 360.);

		tore->vertices[i][0] = (halfSize + halfHeight * cos(phi)) * cos(theta);
		tore->vertices[i][1] = (halfSize + halfHeight * cos(phi)) * sin(theta);
		tore->vertices[i][2] = halfHeight * sin(phi);
	}
	return tore;
}

bool isInCube(float x, float y, float z) {
	return (-.5 <= x && x <= .5) && (-.5 <= y && y <= .5)
			&& (-.5 <= z && z <= .5);
}

ObjCanonique* getCanonicCube() {
	static const float halfSize = CUBE_CANONIC_SIZE / 2;
	ObjCanonique* cube = (ObjCanonique*) malloc(sizeof(ObjCanonique));
	cube->nb_vertices = NB_VERTICES;
	cube->isIn = isInCube;
	for (int i = 0; i < NB_VERTICES; i++) {
		int face = rand() % 6;
		switch (face) {
		case 0:
			cube->vertices[i][0] = -halfSize;
			cube->vertices[i][1] = randomFloat(-halfSize, halfSize);
			cube->vertices[i][2] = randomFloat(-halfSize, halfSize);
			break;
		case 1:
			cube->vertices[i][0] = halfSize;
			cube->vertices[i][1] = randomFloat(-halfSize, halfSize);
			cube->vertices[i][2] = randomFloat(-halfSize, halfSize);
			break;
		case 2:
			cube->vertices[i][0] = randomFloat(-halfSize, halfSize);
			cube->vertices[i][1] = -halfSize;
			cube->vertices[i][2] = randomFloat(-halfSize, halfSize);
			break;
		case 3:
			cube->vertices[i][0] = randomFloat(-halfSize, halfSize);
			cube->vertices[i][1] = halfSize;
			cube->vertices[i][2] = randomFloat(-halfSize, halfSize);
			break;
		case 4:
			cube->vertices[i][0] = randomFloat(-halfSize, halfSize);
			cube->vertices[i][1] = randomFloat(-halfSize, halfSize);
			cube->vertices[i][2] = -halfSize;
			break;
		case 5:
			cube->vertices[i][0] = randomFloat(-halfSize, halfSize);
			cube->vertices[i][1] = randomFloat(-halfSize, halfSize);
			cube->vertices[i][2] = halfSize;
			break;
		}
	}
	return cube;
}

void initCanonicObjects() {
}
