#include "statistics.h"
#include <math.h>

Statistics::Statistics() :
	itemCount{0}
{

}

void Statistics::add(double x)
{
	this->items.push_back(x);
	this->itemCount++;
}

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

void Statistics::setItem(int index, double x)
{
	items[index] = x;
}

double Statistics::getAverage() const
{
	double total = 0;
	for(double x : items){
		total += x;
	}
	return items.empty() ? 0 : total / items.size();
}

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

int Statistics::getItemCount() const
{
	return this->itemCount;
}
