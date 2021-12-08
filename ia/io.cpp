#include "io.h"
#include "modele.h"

//ai io functions

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
	string siteration;
	string sscore;
	getline(file, siteration,' ');
	getline(file, sscore);
	iteration=stoi(siteration);
	sscore=stoi(sscore);
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
	int niteration=iteration;
	while(iteration==niteration){
		try{
			while(get<0>(read_configuration(path))==iteration){
				continue;
			}
		}catch(invalid_argument &e){
			continue;
		}
		niteration=get<0>(read_configuration(path));
	}
	tuple<int, int, Plateau> tup = read_configuration(path);
	return tup;
}



void write_mouvement(string path, int iteration, char mouvement){
	ofstream file;
	if(iteration==0){
		file.open(path);
		file << "BET" << endl;
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