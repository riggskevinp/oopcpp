#ifndef STATISTICS_H
#define STATISTICS_H

#include <vector>

class Statistics
{
public:
	Statistics(); //Constructor: initialize private data

	void add(double x); // add an item to the statistis

	double getItem(int index) const; // get the value of an individual item

	void setItem(int index, double x); // set the value

	double getAverage() const; // get average
	// calculate average

	double getSTD() const; // get Standard deviation: using the hint
	// calculate average

	int getItemCount() const; // get number of items

private:
	// private member data
	int itemCount;
	std::vector<double> items;

};

#endif // STATISTICS_H
