#include <curses.h>
#include "World.c"
#include "ObjGraph.c"
#define MAPX 10
#define MAPY 10

void nCurseOptions();

int main(int argc, char **argv)
{
	WINDOW *win = 0;
	if (argc < 2 || argv[1][0] != 'n') {
		nCurseOptions();
		win = newwin(MAPX, MAPY, 0, 0);
	}
	curWorld = makeMap(MAPX, MAPY);
	checkerMap(curWorld);
	Form_t *player = spawnForm('P', 1, 1);
	ObjNode *cur = setSquare(1, 1, 3);

	int i = 0;
	while (i >= 0) {
		if (win != 0) {
			drawMap(curWorld, win);
		} else {
			i = -1;
		}
		char c = getch();
		if (c == 'd') {
			if (cur->west) {
				curWorld->map[cur->x][cur->y]->effect = 0;
				cur = cur->west;
				curWorld->map[cur->x][cur->y]->effect = A_UNDERLINE;
			}
		} else if (c == 'a') {
			if (cur->east) {
				curWorld->map[cur->x][cur->y]->effect = 0;
				cur = cur->east;
				curWorld->map[cur->x][cur->y]->effect = A_UNDERLINE;
			}
		} else if (c == 'w') {
			if (cur->north) {
				curWorld->map[cur->x][cur->y]->effect = 0;
				cur = cur->north;
				curWorld->map[cur->x][cur->y]->effect = A_UNDERLINE;
			}
		} else if (c == 's') {
			if (cur->south) {
				curWorld->map[cur->x][cur->y]->effect = 0;
				cur = cur->south;
				curWorld->map[cur->x][cur->y]->effect = A_UNDERLINE;
			}
		}else if (c == 'x') {
			placeForm(player, cur->x, cur->y);
		} else if (c == 'q') {
			break;
		}
	}
	
	deleteMap(curWorld);
	free(player);
	if (argc < 2 || argv[1][0] != 'n') {
		endwin();
	}
	return 0;
}

void nCurseOptions()
{
	initscr();
	cbreak();
	noecho();
	nodelay(stdscr,  TRUE);
	curs_set(0);
	keypad(stdscr, TRUE);
	start_color();
	init_pair(1, 0, 1);
	init_pair(2, 0, 4);
	init_pair(3, 7, 1);
	init_pair(4, 7, 4);
	
}
/* player controls
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
*/
