#include <vector>
#include <iostream>
#include <cstdlib> 
#include <time.h>
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

/** génère une nouvelle tuile 2 ou 4 sur une case aleatoire d'un plateau
 * @param Plateau un plateau
 * @return Plateau avec une nouvelle tuile 2 ou 4
 **/
Plateau nouvelleTuile(Plateau plateau);

/** génère deux nombres sur des cases aléatoires d'un Plateau vide
 *  @return un Plateau en début de jeu
 **/
Plateau plateauInitial();

/** Effectue une rotation de 90 degre dans le sens trigonometrique positif d'un plateau
 * @param Plateau plateau
 * @return Plateau rotation d'un quart de tour du plateau
 **/
Plateau flippe90TrigPlus(Plateau plateau);

/** Tasse vers la gauche toutes les tuiles non nuls d'une ligne
 * @param vector<int>: une ligne du plateau
 * @return vector<int>: la ligne tassée a gauche
 **/
vector<int> collapseRowLeft(vector<int> row);

/** Combine les cases d'un tableau si possible, place des zeros
 * @param vector<int> un tableau de taille 4
 * @return vector<int> le tableau avec les cases combinées vers la gauche si possible
 **/
vector<int> mergeRowLeft(vector<int> row);

/** déplace les tuiles d'un Plateau vers la gauche et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers la gauche
 **/
Plateau deplacementGauche(Plateau plateau);

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
 *  @return le Plateau déplacé dans la direction + une nouvelle tuile
 **/
Plateau deplacement(Plateau plateau, int direction);

/** déplace les tuiles d'un Plateau dans la direction donnée et génère une nouvelle tuile si demandé
 *  @param plateau le Plateau
 *  @param direction: la direction 0 droite 1 Haut 2 Gauche 3 Bas
 *  @return le Plateau déplacé dans la direction + une nouvelle tuile si demandé
 **/
Plateau deplacement(Plateau plateau, int direction, bool tuile);

/** affiche un Plateau
 * @param p le Plateau
 * @return un string represeantant le plateau
 **/
string dessine(Plateau p);

/* affiche un Plateau (implementation compatible avec ncurses)
 * @param p le Plateau
 */
void dessine_moderne(Plateau p);

/** affiche un Plateau coloree
 * @param p le Plateau
 * @return void
 **/
void dessine_couleur(Plateau p);

/** permet de savoir si une partie est terminée
 *  @param plateau un Plateau
 *  @return true si le plateau est perdant, false sinon
 **/
bool estPerdant(Plateau plateau);

/** permet de savoir si une partie est gagnée
 * @param plateau un Plateau
 * @return true si le plateau contient un 2048, false sinon
 **/
bool estGagnant(Plateau plateau);

/** compte l'occurence d'une valeur dans un plateau
 * @param plateau 
 * @param powerof2
 * @return le nombre d'occurence de powerof2 dans plateau
 **/
int count(Plateau plateau, int powerof2);

/** calcule le logarithme de base 2 d'une puissance de 2
 * @param int une puissance de deux
 * @return int le log de base 2
 **/
int log2(int powerof2);


/** Calcul le score au tour n en sachant le score au tour n-1
 * @param score_avant int: le score du tour precedent
 * @param avant Plateau: le plateau au tout precedent
 * @param ideplacement le deplacement au tour actuel: 0 droite, 1 haut, 2 gauche, 3 bas
 * @return int: le score au rang n
 **/
int score(int score_avant, Plateau avant, int ideplacement);

/** demande a l'utilisateur un deplacement DHGBQ
 * @return char "D""H""G""B""Q"
 **/
char input_dhgb();

/** converti un deplacement char en deplacement int
 *   (differents formats requis)
 * @param dhgbq un char representant un deplacement
 * @return int un int representant le meme deplacement
 **/
int ideplacement_dhgb(char dhgb);

/** Lit les deplacements de l'utilisateur avec les touches fleches
 * @return int: la representation du deplacement en nombre (sens trigo)
 **/
int get_input_arrows();

/** La fonction principal du jeu, cree le plateau initial, lit les deplacements de l'utilisateur et les execute
 * tour a tour tout en verifiant si la partie est terminen, en incrementant le score et en verifiant la validite des deplacements.
 * @return void
 **/
void jeu();

/** La fonction principal du jeu, cree le plateau initial, lit les deplacements de l'utilisateur avec ncurses et les execute
 * tour a tour tout en verifiant si la partie est terminen, en incrementant le score et en verifiant la validite des deplacements.
 * @return void
 **/
void jeu_moderne();

/** La fonction principal du jeu, cree le plateau initial, lit les deplacements de l'utilisateur avec ncurses et les execute(affice en couleur)
 * tour a tour tout en verifiant si la partie est terminen, en incrementant le score et en verifiant la validite des deplacements.
 * @return void
 **/
void jeu_moderne_couleur();