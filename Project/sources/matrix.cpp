/*
 * matrix.cpp
 *
 *  Created on: 28 avr. 2015
 *      Author: pperonne
 */

#include <matrix.hpp>
#include <stdlib.h>

Matrix* allocNewMatrix() {
	Matrix* mat = (Matrix*) malloc(sizeof(Matrix));
	mat->size = MAT_SIZE;
	for (int i = 0; i < mat->size; i++) {
		for (int j = 0; j < mat->size; j++) {
			if (i == j) {
				mat->points[i][j] = 1.;
			} else {
				mat->points[i][j] = 0.;
			}
		}
	}
	return mat;
}

void freeNewMatrix(Matrix *matrix) {
	free(matrix);
}

Point* allocPoint(float x, float y, float z) {
	Point* p = (Point*) malloc(sizeof(Point));
	p->points[0] = x;
	p->points[1] = y;
	p->points[2] = z;
	p->points[3] = 1.;
	return p;
}

void setPoints(Point* p, float x, float y, float z) {
	p->points[0] = x;
	p->points[1] = y;
	p->points[2] = z;
}

void setMatPoint(Matrix* mat, int row, int col, float val) {
	mat->points[row][col] = val;
}

void matMulPoint(Matrix* mat, Point* p, Point* res) {
	for (int i = 0; i < mat->size; i++) {
		res->points[i] = 0.;
		for (int j = 0; j < mat->size; j++) {
			res->points[i] += mat->points[i][j] * p->points[j];
		}
	}
}

void matMulMat(Matrix* mat, Matrix* mat2, Matrix* res) {
	float sum = 0;
	for (int i = 0; i < mat->size; i++) {
		for (int j = 0; j < mat->size; j++) {
			for (int k = 0; k < mat->size; k++) {
				sum += mat->points[i][k] * mat2->points[k][j];
			}
			res->points[i][j] = sum;
			sum = 0;
		}
	}
}
