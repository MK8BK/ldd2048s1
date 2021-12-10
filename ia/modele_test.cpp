#include <vector>
#include <iostream>
#include <cstdlib> 
#include <time.h>
#include "modele.h"
using namespace std;

#define CHECK(test) if (!(test)) cout << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl

void test_tireDeuxOuQuatre(){
	int fours = 0;
	for(int i=0; i<1000; i++){
		if(tireDeuxOuQuatre()==4){
			fours++;
		}
	}
	CHECK(fours<120 && fours>80);
}

void test_plateauVide(){
	CHECK(plateauVide().size()==4);
	Plateau p = plateauVide();
	for(int i=0; i<4;i++){
		for(int j=0; j<4; j++){
			CHECK(p[i][j]==0);
		}
	}
}

void test_nouvelleTuile(){
	Plateau p = plateauVide();
	p=nouvelleTuile(p);
	int non_zero=0;
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			if(p[i][j]!=0){
				non_zero++;
			}
		}
	}
	CHECK(non_zero==1);
}

void test_plateauInitial(){
	Plateau p=plateauInitial();
	int non_zero=0;
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			if(p[i][j]!=0){
				non_zero++;
			}
		}
	}
	CHECK(non_zero==2);
}

void test_flippe90TrigPlus(){
	Plateau p={{0,2,4,8},
			   {16,0,2,64},
			   {4,32,16,2},
			   {128,0,4,2}
	};
	Plateau rp={{8,64,2,2},
			   {4,2,16,4},
			   {2,0,32,0},
			   {0,16,4,128}
	};
	CHECK(rp==flippe90TrigPlus(p));
}

void test_collapseRowLeft(){
	vector<int> ligne = {0,2,0,64};
	vector<int> ligne2 = {128,4,0,2};
	vector<int> ligne_collapsed = {2,64,0,0};
	vector<int> ligne2_collapsed = {128,4,2,0};
	CHECK(collapseRowLeft(ligne) == ligne_collapsed);
	CHECK(collapseRowLeft(ligne2)==ligne2_collapsed);
}

void test_mergeRowLeft(){
	vector<int> ligne = {2, 2, 2, 2};
	vector<int> lignecompare = {4, 0, 4, 0};
	vector<int> ligne2 = {4, 2, 2, 2};
	vector<int> ligne2compare = {4, 4, 0, 2};
	vector<int> ligne3 = {8, 8, 0, 0};
	vector<int> ligne3compare = {16, 0, 0, 0};
	CHECK(mergeRowLeft(ligne)==lignecompare);
	CHECK(mergeRowLeft(ligne2)==ligne2compare);
	CHECK(mergeRowLeft(ligne3)==ligne3compare);
}

void test_deplacementGauche(){
	Plateau p={{0,2,2,8},
			   {16,0,2,64},
			   {4,32,16,16},
			   {128,0,4,2}
	};
	Plateau gp={{4,8,0,0},
			   {16,2,64,0},
			   {4,32,32,0},
			   {128,4,2,0}
	};
	CHECK(gp==deplacementGauche(p));
}

void test_deplacementDroite(){
	Plateau p={{0,2,2,8},
			   {16,0,2,64},
			   {4,32,16,16},
			   {128,0,4,2}
	};
	Plateau dp={{0,0,4,8},
				{0,16,2,64},
				{0,4,32,32},
				{0,128,4,2}
	};
	CHECK(dp==deplacementDroite(p));
}

void test_deplacementHaut(){
	Plateau p={{0,0,2,0},
			   {2,4,32,0},
			   {0,4,32,8},
			   {128,16,0,0}
	};
	Plateau hp={{2,8,2,8},
				{128,16,64,0},
				{0,0,0,0},
				{0,0,0,0}
	};
	CHECK(hp==deplacementHaut(p));
}

void test_deplacementBas(){
	Plateau p={{16,32,4,0},
			   {2,0,0,0},
			   {2,32,8,8},
			   {0,0,0,0}
	};
	Plateau bp={{0,0,0,0},
				{0,0,0,0},
				{16,0,4,0},
				{4,64,8,8}
	};
	CHECK(bp==deplacementBas(p));
}

void test_deplacement(){
	Plateau p={{16,32,4,0},
		   {2,0,0,0},
		   {2,32,8,8},
		   {0,0,0,0}
	};
	CHECK(deplacementGauche(p) != deplacement(p,2));
	CHECK(deplacementHaut(p)!=deplacement(p,1));
	CHECK(deplacementBas(p)!=deplacement(p,3));
	CHECK(deplacementDroite(p)!=deplacement(p,0));
	CHECK(deplacementHaut(p)==deplacement(p,1, false));
	CHECK(deplacementBas(p)!=deplacement(p,3, true));
	CHECK(deplacementGauche(p)==deplacement(p,2, false));
	CHECK(deplacementDroite(p)!=deplacement(p,0, true));
}

