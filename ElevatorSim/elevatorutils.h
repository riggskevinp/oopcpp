#ifndef ELEVATORUTILS_H
#define ELEVATORUTILS_H

#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <sstream>

#include "passenger.h"

namespace elevatorutils{

void readCSV(const std::string file, std::queue<Passenger>& passengerQueue);


}







#endif // ELEVATORUTILS_H
