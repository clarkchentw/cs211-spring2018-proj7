schen237Proj7:  schen237Proj7.cpp GridDisplay.o Doodlebug.o Ant.o GridControl.o
	g++ -o schen237Proj7 schen237Proj7.cpp GridDisplay.o Doodlebug.o Ant.o GridControl.o

GridDisplay.o: GridDisplay.cpp GridDisplay.h
	g++ -c GridDisplay.cpp

Doodlebug.o: Doodlebug.cpp Doodlebug.h
	g++ -c Doodlebug.cpp

Ant.o: Ant.cpp Ant.h
	g++ -c Ant.cpp

GridControl.o: GridControl.cpp GridControl.h
	g++ -c GridControl.cpp

clean:
	rm *.o schen237Proj7

run:
	./schen237Proj7
