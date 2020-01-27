#include <curses.h>
#include "World.c"
#include "ObjGraph.c"
#define MAPX 20
#define MAPY 20

void nCurseOptions();
void findCursorSpot(ObjNode *nodes, ObjNode **cur, Form *player);
void moveCursor(ObjNode **cur, ObjNode *dir, Form *player);

int main(int argc, char **argv)
{
	WINDOW *win = 0;
	if (argc < 2 || argv[1][0] != 'n') {
		nCurseOptions();
		win = newwin(MAPX, MAPY, 0, 0);
	}
	curWorld = makeMap(MAPX, MAPY);
	checkerMap(curWorld);
	Form *player = spawnForm('P', 10, 10);
	int arr[16] = {-2, 1, /**/-1, 2,/**/ 1, 2,/**/ 2, 1,/**/ -2, -1,/**/ -1, -2,/**/ 1, -2,/**/ 2, -1};

	ObjNode *nodes = makeNodeArray(arr, 16);
	graphNodes(nodes, 8);
	ObjNode *cur = nodes;//setSquare(1, 1, 3);

	findCursorSpot(nodes, &cur, player);
	int i = 0;
	while (i >= 0) {
		if (win != 0) {
			drawMap(curWorld, win);
		} else {
			i = -1;
		}
		char c = getch();
		if (c == 'd') {
			moveCursor(&cur, cur->west, player);
		} else if (c == 'a') {
			moveCursor(&cur, cur->east, player);
		} else if (c == 'w') {
			moveCursor(&cur, cur->north, player);
		} else if (c == 's') {
			moveCursor(&cur, cur->south, player);
		}else if (c == ' ') {
				curWorld->map[player->x + cur->x][player->y + cur->y]->effect = 0;
				placeForm(player, player->x + cur->x, player->y + cur->y);
				int x = player->x + cur->x;
				int y = player->y + cur->y;
				if (x >= 0 && y >= 0 && x < MAPX && y < MAPY) {
					curWorld->map[player->x + cur->x][player->y + cur->y]->effect = A_UNDERLINE;
				} else {
					findCursorSpot(nodes, &cur, player);
				}
		} else if (c == 'q') {
			break;
		}
	}
	
	deleteMap(curWorld);
	free(player);
	if (argc < 2 || argv[1][0] != 'n') {
		endwin();
	}
	/*
	for (int i = 0; i < 8; i++) {
		printNode(nodes[i]);
	}
	*/

	return 0;
}

void moveCursor(ObjNode **cur, ObjNode *dir, Form *player)
{
	if (dir) {
		int x = player->x + (*cur)->x;
		int y = player->y + (*cur)->y;
		if (x > 0 && y > 0 && x < MAPX && y < MAPY) {
			curWorld->map[x][y]->effect = 0;
			*cur = dir;
			curWorld->map[player->x + (*cur)->x][player->y + (*cur)->y]->effect = A_UNDERLINE;
		}
	}

}

void findCursorSpot(ObjNode *nodes, ObjNode **cur, Form *player)
{
	for (int i = 0; i < 8; i++) {
		int x = player->x + nodes[i].x;
		int y = player->y + nodes[i].y;
		if (x >= 0 && y >= 0 && x < MAPX && y < MAPY) {
			*cur = &nodes[i];
			curWorld->map[player->x + (*cur)->x][player->y + (*cur)->y]->effect = A_UNDERLINE;
			break;
		}	
	}

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
