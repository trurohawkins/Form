#include <curses.h>
#include "World.c"
#define MAPX 10
#define MAPY 10

int main()
{
	initscr();
	cbreak();
	noecho();
	nodelay(stdscr,  TRUE);
	curs_set(0);
	keypad(stdscr, TRUE);
	WINDOW *win = newwin(MAPX, MAPY, 0, 0);
	curWorld = makeMap(MAPX, MAPY);
	Form_t *player = spawnForm('P', 0, 2);
	spawnForm('*', 1, 3);
		
	int i = 0;
	while (i >= 0) {
		drawMap(curWorld, win);
		char c = getch();
		if (c == 'd') {
			moveForm(player, 1, 0);
		} else if (c == 'a') {
			moveForm(player, -1, 0);
		} else if (c == 'w') {
			moveForm(player, 0, -1);
		} else if (c == 's') {
			moveForm(player, 0, 1);
		} else if (c == 'q') {
			break;
		}
	}
	
	deleteMap(curWorld);
	endwin();
	return 0;
}
