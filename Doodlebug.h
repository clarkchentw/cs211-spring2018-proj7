#include <cstdio>
#include <stdlib.h>

class Doodlebug{
	private:
		int daysNotEat;
		int dayCountForSpawn;

	public: 
		bool visited;

		Doodlebug();
		bool starve();
		int getDaysNotEat();
		void noFood();
		void gotFood();
		int getDayCountForSpawn();
		void spawned();
		void survived();
		
	
};

