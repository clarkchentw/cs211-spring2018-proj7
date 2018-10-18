/*
        Name: Clark Chen
        NetID: schen237
        File: schen237Proj7.cpp
        Project #: 7
		Project Name: Doodlebugs and Ants
        Description: Main Source File
        Date: 5/3/2018
        Term: Spring 2018
*/
#include "GridControl.h"
#include <time.h>

int main (int argc, char** argv){
	int sleepMS = 1000;
	for (int i = 0; i < argc; i++){
		if ('-' == argv[i][0] && 'd' == argv[i][1] && i+1 < argc){
                	sleepMS = atoi(argv[i+1]);
		}
		
	}
	srand(time(NULL));
	GridControl earth;
		while(true){
			earth.aDayControl();
			//earth.pause(500);
			earth.print();
			earth.pause(sleepMS);
			printf("\n");
		}

	return 1;
}
