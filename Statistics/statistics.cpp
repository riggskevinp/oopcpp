#include "statistics.h"
#include <math.h>

//Constructor:
Statistics::Statistics() :
	itemCount{0}
{

}
// Adds a double to the existing doubles
void Statistics::add(double x)
{
	this->items.push_back(x);
	this->itemCount++;
}

// Returns the value of an entered item based on the index
double Statistics::getItem(int index) const
{
	try {
		if(items.size() > index){
			return this->items[index];
		} else {
			return 0;
		}

	} catch (...) {
		return 0;
	}

}

// Modifies an existing item
void Statistics::setItem(int index, double x)
{
	items[index] = x;
}

// Returns the average of the doubles
double Statistics::getAverage() const
{
	double total = 0;
	for(double x : items){
		total += x;
	}
	return items.empty() ? 0 : total / items.size();
}

// returns the standard deviation of the doubles
double Statistics::getSTD() const
{
	if(items.empty()){
		return 0.0;
	} else {
		double x2 = 0;
		double average = getAverage();
		for(double x : items){
			x2 += x*x;
		}
		double s2 = (x2 - items.size() * pow(average, 2)) / (items.size() - 1);
		return sqrt(s2);
	}
}

// Returns the number of doubles entered
int Statistics::getItemCount() const
{
	return this->itemCount;
}
