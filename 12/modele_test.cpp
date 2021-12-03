#include <vector>
#include <iostream>
#include <cstdlib> 
#include <time.h>
#include "modele.h"
using namespace std;

#define CHECK(test) if (!(test)) cout << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl

void test_plateau_vide(){
	CHECK(plateauInitial().size()==4);
}

void testMergeRowLeft(){
	vector<int> ligne = mergeRowLeft({2, 2, 2, 2});
	vector<int> lignecompare = {4, 0, 4, 0};
	vector<int> ligne2 = mergeRowLeft({4, 2, 2, 2});
	vector<int> ligne2compare = {4, 4, 0, 2};
	vector<int> ligne3 = mergeRowLeft({8, 8, 0, 0});
	vector<int> ligne3compare = {16, 0, 0, 0};
	for (int i = 0; i < 4; i = i + 1){
		CHECK(ligne[i] == lignecompare[i]);
		CHECK(ligne2[i] == ligne2compare[i]);
		CHECK(ligne3[i] == ligne3compare[i]);
	}
}

int main(){
	test_plateau_vide();
	testMergeRowLeft();
}