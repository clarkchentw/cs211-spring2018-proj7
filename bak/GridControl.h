#include <cstdio>
#include <stdlib.h>
#include "GridDisplay.h"
#include "Ant.h"
#include "Doodlebug.h"

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

class GridControl{
	private:
		int mode[20][20]; // 0 for not set, 1 for doodlebug, 2 for ant
		Ant* antData[20][20];
		Doodlebug* doodlebugData[20][20];
		GridDisplay gd;
		
		// Private method
		void clearAt(int x, int y);
		
	public:
		GridControl();
		bool isEmpty(int x, int y);
		void setMode(int x, int y, int newMode);
		void moveTo(int fromX, int fromY, int toX, int toY);
		void kill(int x, int y);
};
