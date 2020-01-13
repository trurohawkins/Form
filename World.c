#include <stdlib.h>
#include <stdbool.h>

typedef struct Cell
{
	void *inhabitant;
	int color;
	int effect;
} Cell_t;

typedef struct World
{
	int sizeX;
	int sizeY;
	Cell_t ***map;
}World_t;

World_t *curWorld;
#include "Form.c"

World_t *makeMap(int sizeX, int sizeY)
{
	Cell_t ***map = (Cell_t***)malloc(sizeof(Cell_t) * sizeY);
	int i = 0;
	while (i < sizeY) {
		Cell_t **t = (Cell_t**)malloc(sizeof(Cell_t) * sizeX);
		//Cell_t *t[sizeX];
		int k = 0;
		while (k < sizeX) {
			t[k] = (Cell_t*)malloc(sizeof(Cell_t));
			k++;
		}
		map[i] = t;
		i++;
	}
	World_t *w = (World_t*)malloc(sizeof(World_t)); 
	World_t tmpW = {sizeX, sizeY, map};
	*w = tmpW;
	return w;
}

void checkerMap(World_t *world)
{
	int x = 0;
	while (x < world->sizeX) {
		int y = 0;
		int color = x % 2;
		while (y < world->sizeY) {
			color = (color + 1) % 2;
			world->map[x][y]->color = 1 + color;
			y++;
		}
 		x++;
	}
}

void drawMap(World_t *world , WINDOW *win)
{
	wmove(win, 0, 0);
	int y = 0;
	while (y < world->sizeY) {
		int x = 0;
		while (x < world->sizeX) {
			char c = ' ';
			int col = 0;
			if (world->map[x][y]->inhabitant != 0) {
				Form_t *f = (Form_t*)world->map[x][y]->inhabitant;
				c = f->sprite;
				col = f->color;
			}
			waddch(win, c | COLOR_PAIR(world->map[x][y]->color + col) | world->map[x][y]->effect);
			wrefresh(win);
			x++;
		}
		y++;
	}
}

void deleteMap(World_t *world)
{
	int x = 0;
	while (x < world->sizeX) {
		int y = 0;
		while (y < world->sizeY) {
			free(world->map[x][y]);
			y++;
		}
		free(world->map[x]);
		x++;
	}
	free(world->map);
	free(world);
}

