#include <ncurses.h>
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


int main() {
	int c;
	initscr();
	keypad(stdscr, true);
	printw("Bonjour!\nIl est temps de presser quelques touches au clavier...\n");
	do {
		c = getch();
		addch(c);
	} while (c != KEY_UP);
	endwin();
	return 0;
}

