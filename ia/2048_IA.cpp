#include <vector>
using namespace std;
#include "modele.h"
#include "io.h"
#include "helper.h"
#include "favor.h"
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
	string pathw = "w.txt";
	vector<int> weights = read_weights(pathw);
	int iteration=-1;
	int game_score=0;
	for(int w:weights){
		cout<<to_string(w)<<", ";
	}
	cout<<endl;
	Plateau p = plateauInitial();
	char answer;
	while(!estPerdant(p)){
		tuple<int, int, Plateau> tup = read_updated_configuration(iteration,pathin);
		iteration = get<0>(tup);
		game_score = get<1>(tup);
		p = get<2>(tup);
		cout << dessine(p) << to_string(iteration)<<endl;
		answer = ai_answer(p,weights);
		cout<<answer<<endl;
		write_mouvement(pathout,iteration,answer);
	}
	ofstream file;
	file.open(pathout);
	file<<"";
	file.close();
	ofstream file2;
	file2.open(pathin);
	file2<<"";
	file2.close();


	//string pathw = "w.txt";
	//vector<int> weights = read_weights(pathw);

	//Plateau p = {{0,0,0,0},
	//			{0,0,0,0},
	//			{0,0,4,2},
	//			{2,4,8,32}
	//};
	//cout<<ai_answer(p,weights)<<endl;
	//cout<<to_string(decroissance_favor(p, deplacementBas(p)))<<endl;
	//for(int i=0; i<1; i++){
	//	cout<<ai_answer(p,weights)<<" | ";
	//}
	//cout<<endl;
	//Plateau p = {{0,2,0,2},
	//			{0,2,32,4},
	//			{0,8,128,512},
	//			{2,2,4,4}};
	//cout << to_string(stable_favor(p,deplacementGauche(p))) <<endl;
	//cout << to_string(stable_favor(p,deplacementDroite(p))) <<endl;
	//Plateau p=get<2>(read_configuration("../archive/tournois/configuration.txt"));
	//cout<<"Gauche: "<<to_string(eval_move(p,'G',weights)) <<endl;
	//cout<<"Haut: "<<to_string(eval_move(p,'H',weights)) <<endl;
	//cout<<"Bas: "<<to_string(eval_move(p,'B',weights)) <<endl;
	//cout<<"Droite: "<<to_string(eval_move(p,'D',weights)) <<endl;
	//cout<<ai_answer(p, weights)<<endl;
	//cout<<to_string(calc_empty_favor(deplacement(p,ideplacement_dhgb('G'), true))*weights[0])<<endl;
	// cout << to_string(maxi(p[0]))<<endl;
	// for(vector<int> hedge:extract_half_edges(p)){
	// 	for(int elem:hedge){
	// 		cout<<elem<<", ";
	// 	}
	// 	cout<<endl;
	// }
	// max_edge(p);
	// for(int i=0; i<(get<1>(max_half_edge(p))).size(); i++){
	// 	for(int j=0;j < (get<1>(max_half_edge(p))[i]).size(); j++){
	// 		cout<<to_string(get<1>(max_half_edge(p))[i][j])<<", ";
	// 	}
	// 	cout<<get<0>(max_half_edge(p))[i]<<endl;
	// }
	// for(vector<int> maximumedge:get<1>(max_edge(p))){
	// 	for(int i:maximumedge){
	// 		cout<<to_string(i)<<", ";
	// 	}
	// 	cout<<endl;
	// }
}