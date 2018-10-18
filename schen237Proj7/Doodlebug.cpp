/*
        Name: Clark Chen
        NetID: schen237
        File: schen237Proj7.cpp
        Project #: 7
		Project Name: Doodlebugs and Ants
        Description: Doodlebug Class source file
        Date: 5/3/2018
        Term: Spring 2018
*/
#include "Doodlebug.h"

// default constructor
Doodlebug::Doodlebug(){
	// setting default value
	daysNotEat = 0;
	dayCountForSpawn = 0;
	visited = false;
}

// Check whether is starve
bool Doodlebug::starve(){
	// Check if the days not eat exceed its limit
	if (daysNotEat >= 3){
		return true;
	}
	return false;
}

// get the day count for not eating
int Doodlebug::getDaysNotEat(){
	return daysNotEat;
}

// report no food, daysNotEat+1
void Doodlebug::noFood(){
	daysNotEat++;
}

// report got food, daysNotEat reset to 0
void Doodlebug::gotFood(){
	daysNotEat = 0;
}

// get the day count used by spawn rule
int Doodlebug::getDayCountForSpawn(){
	return dayCountForSpawn;
}

// report spawned, dayCountForSpawn reset to 0
void Doodlebug::spawned(){
	dayCountForSpawn = 0;
}

// report survived, dayCountForSpawn + 1
void Doodlebug::survived(){
	dayCountForSpawn++;
}
