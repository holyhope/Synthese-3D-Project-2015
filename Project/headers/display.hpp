/*
 * display.hpp
 *
 *  Created on: 29 avr. 2015
 *      Author: pperonne
 */

#ifndef DISPLAY_HPP_
#define DISPLAY_HPP_

#define NUMBER_OBJECT 50

static struct {
	transformedObj *(objects[NUMBER_OBJECT]);
	int number;
} objectToDisplay;

static struct {
	CSGTree *(trees[NUMBER_OBJECT]);
	int number;
} treeToDisplay;

void drawObj(transformedObj* obj);
void drawUnion(CSGTree* fg, CSGTree* fd);
void drawIntersection(CSGTree* fg, CSGTree* fd);
void drawSoustraction(CSGTree* fg, CSGTree* fd);
void drawCSGTree(CSGTree* tree);

#endif /* DISPLAY_HPP_ */
