//#include "modele.h"
#include <vector>
#include <iostream>
// #include <cstdlib> 
// #include <time.h>
using namespace std;
typedef vector<vector<int>> Plateau;


// * "g++ -c modele.cpp"
// * "g++ -c 2048.cpp"
// * "g++ 2048.o modele.o -o 2048"

//jeu()

int main(){
	// Plateau testPlateau = {
	// 	{2,16,8,16},
	// 	{8,4,2,8},
	// 	{2,8,4,2},
	// 	{16,4,2,8}
	// };

	// Plateau test2Plateau = {
	// 	{0,0,0,4},
	// 	{8,0,4,2},
	// 	{0,4,8,2},
	// 	{16,2,2,3}
	// };

	// Plateau test3Plateau = {
	// 	{0,0,0,0},
	// 	{0,0,0,0},
	// 	{0,0,0,0},
	// 	{2048,2048,2048,2048}
	// };
	initscr();
	start_color();
	init_color(COLOR_RED, 700, 0, 0);
	init_color(COLOR_BLACK, 500, 500, 500);
	init_pair(1, COLOR_RED, COLOR_BLACK);	
	attron(COLOR_PAIR(1));
	printw("Viola !!! In color ...");
	attroff(COLOR_PAIR(1));
	// attron(COLOR_PAIR(2));
	getch();
	endwin();
//	srand((unsigned) time(0));
	// cout << dessine(deplacement(testPlateau, 1)) << endl;
	//cout << dessine(deplacement(test3Plateau,3)) << endl;
}