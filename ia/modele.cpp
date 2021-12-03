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

vector<int> read_weights(string path){
	ifstream file;
	file.open(path);
	vector<int> weights=vector<int>(10);
	int temp=0;
	string stemp;
	for(int i=0; i<10; i++){
		getline(file, stemp, ' ');
		temp = stoi(stemp);
		weights[i]=temp;
	}
	file.close();
	return weights;
}

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

float average(vector<int> t){
	float s = (float)(sum_tableau(t)) / (float)(t.size());
	return s;
}

//{"ht","vr","hb","vl"}
vector<vector<int>> extract_edges(Plateau plateau){
	return {plateau[0], {plateau[0][3],plateau[1][3],plateau[2][3],plateau[3][3]},
	plateau[3],{{plateau[0][0],plateau[1][0],plateau[2][0],plateau[3][0]}}};
}

//{"htl","htr","vrt","vrb","hbl","hbr","vlt","vlb"}
vector<vector<int>> extract_half_edges(Plateau plateau){
	vector<vector<int>> extracted = extract_edges(plateau);
	vector<vector<int>> half_edges = vector<vector<int>>(8);
	int count=0;
	for(vector<int> edge:extracted){
		half_edges[count] = {edge[0],edge[1]};
		count++;
		half_edges[count] = {edge[3],edge[2]};
		count++;
	}
	return half_edges;
}

//tested manually
//monstrous, but works, and not that inefficient
tuple<vector<string>, vector<vector<int>>> max_edge(Plateau plateau){
	vector<vector<int>> edges = extract_edges(plateau);
	vector<int> sums = vector<int>(4);
	for(int i=0; i<4; i++){
		sums[i]=sum_tableau(edges[i]);
	}
	int vmax = get<0>(max_tableau(sums));
	int n_vmax = get<1>(max_tableau(sums));
	vector<vector<int>> maximum_edges = vector<vector<int>>(n_vmax);
	vector<string> descriptions=vector<string>(n_vmax);
	vector<string> refs = {"ht", "vr", "hb", "vl"};
	int i=0;
	int count=0;
	for(vector<int> edge:edges){
		if(sum_tableau(edge)==vmax){
			maximum_edges[count] = edge;
			descriptions[count] = refs[i];
			count++;
		}
		i++;
	}
	tuple<vector<string>, vector<vector<int>>> tup = make_tuple(descriptions,maximum_edges);
	return tup;
}

//tested manually
//if you thought max_edge() was monstrous, check this
tuple<vector<string>, vector<vector<int>>> max_half_edge(Plateau plateau){
	vector<vector<int>> half_edges = extract_half_edges(plateau);
	vector<int> sums = vector<int>(8);
	for(int i=0; i<8; i++){
		sums[i]=sum_tableau(half_edges[i]);
	}
	int vmax = get<0>(max_tableau(sums));
	int n_vmax = get<1>(max_tableau(sums));
	vector<vector<int>> maximum_half_edges = vector<vector<int>>(n_vmax);
	vector<string> descriptions=vector<string>(n_vmax);
	vector<string> refs = {"htl","htr","vrt","vrb","hbl","hbr","vlt","vlb"};
	int i=0;
	int count=0;
	for(vector<int> half_edge:half_edges){
		if(sum_tableau(half_edge)==vmax){
			maximum_half_edges[count] = half_edge;
			descriptions[count] = refs[i];
			count++;
		}
		i++;
	}
	tuple<vector<string>, vector<vector<int>>> tup = make_tuple(descriptions,maximum_half_edges);
	return tup;
}

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
int calc_empty_favor(Plateau plateau_apres){
	return count_plateau(plateau_apres,0)*32;
}

//tested manually
//unfulfilled goal:find a way to output between 0-512 in a reasonable way compared to other functions
int incremented_score_favor(Plateau plateau_avant, int deplacement){
	int incremented_game_score = score(0, plateau_avant, deplacement);
	return incremented_game_score;
}

//tested manually
int placement_favor(vector<int> coordinates){
	if((coordinates[0]==0 || coordinates[0]==3) && (coordinates[1]==0 || coordinates[1]==3)){
		return 512;
	}
	else if((coordinates[0]==0 || coordinates[0]==3) || (coordinates[1]==0 || coordinates[1]==3)){
		return 256;
	}
	else{
		return 0;
	}
}

//tested manually
int maximum_value_increase_favor(Plateau pavant, Plateau papres){
	int maxv_avant = get<0>(max_plateau(pavant));
	int maxv_apres = get<0>(max_plateau(papres));
	if(maxv_avant<maxv_apres){
		return 512;
	}
	return 0;
}

//tested manually
int num_maximum_value_increase_favor(Plateau pavant, Plateau papres){
	int num_maxv_avant = get<1>(max_plateau(pavant));
	int num_maxv_apres = get<1>(max_plateau(papres));
	if(num_maxv_apres!=num_maxv_avant){
		return 512;
	}
	return 0;
}

