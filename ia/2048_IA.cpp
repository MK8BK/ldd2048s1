#include <vector>
using namespace std;
#include "modele.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <tuple>
typedef vector<vector<int>> Plateau;


//fo now just testing the function implementations
//half-done, continue after emergency git versions management

int main(){
	string pathin="../archive/tournois/configuration.txt";
	string pathout="../archive/tournois/mouvements.txt";
	int iteration;
	int game_score;
	Plateau p;
	// char move;
	while(true){
		iteration = get<0>(read_configuration(pathin));
		game_score = get<1>(read_configuration(pathin));
		p = get<2>(read_configuration(pathin));
		ai_answer(pathin, pathout, iteration);
		iteration++;
	}
	// Plateau p = {{4,2,4,2},
	// 			 {2,4,2,4},
	// 			 {4,8,16,2},
	// 			 {32,64,16,4}};
	// int gauche = eval_move(p, 'G');
	// int haut = eval_move(p, 'H');
	// int droite = eval_move(p, 'D');
	// int bas = eval_move(p, 'B');
	// cout << to_string(gauche)<<endl;
	// cout << to_string(haut)<<endl;
	// cout << to_string(droite)<<endl;
	// cout << to_string(bas)<<endl;

	// write_mouvement(pathout, iteration, move);
	

}