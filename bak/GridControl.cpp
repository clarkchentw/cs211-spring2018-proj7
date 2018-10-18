#include "GridControl.h"

GridControl::GridControl(){
	for (int x = 0; x < 20; x++){
		for (int y = 0; y < 20; y++){
			mode[x][y] = 0;
			antData[x][y] = NULL;
			doodlebugData[x][y] = NULL;
		}
	}
}

// This will clear
void GridControl::setMode(int x, int y, int newMode){
	clearAt(x, y);
	switch(newMode){
		case 0:
			/* Do nothing */
			break;
		case 1:
			doodlebugData[x][y] = new Doodlebug(x, y);
			break;
		case 2:
			antData[x][y] = new Ant(x, y);
			break;
		default:
			printf("Something wrong in GridControl::setMode()");
			exit(999);
			break;
	}
}

// Private method
void GridControl::clearAt(int x, int y){
	if (antData[x][y] != NULL){
		delete antData[x][y];
	}
	if (doodlebugData[x][y] != NULL){
		delete doodlebugData[x][y];
	}
	if (mode[x][y] != 0){
		mode[x][y] = 0;
	}
}

// Private method
bool isEmpty(int x, int y){
	return mode == 0;
}

void moveTo(int fromX, int fromY, int toX, int toY){
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
			antData[toX][toY] = antDataData[fromX][fromY];
			antDataData[fromX][fromY] = NULL;
		}
		
		// Move mode
		mode[toX][toY] = mode[fromX][fromY];
		mode[fromX][fromY] = 0;
	}
}

void kill(int x, int y){
	if (mode[20] == 1){
		delete doodlebugData[x][y];
	}
	else if (mode[20] == 2){
		delete antData[x][y];
	}
	else{
		printf("Nothing to kill\n");
	}
}


