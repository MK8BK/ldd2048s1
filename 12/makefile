2048: modele.o 2048.o
	g++ modele.o 2048.o -o 2048 -lncurses

2048.o: 2048.cpp
	g++ -c 2048.cpp -lncurses

modele.o: modele.cpp modele.h -lncurses
	g++ -c modele.cpp

clean:
	rm *.o 2048