GridMain:  GridMain.cpp GridDisplay.o
	g++ -o GridMain GridMain.cpp GridDisplay.o

gddemo: gddemo.cpp GridDisplay.o
	g++ -o gddemo gddemo.cpp GridDisplay.o

GridDisplay.o: GridDisplay.cpp GridDisplay.h
	g++ -c GridDisplay.cpp

clean:
	rm -f *.o GridMain
