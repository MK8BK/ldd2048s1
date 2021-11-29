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
	string pathin="configuration.txt";
	string pathout="mouvements.txt";
	char move = 'B';
	int iteration = get<0>(read_configuration(pathin));
	int score = get<1>(read_configuration(pathin));
	Plateau p = get<2>(read_configuration(pathin));
	// write_mouvement(pathout, iteration, move);
	

}