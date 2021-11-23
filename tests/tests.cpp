#include <vector>
#include <iostream>
#include "../modele.h"
#include <cstdlib> 
#include <time.h>
using namespace std;


// #include <unistd.h>










int main(){
	Plateau testPlateau = {
		{0,0,0,4},
		{8,0,4,2},
		{0,4,8,2},
		{16,2,2,8}
	};

	Plateau test2Plateau = {
		{0,0,0,4},
		{8,0,4,2},
		{0,4,8,2},
		{16,2,2,3}
	};

	Plateau test3Plateau = {
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0},
		{0,0,2048,0}
	};

	srand((unsigned) time(0));
	cout << dessine(deplacement(testPlateau, 7)) << endl;
}