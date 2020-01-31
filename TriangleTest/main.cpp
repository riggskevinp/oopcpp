//#include <QCoreApplication>
#include <iostream>
#include <ios>
#include <limits>
#include "triangletest.h"
#include <string>


int main(int argc, char *argv[])
{
	//QCoreApplication a(argc, argv);
	//return a.exec();
	std::string fileName = "scalene.txt";
	TriangleTest a = TriangleTest(fileName);
	fileName = "isosceles.txt";
	a = TriangleTest(fileName);
	fileName = "equilateral.txt";
	a = TriangleTest(fileName);
	fileName = "BadFile";
	a = TriangleTest(fileName);
}
