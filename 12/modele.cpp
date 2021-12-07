#include <vector>
#include <iostream>
#include <cstdlib> 
#include <time.h>
#include "modele.h"
#include <ncurses.h>

using namespace std;

typedef vector<vector<int>>Plateau;
// Des fonctions peuvent être ajoutés à ce fichier si besoin est (fonctions pour mettre à jour le score par exemple)


int tireDeuxOuQuatre(){
	vector<int> fillerValues = {2,2,2,2,4,2,2,2,2,2};
	int index = rand() % 10;
	return fillerValues[index];
}

Plateau plateauVide(){
	Plateau pvide;
	pvide = Plateau(4);
	for(int i=0; i<4; i++){
		pvide[i] = vector<int>(4);
	}
	return pvide;
}

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

Plateau plateauInitial(){
	Plateau plateau = nouvelleTuile(nouvelleTuile(plateauVide()));
	return plateau;
}

Plateau flippe90TrigPlus(Plateau plateau){
	Plateau flippedPlateau = plateauVide();
	for(int row=0; row<4;row++){
		for(int column=0; column<4; column++){
			flippedPlateau[row][column]=plateau[column][3-row];
		}
	}
	return flippedPlateau;
}

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

Plateau deplacementGauche(Plateau plateau){
	Plateau shiftGauchePlateau=plateauVide();
	for(int row=0; row<4; row++){
		shiftGauchePlateau[row]=collapseRowLeft(mergeRowLeft(collapseRowLeft(plateau[row])));
	}
	return shiftGauchePlateau;
}

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

Plateau deplacementBas(Plateau plateau){
	//combine elements when possible
	return flippe90TrigPlus(flippe90TrigPlus(flippe90TrigPlus(deplacementDroite(flippe90TrigPlus(plateau)))));
}

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
	}
	if (auxPlateau==plateau){
		throw invalid_argument("Mouvement Invalide!");
	}
	return nouvelleTuile(auxPlateau);
}

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

void dessine_moderne(Plateau p){
    system("clear");
    refresh();
	printw("\n\n\n*****************************\n*");
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			if (p[i][j]==0){
				printw("      *");
			}
			else if(p[i][j]<10){
				printw("  ");
				printw(to_string(p[i][j]).data()); 
				printw("   *");
			}
			else if(p[i][j]<100){
				printw("  ");
				printw(to_string(p[i][j]).data());
				printw("  *");
			}
			else if(p[i][j]<1000){
				printw(" ");
				printw(to_string(p[i][j]).data());
				printw("  *");
			}
			else if (p[i][j]<10000){
				printw(" ");
				printw(to_string(p[i][j]).data());
				printw(" *");
			}
			else if (p[i][j]<100000){
				printw(to_string(p[i][j]).data());
				printw(" *");
			}
			else{
				printw(to_string(p[i][j]).data());
			}
		}
		printw("\n*****************************\n");
		if (i!=3){
			printw("*");
		}
	}
}

void dessine_couleur(Plateau p){
    system("clear");
    refresh();
	//wbkgd(stdscr, COLOR_PAIR(1));
	printw("\n\n\n*****************************\n*");
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			if (p[i][j]==0){
				printw("      *");
			}
			else if(p[i][j]<10){
				printw("  ");
				attron(COLOR_PAIR(log2(p[i][j])%7 + 1));
				printw(to_string(p[i][j]).data());
				attroff(COLOR_PAIR(log2(p[i][j])%7 + 1));
				printw("   *");
			}
			else if(p[i][j]<100){
				printw("  ");
				attron(COLOR_PAIR(log2(p[i][j])%7 + 1));
				printw(to_string(p[i][j]).data());
				attroff(COLOR_PAIR(log2(p[i][j])%7 + 1));
				printw("  *");
			}
			else if(p[i][j]<1000){
				printw(" ");
				attron(COLOR_PAIR(log2(p[i][j])%7 + 1));
				printw(to_string(p[i][j]).data());
				attroff(COLOR_PAIR(log2(p[i][j])%7 + 1));
				printw("  *");
			}
			else if (p[i][j]<10000){
				printw(" ");
				attron(COLOR_PAIR(log2(p[i][j])%7 + 1));
				printw(to_string(p[i][j]).data());
				attroff(COLOR_PAIR(log2(p[i][j])%7 + 1));
				printw(" *");
			}
			else if (p[i][j]<100000){
				attron(COLOR_PAIR(log2(p[i][j])%7 + 1));
				printw(to_string(p[i][j]).data());
				attroff(COLOR_PAIR(log2(p[i][j])%7 + 1));
				printw(" *");
			}
			else{
				attron(COLOR_PAIR(log2(p[i][j])+ 1));
				printw(to_string(p[i][j]).data());
				attroff(COLOR_PAIR(log2(p[i][j])+ 1));
			}
		}
		printw("\n*****************************\n");
		if (i!=3){
			printw("*");
		}
	}
}

bool estPerdant(Plateau plateau){
	Plateau p = plateau;
	if(deplacementDroite(p)==p && deplacementHaut(p)==p && deplacementGauche(p)==p && deplacementBas(p)==p){
		return true;
	}
	return false;
}

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

int log2(int powerof2){
	int ref = powerof2;
	int l = 0;
	while(ref>1){
		ref = ref/2;
		l = l + 1;
	}
	return l;
}

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
}

