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
	char move = 'H';
	int iteration=1;
	Plateau p = get<2>(read_configuration(pathin));
	int max = get<0>(maxpos(p));
	vector<int> maxi = get<1>(maxpos(p));
	cout << "maximum number" << to_string(max) << "  at position:" 
			<< to_string(maxi[0])+","+to_string(maxi[1])<<endl;
	vector<int> v = {1,9,0,4};
}