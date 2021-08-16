#include "Matrix.h"

Matrix::Matrix(std::vector<std::vector <double>> value = { }) : value(value)
{
	if (value.size() != 0)
	{
		rows = value.size();
		columns = value[0].size();
		checkFormat();
	}
	else
	{
		rows = 0;
		columns = 0;
	}
}
int Matrix::checkFormat()
{
	for (int i = 0; i < value.size(); i++)
		if (value[i].size() != columns)
			throw "Not correct tenzor format";
	return 0;
}
void Matrix::print()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
			std::cout << value[i][j] << " ";
		std::cout << std::endl;
	}
}
void Matrix::transponation()
{
	Matrix res;
	int max = columns > rows ? columns : rows;
	increaseSize(max , max);
	for (int i = 0; i < columns; i++)
	{
		std::vector<double> resColumns;
		for (int j = 0; j < rows; j++)
			resColumns.push_back(value[j][i]);
		res.value.push_back(resColumns);
	}
	value = res.value;
	decreaseSize();
}
int Matrix::increaseSize(int newRows, int newColumns)
{
	if ((rows >= newRows && columns > newColumns) || (rows > newRows && columns >= newColumns))
		return 0;
	std::vector<std::vector<double>> res;
	for (int i = 0; i < newRows; i++)
	{
		std::vector<double> resColumns;
		for (int j = 0; j < newColumns; j++)
		{
			if (i >= rows || j >= columns)
				resColumns.push_back(0);
			else
				resColumns.push_back(value[i][j]);
		}
		res.push_back(resColumns);
	}
	rows = newRows;
	columns = newColumns;
	value = res;
	return 0;
}
void Matrix::findZeroRowsAndColumns(int& newColumns, int& newRows)
{
	bool flag = true;
	std::vector<double> zeroVectorColumns(columns, 0), zeroVectorRows(rows, 0);
	for (int i = 0; i < rows; i++)
	{
		if (flag = true && value[rows - 1 - i] == zeroVectorColumns)
			newRows--;
		else
			flag = false;
	}
	flag = true;
	for (int i = 0; i < columns; i++)
	{
		std::vector<double> vectorRows;
		for (int j = 0; j < rows; j++)
			vectorRows.push_back(value[j][columns - 1 - i]);
		if (flag = true && vectorRows == zeroVectorRows)
			newColumns--;
		else
			flag = false;
	}
}
void Matrix::decreaseSize()
{
	int newColumns = columns; int newRows = rows;
	findZeroRowsAndColumns(newColumns, newRows);
	std::vector <std::vector<double>> res;
	for (int i = 0; i < newRows; i++)
	{
		std::vector <double> resRow;
		for (int j = 0; j < newColumns; j++)
			resRow.push_back(value[i][j]);
		res.push_back(resRow);
	}
	value = res;
	columns = newColumns;
	rows = newRows;
}
Matrix Matrix::operator+(Matrix obj)
{
	Matrix res;
	int maxRows = rows > obj.rows ? rows : obj.rows;
	int maxColumns = columns > obj.columns ? columns : obj.columns;
	increaseSize(maxRows, maxColumns);
	obj.increaseSize(maxRows, maxColumns);
	for (int i = 0; i < maxRows; i++)
	{
		std::vector<double> resColumns;
		for (int j = 0; j < maxColumns; j++)
			resColumns.push_back(value[i][j] + obj.value[i][j]);
		res.value.push_back(resColumns);
	}
	res.columns = maxColumns;
	res.rows = maxRows;
	decreaseSize();
	obj.decreaseSize();
	return res;
}
Matrix Matrix::operator*(Matrix obj)
{
	Matrix res;
	if (columns != obj.rows)
		throw "Size of elements are not compatible";
	for (int i = 0; i < rows; i++)
	{
		std::vector<double> resColumns;
		for (int j = 0; j < obj.columns; j++)
		{
			int sum = 0;
			for (int k = 0; k < columns; k++)
				sum += value[i][k] * obj.value[k][j];
			resColumns.push_back(sum);
		}
		res.value.push_back(resColumns);
	}
	res.columns = obj.columns;
	res.rows = rows;
	return res;
}
Matrix Matrix::operator*(double obj)
{
	Matrix res;
	for (int i = 0; i < rows; i++)
	{
		std::vector<double> resColumns;
		for (int j = 0; j < columns; j++)
		{
			resColumns.push_back(obj * value[i][j]);
		}
		res.value.push_back(resColumns);
	}
	res.columns = columns;
	res.rows = rows;
	return res;
}