#include "statistics.h"

Statistics::Statistics() :
	itemCount{0},
	runningTotal{0.0},
	average{0.0},
	STD{0.0}
{

}

void Statistics::add(double x)
{
	this->items.push_back(x);
	this->itemCount++;
}

void Statistics::removeItem(int index)
{

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

double Statistics::getAverage() const
{
	return this->average;
}

double Statistics::getSTD() const
{
	return this->STD;
}

int Statistics::getItemCount() const
{
	return this->itemCount;
}
