#include <cstdio>
#include <stdlib.h>

class Ant{
	private:
		int dayCountForSpawn;

	public: 
		bool visited;
		Ant();
		int getDayCountForSpawn();
		void spawned();
		void survived();
};
