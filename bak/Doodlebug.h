#include <cstdio>
#include <stdlib.h>

#include "GridControl.h"

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

class Doodlebug{
	private:
		bool hasMoved;
		int posX;
		int posY;
		int daysNotEat;
		int dayCountForSpawn;

		// For passing value out
		int outputX;
		int outputY;
		bool actionCode; // 0 for nothing, 1 for move, 2 for new born

	public: 
		Doodlebug(int x, int y); // x, y represent the coordinate
		void hunt();
		void move(GridControl* control);
		void spawn();
		bool starve();
		bool aDay();
		
		bool getActionCode();
		int getOutputX();
		int getOutputY();
		
	
};

