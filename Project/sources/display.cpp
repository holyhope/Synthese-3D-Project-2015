/*
 * display.cpp
 *
 *  Created on: 29 avr. 2015
 *      Author: pperonne
 */

#include <canonic.hpp>
#include <display.hpp>
#include <GL/gl.h>
#include <matrix.hpp>
#include <cstdio>

static volatile GLenum draw_mod = GL_POINTS;

static struct {
	TransformedObject *(objects[NUMBER_OBJECT_TO_DISPLAY]);
	int number;
} objectToDisplay;

static struct {
	CSGTree *(trees[NUMBER_OBJECT_TO_DISPLAY]);
	int number;
} treeToDisplay;

void addObjectToDisplay(TransformedObject *obj) {
	objectToDisplay.objects[objectToDisplay.number++] = obj;
}

void addTreeToDisplay(CSGTree *obj) {
	treeToDisplay.trees[treeToDisplay.number++] = obj;
}

void initDisplay() {
	objectToDisplay.number = 0;
}

void drawObject(TransformedObject* obj) {
	int nb_vertices = obj->oc->nb_vertices;
	Point* res = allocPoint(0., 0., 0.);
	Point* p = allocPoint(0., 0., 0.);

	glColor3f(obj->color[0], obj->color[1], obj->color[2]);
	glBegin(draw_mod);
	for (int i = 0; i < nb_vertices; i = i + 10) {
		setPoints(p, obj->oc->vertices[i][0], obj->oc->vertices[i][1],
				obj->oc->vertices[i][2]);
		matMulPoint(obj->transf, p, res);
		glVertex3f(res->points[0], res->points[1], res->points[2]);
	}
	glEnd();

	freePoint(res);
	freePoint(p);
}

void drawUnion(CSGTree* fg, CSGTree* fd) {
	Point* p = allocPoint(0., 0., 0.);
	Point* res = allocPoint(0., 0., 0.);
	Point* resInv = allocPoint(0., 0., 0.);

	glColor3f(fg->obj->color[0], fg->obj->color[1], fg->obj->color[2]);
	glBegin(draw_mod);
	for (int i = 0; i < NB_VERTICES; i = i + 10) {
		setPoints(p, fg->obj->oc->vertices[i][0], fg->obj->oc->vertices[i][1],
				fg->obj->oc->vertices[i][2]);
		matMulPoint(fg->obj->transf, p, res);
		matMulPoint(fd->obj->inv, res, resInv);
		if (!fd->obj->oc->isIn(resInv->points[0], resInv->points[1],
				resInv->points[2])) {
			glVertex3f(res->points[0], res->points[1], res->points[2]);
		}
	}
	glEnd();

	glColor3f(fd->obj->color[0], fd->obj->color[1], fd->obj->color[2]);
	glBegin(draw_mod);
	for (int i = 0; i < NB_VERTICES; i = i + 10) {
		setPoints(p, fd->obj->oc->vertices[i][0], fd->obj->oc->vertices[i][1],
				fd->obj->oc->vertices[i][2]);
		matMulPoint(fd->obj->transf, p, res);
		matMulPoint(fg->obj->inv, res, resInv);
		if (!fg->obj->oc->isIn(resInv->points[0], resInv->points[1],
				resInv->points[2])) {
			glVertex3f(res->points[0], res->points[1], res->points[2]);
		}
	}

	glEnd();

	freePoint(p);
	freePoint(res);
	freePoint(resInv);
}

void drawIntersect(CSGTree* fg, CSGTree* fd) {
	Point* p = allocPoint(0., 0., 0.);
	Point* res = allocPoint(0., 0., 0.);
	Point* resInv = allocPoint(0., 0., 0.);

	glColor3f(fg->obj->color[0], fg->obj->color[1], fg->obj->color[2]);
	glBegin(draw_mod);
	for (int i = 0; i < NB_VERTICES; i = i + 10) {
		setPoints(p, fg->obj->oc->vertices[i][0], fg->obj->oc->vertices[i][1],
				fg->obj->oc->vertices[i][2]);
		matMulPoint(fg->obj->transf, p, res);
		matMulPoint(fd->obj->inv, res, resInv);
		if (fd->obj->oc->isIn(resInv->points[0], resInv->points[1],
				resInv->points[2])) {
			glVertex3f(res->points[0], res->points[1], res->points[2]);
		}
	}
	glEnd();

	glColor3f(fd->obj->color[0], fd->obj->color[1], fd->obj->color[2]);
	glBegin(draw_mod);
	for (int i = 0; i < NB_VERTICES; i = i + 10) {
		setPoints(p, fd->obj->oc->vertices[i][0], fd->obj->oc->vertices[i][1],
				fd->obj->oc->vertices[i][2]);
		matMulPoint(fd->obj->transf, p, res);
		matMulPoint(fg->obj->inv, res, resInv);
		if (fg->obj->oc->isIn(resInv->points[0], resInv->points[1],
				resInv->points[2])) {
			glVertex3f(res->points[0], res->points[1], res->points[2]);
		}
	}
	glEnd();

	freePoint(p);
	freePoint(res);
	freePoint(resInv);
}

