#include <camera.hpp>
#include <canonic.hpp>
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <matrix.hpp>
#include <stdio.h>
#include <tools.hpp>
#include <cstdlib>

const static int NUMBER_OBJECT = 50;

// STRUCTURES //

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

////////////////
// OBJ STATIC //
////////////////

static struct {
	transformedObj *(objects[NUMBER_OBJECT]);
	int number;
} objectToDisplay;

static struct {
	CSGTree *(trees[NUMBER_OBJECT]);
	int number;
} treeToDisplay;

/////////////////////
// TRANSFORMATIONS //
/////////////////////

void AddTranslation(transformedObj* obj, float x, float y, float z) {
	// matrice de la transformation
	Matrix* t = allocNewMatrix();
	SetMatPoint(t, 0, 3, x);
	SetMatPoint(t, 1, 3, y);
	SetMatPoint(t, 2, 3, z);

	Matrix* newMat = allocNewMatrix();
	MatMulMat(obj->transf, t, newMat);

	Matrix* old = obj->transf;
	obj->transf = newMat;

	// matrice inverse
	Matrix* inv = allocNewMatrix();
	SetMatPoint(inv, 0, 3, -x);
	SetMatPoint(inv, 1, 3, -y);
	SetMatPoint(inv, 2, 3, -z);

	Matrix* newInv = allocNewMatrix();
	MatMulMat(inv, obj->inv, newInv);

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
	SetMatPoint(h, 0, 0, rx);
	SetMatPoint(h, 1, 1, ry);
	SetMatPoint(h, 2, 2, rz);

	Matrix* newMat = allocNewMatrix();
	MatMulMat(obj->transf, h, newMat);

	Matrix* old = obj->transf;
	obj->transf = newMat;

	// matrice inverse
	Matrix* inv = allocNewMatrix();
	SetMatPoint(inv, 0, 0, 1. / rx);
	SetMatPoint(inv, 1, 1, 1. / ry);
	SetMatPoint(inv, 2, 2, 1. / rz);

	Matrix* newInv = allocNewMatrix();
	MatMulMat(inv, obj->inv, newInv);

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
	SetMatPoint(rz, 0, 0, cos(theta));
	SetMatPoint(rz, 0, 1, sin(theta));
	SetMatPoint(rz, 1, 0, -sin(theta));
	SetMatPoint(rz, 1, 1, cos(theta));

	Matrix* newMat = allocNewMatrix();
	MatMulMat(obj->transf, rz, newMat);

	Matrix* old = obj->transf;
	obj->transf = newMat;

	// matrice inverse
	Matrix* inv = allocNewMatrix();
	SetMatPoint(inv, 0, 0, cos(-theta));
	SetMatPoint(inv, 0, 1, sin(-theta));
	SetMatPoint(inv, 1, 0, -sin(-theta));
	SetMatPoint(inv, 1, 1, cos(-theta));

	Matrix* newInv = allocNewMatrix();
	MatMulMat(inv, obj->inv, newInv);

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
	SetMatPoint(rx, 1, 1, cos(theta));
	SetMatPoint(rx, 1, 2, sin(theta));
	SetMatPoint(rx, 2, 1, -sin(theta));
	SetMatPoint(rx, 2, 2, cos(theta));

	Matrix* newMat = allocNewMatrix();
	MatMulMat(obj->transf, rx, newMat);

	Matrix* old = obj->transf;
	obj->transf = newMat;

	// matrice inverse
	Matrix* inv = allocNewMatrix();
	SetMatPoint(inv, 1, 1, cos(-theta));
	SetMatPoint(inv, 1, 2, sin(-theta));
	SetMatPoint(inv, 2, 1, -sin(-theta));
	SetMatPoint(inv, 2, 2, cos(-theta));

	Matrix* newInv = allocNewMatrix();
	MatMulMat(inv, obj->inv, newInv);

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
	SetMatPoint(ry, 0, 0, cos(theta));
	SetMatPoint(ry, 0, 2, sin(theta));
	SetMatPoint(ry, 2, 0, -sin(theta));
	SetMatPoint(ry, 2, 2, cos(theta));

	Matrix* newMat = allocNewMatrix();
	MatMulMat(obj->transf, ry, newMat);

	Matrix* old = obj->transf;
	obj->transf = newMat;

	// matrice inverse
	Matrix* inv = allocNewMatrix();
	SetMatPoint(inv, 0, 0, cos(-theta));
	SetMatPoint(inv, 0, 2, sin(-theta));
	SetMatPoint(inv, 2, 0, -sin(-theta));
	SetMatPoint(inv, 2, 2, cos(-theta));

	Matrix* newInv = allocNewMatrix();
	MatMulMat(inv, obj->inv, newInv);

	Matrix* oldInv = obj->inv;
	obj->inv = newInv;

	free(oldInv);
	free(inv);
	free(old);
	free(ry);
}

