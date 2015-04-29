/*
 * display.cpp
 *
 *  Created on: 29 avr. 2015
 *      Author: pperonne
 */

#include <advanced.hpp>
#include <canonic.hpp>
#include <GL/gl.h>
#include <matrix.hpp>
#include <stdlib.h>

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
