#include "modele.h"
#include <vector>
#include <iostream>
#include <cstdlib> 
#include <time.h>
#include <ncurses.h>
#include <tuple>
using namespace std;
typedef vector<vector<int>> Plateau;


// * "g++ -c modele.cpp"
// * "g++ -c 2048.cpp"
// * "g++ 2048.o modele.o -o 2048"

//jeu()

int main(){
	//jeu();
	initscr();
	int red = 1000;
	int green = 111;
	int blue = 87;
	tuple<int, int, int> t1 = make_tuple(red, green, blue);
	tuple<int, int, int> t2= make_tuple(red+58, green, blue);
	dessine_string_couleur("2", t1);
	dessine_string_couleur("2048",t2 );
	getch();
	endwin();
	//testing the colors, no fruitfull solution yet
	//half-done, continue after emergency git versions management
	// 
	// 
	// 
	// 
	// 
	// 
	return 0;
}