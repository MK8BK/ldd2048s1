#include <vector>
#include <iostream>
#include <cstdlib> 
#include <time.h>
#include "modele.h"
#include <fstream>
#include <tuple>
using namespace std;

typedef vector<vector<int>>Plateau;


//half-done, continue after emergency git versions management
//if tester notebook is provided by university soon, remove this file and test the AI on their implementation (final test done this way)


int main(){
	srand((unsigned) time(0));
	string pathin="configuration.txt";
	string pathout="mouvements.txt";
	int iteration = 0;
	int game_score = 0;
	Plateau p = plateauInitial();
	Plateau np;
	write_new_config(pathin, iteration, game_score, p);
	// ai_answer(pathin, pathout, iteration);
	// ai_answer(pathin, pathout, iteration+1);
	// ai_answer(pathin, pathout, iteration+2);
	iteration++;
	while(!estPerdant(p) || !estGagnant(p)){
		//some code to execute the ai
		ai_answer(pathin, pathout, iteration);
		iteration++;
		char ai_move = get<1>(read_updated_mouvement(pathout,iteration));
		np = deplacement(p, ideplacement_dhgb(ai_move), true);
		game_score = score(game_score, p, ideplacement_dhgb(ai_move));
		write_new_config(pathin, iteration-1, game_score, np);
		p = np;
	}
	cout << to_string(game_score) << to_string(iteration) <<endl;
	// p = get<2>(read_configuration(testpathin));
	// int j = get<0>(read_configuration(testpathin));
	// int i = get<1>(read_configuration(testpathin));
	// cout << dessine(p) << endl << to_string(i)<<" "<<to_string(j)<<endl;
	// int iteration = get<0>(read_configuration(pathin));
	// int score = get<1>(read_configuration(pathin));
	// Plateau p = get<2>(read_configuration(pathin));

}