#pragma once

#include <iostream>
#include <stdexcept>

template <typename E>
class Matrix {
private:
	E** matrix;
	int rows;
	int cols;

	void checkRowColumn(int row, int col) {
		if (row < 0 || row >= rows)
			throw std::runtime_error("Invalid row.");
		if (col < 0 || col >= cols)
			throw std::runtime_error("Invalid column.");
	}

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
	E getValue(int row, int col) {
		checkRowColumn(row, col);
		return matrix[row][col];
	}
	void setValue(int row, int col, E value) {
		checkRowColumn(row, col);
		matrix[row][col] = value;
	}
	int getRows() {

	}
	int getColumns() {

	}
	void setAll(E value) {

	}
	void transpose() {

	}
	void addRow(E value) {

	}
	void addColumn(E value) {

	}
	void removeRow(int row) {

	}
	void removeColumn(int col) {

	}
	void print() {

	}
};