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
			matrix[i] = new E[cols]();
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
		return rows;
	}
	int getColumns() {
		return cols;
	}
	void setAll(E value) {
		for (int r = 0; r < rows; r++)
			for (int c = 0; c < cols; c++)
				matrix[r][c] = value;
	}
	void transpose() {
		Matrix<E> temp(cols, rows);
		for (int r = 0; r < rows; r++)
			for (int c = 0; c < cols; c++)
				temp.setValue(c, r, matrix[r][c]);

		for (int i = 0; i < rows; i++)
			delete[] matrix[i];
		delete[] matrix;

		rows = temp.getRows();
		cols = temp.getColumns();
		matrix = new E*[rows];
		for (int i = 0; i < rows; i++)
			matrix[i] = new E[cols];

		for (int r = 0; r < rows; r++)
			for (int c = 0; c < cols; c++)
				matrix[r][c] = temp.getValue(r, c);
	}
	void addRow(E value) {
		E** temp = new E*[rows + 1];
		for (int i = 0; i < rows; i++)
			temp[i] = matrix[i];

		temp[rows] = new E[cols];
		for (int c = 0; c < cols; c++)
			temp[rows][c] = value;

		delete[] matrix;
		matrix = temp;
		rows++;
	}
	void addColumn(E value) {
		for (int r = 0; r < rows; r++) {
			E* temp = new E[cols + 1];
			for (int c = 0; c < cols; c++) {
				temp[c] = matrix[r][c];
			}
			temp[cols] = value;
			delete[] matrix[r];
			matrix[r] = temp;
		}
		cols++;
	}
	void removeRow(int row) {
		if (row < 0 || row >= rows)
			throw std::runtime_error("Invalid row.");
		E** temp = new E*[rows - 1];
		for (int i = 0; i < row; i++)
			temp[i] = matrix[i];
		for (int i = row; i < rows - 1; i++)
			temp[i] = matrix[i + 1];

		delete[] matrix[row];
		delete[] matrix;
		matrix = temp;
		rows--;
	}
	void removeColumn(int col) {
		if (col < 0 || col >= cols)
			throw std::runtime_error("Invalid column.");
		for (int r = 0; r < rows; r++) {
			E* temp = new E[cols - 1];
			for (int c = 0; c < col; c++)
				temp[c] = matrix[r][c];
			for (int c = col; c < cols - 1; c++)
				temp[c] = matrix[r][c + 1];
			delete[] matrix[r];
			matrix[r] = temp;
		}
		cols--;
	}
	void print() {

	}
};