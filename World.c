#include <stdlib.h>

typedef struct Form
{
	char sprite;
	int x;
	int y;
} Form_t;

typedef struct World
{
	int sizeX;
	int sizeY;
	Form_t ***map;
}World_t;

World_t *curWorld;

World_t *makeMap(int sizeX, int sizeY)
{
	Form_t ***map = (Form_t***)malloc(sizeof(Form_t) * sizeY);
	int i = 0;
	while (i < sizeY) {
		Form_t **t = (Form_t**)malloc(sizeof(Form_t) * sizeX);
		int k = 0;
		while (k < sizeX) {
			t[k] = 0;//tmp;
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

void moveForm(Form_t *f, int veloX, int veloY)
{
	int x = f->x + veloX;
	int y = f->y + veloY;
	if (x < curWorld->sizeX && x > -1 
	 && y < curWorld->sizeY && y > -1) {
		if (curWorld->map[x][y] == NULL) {
			curWorld->map[f->x][f->y] = 0;
			f->x += veloX;
			f->y += veloY;
			curWorld->map[x][y] = f;
		}
	}
}

Form_t *spawnForm(char obj, int xPos, int yPos)
{
	Form_t *tmp = (Form_t*)malloc(sizeof(Form_t));
	//*tmp = {obj, xPos, yPos};
	tmp->sprite = obj;
	tmp->x = xPos;
	tmp->y = yPos;
	curWorld->map[xPos][yPos] = tmp;
	return tmp;
}

void drawMap(World_t *world , WINDOW *win)
{
	wmove(win, 0, 0);
	int y = 0;
	while (y < world->sizeY) {
		int x = 0;
		while (x < world->sizeX) {
			char c = ' ';
			if (world->map[x][y] != 0) {
				c = world->map[x][y]->sprite;
			} 
			waddch(win, c | A_UNDERLINE);
			wrefresh(win);
			x++;
		}
		y++;
	}
}

void deleteMap(World_t *world)
{
	int y = 0;
	while (y < world->sizeY) {
		free(world->map[y]);
		y++;
	}
	free(world->map);
	free(world);
	
}
