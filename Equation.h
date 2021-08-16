#ifndef EQUATION_H
#define EQUATION_H
#include "Matrix.h"
#include <fstream>
#include <algorithm>
#include <iostream>

class equation
{
public:
	equation();
	void print(struct Matrix* res);
	Matrix *sum(struct Matrix* T1, struct Matrix* T2);
	Matrix *minus(struct Matrix* T1, struct Matrix* T2);
	Matrix *dot(struct Matrix* T1, struct Matrix* T2);
	Matrix* dot(struct Matrix* T1, double T2);
	Matrix* getValueFromfile(std::string fileName);
	Matrix *transponation(struct Matrix* T1);
	Matrix* calculate(std::string config, std::string input);
private:
	Matrix* doOperation(struct Matrix* T1, char op_name, struct Matrix* T2);
	std::vector<double> analyzeDatFile(std::string newRow);
	std::string readConfiguration(std::string config);
	void printInFile(struct Matrix* res);
	void analyzeConfigFile(std::string s, std::string input);
	std::vector<char> op_name;
	std::vector<std::string> var_name;
};

#endif
