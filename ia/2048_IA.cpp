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
	srand((unsigned) time(0));
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


	//Plateau p = {{0,25,0,2},
	//			 {2,0,0,32},
	//			 {20,0,1024,0},
	//			 {0,0,1024,0}};
	//Plateau np = deplacementHaut(p);

	//cout << to_string(maximum_value_change_favor(p,np))<<endl;
	// string edge_description = get<0>(max_edge(p));
	// vector<int> edge = get<1>(max_edge(p));
	// cout<<edge_description<<" "<<to_string(edge[0])<<to_string(edge[1])
	// 	<<to_string(edge[2])<<to_string(edge[3])<<endl;
	//cout << to_string(max_tableau({64,0,128,64,130,64,69,0})[0]) <<endl;
	// string half_edge_description = get<0>(max_half_edge(p));
	// vector<int> edge = get<1>(max_half_edge(p));
	// cout<<half_edge_description<<" "<<to_string(edge[0])<<to_string(edge[1])<<endl;

}