///////////////////
// OBJ CANONIQUE //
///////////////////

CSGTree* NewCSGTree(transformedObj* obj, int type, CSGTree* fg, CSGTree* fd) {
	CSGTree* tree = (CSGTree*) malloc(sizeof(CSGTree));
	tree->type = type;
	tree->obj = obj;
	tree->fg = fg;
	tree->fd = fd;
	return tree;
}

///////////////////////
// OBJ NON CANONIQUE //
///////////////////////

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

////////////////

void drawObj(transformedObj* obj) {
	int nb_vertices = obj->oc->nb_vertices;
	Point* res = NewPoint(0., 0., 0.);
	Point* p = NewPoint(0., 0., 0.);
	glColor3f(obj->color[0], obj->color[1], obj->color[2]);
	glBegin(GL_POINTS);
	for (int i = 0; i < nb_vertices; i = i + 10) {
		SetPoints(p, obj->oc->vertices[i][0], obj->oc->vertices[i][1],
				obj->oc->vertices[i][2]);
		MatMulPoint(obj->transf, p, res);
		glVertex3f(res->points[0], res->points[1], res->points[2]);
	}
	glEnd();
	free(res);
	free(p);
}

void drawUnion(CSGTree* fg, CSGTree* fd) {
	Point* p = NewPoint(0., 0., 0.);
	Point* res = NewPoint(0., 0., 0.);
	Point* resInv = NewPoint(0., 0., 0.);

	glColor3f(fg->obj->color[0], fg->obj->color[1], fg->obj->color[2]);
	glBegin(GL_POINTS);
	for (int i = 0; i < NB_VERTICES; i = i + 10) {
		SetPoints(p, fg->obj->oc->vertices[i][0], fg->obj->oc->vertices[i][1],
				fg->obj->oc->vertices[i][2]);
		MatMulPoint(fg->obj->transf, p, res);
		MatMulPoint(fd->obj->inv, res, resInv);
		if (!fd->obj->oc->isIn(resInv->points[0], resInv->points[1],
				resInv->points[2])) {
			glVertex3f(res->points[0], res->points[1], res->points[2]);
		}
	}
	glEnd();

	glColor3f(fd->obj->color[0], fd->obj->color[1], fd->obj->color[2]);
	glBegin(GL_POINTS);
	for (int i = 0; i < NB_VERTICES; i = i + 10) {
		SetPoints(p, fd->obj->oc->vertices[i][0], fd->obj->oc->vertices[i][1],
				fd->obj->oc->vertices[i][2]);
		MatMulPoint(fd->obj->transf, p, res);
		MatMulPoint(fg->obj->inv, res, resInv);
		if (!fg->obj->oc->isIn(resInv->points[0], resInv->points[1],
				resInv->points[2])) {
			glVertex3f(res->points[0], res->points[1], res->points[2]);
		}
	}
	glEnd();

	free(p);
	free(res);
	free(resInv);
}

void drawIntersection(CSGTree* fg, CSGTree* fd) {
	Point* p = NewPoint(0., 0., 0.);
	Point* res = NewPoint(0., 0., 0.);
	Point* resInv = NewPoint(0., 0., 0.);

	glColor3f(fg->obj->color[0], fg->obj->color[1], fg->obj->color[2]);
	glBegin(GL_POINTS);
	for (int i = 0; i < NB_VERTICES; i = i + 10) {
		SetPoints(p, fg->obj->oc->vertices[i][0], fg->obj->oc->vertices[i][1],
				fg->obj->oc->vertices[i][2]);
		MatMulPoint(fg->obj->transf, p, res);
		MatMulPoint(fd->obj->inv, res, resInv);
		if (fd->obj->oc->isIn(resInv->points[0], resInv->points[1],
				resInv->points[2])) {
			glVertex3f(res->points[0], res->points[1], res->points[2]);
		}
	}
	glEnd();

	glColor3f(fd->obj->color[0], fd->obj->color[1], fd->obj->color[2]);
	glBegin(GL_POINTS);
	for (int i = 0; i < NB_VERTICES; i = i + 10) {
		SetPoints(p, fd->obj->oc->vertices[i][0], fd->obj->oc->vertices[i][1],
				fd->obj->oc->vertices[i][2]);
		MatMulPoint(fd->obj->transf, p, res);
		MatMulPoint(fg->obj->inv, res, resInv);
		if (fg->obj->oc->isIn(resInv->points[0], resInv->points[1],
				resInv->points[2])) {
			glVertex3f(res->points[0], res->points[1], res->points[2]);
		}
	}
	glEnd();

	free(p);
	free(res);
	free(resInv);
}

