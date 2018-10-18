/*
        Name: Clark Chen
        NetID: schen237
        File: schen237Proj7.cpp
        Project #: 7
		Project Name: Doodlebugs and Ants
        Description: Doodlebug Class header file
        Date: 5/3/2018
        Term: Spring 2018
*/
#include <cstdio>
#include <stdlib.h>

// Doodlebug Class, contain information of each individual doodlebug
class Doodlebug{
	private:
		int daysNotEat;			// Days not eating ant
		int dayCountForSpawn;	// day count for spawn rule

	public: 
		bool visited;			// whether visited or not, not a sensitive data, public makes access easier.

		Doodlebug();			// default constructor
		bool starve();			// Check whether is starve
		int getDaysNotEat();	// get the day count for not eating
		void noFood();			// report no food, daysNotEat+1
		void gotFood();			// report got food, daysNotEat reset to 0
		int getDayCountForSpawn();	// get the day count used by spawn rule
		void spawned();			// report spawned, dayCountForSpawn reset to 0
		void survived();		// report survived, dayCountForSpawn + 1
		
	
};

