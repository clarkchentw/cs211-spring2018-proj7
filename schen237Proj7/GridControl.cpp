/*
        Name: Clark Chen
        NetID: schen237
        File: schen237Proj7.cpp
        Project #: 7
		Project Name: Doodlebugs and Ants
        Description: GridControl Class source file
        Date: 5/3/2018
        Term: Spring 2018
*/
#include "GridControl.h"

//////////////////////////////////////////////////////////////////////////////
// Default constructor
GridControl::GridControl(){
	int randomNum;				// Variable for randomNumber
	int doodlebugRemain = 5;	// Remain doodlebug need to be place on board
	int antRemain = 100;		// Remain ant need to be place on board
	
	// Reset all member data
	for (int x = 0; x < 20; x++){
		for (int y = 0; y < 20; y++){
			mode[x][y] = 0;
			antData[x][y] = NULL;
			doodlebugData[x][y] = NULL;
			gd.setChar (x, y, '*');
		}
	}
	
	// Randomly insert creature
	// loop continue until no more creature need to be place on board
	while(doodlebugRemain > 0 || antRemain > 0){
		for (int x = 0; x < 20; x++){
			for (int y = 0; y < 20; y++){
				if (mode[x][y] == 0){
					// If no more creature need to be place, then break the loop.
					if (antRemain <= 0 && doodlebugRemain <= 0){
						x = 99;
						y = 99;
						break;
					}
					
					// The following code help spread the piece out on the board
					// Generate random number from 0~8
					// Here is why choose 8
					// 105 creature in 400 = 105/400, empty space = 1-105/400 = 295/400 = 73.75%
					// 1 and 2 are for 2 creatures. Anything other than 1, 2 will be space
					// % of space will be (i-2)/i, eg. 1/3, 2/4, 3/5...
					// 6/8 = 75% is the closest to 73.75%
					randomNum = rand() % 8;
					
					// If doodlebug exceed quota
					if (randomNum == 1 && doodlebugRemain <= 0 && antRemain > 0){
						randomNum = 2;
					}
					
					// If ant exceed quota
					if (randomNum == 2 && antRemain <= 0 && doodlebugRemain > 0){
						randomNum = 1;
					}
					
					// additional chance for space
					if (randomNum >= 3){
						randomNum = 0;
					}
					
					// Place the creature
					setMode(x, y, randomNum);
					
					// Adjust counter
					if (randomNum == 1){
						doodlebugRemain--;
					}
					else if (randomNum == 2){
						antRemain--;
					}
				}
			}
		}
	}
	
	// Reset temp variable set
	tempOpen = false;
	tempX = 0;
	tempY = 0;
	
}

//////////////////////////////////////////////////////////////////////////////
// Check if the given x, y are within the bound
bool GridControl::arrayBoundCheck(int x, int y){
	if (x > 19 || x < 0 || y > 19 || y < 0){
		return false;
	}
	return true;
		
}

//////////////////////////////////////////////////////////////////////////////
// To clear any element at given x, y posiion
void GridControl::clearAt(int x, int y){
								
	// Reset object* 2d array to NULL
	if (antData[x][y] != NULL){
		delete antData[x][y];
		antData[x][y] = NULL;
	}
	if (doodlebugData[x][y] != NULL){
		delete doodlebugData[x][y];
		doodlebugData[x][y] = NULL;
	}
	
	// Reset mode to 0
	if (mode[x][y] != 0){
		mode[x][y] = 0;
	}
}

//////////////////////////////////////////////////////////////////////////////
// Run daily task on given x, y position
void GridControl::aDay(int x, int y){
	// Doodlebug
	if (mode[x][y] == 1){
		hunt(x, y);
		spawn(x, y);
		starve(x, y);
	}

	// Ant
	else if (mode[x][y] == 2){
		// Find the new nearby position available
		if (randomNearby(x, y, 0)){
			if (tempOpen == false){
				printf("GridControl::aDay temp var access control fail\n");
				abort();
			}
			
			// Moving Process
			int newX = tempX;
			int newY = tempY;
			tempOpen = false; // Close temp access
			moveTo(x, y, newX, newY);
			spawn(x, y);
		}
		antData[x][y]->survived(); // Report survived
		
		tempOpen = false; // Close temp access
	}



}

//////////////////////////////////////////////////////////////////////////////
// Check if given x, y position is empty
bool GridControl::isEmpty(int x, int y){
	return mode[x][y] == 0;
}

//////////////////////////////////////////////////////////////////////////////
// Move given From position to given To position
void GridControl::moveTo(int &fromX, int &fromY, int toX, int toY){
	if (isEmpty(fromX, fromY)){
		printf("Nothing to move\n");
		return;
	}
	if (isEmpty(toX, toY)){
		
		// Move doodlebug
		if (mode[fromX][fromY] == 1){
			doodlebugData[toX][toY] = doodlebugData[fromX][fromY];
			doodlebugData[fromX][fromY] = NULL;
		}
		
		// Move ant
		else if (mode[fromX][fromY] == 2){
			antData[toX][toY] = antData[fromX][fromY];
			antData[fromX][fromY] = NULL;
		}
		
		// Move mode
		mode[toX][toY] = mode[fromX][fromY];
		mode[fromX][fromY] = 0;
		
		// Let original caller know position changed
		fromX = toX;
		fromY = toY;
	}
}

//////////////////////////////////////////////////////////////////////////////
// Set New Mode on the given position
void GridControl::setMode(int x, int y, int newMode){
	clearAt(x, y);
	switch(newMode){
		case 0:
			/* Do nothing */
			break;
		case 1:
			doodlebugData[x][y] = new Doodlebug();
			break;
		case 2:
			antData[x][y] = new Ant();
			break;
		default:
			printf("Something wrong in GridControl::setMode()");
			abort();
			break;
	}
	mode[x][y] = newMode;
}

