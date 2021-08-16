#include "Equation.h"

equation::equation()
{
}
Matrix* equation::sum(struct Matrix* T1, struct Matrix* T2)
{
	Matrix* res = new Matrix({});
	*res = *T1 + *T2;
	return res;
}
Matrix* equation::minus(struct Matrix* T1, struct Matrix* T2)
{
	Matrix* res = new Matrix({});
	T2 = dot(T2 , -1);
	*res = *T1 + *T2;
	return res;
}
void equation::print(struct Matrix* res)
{
	res->print();
}
Matrix* equation::dot(struct Matrix* T1, struct Matrix* T2)
{
	Matrix* res = new Matrix({});
	if (T1->columns == 1 && T2->columns == 1)
		T1 = transponation(T1);
	*res = *T1 * *T2;
	return res;
}
Matrix* equation::dot(struct Matrix* T1, double T2)
{
	Matrix* res = new Matrix({});
	*res = *T1 * T2;
	return res;
}
Matrix* equation::transponation(struct Matrix* T1)
{
	Matrix* res = new Matrix({});
	*res = *T1;
	res->transponation();
	return res;
}
void equation::analyzeConfigFile(std::string s, std::string input)
{
	char const* operators = "+*-";
	s.erase(remove(s.begin(), s.end(), ' '), s.end());
	int n = s.find_first_of(operators);
	while (n != -1)
	{
		std::string newOperand = "";
		for (int i = 0;i < n;i++) newOperand += s[i];
		if(newOperand == "x") newOperand = input;
		op_name.push_back(s[n]);
		var_name.push_back(newOperand);
		s.erase(s.begin(), s.begin() + n + 1);
		n = s.find_first_of(operators);
	}
	std::string newOperand = "";
	for (int i = 0;i < s.size();i++) newOperand += s[i];
	var_name.push_back(newOperand);
}
std::vector<double> equation::analyzeDatFile(std::string newRow)
{
	std::vector<double> row;
	std::string number = "";
	for (int i = 0; i < newRow.size(); i++)
	{
		number += newRow[i];
		if (newRow[i] == ' ' || i == newRow.size() - 1)
		{
			row.push_back(std::stod(number));
			number = "";
		}
	}
	return row;

}
Matrix* equation::getValueFromfile(std::string fileName)
{
	Matrix* res = new Matrix({});
	std::ifstream file;
	std::string newRow;
	file.open("DatFiles/"+fileName);
	if (!file.is_open())
		throw "one of the elements is not exists";
	while (getline(file, newRow))
	{
		res->value.push_back(analyzeDatFile(newRow));
		res->rows++;
		res->columns = analyzeDatFile(newRow).size();
	}
	file.close();
	return res;
}
Matrix* equation::doOperation(struct Matrix* T1, char op_name, struct Matrix* T2)
{
	if (op_name == '*')
		return dot(T1, T2);
	if (op_name == '-')
		return minus(T1, T2);
	if (op_name == '+')
		return sum(T1, T2);
	return T1;
}
std::string equation::readConfiguration(std::string config)
{
	std::ifstream file;
	file.open(config);
	if (!file.is_open())
		throw "configuration is not exists";
	std::string newRow;
	getline(file, newRow);
	return newRow;
}
Matrix* equation::calculate(std::string config, std::string input)
{
	Matrix* res = new Matrix({});
	std::string conf = readConfiguration(config);
	analyzeConfigFile(conf, input);
	res = getValueFromfile(var_name[0]);
	for (int i = 0; i < var_name.size() - 1; i++)
		res = doOperation(res,op_name[i], getValueFromfile(var_name[i + 1]));
	printInFile(res);
	return res;
}
void equation::printInFile(struct Matrix* res)
{
	std::ofstream file;
	file.open("output.dat");
	if (!file.is_open())
		throw "file output is not exists";
	file.clear();
	for (int i = 0;i < res->rows;i++)
	{
		for (int j = 0;j < res->columns;j++)
			file << res->value[i][j]<<" ";
		file << "\n";
	}
}
