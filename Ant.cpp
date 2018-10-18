#include "Ant.h"

Ant::Ant(){
	dayCountForSpawn = 0;
	visited = false;
}

int Ant::getDayCountForSpawn(){
	return dayCountForSpawn;
}

void Ant::spawned(){
	dayCountForSpawn-=3;
}

void Ant::survived(){
	dayCountForSpawn++;
}
