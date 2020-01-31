#include "triangletest.h"
#include <fstream>

TriangleTest::TriangleTest(std::string fileName)
{
	int side1 = 0, side2 = 0, side3 = 0;

	std::ifstream ifs;
	ifs.open(fileName, std::ifstream::in);
	side1 = getSide(ifs);
	side2 = getSide(ifs);
	side3 = getSide(ifs);

	if(side1 == side2 && side2 == side3)
	{
		std::cout << "Triangle is equilateral" << std::endl;
	}
	else if (side1 == side2 || side1 == side3 || side2 == side3)
	{
		std::cout << "Triangle is isosceles" << std::endl;
	}
	else
	{
		std::cout << "Triangle is scalene" << std::endl;
	}
}

TriangleTest::TriangleTest()
{
	int side1 = 0, side2 = 0, side3 = 0;

	side1 = getSide(std::cin);
	side2 = getSide(std::cin);
	side3 = getSide(std::cin);

	if(side1 == side2 && side2 == side3)
	{
		std::cout << "Triangle is equilateral" << std::endl;
	}
	else if (side1 == side2 || side1 == side3 || side2 == side3)
	{
		std::cout << "Triangle is isosceles" << std::endl;
	}
	else
	{
		std::cout << "Triangle is scalene" << std::endl;
	}
}

int TriangleTest::getSide(std::istream& input)
{
	int side = 0;
	int i = 0;
	std::cout << "Enter a postive integer" << std::endl;
	while(i < 3){
		if(!(input >> side)){
			std::cout << side << std::endl;
			input.clear();
			input.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
		}
		if(side > 0){
			input.clear();
			input.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
			return side;
		}
		else{
			std::cout << "Bad input try again" << std::endl;
		}
		i++;
	}
	throw std::string("Too many bad inputs, quitting");
}
