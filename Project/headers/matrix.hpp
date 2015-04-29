/*
 * matrix.hpp
 *
 *  Created on: 28 avr. 2015
 *      Author: pperonne
 */

#ifndef MATRIX_HPP_
#define MATRIX_HPP_

const static int MAT_SIZE = 4;

struct Matrix {
	int size;
	float points[MAT_SIZE][MAT_SIZE];
};

struct Point {
	float points[4];
};

Matrix* allocNewMatrix();
void freeNewMatrix(Matrix*);

Point* allocPoint(float x, float y, float z);
void setPoints(Point* p, float x, float y, float z);
void setMatPoint(Matrix* mat, int row, int col, float val);
void matMulPoint(Matrix* mat, Point* p, Point* res);
void matMulMat(Matrix* mat, Matrix* mat2, Matrix* res);

#endif /* MATRIX_HPP_ */
