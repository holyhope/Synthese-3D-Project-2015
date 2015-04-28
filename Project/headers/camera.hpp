/*
 * camera.hpp
 *
 *  Created on: 28 avr. 2015
 *      Author: pperonne
 */

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

void initCamera();
void displayCamera();
void updateMouseCoords(int x, int y);
void moveCameraMouse(int x, int y);

void addCameraXPos(float x);
void addCameraYPos(float y);
void addCameraZPos(float z);
void addCameraXRot(float x);
void addCameraYRot(float y);
void addCameraZRot(float z);

float getCameraXPos();
float getCameraYPos();
float getCameraZPos();
float getCameraXRot();
float getCameraYRot();
float getCameraZRot();

#endif /* CAMERA_HPP_ */
