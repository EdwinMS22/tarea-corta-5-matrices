#pragma once

#include <iostream>
#include <stdexcept>

template <typename E>
class Matrix {
private:
	E** matrix;
	int rows;
	int cols;
public:
	Matrix(int rows, int cols) {
		if (rows <= 0 || cols <= 0)
			throw std::runtime_error("Number of rows and columns must be greater than zero.");
		this->rows = rows;
		this->cols = cols;
		matrix = new E*[rows];
		for (int i = 0; i < rows; i++)
			matrix[i] = new E[cols];
	}
	~Matrix() {
		for (int i = 0; i < rows; i++)
			delete[] matrix[i];
		delete[] matrix;
	}
};