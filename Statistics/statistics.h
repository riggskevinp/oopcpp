#ifndef STATISTICS_H
#define STATISTICS_H

#include <vector>

class Statistics
{
public:
	Statistics(); //Constructor: initialize private data

	void add(double x); // add an item to the statistis

	void removeItem(int index);// remove an item

	double getItem(int index) const; // get the value of an individual item

	double getAverage() const; // get average
	// calculate average

	double getSTD() const; // get Standard deviation: using the hint
	// calculate average

	int getItemCount() const; // get number of items

private:
	// private member data
	int itemCount;
	double average;
	double runningTotal;
	double STD;
	std::vector<double> items;

};

#endif // STATISTICS_H
