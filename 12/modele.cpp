#include <vector>
#include <iostream>
#include <cstdlib> 
#include <time.h>
#include "modele.h"
#include <ncurses.h>

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

/** génère une nouvelle tuile 2 ou 4 sur une case aleatoire d'un plateau
 * @param Plateau un plateau
 * @return Plateau avec une nouvelle tuile 2 ou 4
 **/
Plateau nouvelleTuile(Plateau plateau){
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

/**
 * Effectue une rotation de 90 degre dans le sens trigonometrique positif d'un plateau
 * @param Plateau plateau
 * @return Plateau rotation d'un quart de tour du plateau
 */
Plateau flippe90TrigPlus(Plateau plateau){
	Plateau flippedPlateau = plateauVide();
	for(int row=0; row<4;row++){
		for(int column=0; column<4; column++){
			flippedPlateau[row][column]=plateau[column][3-row];
		}
	}
	return flippedPlateau;
}

/**
 * Tasse vers la gauche toutes les tuiles non nuls d'une ligne
 * @param vector<int>: une ligne du plateau
 * @return vector<int>: la ligne tassée a gauche
 */
vector<int> collapseRowLeft(vector<int> row){
	vector<int> nrow = vector<int>(4);
	int count=0;
	for (int column=0; column<4; column++){
			if(row[column]!=0){
				nrow[count]=row[column];
				count++;
			}
			else{
				continue;
			}
	}
	return nrow;
}

/**
 * Combine les cases d'un tableau si possible, place des zeros
 * 
 * @param vector<int> un tableau de taille 4
 * @return vector<int> le tableau avec les cases combinées vers la gauche si possible
 */
vector<int> mergeRowLeft(vector<int> row){
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

/** déplace les tuiles d'un Plateau vers la gauche et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers la gauche
 **/
Plateau deplacementGauche(Plateau plateau){
	Plateau shiftGauchePlateau=plateauVide();
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
Plateau deplacement(Plateau plateau, int direction, bool tuile){
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
	}
	if (auxPlateau==plateau){
		throw invalid_argument("Mouvement Invalide!");
	}
	else{
		if(tuile){
		return nouvelleTuile(auxPlateau);
		}
		else{
			return auxPlateau;
		}
	}
}


/** affiche un Plateau
 * @param p le Plateau
 **/
string dessine(Plateau p){
	string aDessiner = 	"\n*****************************\n*";
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			if (p[i][j]==0){
				aDessiner += "      *";
			}
			else if(p[i][j]<10){
				aDessiner += "  "+ to_string(p[i][j]) + "   *";
			}
			else if(p[i][j]<100){
				aDessiner += "  " + to_string(p[i][j]) + "  *";
			}
			else if(p[i][j]<1000){
				aDessiner += " " + to_string(p[i][j]) + "  *";
			}
			else if (p[i][j]<10000){
				aDessiner += " " + to_string(p[i][j]) + " *";
			}
			else if (p[i][j]<100000){
				aDessiner += "" + to_string(p[i][j]) + " *";
			}
			else{
				aDessiner += "" + to_string(p[i][j]) + "*";
			}
		}
		if (i!=3){
			aDessiner += "\n*****************************\n*";
		}else{
			aDessiner += "\n*****************************\n";
		}
	}
	return aDessiner;
}


/** permet de savoir si une partie est terminée
 *  @param plateau un Plateau
 *  @return true si le plateau est vide, false sinon
 **/
