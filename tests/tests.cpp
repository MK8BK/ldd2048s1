#include <vector>
#include <iostream>
#include "../modele.h"
#include <cstdlib> 
#include <time.h>
using namespace std;


#include <unistd.h>



typedef vector<vector<int>> Plateau;

void dispPlateau(Plateau plateau){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			cout << plateau[i][j] << " ";
		}
		cout << endl;
	}
}









int main(){
	Plateau testPlateau = {
		{0,0,0,4},
		{8,0,4,2},
		{0,4,8,2},
		{16,2,2,8}
	};

	Plateau test2Plateau = {
		{4,8,2,8},
		{2,4,8,2},
		{2,4,2,4},
		{4,2,4,2}
	};

	srand((unsigned) time(0));
	dispPlateau(deplacement(test2Plateau, 3));
}