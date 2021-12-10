#include "io.h"
#include "modele.h"
#include "helper.h"

// int calc_empty_favor(Plateau pavant,Plateau papres);
int val_adjacency_favor(Plateau p, vector<int> coordinates);

int adjacency_favor(Plateau pavant, Plateau papres);
int incremented_score_favor(Plateau plateau_avant, int deplacement);
int stability_favor(Plateau pavant, Plateau papres);
int decroissance_favor(Plateau pavant, Plateau papres);
int eval_move(Plateau p, char move, vector<int> weights);
char ai_answer(Plateau p, vector<int> w);

