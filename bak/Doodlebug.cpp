#include "Doodlebug.h"

Doodlebug::Doodlebug(int x, int y){
	hasMoved = false;
	posX = x;
	posY = y;
	daysNotEat = 0;
	dayCountForSpawn = 0;
	actionCode = 0;
}
void Doodlebug::hunt(){
	if (true/* If ant around*/){
		// Process eating
		daysNotEat = 0;
	}
	else{
		//Move
		daysNotEat++;
	}
}


void Doodlebug::move(GridControl* control){
        int randomValue;
        int moveComplete = false;
        bool directionTried[4] = {false};
        while(!moveComplete){
                randomValue = rand() % 4;
                switch(randomValue){
                        case UP:
                                directionTried[UP] = true;
                                if (posY > 0 && control->isEmpty(posX, posY-1)){
                                        posY--;
                                        moveComplete = true;
                                }
                                break;
                        case DOWN:
                                directionTried[DOWN] = true;
                                if (posY < 19 && control->isEmpty(posX, posY+1)){
                                        posY++;
                                        moveComplete = true;
                                }
                                break;
                        case LEFT:
                                directionTried[LEFT] = true;
                                if (posX > 0 && control->isEmpty(posX-1, posY)){
                                        posX--;
                                        moveComplete = true;
                                }
                                break;
                        case RIGHT:
                                directionTried[RIGHT] = true;
                                if (posY < 19 && control->isEmpty(posX+1, posY)){
                                        posX++;
                                        moveComplete = true;
                                }
                                break;
                        default:
                                printf("Something wrong in Doodlebug::move()");
                                exit(999);
                                break;
                }
        }

}

void Doodlebug::spawn(){
	if (dayCountForSpawn >= 8){
		// Generate random value
		// Check if position occupy
		// execute
		if (true /* No position to spawn */){
			return;
		}
		dayCountForSpawn = 0;
	}
}
bool Doodlebug::starve(){
	if (daysNotEat >= 3){
		return true;
	}
	return false;
}

// Return boolean to decide if object should be deallocate
bool Doodlebug::aDay(){
	hunt();
	spawn();
	return starve();
}



bool Doodlebug::getActionCode(){
	return actionCode;
}
int Doodlebug::getOutputX(){
	return outputX;
}
int Doodlebug::getOutputY(){
	return outputY;
}


