#include <vector>
#include <iostream>
#include <cstdlib> 
#include <time.h>
#include <fstream>
#include <tuple>
using namespace std;

typedef vector<vector<int>> Plateau;
/** Des fonctions peuvent être ajoutés à ce fichier si besoin est (fonctions pour mettre à jour le score par exemple)
 * //


/** génère aléatoirement un 2 ou un 4 avec des probabilités respectives de 9/10 et 1/10
 *  @return 2 ou 4
 **/
int tireDeuxOuQuatre();

/** génère un Plateau de dimensions 4*4 ne contenant que des 0
 *  @return un Plateau vide
 **/
Plateau plateauVide();

static Plateau nouvelleTuile(Plateau plateau);


/** génère deux nombres sur des cases aléatoires d'un Plateau vide
 *  @return un Plateau en début de jeu
 **/
Plateau plateauInitial();



/** déplace les tuiles d'un Plateau vers la gauche et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers la gauche
 **/
static vector<int> collapseRowLeft(vector<int> row);
static vector<int> mergeRowLeft(vector<int> row);
Plateau deplacementGauche(Plateau plateau);

static Plateau flippe90TrigPlus(Plateau plateau);

/** déplace les tuiles d'un Plateau vers la droite et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers la droite
 **/
Plateau deplacementDroite(Plateau plateau);


/** déplace les tuiles d'un Plateau vers le haut et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers le haut
 **/
Plateau deplacementHaut(Plateau plateau);


/** déplace les tuiles d'un Plateau vers le bas et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers le bas
 **/
Plateau deplacementBas(Plateau plateau);


/** déplace les tuiles d'un Plateau dans la direction donnée et génère une nouvelle tuile si le déplacement est valide
 *  @param plateau le Plateau
 *  @param direction la direction 0 droite 1 Haut 2 Gauche 3 Bas
 *  @return le Plateau déplacé dans la direction
 **/
Plateau deplacement(Plateau plateau, int direction, bool tuile);


/** affiche un Plateau
 * @param p le Plateau
 **/
string dessine(Plateau p);


/** permet de savoir si une partie est terminée
 *  @param plateau un Plateau
 *  @return true si le plateau est vide, false sinon
 **/
bool estPerdant(Plateau plateau);

/** permet de savoir si une partie est gagnée
 * @param plateau un Plateau
 * @return true si le plateau contient un 2048, false sinon
 **/
bool estGagnant(Plateau plateau);


static int count(Plateau plateau, int powerof2);
int log2(int powerof2);
int score(int score_avant, Plateau avant, int ideplacement);



char input_dhgb();

int ideplacement_dhgb(char dhgb);



//half-done, continue after emergency git versions management
//temporarily commented, will soon be deleted, no need for the AI, just awaiting the completion and successful compilation 
//  of ia_tester.cpp
// void jeu();




tuple<int, int, Plateau> read_configuration(string path);

tuple<int, int, Plateau> read_updated_configuration(int iteration, string path);


void write_mouvement(string path, int iteration, char mouvement);

tuple<int, char> read_mouvement(string path);
tuple<int, char> read_updated_mouvement(string path, int iteration);
void write_new_config(string path, int iteration, int game_score, Plateau plateau);


int calc_empty(Plateau plateau);

tuple<int, vector<int>> maxpos(Plateau plateau);

int sum(vector<int> row_or_column);
// tuple<char, vector<int>> maxedge(Plateau plateau);
//half-done, continue after emergency git versions management

int eval_move(Plateau p, char move);
void ai_answer(string config_path, string move_path, int iteration);