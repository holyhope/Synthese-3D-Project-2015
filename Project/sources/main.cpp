#include <advanced.hpp>
#include <camera.hpp>
#include <canonic.hpp>
#include <display.hpp>
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <tools.hpp>
#include <cstdlib>

void keyfonc(unsigned char key, int x, int y) {
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
