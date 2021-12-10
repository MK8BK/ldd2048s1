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

int main(){
	// string pathin="../archive/tournois/configuration.txt";
	// string pathout="../archive/tournois/mouvements.txt";
	srand((unsigned) time(0));
	string pathin="configuration.txt";
	string pathout="mouvements.txt";
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
}