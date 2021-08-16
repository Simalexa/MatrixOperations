#include "Matrix.h"
#include "Equation.h"

int main()
{
    try
    {
	equation e;
	std::string config, input;
	std::cout<<"Configurations file:";
    std::cin >> config;
	std::cout<<"Input file:";
    std::cin >> input;
        e.calculate(config , input);
    }
    catch (const char* msg)
    {
        std::cout << msg;
        return -1;
    }
    return 0;
}
