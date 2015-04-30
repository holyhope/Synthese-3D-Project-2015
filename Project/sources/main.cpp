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
	case GLUT_KEY_F1:
		changeDisplayMod();
		break;
	}
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluPerspective(60, 1, 0.1, 1000); // Render distance

	displayCamera();

	displayAll();

	glutSwapBuffers();
	addCameraZRot(1);
}

void setup() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void init() {
	initTools();
	initCamera();
	initDisplay();
	initCanonicObjects();

	addCameraZPos(8);
}

void createCanonicShapes() {
	TransformedObject *object1;

	// Cube canonique en (4,2)
	object1 = Cube();
	addTranslation(object1, 4, 0, 0);
	addObjectToDisplay(object1);

	// Cone canonique en (2,2)
	object1 = Cone();
	addTranslation(object1, 2, 0, 0);
	addObjectToDisplay(object1);
	addRotationX(object1, M_PI / 2);

	// Tore canonique en (-2,2)
	object1 = Sphere();
	addTranslation(object1, 0, 0, 0);
	addObjectToDisplay(object1);

	// Tore canonique en (-2,2)
	object1 = Tore();
	addTranslation(object1, -2, 0, 0);
	addObjectToDisplay(object1);

	// Tore canonique en (-4,2)
	object1 = Cylindre();
	addTranslation(object1, -4, 0, 0);
	addObjectToDisplay(object1);
}

void createComposedShapesTmp(TreeType type, float y) {
	TransformedObject *object1;
	TransformedObject *object2;
	CSGTree* tree;

	//*******************************//

	object1 = Cube();
	addTranslation(object1, 5, y, 0);
	addHomothety(object1, 3, 1, 1);
	setColor(object1, 1, 0, 0);

	object2 = Cylindre();
	setColor(object2, 0, 0, 1);
	addTranslation(object2, 5, y, 0);
	addHomothety(object2, 1, 2, .9);

	tree = allocCSGTree(NULL, type, allocCSGTree(object1, NONE, NULL, NULL),
			allocCSGTree(object2, NONE, NULL, NULL));

	addTreeToDisplay(tree);

	//*******************************//

	object1 = Cube();
	addTranslation(object1, 2, y, 0);
	setColor(object1, 1, 0, 1);

	object2 = Sphere();
	setColor(object2, 1, 1, 0);
	addTranslation(object2, 2, y - 1, 0);

	tree = allocCSGTree(NULL, type, allocCSGTree(object1, NONE, NULL, NULL),
			allocCSGTree(object2, NONE, NULL, NULL));

	addTreeToDisplay(tree);

	//*******************************//

	object1 = Tore();
	addTranslation(object1, 0, y, 0);
	setColor(object1, 1, 0, 1);
	addRotationZ(object1, M_PI / 2);

	object2 = Sphere();
	setColor(object2, 0, 0, 1);
	addTranslation(object2, 0, y, 0);
	addHomothety(object2, .7, .4, .7);

	tree = allocCSGTree(NULL, type, allocCSGTree(object1, NONE, NULL, NULL),
			allocCSGTree(object2, NONE, NULL, NULL));

	addTreeToDisplay(tree);

	//*******************************//

	object1 = Tore();
	addTranslation(object1, -2, y, 0);
	addRotationZ(object1, M_PI / 2);

	object2 = Tore();
	addTranslation(object2, -2, y, 0);
	addRotationY(object2, M_PI / 2);

	tree = allocCSGTree(NULL, type, allocCSGTree(object1, NONE, NULL, NULL),
			allocCSGTree(object2, NONE, NULL, NULL));

	addTreeToDisplay(tree);

	//*******************************//

	object1 = Tore();
	addTranslation(object1, -2, y, 0);
	addRotationZ(object1, M_PI / 2);

	object2 = Tore();
	addTranslation(object2, -2, y, 0);
	addRotationY(object2, M_PI / 2);

	tree = allocCSGTree(NULL, type, allocCSGTree(object1, NONE, NULL, NULL),
			allocCSGTree(object2, NONE, NULL, NULL));

	addTreeToDisplay(tree);

	//*******************************//

	object1 = Cube();
	addTranslation(object1, -4, y, 0);
	addRotationX(object1, M_PI / 4);
	addRotationZ(object1, M_PI / 4);

	object2 = Tore();
	addTranslation(object2, -4, y, 0);

	tree = allocCSGTree(NULL, type, allocCSGTree(object1, NONE, NULL, NULL),
			allocCSGTree(object2, NONE, NULL, NULL));

	addTreeToDisplay(tree);
}

void createComposedShapes() {
	static const float step = 2;
	float y = 0;
	createComposedShapesTmp(UNION, y -= step);
	createComposedShapesTmp(INTER, y -= step);
	createComposedShapesTmp(SUBSTRACT, y -= step);
}

int main(int argc, char* argv[]) {
	init();

	// construction et transformation
	createCanonicShapes();
	createComposedShapes();

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