//tested manually
int maximum_values_placement_favor(Plateau pavant, Plateau papres){
	int favor=0;
	vector<vector<int>> maxv_avant_coordinates = get<2>(max_plateau(pavant));
	vector<vector<int>> maxv_apres_coordinates = get<2>(max_plateau(papres));
	int avg_avant;
	int avg_apres;
	vector<int> favors_avant = vector<int>(maxv_avant_coordinates.size());
	vector<int> favors_apres = vector<int>(maxv_apres_coordinates.size());
	int i = 0;
	for(vector<int> coordinate_pair:maxv_avant_coordinates){
		favors_avant[i] = placement_favor(coordinate_pair);
		i++;
	}
	i=0;
	avg_avant = average(favors_avant);
	for(vector<int> coordinate_pair:maxv_apres_coordinates){
		favors_apres[i] = placement_favor(coordinate_pair);
		i++;
	}
	avg_apres = average(favors_apres);
	if(avg_avant>avg_apres){
		return 0;
	}else if(avg_avant<avg_apres){
		return 512;
	}else{
		return 256;
	}
}

//a revoir
int max_edge_change_favor(Plateau pavant, Plateau papres){
	if(get<0>(max_edge(pavant))==get<0>(max_edge(papres))){
		return 512;
	}
	return 0;
}
//a revoir
int max_half_edge_change_favor(Plateau pavant, Plateau papres){
	if(get<0>(max_half_edge(pavant))==get<0>(max_half_edge(papres))){
		return 512;
	}
	return 0;
}

//tested manually, has to be tested thouroughly
int val_adjacency_favor(Plateau p, vector<int> coordinates){
	int fav=0;
	int i = coordinates[0];
	int j = coordinates[1];
	int value=p[i][j];
	if((i==0)&&(j==0)){
		if(value==p[0][1]){
			fav+=1;
		}
		if(value==p[1][0]){
			fav+=128;
		}
		return fav;
	}else if((i==0)&&(j==3)){
		if(value==p[0][2]){
			fav+=128;
		}
		if(value==p[1][3]){
			fav+=128;
		}
		return fav;
	}else if((i==3)&&(j==0)){
		if(value==p[2][0]){
			fav+=128;
		}
		if(value==p[3][1]){
			fav+=128;
		}
		return fav;
	}else if((i==3)&&(j==3)){
		if(value==p[3][2]){
			fav+=128;
		}
		if(value==p[2][3]){
			fav+=128;
		}
		return fav;
	}else if(i==0){
		if(value==p[0][j+1]){
			fav+=128;
		}
		if(value==p[0][j-1]){
			fav+=128;
		}
		if(value==p[1][j]){
			fav+=128;
		}
		return fav;
	}else if(i==3){
		if(value==p[3][j+1]){
			fav+=128;
		}
		if(value==p[3][j-1]){
			fav+=128;
		}
		if(value==p[2][j]){
			fav+=128;
		}
		return fav;
	}else if(j==0){
		if(value==p[i][1]){
			fav+=128;
		}
		if(value==p[i+1][0]){
			fav+=128;
		}
		if(value==p[i-1][0]){
			fav+=128;
		}
		return fav;
	}else if(j==3){
		if(value==p[i][2]){
			fav+=128;
		}
		if(value==p[i+1][3]){
			fav+=128;
		}
		if(value==p[i-1][3]){
			fav+=128;
		}
		return fav;
	}else{
		if(value==p[i+1][j]){
			fav+=128;
		}
		if(value==p[i-1][j]){
			fav+=128;
		}
		if(value==p[i][j+1]){
			fav+=128;
		}
		if(value==p[i][j-1]){
			fav+=128;
		}
		return fav;
	}
	return fav;
}



int adjacency_favor(Plateau p){
	int favor=0;
	for(int row=0; row<4; row++){
		for(int column=0; column<4; column++){
			favor+=val_adjacency_favor(p,{row,column})*p[row][column];
		}
	}
	return favor;
}


//the final ai does not work yet, saving for later  vector<int> weights
int eval_move(Plateau p, char move, vector<int> w){
	try{
		deplacement(p,ideplacement_dhgb(move),false);
	}catch(invalid_argument e){
		return -1;
	}
	if(estPerdant(deplacement(p,ideplacement_dhgb(move), false))){
		return -1;
	}
	Plateau np = deplacement(p,ideplacement_dhgb(move),false);
	int favor=0;
	favor+= calc_empty_favor(deplacement(p,ideplacement_dhgb(move), true))*w[0];
	favor+=incremented_score_favor(p,ideplacement_dhgb(move))*w[1];
	favor+=maximum_value_increase_favor(p, np)*w[2];
	favor+=num_maximum_value_increase_favor(p, np)*w[3];
	favor+=maximum_values_placement_favor(p,np)*w[4];
	favor+=max_edge_change_favor(p, np)*w[5];
	favor+=max_half_edge_change_favor(p, np)*w[6];
	favor+=adjacency_favor(p)*w[7];
	return favor;
}

char ai_answer(Plateau p, vector<int> w){
	vector<char> moves = {'H','B','G','D'};
	vector<int> move_favors = {eval_move(p, moves[0], w), 
			eval_move(p, moves[1], w), eval_move(p, moves[2], w),
			eval_move(p, moves[3], w)};
	if(get<1>(max_tableau(move_favors))==1){
		return moves[get<2>(max_tableau(move_favors))[0]];
	}
	int i=0;
	vector<char> nmv;
	for(int move_favor: move_favors){
		if(move_favor==get<0>(max_tableau(move_favors))){
			nmv.push_back(moves[i]);
	 	}
		i++;
	}
	int choice = rand()%(nmv.size());
	return nmv[choice];
}