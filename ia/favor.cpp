#include "io.h"
#include "modele.h"
#include "favor.h"


int val_adjacency_favor(Plateau p, vector<int> coordinates){
	int fav=0;
	int i = coordinates[0];
	int j = coordinates[1];
	int value=p[i][j];
	int logv = log2(value);
	if((i==0)&&(j==0)){
		if(value==p[0][1]){
			fav+=p[i][j]*(17-abs(logv-log2(p[0][1])));
		}
		if(value==p[1][0]){
			fav+=p[i][j]*(17-abs(logv-log2(p[1][0])));
		}
		return fav*logv*logv;
	}else if((i==0)&&(j==3)){
		if(value==p[0][2]){
			fav+=p[i][j]*(17-abs(logv-log2(p[0][2])));
		}
		if(value==p[1][3]){
			fav+=p[i][j]*(17-abs(logv-log2(p[1][3])));
		}
		return fav*logv*logv;
	}else if((i==3)&&(j==0)){
		if(value==p[2][0]){
			fav+=p[i][j]*(17-abs(logv-log2(p[2][0])));
		}
		if(value==p[3][1]){
			fav+=p[i][j]*(17-abs(logv-log2(p[3][1])));
		}
		return fav*logv*logv;
	}else if((i==3)&&(j==3)){
		if(value==p[3][2]){
			fav+=p[i][j]*(17-abs(logv-log2(p[3][2])));
		}
		if(value==p[2][3]){
			fav+=p[i][j]*(17-abs(logv-log2(p[2][3])));
		}
		return fav*logv*logv;
	}else if(i==0){
		if(value==p[0][j+1]){
			fav+=p[i][j]*(17-abs(logv-log2(p[0][j+1])));
		}
		if(value==p[0][j-1]){
			fav+=p[i][j]*(17-abs(logv-log2(p[0][j-1])));
		}
		if(value==p[1][j]){
			fav+=p[i][j]*(17-abs(logv-log2(p[1][j])));
		}
		return fav*logv*logv;
	}else if(i==3){
		if(value==p[3][j+1]){
			fav+=p[i][j]*(17-abs(logv-log2(p[3][j+1])));
		}
		if(value==p[3][j-1]){
			fav+=p[i][j]*(17-abs(logv-log2(p[3][j-1])));
		}
		if(value==p[2][j]){
			fav+=p[i][j]*(17-abs(logv-log2(p[2][j])));
		}
		return fav*logv*logv;
	}else if(j==0){
		if(value==p[i][1]){
			fav+=p[i][j]*(17-abs(logv-log2(p[i][1])));
		}
		if(value==p[i+1][0]){
			fav+=p[i][j]*(17-abs(logv-log2(p[i+1][0])));
		}
		if(value==p[i-1][0]){
			fav+=p[i][j]*(17-abs(logv-log2(p[i-1][0])));
		}
		return fav*logv*logv;
	}else if(j==3){
		if(value==p[i][2]){
			fav+=p[i][j]*(17-abs(logv-log2(p[i][2])));
		}
		if(value==p[i+1][3]){
			fav+=p[i][j]*(17-abs(logv-log2(p[i+1][3])));
		}
		if(value==p[i-1][3]){
			fav+=p[i][j]*(17-abs(logv-log2(p[i-1][3])));
		}
		return fav*logv*logv;
	}else{
		if(value==p[i+1][j]){
			fav+=p[i][j]*(17-abs(logv-log2(p[i+1][j])));
		}
		if(value==p[i-1][j]){
			fav+=p[i][j]*(17-abs(logv-log2(p[i-1][j])));
		}
		if(value==p[i][j+1]){
			fav+=p[i][j]*(17-abs(logv-log2(p[i][j+1])));
		}
		if(value==p[i][j-1]){
			fav+=p[i][j]*(17-abs(logv-log2(p[i][j-1])));
		}
		return fav*logv*logv;
	}
	return fav;
}

