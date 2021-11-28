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
tuple<Plateau, int nscore> make_mouvement(Plateau plateau,string path, int game_score){
	Plateau nplateau=plateau;
	ifstream mouvements_file;
	mouvements_file.open(path);

}

int main(){

}