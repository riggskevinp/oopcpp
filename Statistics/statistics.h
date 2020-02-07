#ifndef STATISTICS_H
#define STATISTICS_H

#include <vector>
#include <iostream>


/*
* Statistics Class
* 	Class accepts a double as an input
* 	Stores that double and will return
* 	the average and standard deviation
* 	of the doubles.
*/

class Statistics
{
public:
	//Constructor: initialize private data
	Statistics(); 

	// add an item to the statistis
	void add(double x); 

	// get the value of an individual item
	double getItem(int index) const; 

	// set the value
	void setItem(int index, double x); 

	// get average
	double getAverage() const; 

	// get Standard deviation: using the hint
	double getSTD() const; 

	// get number of items
	int getItemCount() const; 

private:
	// count containing the number of items
	int itemCount;
	// holds all entered items
	std::vector<double> items;

};

#endif // STATISTICS_H
