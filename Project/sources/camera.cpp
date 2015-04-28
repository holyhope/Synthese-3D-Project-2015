/*
 * camera.cpp
 *
 *  Created on: 28 avr. 2015
 *      Author: pperonne
 */

#include <GL/gl.h>
#include <camera.hpp>
#include <math.h>

static long int lastx, lasty;
static float xpos = 0., ypos = 0., zpos = 0.;
static float xrot = 0., yrot = 0., zrot = 0.;

void initCamera() {
	xpos = ypos = zpos = 0.;
	xrot = yrot = zrot = 0.;
}

void displayCamera() {
	glRotatef(xrot, 1.0, 0.0, 0.0);
	glRotatef(yrot, 0.0, 1.0, 0.0);
	glTranslated(-xpos, -ypos, -zpos);
}

void updateMouseCoords(int x, int y) {
	lastx = x;
	lasty = y;
}

void moveCameraMouse(int x, int y) {
	int diffx = x - lastx;
	int diffy = y - lasty;
	addCameraXRot(diffy / 5.);
	addCameraYRot(diffx / 5.);
}

void addCameraXPos(float x) {
	xpos += x;
}

void addCameraYPos(float y) {
	ypos += y;
}

void addCameraZPos(float z) {
	zpos += z;
}

void addCameraXRot(float x) {
	xrot = fmod(xrot + x + 360, 360);
}

void addCameraYRot(float y) {
	yrot = fmod(yrot + y + 360, 360);
}

void addCameraZRot(float z) {
	zrot = fmod(zrot + z + 360, 360);
}

float getCameraXPos() {
	return xpos;
}

float getCameraYPos() {
	return ypos;
}

float getCameraZPos() {
	return zpos;
}

float getCameraXRot() {
	return xrot;
}

float getCameraYRot() {
	return yrot;
}

float getCameraZRot() {
	return zrot;
}
