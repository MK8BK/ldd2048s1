#include "modele.h"

//ai io functions
vector<int> read_weights(string path);

tuple<int, int, Plateau> read_configuration(string path);

tuple<int, int, Plateau> read_updated_configuration(int iteration, string path);

void write_mouvement(string path, int iteration, char mouvement);

tuple<int, char> read_mouvement(string path);

tuple<int, char> read_updated_mouvement(string path, int iteration);

void write_new_config(string path, int iteration, int game_score, Plateau plateau);
