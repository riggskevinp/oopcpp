#ifndef TRIANGLETEST_H
#define TRIANGLETEST_H
#include <iostream>
#include <ios>
#include <limits>
#include <string>

class TriangleTest
{
public:
	TriangleTest(std::string fileName);
	TriangleTest();
	int getSide(std::istream& input);
};

#endif // TRIANGLETEST_H
