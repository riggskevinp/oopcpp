#include "elevatorutils.h"


void elevatorutils::readCSV(const std::string file, std::queue<Passenger> &passengerQueue){

	std::fstream fin;
	fin.open(file, std::ios::in);
	std::string line;
	std::string header;
	std::getline(fin, header);
	if(header.at(0) != 'S'){
		throw;
	}

	while(std::getline(fin, line)){
		std::istringstream s(line);
		std::string cell;
		std::vector<int> row;
		while(std::getline(s,cell,',')){
			row.push_back(std::stoi(cell));
		}
		if(row[1] != row[2]){
			passengerQueue.push(Passenger(row[0],row[1],row[2]));
		}
	}
	fin.close();


}