int adjacency_favor(Plateau pavant, Plateau papres){
	int favor_avant=0;
	for(int row=0; row<4; row++){
		for(int column=0; column<4; column++){
			vector<int> coordinates = {row,column};
			favor_avant+=val_adjacency_favor(pavant,coordinates);
		}
	}
	int favor_apres=0;
	for(int row=0; row<4; row++){
		for(int column=0; column<4; column++){
			vector<int> coordinates = {row,column};
			favor_apres+=val_adjacency_favor(papres,coordinates);
		}
	}
	if(favor_apres>favor_avant){
		return favor_apres-favor_avant;
	}
	return 0;
}

int incremented_score_favor(Plateau plateau_avant, int deplacement){
	int incremented_game_score = score(0, plateau_avant, deplacement);
	return incremented_game_score;
}

int stability_favor(Plateau pavant, Plateau papres){
	int favor=0;
	for(int row=0; row<4; row++){
		for(int column=0; column<4; column++){
			favor+=17-abs(log2(papres[row][column]-pavant[row][column]));
		}
	}
	return favor;
}

int decroissance_favor(Plateau pavant, Plateau papres){
	int favor_avant = 0;
	int favor_apres = 0;
	if(get<1>(max_edge(pavant)).size()==1 && get<1>(max_edge(papres)).size()==1){
		favor_avant = decroissance_tableau(tabl_plateau(pavant, get<0>(max_edge(pavant))[0]));
		favor_apres = decroissance_tableau(tabl_plateau(papres, get<0>(max_edge(papres))[0]));
		if(get<0>(max_plateau(papres))==get<1>(max_edge(papres))[0][0]){
			favor_apres+=get<0>(max_plateau(papres))*get<0>(max_plateau(papres));
		}
	}
	if(sum_tableau(get<1>(max_edge(papres))[0])>sum_tableau(get<1>(max_edge(pavant))[0])){
		favor_apres+=sum_tableau(get<1>(max_edge(papres))[0])-sum_tableau(get<1>(max_edge(pavant))[0]);
	}

	if(favor_apres>favor_avant){
		return favor_apres-favor_avant;
	}
	return 0;
}

int eval_move(Plateau p, char move, vector<int> w){
	//cout<<move<<endl;
	int favor=0;
	try{
		deplacement(p,ideplacement_dhgb(move));
	}catch(invalid_argument e){
		throw invalid_argument("Deplacement invalide");
	}
	if(estPerdant(p)){
		throw invalid_argument("Deplacement invalide");
	}
	Plateau npat = deplacement(p,ideplacement_dhgb(move),true);
	Plateau npst = deplacement(p,ideplacement_dhgb(move),false);
	Plateau pfilled = rand_filler(p);
	
	favor += adjacency_favor(p,npat)*w[0];
	favor += incremented_score_favor(p,ideplacement_dhgb(move))*w[1];
	favor += stability_favor(p, npst)*w[2];
	favor += decroissance_favor(p, npst)*w[3];
	//favor += calc_empty_favor(p,npat)*w[0];
	//favor += max_vals_favors(p, npat)*w[2];
	//favor+=max_edge_change_favor(p, npst)*w[3];
	//favor+=max_half_edge_change_favor(p, npst)*w[4];
	//favor+=repartition_favor(p,npst)*w[6];
	//favor += vals_favor(p,npst)*w[8];
	////cout << to_string(favor)<<endl;
	return favor;
}

char ai_answer(Plateau p, vector<int> w){
	vector<char> moves = {'H','B','G','D'};
	vector<char> allowed_moves;
	if(estPerdant(p)){
		return 'F';
	}
	for(int i=0; i<4 ; i++){
		try{
			eval_move(p,moves[i],w);
			// cout<<moves[i]<<endl;
			allowed_moves.push_back(moves[i]);
		}catch (invalid_argument){
			continue;
		}
	}
	vector<int> allowed_moves_favors = vector<int>(allowed_moves.size());
	for(int i=0; i<allowed_moves.size(); i++){
		allowed_moves_favors[i]=eval_move(p,allowed_moves[i], w);
	}
	int num_maxfav = get<1>(max_tableau(allowed_moves_favors));
	if(num_maxfav==1){
		return allowed_moves[get<2>(max_tableau(allowed_moves_favors))[0]];
	}else{
		int choice = rand()% (get<2>(max_tableau(allowed_moves_favors)).size());
		return allowed_moves[choice];
	}
	cout<<endl;
	return(moves[0]);
}
