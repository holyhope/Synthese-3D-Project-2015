/*
 * display.hpp
 *
 *  Created on: 29 avr. 2015
 *      Author: pperonne
 */

#ifndef DISPLAY_HPP_
#define DISPLAY_HPP_

#include <advanced.hpp>

#define NUMBER_OBJECT_TO_DISPLAY 50

void addObjectToDisplay(transformedObj *obj);
void addTreeToDisplay(CSGTree *obj);

void drawObj(transformedObj* obj);
void drawUnion(CSGTree* fg, CSGTree* fd);
void drawIntersection(CSGTree* fg, CSGTree* fd);
void drawSoustraction(CSGTree* fg, CSGTree* fd);
void drawCSGTree(CSGTree* tree);

void displayAll();
void initDisplay();

#endif /* DISPLAY_HPP_ */
