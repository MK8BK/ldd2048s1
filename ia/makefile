2048: modele.o io.o helper.o favor.o 2048_IA.o
	g++ modele.o io.o helper.o favor.o 2048_IA.o -o 2048_IA

2048_IA.o: 2048_IA.cpp
	g++ -c 2048_IA.cpp

favor.o: favor.cpp favor.h
	g++ -c favor.cpp

helper.o: helper.cpp helper.h
	g++ -c helper.cpp

io.o: io.cpp io.h
	g++ -c io.cpp

modele.o: modele.cpp modele.h
	g++ -c modele.cpp

clean:
	rm *.o 2048_IA log.txt ../archive/tournois/mouvements.txt ../archive/tournois/configuration.txt ../archive/tournois/log.txt