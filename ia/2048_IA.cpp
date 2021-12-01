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
	//important
	// srand((unsigned) time(0));
	// string pathin="../archive/tournois/configuration.txt";
	// string pathout="../archive/tournois/mouvements.txt";
	// int iteration;
	// int game_score;
	// Plateau p;
	// p = get<2>(read_configuration(pathin));
	// char move;
	// while(!estPerdant(p)){
	// 	iteration = get<0>(read_configuration(pathin));
	// 	game_score = get<1>(read_configuration(pathin));
	// 	p = get<2>(read_configuration(pathin));
	// 	cout << dessine(p)<<endl;
	// 	ai_answer(pathin, pathout, iteration);
	// 	iteration++;
	// }

	Plateau p = {{0,0,5,0},
				 {0,2,0,0},
				 {0,2,0,2},
				 {0,33,0,0}};
	
	for(vector<int> i:get<1>(max_edge(p))){
		for(int j:i){
			cout<<to_string(j)<<", ";
		}
		cout<<endl;
	}
	for(string i:get<0>(max_edge(p))){
		cout << i<<endl;
	}
}