void testDessine(){
	string compare1 =dessine({{2, 0, 4, 8}, {8, 2, 0, 2}, {0, 0, 2, 2}, {0, 0, 8, 0}}) ;
	CHECK(compare1== "*****************************\n*  2   *      *  4   *  8   *\n*****************************\n*  8   *  2   *      *  2   *\n*****************************\n*      *      *  2   *  2   *\n*****************************\n*      *      *  8   *      *\n*****************************\n");
	string compare2 = dessine({{2, 0, 4, 8}, {16, 64, 0, 2}, {0, 0, 2, 2}, {0, 0, 8, 0}});
	CHECK(compare2== "*****************************\n*  2   *      *  4   *  8   *\n*****************************\n*  16  *  64  *      *  2   *\n*****************************\n*      *      *  2   *  2   *\n*****************************\n*      *      *  8   *      *\n*****************************\n");
	string compare3 = dessine({{2, 0, 4, 8}, {16, 64, 0, 2}, {256, 0, 2, 2}, {0, 0, 8, 0}});
	CHECK(compare3== "*****************************\n*  2   *      *  4   *  8   *\n*****************************\n*  16  *  64  *      *  2   *\n*****************************\n* 256  *      *  2   *  2   *\n*****************************\n*      *      *  8   *      *\n*****************************\n");
	string compare4 = dessine({{2, 0, 2048, 8}, {16, 64, 0, 2}, {256, 0, 2, 2}, {0, 0, 8, 0}});
	CHECK(compare4== "*****************************\n*  2   *      * 2048 *  8   *\n*****************************\n*  16  *  64  *      *  2   *\n*****************************\n* 256  *      *  2   *  2   *\n*****************************\n*      *      *  8   *      *\n*****************************\n");
	string compare5 = dessine({{2, 0, 2048, 8}, {16, 64, 0, 2}, {256, 0, 16384, 2}, {0, 0, 8, 0}});
	CHECK(compare5== "*****************************\n*  2   *      * 2048 *  8   *\n*****************************\n*  16  *  64  *      *  2   *\n*****************************\n* 256  *      *16384 *  2   *\n*****************************\n*      *      *  8   *      *\n*****************************\n");
	string compare6 = dessine({{2, 0, 2048, 8}, {16, 64, 131072, 2}, {256, 0, 16384, 2}, {0, 0, 8, 0}});
	CHECK(compare6== "*****************************\n*  2   *      * 2048 *  8   *\n*****************************\n*  16  *  64  *131072*  2   *\n*****************************\n* 256  *      *16384 *  2   *\n*****************************\n*      *      *  8   *      *\n*****************************\n");
}

void testEstPerdantGagnant(){
	CHECK(estPerdant({{2, 2, 2, 2}, {2, 2, 2, 2}, {2, 2, 2, 2}, {2, 2, 2, 2}}) == false);
	CHECK(estPerdant({{2, 8, 2, 8}, {8, 2, 8, 2}, {2, 8, 2, 8}, {8, 2, 8, 2}}) == true);
	CHECK(estGagnant({{2, 2, 2, 2}, {2, 2, 2, 2}, {2, 2, 2, 2}, {2, 2, 2, 2}}) == false);
	CHECK(estGagnant({{2048, 2, 2, 2}, {2, 2, 2, 2}, {2, 2, 2, 2}, {2, 2, 2, 2}}) == true);
	CHECK(estGagnant({{4096, 2048, 2, 2}, {2, 2, 2, 2}, {2, 2, 2, 2}, {2, 2, 2, 2}}) == true);
}

void testCount(){
	CHECK(count_plateau({{4096, 2048, 2, 2}, {2, 2, 2, 2}, {2, 2, 2, 2}, {2, 2, 2, 2}}, 2) == 14);
	CHECK(count_plateau({{4096, 2048, 2, 2}, {2, 2, 2, 2}, {2, 2, 2, 2}, {2, 2, 2, 2}}, 2048) == 1);
	CHECK(count_plateau({{4096, 2048, 2, 2}, {2, 2, 2, 2}, {2, 2, 2, 2}, {2, 2, 2, 2}}, 8) == 0);
}

void testScore(){
	CHECK(score(1234, {{4096, 2048, 2, 2}, {2, 2, 2, 2}, {2, 2, 2, 2}, {2, 2, 2, 2}}, 2) == 1262);
	CHECK(score(1234, {{4, 2, 2, 4}, {4, 2, 2, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, 1) == 1250);
	CHECK(score(1234, {{4, 2, 2, 4}, {4, 2, 2, 0}, {512, 0, 0, 0}, {512, 0, 0, 0}}, 1) == 2274);
}

int main(){
	test_tireDeuxOuQuatre();
	test_plateauVide();
	test_nouvelleTuile();
	test_plateauInitial();
	test_flippe90TrigPlus();
	test_collapseRowLeft();
	test_mergeRowLeft();
	test_deplacementGauche();
	test_deplacementDroite();
	test_deplacementHaut();
	test_deplacementBas();
	test_deplacement();
}