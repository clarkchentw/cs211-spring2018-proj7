#include "Doodlebug.h"

Doodlebug::Doodlebug(){
	daysNotEat = 0;
	dayCountForSpawn = 0;
	visited = false;
}

bool Doodlebug::starve(){
	if (daysNotEat >= 3){
		return true;
	}
	return false;
}

int Doodlebug::getDaysNotEat(){
	return daysNotEat;
}

int Doodlebug::getDayCountForSpawn(){
	return dayCountForSpawn;
}

void Doodlebug::noFood(){
	daysNotEat++;
}

void Doodlebug::gotFood(){
	daysNotEat = 0;
}

void Doodlebug::spawned(){
	dayCountForSpawn-=8;
}

void Doodlebug::survived(){
	dayCountForSpawn++;
}
