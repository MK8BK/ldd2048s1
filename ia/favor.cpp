#include "io.h"
#include "modele.h"
#include "favor.h"

//favor functions
// favor functions use all the previous functions to give a "favor score" 
// to a plateau, depending on the good or bad disposition of the numbers,
//these functions return a postiive or negative number (for later statistical
// optimization)

//tested manually
// int calc_empty_favor(Plateau pavant,Plateau papres){
// 	int nul_avant = count_plateau(pavant,0);
// 	int nul_apres = count_plateau(papres,0);
// 	if(nul_apres>=nul_avant){
// 		return 256 + (nul_apres-nul_avant)*32;
// 	}
// 	return 0;
// }


//adjacency functions
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


//tested manually
//unfulfilled goal:find a way to output between 0-512 in a reasonable way compared to other functions
int incremented_score_favor(Plateau plateau_avant, int deplacement){
	int incremented_game_score = score(0, plateau_avant, deplacement);
	return incremented_game_score;
}

//tested manually
// int placement_favor(Plateau p, vector<int> coordinates){
// 	int i=coordinates[0];
// 	int j=coordinates[1];
// 	if((i==0 || i==3) && (j==0 || j==3)){
// 		return 32*log2(p[i][j])*log2(p[i][j]);
// 	}
// 	else if((i==0 || i==3) || (j==0 || j==3)){
// 		return 2*log2(p[i][j])*log2(p[i][j]);
// 	}
// 	else{
// 		return 0;
// 	}
// }
//tested manually
// int maximum_value_increase_favor(Plateau pavant, Plateau papres){
// 	int maxv_avant = get<0>(max_plateau(pavant));
// 	int maxv_apres = get<0>(max_plateau(papres));
// 	if(maxv_avant<maxv_apres){
// 		return 512;
// 	}
// 	return 0;
// }
//tested manually
// int num_maximum_value_increase_favor(Plateau pavant, Plateau papres){
// 	int num_maxv_avant = get<1>(max_plateau(pavant));
// 	int num_maxv_apres = get<1>(max_plateau(papres));
// 	if(num_maxv_apres>num_maxv_avant){
// 		if(placement_favor(,))
// 		return 512;
// 	}
// 	return 0;
// }
//tested manually
// int maximum_values_placement_favor(Plateau pavant, Plateau papres){
// 	int favor=0;
// 	vector<vector<int>> maxv_avant_coordinates = get<2>(max_plateau(pavant));
// 	vector<vector<int>> maxv_apres_coordinates = get<2>(max_plateau(papres));
// 	int sum_avant;
// 	int sum_apres;
// 	vector<int> favors_avant = vector<int>(maxv_avant_coordinates.size());
// 	vector<int> favors_apres = vector<int>(maxv_apres_coordinates.size());
// 	int i = 0;
// 	for(vector<int> coordinate_pair:maxv_avant_coordinates){
// 		favors_avant[i] = placement_favor(coordinate_pair);
// 		i++;
// 	}
// 	i=0;
// 	sum_avant = sum_tableau(favors_avant);
// 	for(vector<int> coordinate_pair:maxv_apres_coordinates){
// 		favors_apres[i] = placement_favor(coordinate_pair);
// 		i++;
// 	}
// 	sum_apres = sum_tableau(favors_apres);
// 	if(sum_avant>sum_apres){
// 		return 0;
// 	}else if(sum_avant<sum_apres){
// 		return sum_apres-sum_avant;
// 	}else{
// 		return 0;
// 	}
// }
// int repartition_favor(Plateau pavant, Plateau papres){
// 	int avant_sumextern = sum_tableau(pavant[0])+sum_tableau(pavant[3])
// 					+pavant[1][0]+pavant[1][3]+pavant[2][0]+pavant[2][3];
// 	int apres_sumextern = sum_tableau(papres[0])+sum_tableau(papres[3])
// 					+papres[1][0]+papres[1][3]+papres[2][0]+papres[2][3];
// 	int sum_pavant = sum_plateau(pavant);
// 	int sum_papres = sum_plateau(papres);
// 	int avant_sumintern = sum_pavant-avant_sumextern;
// 	int apres_sumintern = sum_papres-apres_sumextern;
// 	int favor=0;
// 	if(apres_sumintern<avant_sumintern){
// 		return avant_sumintern-apres_sumintern;
// 	}
// 	return 0;
// }

int stability_favor(Plateau pavant, Plateau papres){
	int favor=0;
	for(int row=0; row<4; row++){
		for(int column=0; column<4; column++){
			favor+=17-abs(log2(papres[row][column]-pavant[row][column]));
		}
	}
	return favor;
}


// int vals_favor(Plateau pavant, Plateau papres){
// 	int favor_apres=0;
// 	int favor_avant=0;
// 	for(int row=0; row<4; row++){
// 		for(int column=0; column<4; column++){
// 			favor_avant+=placement_favor(pavant, {row, column});//*log2(p[row][column])
// 			favor_apres+=placement_favor(papres, {row, column});
// 		}
// 	}
// 	if(favor_apres<favor_avant){
// 		return 0;
// 	}
// 	return 526;
// }
// int max_vals_favors(Plateau pavant, Plateau papres){
// 	int favor=0;
// 	int maxv_avant = get<0>(max_plateau(pavant));
// 	int maxv_apres = get<0>(max_plateau(papres));
// 	int num_maxv_avant = get<1>(max_plateau(pavant));
// 	int num_maxv_apres = get<1>(max_plateau(papres));
// 	vector<vector<int>> maxv_avant_coordinates = get<2>(max_plateau(pavant));
// 	vector<vector<int>> maxv_apres_coordinates = get<2>(max_plateau(papres));
// 	if(num_maxv_apres==1){
// 		favor+=maxv_apres;
// 		favor+=placement_favor(papres, maxv_apres_coordinates[0]);
// 	}else{
// 		int sum_avant;
// 		int sum_apres;
// 		vector<int> favors_avant = vector<int>(num_maxv_avant);
// 		vector<int> favors_apres = vector<int>(num_maxv_apres);
// 		int i = 0;
// 		for(vector<int> coordinate_pair:maxv_avant_coordinates){
// 			favors_avant[i] = placement_favor(pavant, coordinate_pair);
// 			i++;
// 		}
// 		i=0;
// 		sum_avant = sum_tableau(favors_avant);
// 		for(vector<int> coordinate_pair:maxv_apres_coordinates){
// 			favors_apres[i] = placement_favor(papres, coordinate_pair);
// 			i++;
// 		}
// 		sum_apres = sum_tableau(favors_apres);
// 		favor+=256;
// 		cout<<to_string(sum_avant)<<" , "<<to_string(sum_apres)<<endl;
// 		if(sum_apres<sum_avant){
// 			favor-=256;
// 		}else{
// 			favor+=256;
// 		}
// 		return favor;
// 	}
// 	return favor;
// }
//a revoir
// int max_edge_change_favor(Plateau pavant, Plateau papres){
// 	if(get<0>(max_edge(pavant))==get<0>(max_edge(papres))){
// 		return 512;
// 	}
// 	return 0;
// }
// //a revoir
// int max_half_edge_change_favor(Plateau pavant, Plateau papres){
// 	if(get<0>(max_half_edge(pavant))==get<0>(max_half_edge(papres))){
// 		return 512;
// 	}
// 	return 0;
// }


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