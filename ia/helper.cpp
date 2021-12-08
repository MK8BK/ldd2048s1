#include "modele.h"
#include "io.h"


Plateau rand_filler(Plateau p){
	Plateau np =p;
	for(int row=0; row<4; row++){
		for(int column=0; column<4; column++){
			if(np[row][column]==0){
				np[row][column]=tireDeuxOuQuatre();
			}
		}
	}
	return np;
}


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


vector<int> reverse_tableau(vector<int> t){
	vector<int> reversed_t = vector<int> (t.size());
	int j=0;
	for(int i=t.size()-1; i>=0; i--){
		reversed_t[j]=t[i];
		j++;
	}
	return reversed_t;
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

int abs(int num){
	if(num<0){
		return -num;
	}
	return num;
}

float average(vector<int> t){
	float s = (float)(sum_tableau(t)) / (float)(t.size());
	return s;
}

vector<int> getrow(Plateau p, int i){
	return p[i];
}

vector<int> getcolumn(Plateau p, int j){
	return {p[0][j], p[1][j], p[2][j], p[3][j]};
}

//{"ht","vr","hb","vl"}
vector<vector<int>> extract_edges(Plateau p){
	return {getrow(p,0),getcolumn(p,3), getrow(p,3), getcolumn(p,0)};
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
			vector<int> nedge = vector<int>(4);
			string description = "";
			if(edge[0]<edge[3]){
				nedge=reverse_tableau(edge);
				description = "r";
			}else{
				nedge = edge;
			}
			maximum_edges[count] = nedge;
			descriptions[count] = refs[i]+description;
			count++;
		}
		i++;
	}
	tuple<vector<string>, vector<vector<int>>> tup = make_tuple(descriptions,maximum_edges);
	return tup;
}


//tested manually
int decroissance_tableau(vector<int> tableau){
	int count = 1;
	if(count_tableau(tableau, tableau[0])==tableau.size()){
		return 16;
	}
	for(int i=0; i<tableau.size()-1; i++){
		if(tableau[i]<tableau[i+1]){
			return count;
		}else{
			count++;
		}
	}
	return count;

}

vector<int> concatrc(vector<vector<int>> setrc){
	vector<int> v = vector<int>(16);
	int count = 0;
	for(vector<int> sv : setrc){
		for(int elem:sv){
			v[count] = elem;
			count++;
		}
	}
	return v;
}

vector<int> tabl_plateau(Plateau p, string description){
	vector<int> v = vector<int>(16);
	if(description.length()==3){
		if(description.substr(0,2)=="vl"){
			return concatrc({reverse_tableau(getcolumn(p,0)),getcolumn(p,1),
			reverse_tableau(getcolumn(p,2)),getcolumn(p,3)});
		}else if(description.substr(0,2)=="vr"){
			return concatrc({reverse_tableau(getcolumn(p,3)), getcolumn(p,2),
			reverse_tableau(getcolumn(p,1)), getcolumn(p,0)});
		}else if(description.substr(0,2)=="ht"){
			return concatrc({reverse_tableau(getrow(p,0)), getrow(p,1),
			reverse_tableau(getrow(p,2)), getrow(p,3)});
		}else{
			return concatrc({reverse_tableau(getrow(p,3)), getrow(p,2),
			reverse_tableau(getrow(p,1)), getrow(p,0)});
		}
	}else{
		if(description=="vl"){
			return concatrc({getcolumn(p,0),reverse_tableau(getcolumn(p,1))
			,getcolumn(p,2),reverse_tableau(getcolumn(p,3))});
		}else if(description=="vr"){
			return concatrc({getcolumn(p,3), reverse_tableau(getcolumn(p,2)),
			getcolumn(p,1), reverse_tableau(getcolumn(p,0))});
		}else if(description=="ht"){
			return concatrc({getrow(p,0), reverse_tableau(getrow(p,1)),
			getrow(p,2), reverse_tableau(getrow(p,3))});
		}else{
			return concatrc({getrow(p,3), reverse_tableau(getrow(p,2)),
			getrow(p,1), reverse_tableau(getrow(p,0))});
		}
	}
	return v;
}
