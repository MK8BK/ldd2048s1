#include <ncurses.h>
using namespace std;
#include <iostream>
//g++ ncurses_min.cpp -o ncurses_min.o -lncurses -I "/usr/include/ncursesw"
	// initscr();
	// start_color();
	// init_color(COLOR_RED, 700, 0, 0);
	// init_color(COLOR_BLACK, 500, 500, 500);
	// init_color(COLOR_BLACK, 120, 111, 87)
	// init_pair(1, COLOR_RED, COLOR_BLACK);	
	// attron(COLOR_PAIR(1));
	// printw("Viola !!! In color ...");
	// attroff(COLOR_PAIR(1));
	// // attron(COLOR_PAIR(2));
	// getch();
	// endwin();



int get_input_arrows(){
	int c;
	initscr();
	keypad(stdscr, true);
	c = getch();
	addch(c);
	endwin();
	int answer;
	if(c==KEY_RIGHT){
		answer=0;
	}
	else if(c==KEY_UP){
		answer =1;
	}else if(c==KEY_LEFT){
		answer=2;
	}else if(c==KEY_DOWN){
		answer=3;
	}
	return answer;
}

int main() {
	cout<<"this text"<<endl;
	cout<<to_string(get_input_arrows())<<endl;
	cout<<"this other text"<<endl;
	// int c;
	// initscr();
	// keypad(stdscr, true);
	// printw("Bonjour!\nIl est temps de presser quelques touches au clavier...\n");
	// do {
	// 	c = getch();
	// 	addch(c);
	// } while (c != KEY_UP);
	// endwin();
	return 0;
}

