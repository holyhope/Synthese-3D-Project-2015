/*
 * matrix.hpp
 *
 *  Created on: 28 avr. 2015
 *      Author: pperonne
 */

#ifndef MATRIX_HPP_
#define MATRIX_HPP_

#define MAT_SIZE 4

typedef struct  {
	int size;
	float points[MAT_SIZE][MAT_SIZE];
} Matrix;

typedef struct {
	float points[4];
} Point;

Matrix* allocNewMatrix();
void freeNewMatrix(Matrix*);

Point* allocPoint(float x, float y, float z);
void freePoint(Point *point);

void setPoints(Point* p, float x, float y, float z);
void setMatPoint(Matrix* mat, int row, int col, float val);
void matMulPoint(Matrix* mat, Point* p, Point* res);
void matMulMat(Matrix* mat, Matrix* mat2, Matrix* res);

#endif /* MATRIX_HPP_ */
