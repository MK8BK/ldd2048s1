#include "modele.h"
#include <vector>
#include <iostream>
#include <cstdlib> 
#include <time.h>
#include <ncurses.h>

using namespace std;
typedef vector<vector<int>> Plateau;

//jeu()

int main(){
	initscr();
	start_color();
	if(can_change_color()){
		jeu_moderne_couleur();
	} else {
		jeu_moderne();
	}
}