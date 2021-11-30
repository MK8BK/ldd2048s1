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



static int count(Plateau plateau, int powerof2){
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



// int score(int score_avant, Plateau avant, int ideplacement){
// 	Plateau apres;
// 	apres = deplacement(avant, ideplacement, false);
// 	int nscore=score_avant;
// 	vector<vector<int>> avant_freq= {{2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072},
// 	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
// 	vector<vector<int>> apres_freq= avant_freq;
// 	for(int column=0; column<17; column++){
// 		avant_freq[1][column]=count(avant, avant_freq[0][column]);
// 		apres_freq[1][column]=count(apres, apres_freq[0][column]);
// 		if(apres_freq[1][column]>avant_freq[1][column]){
// 			nscore += avant_freq[0][column]*(apres_freq[1][column]-avant_freq[1][column]);
// 		}
// 	}
// 	return nscore;
// }



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

//temporarily commented to test te AI, will probably soon be deleted
// void jeu(){
// 	srand((unsigned) time(0));
// 	int game_score = 0;
// 	Plateau plateau = plateauInitial();
// 	Plateau plateau_next = plateauVide();
// 	while(true){
// 		cout << dessine(plateau)<< "score:" <<game_score<<endl;
// 		try{
// 			int deplacement_id = ideplacement_dhgb(input_dhgb());
// 			plateau_next = deplacement(plateau, deplacement_id, true);
// 			game_score = score(game_score, plateau, deplacement_id);
// 			plateau = plateau_next;
// 			if(estGagnant(plateau)){
// 				cout << dessine(plateau_next) << endl;
// 				cout << "Vous avez Gagne!"<<endl;
// 				return;
// 			}else if(estPerdant(plateau)){
// 				cout << dessine(plateau_next) << endl;
// 				cout << "Vous avez Perdu!"<<endl;
// 				return;
// 			}
// 		}catch(invalid_argument e){

// 			cout << e.what() << endl;
// 			continue;
// 		}
// 	}
// }


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




int calc_empty(Plateau plateau){
	int sum=0;
	for(int row=0; row<4; row++){
		for(int column=0; column<4; column++){
			if(plateau[row][column]==0){
				sum++;
			}
		}
	}
	return sum;
}

tuple<int, vector<int>> maxpos(Plateau plateau){
	tuple<int, vector<int>> m;
	int max=0;
	vector<int> maxi = vector<int>(2);
	for(int row=0; row<4; row++){
		for(int column=0; column<4; column++){
			if(plateau[row][column]>max){
				max = plateau[row][column];
				maxi = {row, column};
			}
		}
	}
	if(count(plateau, max)>1){
		throw "Two maximums, it's not going well!";
	}
	m = make_tuple(max, maxi);
	return m;
}


//@pablo-chulilla
int log2(int powerof2){
	return 0;
}


int sum(vector<int> row_or_column){
	int sum=0;
	for(int i=0; i<4; i++){
			sum+=row_or_column[i];
	}	
	return sum;
}






//half-done, continue after emergency git versions management
// tuple<char, vector<int>> maxedge(Plateau plateau){
// 	char vh;
// 	vector<int> max_vector=vector<int>(4);
// 	
		
// }



//the final ai does not work yet, saving for later
int eval_move(Plateau p, char move, vector<int> weights){
	try{
		deplacement(p,ideplacement_dhgb(move),false);
	}catch(invalid_argument e){
		return 0;
	}

	if(estPerdant(deplacement(p,ideplacement_dhgb(move), true))){
		return 0;
	}



	int w1, w2, w3, w4, w5, w6, w7, w8, w9, w10;
	w1, w2, w3 = weights[0], weights[1], weights[2];
	w4, w5, w6 = weights[3], weights[4], weights[5];
	w7, w8, w9 = weights[6], weights[7], weights[8];
	w10 = weights[9];

	Plateau np = deplacement(p,ideplacement_dhgb(move),false);
	int favor=0;

	//max pos change
	if(get<1>(maxpos(np))==get<1>(maxpos(p))){
		favor+=w1;
	}
	//max pos value change favor
	if(get<0>(maxpos(np))>get<0>(maxpos(p))){
		favor+=w2*(log2(get<0>(maxpos(np))) - log2(get<0>(maxpos(p)) ));
	}
	
	
	//max edge change favor
	//max half edge change favor
	//max edge decroissance favor
	//max half edge decroissance favor

	//adjacency favor
	//empty favor
	if(calc_empty(p)<calc_empty(np)){
		favor += (calc_empty(np)-calc_empty(p))*w8;
	}
	//max score favor
	int game_score = 0;
	int ngame_score = score(game_score, p,)
	if()
	//compactness favor

	return favor;
}




void ai_answer(string config_path, string move_path, int iteration){
	Plateau p = get<2>(read_updated_configuration(iteration,move_path));
	Plateau np;
	int choice = rand() % 4;
	vector<char> moves = {'H','B','G','D'};
	vector<int> move_favors = vector<int>(4);
	char maxm=moves[0];
	int maxi=-1;
	for(int i=0; i<4; i++){
		move_favors[i] = eval_move(p, moves[i]);
		cout << to_string(move_favors[i]) << moves[i]<<endl;
		if(move_favors[i]>maxi){
			maxi = move_favors[i];
			maxm = moves[i];
		}
	}
	
	write_mouvement(move_path, iteration, maxm);
}