bool estPerdant(Plateau plateau){
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



int count(Plateau plateau, int powerof2){
	int sum = 0;
	for(int row=0; row<4; row++){
		for(int column=0; column<4; column++){
			if(plateau[row][column]==powerof2){
				sum++;
			}
		}
	}
	return sum;
}


//new proposed implementation by @pablo-chulilla
//still debating logic regarding the score incrementation

int score(int score_avant, Plateau avant, int ideplacement){
	Plateau apres;
	apres = deplacement(avant, ideplacement, false);
	int nscore=score_avant;
	vector<vector<int>> avant_freq= {{2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
	vector<vector<int>> apres_freq= avant_freq;
	for(int column=0; column<17; column++){
		avant_freq[1][column]=count(avant, avant_freq[0][column]);
		apres_freq[1][column]=count(apres, apres_freq[0][column]);
	}
	for(int column=0; column<17; column++){
		if(apres_freq[1][column]>avant_freq[1][column]){
			nscore += avant_freq[0][column]*(apres_freq[1][column]-avant_freq[1][column]);
		}
		if(apres_freq[1][column]<avant_freq[1][column] and apres_freq[1][column + 1]==avant_freq[1][column + 1]){
			nscore = nscore + avant_freq[0][column]*(avant_freq[1][column]-apres_freq[1][column]);
		}
	}
	return nscore;
}




char input_dhgb(){
	// cin.ignore(12000,'\n');
	string input;
	cout<<"Entrer commande:";
	getline(cin, input);
	if(input.length()!=1){
		throw invalid_argument("Deplacement non-autorise!");
	}
	char output = input[0];
	output = toupper(output);
	if(output!='D' && output!='H' && output!='G' && output!='B' && output!='Q'){
		throw invalid_argument("Deplacement non-autorise!");
	}
	return output;

	// char output = input[0];
	// output = toupper(output);
		
	// return output;
}



int ideplacement_dhgb(char dhgb){
	switch (dhgb){
		case 'D':
			return 0;
			break;
		case 'H':
			return 1;
			break;
		case 'G':
			return 2;
			break;
		case 'B':
			return 3;
			break;
		case 'Q':
			return -1;
			break;
		default:
			throw invalid_argument("if this appears, run!");
		}
}



int get_input_arrows(){
	int c;
	// newterm(NULL, stdin, stdout);
	// keypad(stdscr, true);
	c = getch();
	addch(c);
	// ;
	int answer;
	if(c==KEY_RIGHT){
		answer=0;
	}
	else if(c==KEY_UP){
		answer =1;
	}else if(c==KEY_LEFT){
		answer=2;
	}else if(c==KEY_DOWN){
		answer=3;
	}else{
		answer=-1;
	}
	return answer;
}


void jeu(){
	srand((unsigned) time(0));
	int game_score = 0;
	Plateau plateau = plateauInitial();
	Plateau plateau_next = plateauVide();
	bool jeuGagne = false;
	while(true){
		cout << dessine(plateau)<< endl << "score:" <<game_score<<endl;
		try{
			int deplacement_id = ideplacement_dhgb(input_dhgb());
			if(deplacement_id==-1){
				cout << "Jeu terminee" << endl;
				return;
			}
			plateau_next = deplacement(plateau, deplacement_id, true);
			game_score = score(game_score, plateau, deplacement_id);
			plateau = plateau_next;
			if(estGagnant(plateau) && jeuGagne==false){
				cout << dessine(plateau_next) << endl;
				jeuGagne = true;
				cout << "Vous avez Gagne!\nVoulez vous continuer a jouer?(Y/N):";
				string choice;
				getline(cin, choice);
				if(choice=="N"){
					return;
				}
			}else if(estPerdant(plateau)){
				cout << dessine(plateau_next) << endl;
				cout << "Vous avez Perdu!"<<endl;
				return;
			}
			system("clear");
		}catch(invalid_argument e){
			system("clear");
			cout << endl << e.what() << endl;
			continue;
		}
	}
}



// void jeu(){
// 	// initscr();
// 	// raw();
// 	// noecho();
// 	// keypad(stdscr,true);
// 	// srand((unsigned) time(0));
// 	// int game_score = 0;
// 	// Plateau plateau = plateauInitial();
// 	// Plateau plateau_next = plateauVide();
// 	// bool jeuGagne = false;
// 	// while(true){
// 	// 	cout << dessine(plateau)<< endl << "score:" <<game_score<<endl;
// 	// 	try{
// 	// 		//int deplacement_id = ideplacement_dhgb(input_dhgb());
// 	// 		int deplacement_id = get_input_arrows();
// 	// 		if(deplacement_id==-1){
// 	// 			cout << "Jeu terminee" << endl;
// 	// 			return;
// 	// 		}
// 	// 		plateau_next = deplacement(plateau, deplacement_id, true);
// 	// 		game_score = score(game_score, plateau, deplacement_id);
// 	// 		plateau = plateau_next;
// 	// 		if(estGagnant(plateau) && jeuGagne==false){
// 	// 			cout << dessine(plateau_next) << endl;
// 	// 			jeuGagne = true;
// 	// 			cout << "Vous avez Gagne!\nVoulez vous continuer a jouer?(Y/N):";
// 	// 			string choice;
// 	// 			getline(cin, choice);
// 	// 			if(choice=="N"){
// 	// 				return;
// 	// 			}
// 	// 		}else if(estPerdant(plateau)){
// 	// 			cout << dessine(plateau_next) << endl;
// 	// 			cout << "Vous avez Perdu!"<<endl;
// 	// 			return;
// 	// 		}
// 	// 		system("clear");
// 	// 	}catch(invalid_argument e){
// 	// 		system("clear");
// 	// 		cout << endl << e.what() << endl;
// 	// 		continue;
// 	// 	}
// 	// }
// 	// endwin();





//@pablo-chulilla
//issues left: should display deplacement invalide when non arrow key pressed
//instead of exiting the game, also displays ^D when up is pressed, shouldnt
//messes up the terminal display after game, undisplayed comands and no newlines




// 	initscr();
// 	refresh();
// 	cbreak();
// 	noecho();
// 	keypad(stdscr,true);
// 	srand((unsigned) time(0));
// 	char vide = ' ';
// 	int xMax, yMax;
// 	getmaxyx(stdscr, yMax, xMax);
// 	WINDOW * board_win = newwin(11, 31, (yMax/2) - 7, (xMax/2) - 16);
// 	refresh();
// 	int game_score = 0;
// 	Plateau plateau = plateauInitial();
// 	Plateau plateau_next = plateauVide();
// 	bool jeuGagne = false;
// 	while(true){		
// 		refresh();
// 		mvwprintw(board_win, 0, 0, "-----------------------------\n-      -      -      -      -\n-----------------------------\n-      -      -      -      -\n-----------------------------\n-      -      -      -      -\n-----------------------------\n-      -      -      -      -\n-----------------------------\n-----------------------------");
// 		wrefresh(board_win);
// 		mvwprintw(board_win, 0, 0, dessine(plateau).data());
// 		wrefresh(board_win);
// 		//dessine(plateau);
// 		//cout << endl; 
// 		//cout << "score:" <<game_score<<endl;
// 		//cout << dessine(plateau)<< endl << "score:" <<game_score<<endl;
// 		try{
// 			//int deplacement_id = ideplacement_dhgb(input_dhgb());
// 			int deplacement_id = get_input_arrows();
// 			if(deplacement_id==-1){
// 				cout << "Jeu termine" << endl;
// 				return;
// 			}
// 			plateau_next = deplacement(plateau, deplacement_id, true);
// 			game_score = score(game_score, plateau, deplacement_id);
// 			plateau = plateau_next;
// 			if(estGagnant(plateau) && jeuGagne==false){		
// 				mvwprintw(board_win, 0, 0, dessine(plateau_next).data());
// 				wrefresh(board_win);
// 				//dessine(plateau_next);
// 				//cout << endl; 
// 				//cout << dessine(plateau_next) << endl;
// 				jeuGagne = true;
// 				cout << "Vous avez Gagne!\nVoulez vous continuer a jouer?(Y/N):";
// 				string choice;
// 				getline(cin, choice);
// 				if(choice=="N"){
// 					return;
// 				}
// 			}else if(estPerdant(plateau)){
// 				mvwprintw(board_win, 0, 0, dessine(plateau_next).data());
// 				wrefresh(board_win);
// 				//dessine(plateau_next);
// 				//cout << endl; 
// 				//cout << dessine(plateau_next) << endl;
// 				cout << "Vous avez Perdu!"<<endl;
// 				return;
// 			}
// 			system("clear");
// 		}catch(invalid_argument e){
// 			system("clear");
// 			cout << endl << e.what() << endl;
// 			continue;
// 		}
// 	}
// 	system("clear");
// 	endwin();
// }