//tests
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
	int answer = -2;
	while (answer == -2){
		c = getch();
		if(c==KEY_RIGHT){
			answer=0;
		}else if(c==KEY_UP){
			answer =1;
		}else if(c==KEY_LEFT){
			answer=2;
		}else if(c==KEY_DOWN){
			answer=3;
		}else if(c==KEY_DC){
			answer=-1;
		}else{
			answer=-2;
			printw("\nDeplacement non-autorise!\n");
		}
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

void jeu_moderne(){
	initscr();
	refresh();
	cbreak();
	noecho();
	keypad(stdscr,true);
	srand((unsigned) time(0));
	int game_score = 0;
	Plateau plateau = plateauInitial();
	Plateau plateau_next = plateauVide();
	bool jeuGagne = false;
	while(true){		
		dessine_moderne(plateau);
		printw("score :");
		printw(to_string(game_score).data());
		cout << endl;
		try{
			int deplacement_id = get_input_arrows();
			if(deplacement_id==-1){
				printw("Jeu termine");
				system("stty sane");
				return;
			}
			plateau_next = deplacement(plateau, deplacement_id, true);
			game_score = score(game_score, plateau, deplacement_id);
			plateau = plateau_next;
			if(estGagnant(plateau) && jeuGagne==false){	
				jeuGagne = true;
				refresh();
				clear();
				dessine_moderne(plateau);
				printw("Vous avez Gagne! Voulez vous continuer a jouer?(Y/Supr):");
				int c;
				c = getch();
				if(c ==KEY_DC){
					system("stty sane");
					return;
				}
			}else if(estPerdant(plateau)){
				refresh();
				clear();
				dessine_moderne(plateau);
				printw("Vous avez Perdu!");
				system("stty sane");
				return;
			}
			system("clear");
		}catch(invalid_argument e){
			system("clear");
			refresh();
			clear();
			printw("\n");
			printw(e.what());
			printw("\n");
			continue;
		}
		refresh();
		clear();
	}
}

void jeu_moderne_couleur(){
	initscr();
	start_color();
	refresh();
	cbreak();
	noecho();
	keypad(stdscr,true);
	srand((unsigned) time(0));
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(5, COLOR_GREEN, COLOR_BLACK);
	init_pair(6, COLOR_YELLOW, COLOR_BLACK);
	init_pair(7, COLOR_CYAN, COLOR_BLACK);
	int game_score = 0;
	Plateau plateau = plateauInitial();
	Plateau plateau_next = plateauVide();
	bool jeuGagne = false;
	while(true){
		dessine_couleur(plateau);
		printw("score :");
		printw(to_string(game_score).data());
		cout << endl;
		try{
			int deplacement_id = get_input_arrows();
			if(deplacement_id==-1){
				printw("Jeu termine");
				system("stty sane");
				return;
			}
			plateau_next = deplacement(plateau, deplacement_id, true);
			game_score = score(game_score, plateau, deplacement_id);
			plateau = plateau_next;
			if(estGagnant(plateau) && jeuGagne==false){	
				jeuGagne = true;
				refresh();
				clear();
				dessine_couleur(plateau);
				printw("Vous avez Gagne! Voulez vous continuer a jouer?(Y/Supr):");
				int c;
				c = getch();
				if(c ==KEY_DC){
					system("stty sane");
					return;
				}
			}else if(estPerdant(plateau)){
				refresh();
				clear();
				dessine_couleur(plateau);
				printw("Vous avez Perdu!");
				system("stty sane");
				return;
			}
			system("clear");
		}catch(invalid_argument e){
			system("clear");
			refresh();
			clear();
			printw("\n");
			printw(e.what());
			printw("\n");
			continue;
		}
		refresh();
		clear();
	}
	endwin();
	system("stty sane");
}
// void jeu(){
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
// 		cout << "score :" << game_score << endl;
// 		try{
// 			int deplacement_id = get_input_arrows();
// 			if(deplacement_id==-1){
// 				cout << "Jeu termine" << endl;
// 				system("stty sane");
// 				return;
// 			}
// 			plateau_next = deplacement(plateau, deplacement_id, true);
// 			game_score = score(game_score, plateau, deplacement_id);
// 			plateau = plateau_next;
// 			if(estGagnant(plateau) && jeuGagne==false){		
// 				mvwprintw(board_win, 0, 0, dessine(plateau_next).data());
// 				wrefresh(board_win);
// 				jeuGagne = true;
// 				cout << "Vous avez Gagne!\nVoulez vous continuer a jouer?(Y/N):";
// 				string choice;
// 				getline(cin, choice);
// 				if(choice=="N"){
// 					system("stty sane");
// 					return;
// 				}
// 			}else if(estPerdant(plateau)){
// 				mvwprintw(board_win, 0, 0, dessine(plateau_next).data());
// 				wrefresh(board_win);
// 				cout << "Vous avez Perdu!"<<endl;
// 				system("stty sane");
// 				return;
// 			}
// 			system("clear");
// 		}catch(invalid_argument e){
// 			system("clear");
// 			cout << endl << e.what() << endl;
// 			continue;
// 		}
// 	}
// 	endwin();
// 	system("stty sane");
// }




//@pablo-chulilla
//issues left: should display deplacement invalide when non arrow key pressed
//instead of exiting the game, also displays ^D when up is pressed, shouldnt
//messes up the terminal display after game, undisplayed comands and no newlines

