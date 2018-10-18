/*
        Name: Clark Chen
        NetID: schen237
        File: schen237Proj7.cpp
        Project #: 7
		Project Name: Doodlebugs and Ants
        Description: GridControl Class header file
        Date: 5/3/2018
        Term: Spring 2018
*/
#include <cstdio>
#include <stdlib.h>
#include "GridDisplay.h"
#include "Ant.h"
#include "Doodlebug.h"

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

// GridControl Class, to control ant class and doodlebug class
class GridControl{
	private:
		int mode[20][20]; // 0 for not set, 1 for doodlebug, 2 for ant
		Ant* antData[20][20];
		Doodlebug* doodlebugData[20][20];
		GridDisplay gd;
		
		// Temp variable set
		bool tempOpen;	// Determine if temp variable is in use, prevent incomplete transaction
		int tempX;		// data variable for X
		int tempY;		// data variable for Y

		// Assistant method
		bool arrayBoundCheck(int x, int y);						// Check if the given x, y are within the bound
		void clearAt(int x, int y);								// To clear any element at given x, y posiion
		void aDay(int x, int y);								// Run daily task on given x, y position
		bool isEmpty(int x, int y);								// Check if given x, y position is empty
		void moveTo(int &fromX, int &fromY, int toX, int toY);	// Move given From position to given To position
		void setMode(int x, int y, int newMode);				// Set New Mode on the given position
		
		// Action method
		void hunt(int &x, int &y);								// hunt ant if any nearby, or move to a random empty nearby position
		void spawn(int x, int y);								// Spawn a new creature in random nearby position
		void starve(int x, int y);								// Check if it's starved, if so kill itself
		bool randomNearby(int x, int y, int targetMode);		// generate a random nearby qualified target
		
		
	public:
		GridControl();		// Default constructor
		void aDayControl();	// A method to run daily task on all the elements
		void print();		// Print out the grid using the GridDisplay API
		void pause(int ms);	// Relay method to GridDisplay Class's mySleep
};