void drawSubstract(CSGTree* fg, CSGTree* fd) {
	Point* p = allocPoint(0., 0., 0.);
	Point* res = allocPoint(0., 0., 0.);
	Point* resInv = allocPoint(0., 0., 0.);

	glColor3f(fg->obj->color[0], fg->obj->color[1], fg->obj->color[2]);
	glBegin(draw_mod);
	for (int i = 0; i < NB_VERTICES; i = i + 10) {
		setPoints(p, fg->obj->oc->vertices[i][0], fg->obj->oc->vertices[i][1],
				fg->obj->oc->vertices[i][2]);
		matMulPoint(fg->obj->transf, p, res);
		matMulPoint(fd->obj->inv, res, resInv);
		if (!fd->obj->oc->isIn(resInv->points[0], resInv->points[1],
				resInv->points[2])) {
			glVertex3f(res->points[0], res->points[1], res->points[2]);
		}
	}
	glEnd();

	glColor3f(fd->obj->color[0], fd->obj->color[1], fd->obj->color[2]);
	glBegin(draw_mod);
	for (int i = 0; i < NB_VERTICES; i = i + 10) {
		setPoints(p, fd->obj->oc->vertices[i][0], fd->obj->oc->vertices[i][1],
				fd->obj->oc->vertices[i][2]);
		matMulPoint(fd->obj->transf, p, res);
		matMulPoint(fg->obj->inv, res, resInv);
		if (fg->obj->oc->isIn(resInv->points[0], resInv->points[1],
				resInv->points[2])) {
			glVertex3f(res->points[0], res->points[1], res->points[2]);
		}
	}
	glEnd();

	freePoint(p);
	freePoint(res);
	freePoint(resInv);
}

void drawCSGTree(CSGTree* tree) {
	switch (tree->type) {
	case NONE:
		drawObject(tree->obj);
		break;
	case UNION:
		drawUnion(tree->fg, tree->fd);
		break;
	case INTER:
		drawIntersect(tree->fg, tree->fd);
		break;
	case SUBSTRACT:
		drawSubstract(tree->fg, tree->fd);
		break;
	}
}

void changeDisplayMod() {
	switch (draw_mod) {
	case GL_POINTS:
		draw_mod = GL_POINT_SMOOTH;
		break;
	default:
		draw_mod = GL_POINTS;
	}
}

void displayAll() {
	// Display all objects
	for (int i = 0; i < objectToDisplay.number; i++) {
		drawObject(objectToDisplay.objects[i]);
	}

	// Display all tree (combined objects)
	for (int i = 0; i < treeToDisplay.number; i++) {
		drawCSGTree(treeToDisplay.trees[i]);
	}
}

