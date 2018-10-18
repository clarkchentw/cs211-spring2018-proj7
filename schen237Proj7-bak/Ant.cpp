/*
        Name: Clark Chen
        NetID: schen237
        File: schen237Proj7.cpp
        Project #: 7
		Project Name: Doodlebugs and Ants
        Description: Ant Class source file
        Date: 5/3/2018
        Term: Spring 2018
*/
#include "Ant.h"

// default constructor
Ant::Ant(){
	dayCountForSpawn = 0;
	visited = false;
}

// get the day count used by spawn rule
int Ant::getDayCountForSpawn(){
	return dayCountForSpawn;
}

// report spawned, dayCountForSpawn reset to 0
void Ant::spawned(){
	dayCountForSpawn = 0;
}

// report survived, dayCountForSpawn + 1
void Ant::survived(){
	dayCountForSpawn++;
}
