#include "modele.h"

Plateau rand_filler(Plateau p);

tuple<int,int,vector<int>> max_tableau(vector<int> tableau);

tuple<int, int, vector<vector<int>>> max_plateau(Plateau plateau);

int sum_tableau(vector<int> tableau);

int sum_plateau(Plateau plateau);

vector<int> reverse_tableau(vector<int> t);

int log2(int powerof2);

int abs(int num);

float average(vector<int> t);

vector<int> getcolumn(Plateau p, int j);

vector<vector<int>> extract_edges(Plateau p);

vector<vector<int>> extract_edges(Plateau plateau);

vector<vector<int>> extract_half_edges(Plateau plateau);

tuple<vector<string>, vector<vector<int>>> max_edge(Plateau plateau);

tuple<vector<string>, vector<vector<int>>> max_half_edge(Plateau plateau);

int decroissance_tableau(vector<int> tableau);
vector<int> concatrc(vector<vector<int>> setrc);

vector<int> tabl_plateau(Plateau p, string description);