/**

 typedef float Point3D[3];

 typedef struct {
 Point3D *points;
 int size;
 } displayPoints;

 bool isInTree(CSGTree *tree, float x, float y, float z) {
 Point *point;
 Point *result;
 switch (tree->type) {
 case NONE:
 point = allocPoint(x, y, z);
 result = allocPoint(0., 0., 0.);
 matMulPoint(tree->obj->transf, point, result);
 return tree->obj->oc->isIn(result->points[0], result->points[1],
 result->points[2]);
 case UNION:
 point = allocPoint(x, y, z);
 result = allocPoint(0., 0., 0.);
 matMulPoint(tree->fg->obj->transf, point, result);
 if (tree->fg->obj->oc->isIn(result->points[0], result->points[1],
 result->points[2])) {
 return true;
 }
 matMulPoint(tree->fd->obj->transf, point, result);
 return tree->fd->obj->oc->isIn(result->points[0], result->points[1],
 result->points[2]);
 case INTER:
 point = allocPoint(x, y, z);
 result = allocPoint(0., 0., 0.);
 matMulPoint(tree->fg->obj->transf, point, result);
 if (!tree->fg->obj->oc->isIn(result->points[0], result->points[1],
 result->points[2])) {
 return false;
 }
 matMulPoint(tree->fd->obj->transf, point, result);
 return tree->fd->obj->oc->isIn(result->points[0], result->points[1],
 result->points[2]);
 case SUBSTRACT:
 point = allocPoint(x, y, z);
 result = allocPoint(0., 0., 0.);
 matMulPoint(tree->fg->obj->transf, point, result);
 if (!tree->fg->obj->oc->isIn(result->points[0], result->points[1],
 result->points[2])) {
 return false;
 }
 matMulPoint(tree->fd->obj->transf, point, result);
 return !tree->fd->obj->oc->isIn(result->points[0], result->points[1],
 result->points[2]);
 }
 return false;
 }

 void freeDisplayablesPoints(displayPoints *points) {
 free(points->points);
 free(points);
 }

 displayPoints *allocDisplayablesPoints(CSGTree *tree) {
 displayPoints *points;
 displayPoints *points1;
 displayPoints *points2;
 int cursor = 0;
 switch (tree->type) {
 case NONE:
 points = (displayPoints*) malloc(sizeof(displayPoints));
 points->points = (Point3D*) malloc(sizeof(Point3D) * NB_VERTICES);
 points->size = NB_VERTICES;
 for (int i = 0; i < NB_VERTICES; i++) {
 points->points[i][0] = tree->obj->oc->vertices[i][0];
 points->points[i][1] = tree->obj->oc->vertices[i][1];
 points->points[i][2] = tree->obj->oc->vertices[i][2];
 }
 return points;
 case UNION:
 points1 = allocDisplayablesPoints(tree->fg);
 points2 = allocDisplayablesPoints(tree->fd);
 points = (displayPoints*) malloc(sizeof(displayPoints));
 points->points = (Point3D*) malloc(sizeof(Point3D) * NB_VERTICES);
 points->size = NB_VERTICES;
 for (int i = 0; i < NB_VERTICES; i++) {
 if (isInTree(tree, points1->points[i][0], points1->points[i][1],
 points1->points[i][2])) {
 if (cursor == points->size) {
 points->size *= 2;
 points->points = (Point3D*) realloc(points->points,
 sizeof(Point3D) * points->size);
 }
 points->points[cursor][0] = points1->points[i][0];
 points->points[cursor][1] = points1->points[i][1];
 points->points[cursor++][2] = points1->points[i][2];
 }
 }
 for (int i = 0; i < NB_VERTICES; i++) {
 if (isInTree(tree, points2->points[i][0], points2->points[i][1],
 points2->points[i][2])) {
 if (cursor == points->size) {
 points->size *= 2;
 points->points = (Point3D*) realloc(points->points,
 sizeof(Point3D) * points->size);
 }
 points->points[cursor][0] = points1->points[i][0];
 points->points[cursor][1] = points1->points[i][1];
 points->points[cursor++][2] = points1->points[i][2];
 }
 }
 points->points = (Point3D*) realloc(points->points,
 sizeof(Point3D) * cursor);
 points->size = cursor;
 freeDisplayablesPoints(points2);
 freeDisplayablesPoints(points1);
 return points;
 case INTER:
 points1 = allocDisplayablesPoints(tree->fg);
 points2 = allocDisplayablesPoints(tree->fd);
 points = (displayPoints*) malloc(sizeof(displayPoints));
 points->points = (Point3D*) malloc(sizeof(Point3D) * NB_VERTICES);
 points->size = NB_VERTICES;
 for (int i = 0; i < NB_VERTICES; i++) {
 if (isInTree(tree->fd, points1->points[i][0], points1->points[i][1],
 points1->points[i][2])) {
 if (cursor == points->size) {
 points->size *= 2;
 points->points = (Point3D*) realloc(points->points,
 sizeof(Point3D) * points->size);
 }
 points->points[cursor][0] = points1->points[i][0];
 points->points[cursor][1] = points1->points[i][1];
 points->points[cursor++][2] = points1->points[i][2];
 }
 }
 for (int i = 0; i < NB_VERTICES; i++) {
 if (isInTree(tree->fg, points2->points[i][0], points2->points[i][1],
 points2->points[i][2])) {
 if (cursor == points->size) {
 points->size *= 2;
 points->points = (Point3D*) realloc(points->points,
 sizeof(Point3D) * points->size);
 }
 points->points[cursor][0] = points2->points[i][0];
 points->points[cursor][1] = points2->points[i][1];
 points->points[cursor++][2] = points2->points[i][2];
 }
 }
 points->points = (Point3D*) realloc(points->points,
 sizeof(Point3D) * cursor);
 points->size = cursor;
 freeDisplayablesPoints(points2);
 freeDisplayablesPoints(points1);
 return points;
 case SUBSTRACT:
 displayPoints *points1 = allocDisplayablesPoints(tree->fg);
 displayPoints *points2 = allocDisplayablesPoints(tree->fd);
 displayPoints *points = (displayPoints*) malloc(sizeof(displayPoints));
 points->points = (Point3D*) malloc(sizeof(Point3D) * NB_VERTICES);
 points->size = NB_VERTICES;
 for (int i = 0; i < NB_VERTICES; i++) {
 if (!isInTree(tree->fd, points1->points[i][0],
 points1->points[i][1], points1->points[i][2])) {
 if (cursor == points->size) {
 points->size *= 2;
 points->points = (Point3D*) realloc(points->points,
 sizeof(Point3D) * points->size);
 }
 points->points[cursor][0] = points1->points[i][0];
 points->points[cursor][1] = points1->points[i][1];
 points->points[cursor++][2] = points1->points[i][2];
 }
 }
 points->points = (Point3D*) realloc(points->points,
 sizeof(Point3D) * cursor);
 points->size = cursor;
 freeDisplayablesPoints(points2);
 freeDisplayablesPoints(points1);
 return points;
 }
 }
 **/
