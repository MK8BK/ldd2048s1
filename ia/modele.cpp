#include <vector>
#include <iostream>
#include <cstdlib> 
#include <time.h>
#include "modele.h"
#include <fstream>
#include <tuple>
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


Plateau flippe90TrigPlus(Plateau plateau){
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
				// count++;
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
	string aDessiner = 	"*****************************\n*";
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




//tested manually
int count_tableau(vector<int> tableau, int valeur){
	int sum = 0;
	for(int row=0; row<tableau.size(); row++){
		if(tableau[row]==valeur){
			sum=sum+1;
		}
		else{
			continue;
		}
	}
	return sum;
}

//tested manually
int count_plateau(Plateau plateau, int valeur){
	int sum=0;
	for(int row=0; row<4; row++){
		sum+= count_tableau(plateau[row], valeur);

	}
	return sum;
}

//well tested by @pablo-chullila
int score(int score_avant, Plateau avant, int ideplacement){
	Plateau apres;
	apres = deplacement(avant, ideplacement, false);
	int nscore=score_avant;
	vector<vector<int>> avant_freq= {{2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
	vector<vector<int>> apres_freq= avant_freq;
	for(int column=0; column<17; column++){
		avant_freq[1][column]=count_plateau(avant, avant_freq[0][column]);
		apres_freq[1][column]=count_plateau(apres, apres_freq[0][column]);
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

//well tested
char input_dhgb(){
	char output;

	cout<<"Entrer commande:";
	cin >> output;
	output = toupper(output);
	if(output!='D' && output!='H' && output!='G' && output!='B'){
		throw invalid_argument("Deplacement non-autorise!");
	}	
	return output;
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

//io functions
tuple<int, int, Plateau> read_configuration(string path){
	Plateau plateau = plateauVide();
	ifstream file;
	file.open(path);
	int iteration;
	int score;
	file >> iteration;
	file >> score;
	string v0;
	string v1;
	string v2;
	string v3;
	int i=0;
	while (getline(file, v0,',')){
		getline(file, v1, ',');
		getline(file, v2, ',');
		getline(file, v3, ';');
		plateau[i][0]=stoi(v0);
		plateau[i][1]=stoi(v1);
		plateau[i][2]=stoi(v2);
		plateau[i][3]=stoi(v3);
		i++;
	}
	file.close();
	tuple<int, int, Plateau> tup(iteration, score, plateau);
	return tup;
}

tuple<int, int, Plateau> read_updated_configuration(int iteration, string path){
	while(get<0>(read_configuration(path))==iteration){
		continue;
	}
	tuple<int, int, Plateau> tup = read_configuration(path);
	return tup;
}

void write_mouvement(string path, int iteration, char mouvement){
	ofstream file;
	if(iteration==0){
		file.open(path);
		file << "MIP" << endl;
	}
	else{
		file.open(path, ios::app);
	}
	file << to_string(iteration) << " " << mouvement << endl;
	file.close();
}

tuple<int, char> read_mouvement(string path){
	ifstream mouvements_file;
	mouvements_file.open(path);
	int iteration;
	string c;
	mouvements_file >> c;
	while(mouvements_file.good()){
		mouvements_file >> iteration;
		mouvements_file >> c;
	}
	mouvements_file.close();
	char rc = c[0];
	tuple<int, char> tup = make_tuple(iteration, rc);
	return tup;
}

tuple<int, char> read_updated_mouvement(string path, int iteration){
	while(get<0>(read_mouvement(path))==iteration){
		continue;
	}
	return(read_mouvement(path));
}

void write_new_config(string path, int iteration, int game_score, Plateau plateau){
	ofstream configuration;
	configuration.open(path);
	configuration << iteration << " "<< game_score << endl;
	for(int row=0; row<4; row++){
		configuration <<plateau[row][0]<<","<<plateau[row][1]<<","
			<<plateau[row][2]<<","<<plateau[row][3]<<";";
		if(row!=3){
			configuration << endl;
		}
	}
	configuration.close();
}



//helper functions

//tested manually
tuple<int,int,vector<int>> max_tableau(vector<int> tableau){
	int vmax=tableau[0];
	for(int column=0; column<tableau.size(); column++){
		if(tableau[column]>vmax){
			vmax = tableau[column];
		}
	}	
	int n_vmax = count_tableau(tableau, vmax);
	vector<int> ivmax = vector<int>(n_vmax);
	int i=0;
	for(int column=0; column<tableau.size(); column++){
		if(tableau[column]==vmax){
			ivmax[i]=column;
			i++;
		}
	}
	tuple<int, int, vector<int>> tup = make_tuple(vmax, n_vmax, ivmax);

	return tup;
}


//tested manually
tuple<int, int, vector<vector<int>>> max_plateau(Plateau plateau){
	int maxv=plateau[0][0];
	for(int row=0; row<4; row++){
		for(int column=0; column<4; column++){
			if(plateau[row][column]>maxv){
				maxv = plateau[row][column];
			}
		}
	}
	int num_maxv=count_plateau(plateau, maxv);
	vector<vector<int>> coordinates = vector<vector<int>>(num_maxv);
	int i=0;
	for(int row=0; row<4; row++){
			for(int column=0; column<4; column++){
				if(plateau[row][column]==maxv){
					coordinates[i] = vector<int>(2);
					coordinates[i] = {row, column};
					i++;
				}
			}
		}

	tuple<int, int, vector<vector<int>>> tup = make_tuple(maxv, num_maxv, coordinates);
	return tup;
}

//tested manually
int sum_tableau(vector<int> tableau){
	int sum=0;
	for(int i=0; i<tableau.size(); i++){
			sum+=tableau[i];
	}	
	return sum;
}

//tested manually
int sum_plateau(Plateau plateau){
	int sum=0;
	for(int row=0; row<4; row++){
		sum+=sum_tableau(plateau[row]);
	}
	return sum;
}

//tested manually
//@pablo-chulilla
int log2(int powerof2){
	int ref = powerof2;
	int l = 0;
	while(ref>1){
		ref = ref/2;
		l = l + 1;
	}
	return l;
}

//tested manually
//monstrous, but works, and not that inefficient
//currnly modifying
/**
 * @brief returns a tuple containing the a vector of the descriptions of max edges,
 * and a vector containing the max_edges
 * 
 * @param Plateau plateau 
 * @return tuple<vector<string>, vector<vector<int>>> 
 */
tuple<vector<string>, vector<vector<int>>> max_edge(Plateau plateau){
	Plateau np = plateau;
	vector<int> sums = vector<int>(4);
	for(int i=0; i<4; i++){
		sums[i]=sum_tableau(np[0]);
		np=flippe90TrigPlus(np);
	}
	int vmax = get<0>(max_tableau(sums));
	
}

//tested manually
//if you thought max_edge() was monstrous, check this
// tuple<string, vector<int>> max_half_edge(Plateau plateau){
// 	vector<int> vertical_right_up_hedge = {plateau[0][3], plateau[1][3]};
// 	vector<int> vertical_right_bottom_hedge = {plateau[2][3], plateau[3][3]};
// 	vector<int> vertical_left_up_hedge = {plateau[0][0], plateau[1][0]};
// 	vector<int> vertical_left_bottom_hedge = {plateau[2][0], plateau[3][0]};
// 	vector<int> horizontal_top_left_hedge = {plateau[0][0], plateau[0][1]};
// 	vector<int> horizontal_top_right_hedge = {plateau[0][2], plateau[0][3]};
// 	vector<int> horizontal_bottom_left_hedge = {plateau[3][0], plateau[3][1]};
// 	vector<int> horizontal_bottom_right_hedge = {plateau[3][2], plateau[3][3]};
// 	int vertical_right_up_hedge_sum      = sum_tableau(vertical_right_up_hedge);
// 	int vertical_right_bottom_hedge_sum  = sum_tableau(vertical_right_bottom_hedge);
// 	int vertical_left_up_hedge_sum       = sum_tableau(vertical_left_up_hedge);
// 	int vertical_left_bottom_hedge_sum   = sum_tableau(vertical_left_bottom_hedge);
// 	int horizontal_top_left_hedge_sum    = sum_tableau(horizontal_top_left_hedge);
// 	int horizontal_top_right_hedge_sum   = sum_tableau(horizontal_top_right_hedge);
// 	int horizontal_bottom_left_hedge_sum = sum_tableau(horizontal_bottom_left_hedge);
// 	int horizontal_bottom_right_hedge_sum= sum_tableau(horizontal_bottom_right_hedge);
// 	vector<int> sums = {vertical_right_up_hedge_sum, vertical_right_bottom_hedge_sum,
// 						vertical_left_up_hedge_sum, vertical_left_bottom_hedge_sum, 
// 						horizontal_top_left_hedge_sum, horizontal_top_right_hedge_sum,
// 						horizontal_bottom_left_hedge_sum, horizontal_bottom_right_hedge_sum};
// 	try{
// 		int max_edge_sum = max_tableau(sums)[0];
// 		int max_edge_sum_index = max_tableau(sums)[1];
// 		cout << to_string(max_edge_sum) << "  " <<to_string(max_edge_sum_index)<<endl;
// 		if(max_edge_sum_index==0){
// 			tuple<string, vector<int>> tup1 = make_tuple("vru",vertical_right_up_hedge);
// 			return tup1;
// 		}
// 		else if(max_edge_sum_index==1){
// 			tuple<string, vector<int>> tup2 = make_tuple("vrb",vertical_right_bottom_hedge);
// 			return tup2;
// 		}
// 		else if(max_edge_sum_index==2){
// 			tuple<string, vector<int>> tup3 = make_tuple("vlu",vertical_left_up_hedge);
// 			return tup3;
// 		}
// 		else if(max_edge_sum_index==3){
// 			tuple<string, vector<int>> tup4 = make_tuple("vlb",vertical_left_bottom_hedge);
// 			return tup4;
// 		}
// 		else if(max_edge_sum_index==4){
// 			tuple<string, vector<int>> tup5 = make_tuple("htl",horizontal_top_left_hedge);
// 			return tup5;
// 		}
// 		else if(max_edge_sum_index==5){
// 			tuple<string, vector<int>> tup6 = make_tuple("htr",horizontal_top_right_hedge);
// 			return tup6;
// 		}
// 		else if(max_edge_sum_index==6){
// 			tuple<string, vector<int>> tup7 = make_tuple("hbl",horizontal_bottom_left_hedge);
// 			return tup7;
// 		}
// 		else{
// 			tuple<string, vector<int>> tup8 = make_tuple("hbr",horizontal_bottom_right_hedge);
// 			return tup8;
// 		}
// 	}catch(invalid_argument &e){
// 		throw e;
// 	}
// }

//tested manually
bool decroissance(vector<int> tableau){
	if(tableau[0]>tableau[1]){
		for(int i=0; i<tableau.size()-1; i++){
			if(tableau[i]<tableau[i+1]){
				return false;
			}
		}
	}else{
		for(int i=0; i<tableau.size()-1; i++){
			if(tableau[i]>tableau[i+1]){
				return false;
			}
		}
	}
	return true;
}





//favor functions
// favor functions use all the previous functions to give a "favor score" 
// to a plateau, depending on the good or bad disposition of the numbers,
//these functions return a number in the range 0-512 (for later statistical
// optimization)

//tested manually
int calc_empty_favor(Plateau plateau){
	return count_plateau(plateau,0)*32;
}


//tested manually
//find a way to output between 0-512 in a reasonable way compared to other functions
int incremented_score_favor(Plateau plateau_avant, int deplacement){
	int incremented_game_score = score(0, plateau_avant, deplacement);
	return incremented_game_score;
}

//tested manually
// int maximum_placement_favor(Plateau plateau){
// 	vector<int> placement = get<1>(max_plateau(plateau));
// 	if((placement[0]==0 || placement[0]==3) && (placement[1]==0 || placement[1]==3)){
// 		return 512;
// 	}
// 	else if((placement[0]==0 || placement[0]==3) || (placement[1]==0 || placement[1]==3)){
// 		return 256;
// 	}
// 	else{
// 		return 0;
// 	}
// }


//still needs more logical maturity and outlook
// int maximum_movement_favor(Plateau pavant, Plateau papres){
// 	int favor_avant = maximum_placement_favor(pavant);
// 	int favor_apres = maximum_placement_favor(papres);
// 	if(favor_apres==512){
// 		return 512;
// 	}else if(favor_apres==256){
// 		if(favor_avant==512){
// 			return 0;
// 		}else if(favor_avant==256){
// 			return 256;
// 		}else{
// 			return 512;
// 		}
// 	}else{
// 		return 0;
// 	}
// }

// int maximum_value_change_favor(Plateau pavant, Plateau papres){
// 	try{
// 		int maxapres = get<0>(max_plateau(papres));
// 		if(count_plateau())
// 		return 256;
// 	}catch(invalid_argument &e){
// 		return 512;
// 	}

// 	return 0;
// }



//the final ai does not work yet, saving for later  vector<int> weights
// int eval_move(Plateau p, char move, vector<int> weights){
// 	try{
// 		deplacement(p,ideplacement_dhgb(move),false);
// 	}catch(invalid_argument e){
// 		return -1;
// 	}
// 	if(estPerdant(deplacement(p,ideplacement_dhgb(move), false))){
// 		return -1;
// 	}

// 	int w1, w2, w3, w4, w5, w6, w7, w8, w9, w10;
// 	w1, w2, w3 = weights[0], weights[1], weights[2];
// 	w4, w5 = weights[3], weights[4];//, weights[5];
// 	//w7, w8, w9 = weights[6], weights[7], weights[8];
// 	//w10 = weights[9];

// 	Plateau np = deplacement(p,ideplacement_dhgb(move),false);
// 	int favor=0;
// 	favor+=calc_empty_favor(deplacement(p,ideplacement_dhgb(move), true))*w1;
// 	//favor+=maximum_movement_favor(p, np)*w2;
// 	favor+=incremented_score_favor(p,ideplacement_dhgb(move))*w3;
// 	//favor+=maximum_placement_favor(p)*w4;
// 	//favor+=maximum_placement_favor(np)*w5;
// 	return favor;
// }





// void ai_answer(string config_path, string move_path, int iteration){
// 	Plateau p = get<2>(read_updated_configuration(iteration,move_path));
// 	Plateau np;
// 	vector<int> weights = {1,1,10,1,1};
// 	vector<char> moves = {'H','B','G','D'};
// 	vector<int> favor_moves = {eval_move(p, moves[0], weights), 
// 			eval_move(p, moves[1], weights), eval_move(p, moves[2], weights),
// 			eval_move(p, moves[3], weights)};
	
// 	// if(count_tableau(favor_moves, -1)==4){
// 	// 	cout<<"perd"<<endl;
// 	// 	exit(1);
// 	// }
// 	try{
// 		write_mouvement(move_path,iteration,moves[max_tableau(favor_moves)[2]]);
// 	}catch(invalid_argument &e){
// 		write_mouvement(move_path,iteration,moves[rand()%4]);

// 	}
// 	//write_mouvement(move_path, iteration, maxm);
// }