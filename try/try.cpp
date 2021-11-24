// #include <vector>
// #include <iostream>
// #include "../modele.h"
// #include <cstdlib> 
// #include <time.h>
// //#include <ncurses.h>
// using namespace std;
// typedef vector<vector<int> > Plateau;

// #include <unistd.h>



#include <vector>
#include <iostream>
#include <cstdlib> 
#include <time.h>
#include "../modele.h"
using namespace std;


typedef vector<vector<int>>Plateau;
/** Des fonctions peuvent être ajoutés à ce fichier si besoin est (fonctions pour mettre à jour le score par exemple)
 * //


/** génère aléatoirement un 2 ou un 4 avec des probabilités respectives de 9/10 et 1/10
 *  @return 2 ou 4
 **/
int tireDeuxOuQuatre(){
	vector<int> fillerValues = {2,2,2,2,4,2,2,2,2,2};
	int index = rand() % 10;
	return fillerValues[index];
}

/** génère un Plateau de dimensions 4*4 ne contenant que des 0
 *  @return un Plateau vide
 **/
Plateau plateauVide(){
	Plateau pvide;
	pvide = Plateau(4);
	for(int i=0; i<4; i++){
		pvide[i] = vector<int>(4);
	}
	return pvide;
}

static Plateau nouvelleTuile(Plateau plateau){
	int v = tireDeuxOuQuatre();
	int i = rand() % 4;
	int j = rand() % 4;
	Plateau copy = plateau;
	while (copy[i][j]!=0){
		i = rand() % 4;
		j = rand() % 4;
	}
	copy[i][j]=v;
	return copy;
}


/** génère deux nombres sur des cases aléatoires d'un Plateau vide
 *  @return un Plateau en début de jeu
 **/
Plateau plateauInitial(){
	Plateau plateau = nouvelleTuile(nouvelleTuile(plateauVide()));
	return plateau;
}


static Plateau flippe90TrigPlus(Plateau plateau){
	Plateau flippedPlateau = plateauVide();
	for(int row=0; row<4;row++){
		for(int column=0; column<4; column++){
			flippedPlateau[row][column]=plateau[column][3-row];
		}
	}
	return flippedPlateau;
}


/** déplace les tuiles d'un Plateau vers la gauche et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers la gauche
 **/
static vector<int> collapseRowLeft(vector<int> row){
	vector<int> nrow = vector<int>(4);
	int count=0;
	for (int column=0; column<4; column++){
			if(row[column]!=0){
				nrow[count]=row[column];
				count++;
			}
			else{
				continue;
				// count++;
			}
	}
	return nrow;
}
static vector<int> mergeRowLeft(vector<int> row){
	vector<int> nrow = vector<int>(4);
	int count=0;
	for (int column=0; column<4; column++){
		if (column!=3 && row[column]==row[column+1]){
			nrow[count]=row[count]*2;
			column++;
			count++;
		}
		else{
			nrow[count]=row[column];
		}
		count++;
	}
	return nrow;
}
Plateau deplacementGauche(Plateau plateau){
	Plateau shiftGauchePlateau=plateauVide();
	//combine elements when possible
	for(int row=0; row<4; row++){
		shiftGauchePlateau[row]=collapseRowLeft(mergeRowLeft(collapseRowLeft(plateau[row])));
	}
	return shiftGauchePlateau;
}


/** déplace les tuiles d'un Plateau vers la droite et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers la droite
 **/
Plateau deplacementDroite(Plateau plateau){
	//combine elements when possible
	return flippe90TrigPlus(flippe90TrigPlus(deplacementGauche(flippe90TrigPlus(flippe90TrigPlus(plateau)))));
}


/** déplace les tuiles d'un Plateau vers le haut et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers le haut
 **/
Plateau deplacementHaut(Plateau plateau){
	//combine elements when possible
	return flippe90TrigPlus(flippe90TrigPlus(flippe90TrigPlus(deplacementGauche(flippe90TrigPlus(plateau)))));
}


/** déplace les tuiles d'un Plateau vers le bas et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers le bas
 **/
Plateau deplacementBas(Plateau plateau){
	//combine elements when possible
	return flippe90TrigPlus(flippe90TrigPlus(flippe90TrigPlus(deplacementDroite(flippe90TrigPlus(plateau)))));
}





/** déplace les tuiles d'un Plateau dans la direction donnée et génère une nouvelle tuile si le déplacement est valide
 *  @param plateau le Plateau
 *  @param direction la direction 0 droite 1 Haut 2 Gauche 3 Bas
 *  @return le Plateau déplacé dans la direction
 **/
