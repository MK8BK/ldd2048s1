#include <ncurses.h>
//g++ ncurses_min.cpp -o ncurses_min.o -lncurses -I "/usr/include/ncursesw"
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