//////////////////////////////////////////////////////////////////////////////
// hunt ant if any nearby, or move to a random empty nearby position
void GridControl::hunt(int &x, int &y){
	if (mode[x][y] != 1){
		printf("GridControl::hunt given position is not doodlebug\n");
		abort();
	}
	
	
	if (randomNearby(x, y, 2)){
		
		if (tempOpen == false){
			printf("GridControl::hunt temp var access control fail\n");
			abort();
		}
		int killX = tempX;
		int killY = tempY;
		tempOpen = false; // Close temp access
		
		setMode(killX, killY, 0);
		doodlebugData[x][y]->gotFood(); // Report got food
	}
	else{
		tempOpen = false; // Close temp access from the if statement
		randomNearby(x, y, 0);	// Find randomNearby position(return are send back by tempX, Y)
		doodlebugData[x][y]->noFood(); // Report no food
		
		// Moving Process
		int newX = tempX;
		int newY = tempY;
		tempOpen = false; // Close temp access
		moveTo(x, y, newX, newY);
		
	}
}

//////////////////////////////////////////////////////////////////////////////
// Spawn a new creature in random nearby position
void GridControl::spawn(int x, int y){
	
	// If no spot nearby
	if (!randomNearby(x, y, 0)){
		tempOpen = false; // Close temp access
		return;
	}
	// Check if access open
	if (tempOpen == false){
		printf("GridControl::spawn temp var access control fail\n");
		abort();
	}
	
	// Save send back value
	int newX = tempX;
	int newY = tempY;
	tempOpen = false; // Close temp access
	
	// If is doodlebug
	if (mode[x][y] == 1){
			if (doodlebugData[x][y]->getDayCountForSpawn() >= 8){
				setMode(newX, newY, 1);
				doodlebugData[x][y]->spawned();
			}
	}
	
	// If is ant
	else if (mode[x][y] == 2){
			if (antData[x][y]->getDayCountForSpawn() >= 3){
				setMode(newX, newY, 2);
				antData[x][y]->spawned();
			}
	}
	
	
	
}

//////////////////////////////////////////////////////////////////////////////
// Check if it's starved, if so kill itself, or report survived
void GridControl::starve(int x, int y){
	if (mode[x][y] == 1){
		if (doodlebugData[x][y]->starve()){
			setMode(x, y, 0);
		}
		else{
			doodlebugData[x][y]->survived();
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
// generate a random nearby qualified target
bool GridControl::randomNearby(int x, int y, int targetMode){
	// Check temp variable status
	if (tempOpen == true){
		printf("GridControl::randomNearby temp var access control fail\n");
		abort();
	}
	tempOpen = true;
	tempX = x;
	tempY = y;
	int randomNum;
	bool accessLog[4] = {false};

	
	// Loop until no available position to continue
	while(!accessLog[0] || !accessLog[1] || !accessLog[2] || !accessLog[3]){
		// Decide by random available nearby position
		randomNum = rand() % 4;
		switch(randomNum){
			case UP:
				accessLog[UP] = true;
				if (mode[x][y-1] == targetMode){
					if (!arrayBoundCheck(tempX, tempY-1)){continue;}
					tempY--;
					return true;
				}
				break;
			case DOWN:
				accessLog[DOWN] = true;
				if (mode[x][y+1] == targetMode){
					if (!arrayBoundCheck(tempX, tempY+1)){continue;}
					tempY++;
					return true;
				}
				break;
			case LEFT:
				accessLog[LEFT] = true;
				if (mode[x-1][y] == targetMode){
					if (!arrayBoundCheck(tempX-1, tempY)){continue;}
					tempX--;
					return true;
				}
				break;
			case RIGHT:
				accessLog[RIGHT] = true;
				if (mode[x+1][y] == targetMode){
					if (!arrayBoundCheck(tempX+1, tempY)){continue;}
					tempX++;
					return true;
				}
				break;
		}
	}
	
	return false;
}

//////////////////////////////////////////////////////////////////////////////
// A method to run daily task on all the elements
void GridControl::aDayControl(){
	//reset visited
	for (int x = 0; x < 20; x++){
		for (int y = 0; y < 20; y++){
			if (mode[x][y] == 1){
				doodlebugData[x][y]->visited = false;
			}
			if (mode[x][y] == 2){
				antData[x][y]->visited = false;
			}
		}
	}
	
	// doodlebug's turn
	for (int x = 0; x < 20; x++){
		for (int y = 0; y < 20; y++){
			if (mode[x][y] == 1 && !(doodlebugData[x][y]->visited)){
				doodlebugData[x][y]->visited = true;
				aDay(x, y);
			}
		}
	}
	
	// Ant's turn
	for (int x = 0; x < 20; x++){
		for (int y = 0; y < 20; y++){
			if (mode[x][y] == 2 && !(antData[x][y]->visited)){
				antData[x][y]->visited = true;
				aDay(x, y);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
// Print out the grid using the GridDisplay API
void GridControl::print(){
	char displayText;
	
	for (int x = 0; x < 20; x++){
		for (int y = 0; y < 20; y++){
			switch (mode[x][y]){
				case 0:
					displayText = ' ';
					break;
				case 1:
					displayText = 'D';
					break;
				case 2:
					displayText = 'A';
					break;
			}
			gd.setChar (x, y, displayText);
		}
	}
	
	gd.showGrid ( );
}

//////////////////////////////////////////////////////////////////////////////
// Relay method to GridDisplay Class's mySleep
void GridControl::pause(int ms){
	gd.mySleep(ms);
}