void drawSoustraction(CSGTree* fg, CSGTree* fd) {
	Point* p = NewPoint(0., 0., 0.);
	Point* res = NewPoint(0., 0., 0.);
	Point* resInv = NewPoint(0., 0., 0.);

	glColor3f(fg->obj->color[0], fg->obj->color[1], fg->obj->color[2]);
	glBegin(GL_POINTS);
	for (int i = 0; i < NB_VERTICES; i = i + 10) {
		SetPoints(p, fg->obj->oc->vertices[i][0], fg->obj->oc->vertices[i][1],
				fg->obj->oc->vertices[i][2]);
		MatMulPoint(fg->obj->transf, p, res);
		MatMulPoint(fd->obj->inv, res, resInv);
		if (!fd->obj->oc->isIn(resInv->points[0], resInv->points[1],
				resInv->points[2])) {
			glVertex3f(res->points[0], res->points[1], res->points[2]);
		}
	}
	glEnd();

	glColor3f(fd->obj->color[0], fd->obj->color[1], fd->obj->color[2]);
	glBegin(GL_POINTS);
	for (int i = 0; i < NB_VERTICES; i = i + 10) {
		SetPoints(p, fd->obj->oc->vertices[i][0], fd->obj->oc->vertices[i][1],
				fd->obj->oc->vertices[i][2]);
		MatMulPoint(fd->obj->transf, p, res);
		MatMulPoint(fg->obj->inv, res, resInv);
		if (fg->obj->oc->isIn(resInv->points[0], resInv->points[1],
				resInv->points[2])) {
			glVertex3f(res->points[0], res->points[1], res->points[2]);
		}
	}
	glEnd();

	free(p);
	free(res);
	free(resInv);
}

void drawCSGTree(CSGTree* tree) {
	switch (tree->type) {
	case 0:
		break;
	case 1:
		drawUnion(tree->fg, tree->fd);
		break;
	case 2:
		drawIntersection(tree->fg, tree->fd);
		break;
	case 3:
		drawSoustraction(tree->fg, tree->fd);
		break;
	default:
		break;
	}
}

// GLUT FUNCTIONS //

void keyfonc(unsigned char key, int x, int y) {
	//printf("key: %c - x: %d - y: %d\n", key, x, y);

	float xrotrad, yrotrad;

	switch (key) {
	case 'q':
		yrotrad = getCameraYRot() * M_PI / 180;
		addCameraXPos(-cos(yrotrad) / 10.);
		addCameraZPos(-sin(yrotrad) / 10.);
		break;
	case 'd':
		yrotrad = getCameraYRot() * M_PI / 180;
		addCameraXPos(cos(yrotrad) / 10.);
		addCameraZPos(sin(yrotrad) / 10.);
		break;
	case 'z':
		yrotrad = getCameraYRot() * M_PI / 180;
		xrotrad = getCameraXRot() * M_PI / 180;
		addCameraXPos(sin(yrotrad) / 10.);
		addCameraZPos(-cos(yrotrad) / 10.);
		addCameraYPos(-sin(xrotrad) / 10.);
		break;
	case 's':
		yrotrad = getCameraYRot() * M_PI / 180;
		xrotrad = getCameraXRot() * M_PI / 180;
		addCameraXPos(-sin(yrotrad) / 10.);
		addCameraZPos(+cos(yrotrad) / 10.);
		addCameraYPos(+sin(xrotrad) / 10.);
		break;
	case 27:
		exit(0);
		break;
	}
}

void mouseMovementPassive(int x, int y) {
	updateMouseCoords(x, y);
}

void mouseMovement(int x, int y) {
	moveCameraMouse(x, y);
	updateMouseCoords(x, y);
}

void mouseFunction(int button, int state, int x, int y) {
	if (button != GLUT_LEFT_BUTTON) {
		return;
	}
	switch (state) {
	case GLUT_UP:
		mouseMovementPassive(x, y);
		break;
	case GLUT_DOWN:
		mouseMovement(x, y);
		break;
	default:
		return;
	}
}

