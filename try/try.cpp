// #include <vector>
// #include <iostream>
// #include "../modele.h"
// #include <cstdlib> 
// #include <time.h>
// //#include <ncurses.h>
// using namespace std;
// typedef vector<vector<int> > Plateau;

// #include <unistd.h>



#include <vector>
#include <iostream>
#include <cstdlib> 
#include <time.h>
#include "../modele.h"
using namespace std;


typedef vector<vector<int>>Plateau;
/** Des fonctions peuvent être ajoutés à ce fichier si besoin est (fonctions pour mettre à jour le score par exemple)
 * //






int main(){
	// initscr();
	// start_color();
	// init_color(COLOR_RED, 700, 0, 0);
	// init_color(COLOR_BLACK, 500, 500, 500);
	// init_pair(1, COLOR_RED, COLOR_BLACK);	
	// attron(COLOR_PAIR(1));
	// printw("Viola !!! In color ...");
	// attroff(COLOR_PAIR(1));
	// // attron(COLOR_PAIR(2));
	// getch();
	// endwin();
	Plateau testPlateau = {
		{,16,8,16},
		{8,4,2,8},
		{2,8,4,2},
		{16,4,2,8}
	};
	Plateau test2Plateau = {
		{0,0,0,4},
		{8,0,4,2},
		{0,4,8,2},
		{16,2,2,3}
	};
	Plateau test3Plateau = {
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0},
		{2048,2048,2048,2048}
	};
	cout<< abs(-3)<<endl;
}