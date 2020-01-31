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
	try{
		if(argv[2]){
			std::string fileName = "scalene.txt";
			TriangleTest a = TriangleTest(fileName);
			fileName = "isosceles.txt";
			a = TriangleTest(fileName);
			fileName = "equilateral.txt";
			a = TriangleTest(fileName);
			fileName = "BadFile";
			a = TriangleTest(fileName);

		} else if(argv[1]){
			// Test catching some exception(Will not reach this test, move to top of try statement)
			throw "error";
		} else{
			TriangleTest a = TriangleTest();
		}

	} catch(std::string p){
		std::cout << p << std::endl;
		exit(EXIT_SUCCESS);
	} catch(...){
		std::cout << "Some exception caught" << std::endl;
		exit(EXIT_FAILURE);
	}
}
