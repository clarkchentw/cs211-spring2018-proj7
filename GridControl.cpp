#include "GridControl.h"

GridControl::GridControl(){
	int randomNum;
	int doodlebugRemain = 5;
	int antRemain = 100;
	
	// Reset Board
	for (int x = 0; x < 20; x++){
		for (int y = 0; y < 20; y++){
			mode[x][y] = 0;
			antData[x][y] = NULL;
			doodlebugData[x][y] = NULL;
			gd.setChar (x, y, '*');
		}
	}
	
	// Randomly insert creature
	while(doodlebugRemain > 0 || antRemain > 0){
		for (int x = 0; x < 20; x++){
			for (int y = 0; y < 20; y++){
				if (mode[x][y] == 0){
					if (antRemain <= 0 && doodlebugRemain <= 0){
						x = 99;
						y = 99;
						break;
					}
					
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
																													//	printf("rand: %d at (%d, %d)\n", randomNum, x, y);
					
					setMode(x, y, randomNum);
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
	
	tempOpen = false;
	tempX = 0;
	tempY = 0;
																																	//print();
}

// This will clear
void GridControl::setMode(int x, int y, int newMode){
																										//printf("SetMode at (%d, %d)\n", x, y);
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

// Private method
void GridControl::clearAt(int x, int y){
																										//printf("clearAt at (%d, %d)\n", x, y);
	if (antData[x][y] != NULL){
		delete antData[x][y];
		antData[x][y] = NULL;
	}
	if (doodlebugData[x][y] != NULL){
		delete doodlebugData[x][y];
		doodlebugData[x][y] = NULL;
	}
	if (mode[x][y] != 0){
		mode[x][y] = 0;
	}
}

// Private method
bool GridControl::isEmpty(int x, int y){
	return mode[x][y] == 0;
}

bool GridControl::isAnt(int x, int y){
	return mode[x][y] == 2;
}

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
/*
void GridControl::kill(int x, int y){
	if (mode[x][y] == 1){
		delete doodlebugData[x][y];
		doodlebugData[x][y] = NULL;
	}
	else if (mode[x][y] == 2){
		delete antData[x][y];
		antData[x][y] = NULL;;
	}
	else{
		printf("Nothing to kill\n");
	}
	mode[x][y] = 0;
}
*/
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

void GridControl::aDay(int x, int y){
	// Doodlebug
	if (mode[x][y] == 1){
		hunt(x, y);
		spawn(x, y);
		starve(x, y);
	}

	// Ant
	else if (mode[x][y] == 2){
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
		antData[x][y]->survived();
		
		tempOpen = false; // Close temp access
	}



}

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
		doodlebugData[x][y]->gotFood();
	}
	else{
		tempOpen = false; // Close temp access from the if statement
		randomNearby(x, y, 0);
		doodlebugData[x][y]->noFood();
		
		// Moving Process
		int newX = tempX;
		int newY = tempY;
		tempOpen = false; // Close temp access
		moveTo(x, y, newX, newY);
		
	}
}

void GridControl::spawn(int x, int y){

	
	if (!randomNearby(x, y, 0)){
		tempOpen = false; // Close temp access
		return;
	}
	// Check if access open
	if (tempOpen == false){
		printf("GridControl::spawn temp var access control fail\n");
		abort();
	}
	
	int newX = tempX;
	int newY = tempY;
	tempOpen = false; // Close temp access
	
	
	if (mode[x][y] == 1){
			if (doodlebugData[x][y]->getDayCountForSpawn() >= 8){
				setMode(newX, newY, 1);
				doodlebugData[x][y]->spawned();
			}
	}
	else if (mode[x][y] == 2){
			if (antData[x][y]->getDayCountForSpawn() >= 3){
				setMode(newX, newY, 2);
				antData[x][y]->spawned();
			}
	}
	
	
	
}

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

bool GridControl::randomNearby(int x, int y, int targetMode){
	if (tempOpen == true){
		printf("GridControl::randomNearby temp var access control fail\n");
		abort();
	}
	tempOpen = true;
	tempX = x;
	tempY = y;
	int randomNum;
	bool accessLog[4] = {false};

	while(!accessLog[0] || !accessLog[1] || !accessLog[2] || !accessLog[3]){
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

void GridControl::pause(int ms){
	gd.mySleep(ms);
}

bool GridControl::arrayBoundCheck(int x, int y){
	if (x > 19 || x < 0 || y > 19 || y < 0){
		return false;
	}
	return true;
		
}
