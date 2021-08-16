#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <iostream>
#include <stdexcept>
#include <limits>
#include <string>

struct Matrix
{
	Matrix(std::vector<std::vector <double>> value);
	friend class equation;
	void print();
	void transponation();
	Matrix operator+(Matrix obj);
	Matrix operator*(Matrix obj);
	Matrix operator*(double obj);
private:
	int checkFormat();
	int increaseSize(int newRows, int newColumns);
	void decreaseSize();
	void findZeroRowsAndColumns(int& newColumns, int& newRows);
protected:
	int rows = 0;
	int columns = 0;
	std::vector<std::vector <double>> value;
};

#endif
