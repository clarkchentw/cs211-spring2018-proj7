/*
        Name: Clark Chen
        NetID: schen237
        File: schen237Proj7.cpp
        Project #: 7
		Project Name: Doodlebugs and Ants
        Description: Ant Class header file
        Date: 5/3/2018
        Term: Spring 2018
*/
#include <cstdio>
#include <stdlib.h>

class Ant{
	private:
		int dayCountForSpawn;	// day count for spawn rule

	public: 
		bool visited;			// whether visited or not, not a sensitive data, public makes access easier.
		
		Ant();					// default constructor	
		int getDayCountForSpawn();	// get the day count used by spawn rule
		void spawned();			// report spawned, dayCountForSpawn reset to 0
		void survived();		// report survived, dayCountForSpawn + 1
};