Plateau deplacement(Plateau plateau, int direction){
	Plateau auxPlateau;
	switch (direction){
		case 0:
			auxPlateau = deplacementDroite(plateau);
			break;
		case 1:
			auxPlateau = deplacementHaut(plateau);
			break;
		case 2:
			auxPlateau = deplacementGauche(plateau);
			break;
		case 3:
			auxPlateau = deplacementBas(plateau);
			break;
		default:
			cerr << "Deplacement non-autorise!" << endl;
			exit(-1);
	}
	if (auxPlateau==plateau){
		throw invalid_argument("Mouvement Invalide!");
	}
	else{
		return nouvelleTuile(auxPlateau);
	}
}


/** affiche un Plateau
 * @param p le Plateau
 **/
string dessine(Plateau p){
	string aDessiner = 	"*************************\n*";
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			if (p[i][j]==0){
				aDessiner += "     *";
			}
			else if(p[i][j]<10){
				aDessiner += "  "+ to_string(p[i][j]) + "  *";
			}
			else if(p[i][j]<100){
				aDessiner += " " + to_string(p[i][j]) + "  *";
			}
			else if(p[i][j]<1000){
				aDessiner += " " + to_string(p[i][j]) + " *";
			}
			else{
				aDessiner += "" + to_string(p[i][j]) + " *";
			}
			// aDessiner += to_string(p[i][j]) + " ";
		}
		if (i!=3){
			aDessiner += "\n*************************\n*";
		}else{
			aDessiner += "\n*************************\n";
		}
	}
	return aDessiner;
}


/** permet de savoir si une partie est terminée
 *  @param plateau un Plateau
 *  @return true si le plateau est vide, false sinon
 **/
bool estTermine(Plateau plateau){
	Plateau p = plateau;
	if(deplacementDroite(p)==p && deplacementHaut(p)==p && deplacementGauche(p)==p && deplacementBas(p)==p){
		return true;
	}
	return false;
}


/** permet de savoir si une partie est gagnée
 * @param plateau un Plateau
 * @return true si le plateau contient un 2048, false sinon
 **/
bool estGagnant(Plateau plateau){
	for(int row=0; row<4; row++){
		for(int column=0; column<4; column++){
			if(plateau[row][column]==2048){
				return true;
			}
		}
	}
	return false;
}


static int log2(int n){
	int count=1;
	int nn = n;
	while(nn!=2){
		nn = nn / 2;
		count++;
	}
	return count;
}

int abs(int n){
	if(n>=0){
		return n;
	}
	return -n;
}

int score(int score_avant, Plateau avant, int deplacement){
	Plateau apres;
	switch (deplacement){
	case 0:
		apres = deplacementDroite(avant);
		break;
	case 1:
		apres = deplacementHaut(avant);
		break;
	case 2:
		apres = deplacementGauche(avant);
		break;
	case 3:
		apres = deplacementBas(avant);
		break;
	}
	vector<vector<int>> avant_apres= vector<vector<int>>(17);
	for(int i=0; i<17; i++){
		avant_apres[i]=vector<int>(2);
		avant_apres[i]={0,0};
	}
	for(int row=0; row<4;row++){
		for(int column=0; column<4; column++){
			if(avant[row][column]!=0){
				avant_apres[log2(avant[row][column])][0] == avant_apres[log2(avant[row][column])][0]+1;
			}
			if(apres[row][column]!=0){
				avant_apres[log2(apres[row][column])][1] == avant_apres[log2(avant[row][column])][1]+1;
			}
		}
	}
	int somme=0;
	int c = 1;
	for(int i=0; i<17; i++){
		c = c * 2;
		if (abs(avant_apres[i][1]-avant_apres[i][0])==(avant_apres[i][1]-avant_apres[i][0]) and (avant_apres[i][1]-avant_apres[i][0]!= 0)){
			score = score + abs(avant_apres[i][1]-avant_apres[i][0])*c;
		}
		if (abs(avant_apres[i][1]-avant_apres[i][0])>(avant_apres[i][1]-avant_apres[i][0]) and (avant_apres[i][1]-avant_apres[i][0]!= 0)){
			score = score + abs(avant_apres[i][1]-avant_apres[i][0])*c*2;
		}
	}
	return score;
	
}




int main(){
	// initscr();
	// start_color();
	// init_color(COLOR_RED, 700, 0, 0);
	// init_color(COLOR_BLACK, 500, 500, 500);
	// init_pair(1, COLOR_RED, COLOR_BLACK);	
	// attron(COLOR_PAIR(1));
	// printw("Viola !!! In color ...");
	// attroff(COLOR_PAIR(1));
	// // attron(COLOR_PAIR(2));
	// getch();
	// endwin();
	Plateau testPlateau = {
		{,16,8,16},
		{8,4,2,8},
		{2,8,4,2},
		{16,4,2,8}
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
		{2048,2048,2048,2048}
	};
	cout<< abs(-3)<<endl;
}