void processSpecialKeys(int key, int xx, int yy) {
	switch (key) {
	case GLUT_KEY_LEFT:
		addCameraYRot(-2);
		break;
	case GLUT_KEY_RIGHT:
		addCameraYRot(2);
		break;
	case GLUT_KEY_UP:
		addCameraXRot(2);
		break;
	case GLUT_KEY_DOWN:
		addCameraXRot(-2);
		break;
	}
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluPerspective(60, 1, 0.1, 1000); // Render distance

	displayCamera();

	// Display all objects
	for (int i = 0; i < objectToDisplay.number; i++) {
		drawObj(objectToDisplay.objects[i]);
	}

	// Display all tree (combined objects)
	for (int i = 0; i < treeToDisplay.number; i++) {
		drawCSGTree(treeToDisplay.trees[i]);
	}

	glutSwapBuffers();
	addCameraZRot(1);
}

void setup() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void init() {
	objectToDisplay.number = 0;

	initTools();
	initCamera();
	initCanonicObjects();
}

void addObjectToDisplay(transformedObj *obj) {
	objectToDisplay.objects[objectToDisplay.number++] = obj;
}

void addTreeToDisplay(CSGTree *obj) {
	treeToDisplay.trees[treeToDisplay.number++] = obj;
}

int main(int argc, char* argv[]) {
	init();

// construction et transformation
	transformedObj* cylindre;
	transformedObj* tore;
	transformedObj* sphere;

// Cube canonique en (4,2)
	transformedObj* cubeCanonique1;
	cubeCanonique1 = Cube();
	AddTranslation(cubeCanonique1, 4., 2., 0.);
	addObjectToDisplay(cubeCanonique1);

// Cone canonique en (2,2)
	transformedObj* coneCanonique1;
	coneCanonique1 = Cone();
	AddTranslation(coneCanonique1, 2., 2., 0.);
	addObjectToDisplay(coneCanonique1);

	// Cone canonique penché en (0,2)
	transformedObj* coneCanonique2;
	coneCanonique2 = Cone();
	AddTranslation(coneCanonique2, 2., 2., 0.);
	AddRotationX(coneCanonique2, 60.);
	addObjectToDisplay(coneCanonique2);

	// Tore canonique en (-2,2)
	transformedObj* toreCanonique1;
	toreCanonique1 = Tore();
	AddTranslation(toreCanonique1, -2., 2., 0.);
	addObjectToDisplay(toreCanonique1);

//AddRotationZ(cubeCanonique1, 60.);
//AddRotationX(cube, 60.);
//AddHomo(cube, .5, .5, .5);

	tore = Tore();
	SetColor(tore, 1., 1., .0);
	AddTranslation(tore, 0., 0., 1.);
//AddRotationX(tore, 90.);
//AddHomo(tore, 1.3,1.3,1.3);

	coneCanonique1 = Cone();
	SetColor(coneCanonique1, 0., 1., 1.);
//AddRotationZ(cone, 60.);
//AddRotationY(cone, 30.);
	AddTranslation(coneCanonique1, 0., 0., -.5);

	sphere = Sphere();
	SetColor(sphere, .0, 1., .0);
	AddTranslation(sphere, 0., 0., -.5);
	AddHomo(sphere, .6, .6, .6);

	cylindre = Cylindre();
	SetColor(cylindre, .0, .0, 1.);

	CSGTree* tree = NewCSGTree(NULL, 1,
			NewCSGTree(cubeCanonique1, 0, NULL, NULL),
			NewCSGTree(tore, 0, NULL, NULL));
	CSGTree* tree2 = NewCSGTree(NULL, 2, NewCSGTree(sphere, 0, NULL, NULL),
			NewCSGTree(coneCanonique1, 0, NULL, NULL));
	CSGTree* tree3 = NewCSGTree(NULL, 3, NewCSGTree(cylindre, 0, NULL, NULL),
			NewCSGTree(sphere, 0, NULL, NULL));

	addTreeToDisplay(tree);
	addTreeToDisplay(tree2);
	addTreeToDisplay(tree3);

// glut
	glutInit(&argc, argv);
	glutInitWindowSize(640, 480);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

	glutCreateWindow("Project");
	glutFullScreen();

	setup();
	glutDisplayFunc(display);
	glutIdleFunc(display);

	glutPassiveMotionFunc(mouseMovementPassive);
	glutMotionFunc(mouseMovement);

	glutKeyboardFunc(keyfonc);
	glutSpecialFunc(processSpecialKeys);
	glEnable(GL_DEPTH_TEST);

	glutShowWindow();
	glutMainLoop();
}
