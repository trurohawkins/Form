
typedef struct Form
{
	char sprite;
	int color;
	int x;
	int y;
} Form_t;

void moveForm(Form_t *f, int veloX, int veloY)
{
	int x = f->x + veloX;
	int y = f->y + veloY;
	if (x < curWorld->sizeX && x > -1 
	 && y < curWorld->sizeY && y > -1) {
		if (curWorld->map[x][y]->inhabitant == NULL) {
			curWorld->map[f->x][f->y]->inhabitant = 0;
			f->x += veloX;
			f->y += veloY;
			curWorld->map[x][y]->inhabitant = f;
		}
	}
}

void placeForm(Form_t *f, int x, int y)
{
	if (x < curWorld->sizeX && x > -1 
	 && y < curWorld->sizeY && y > -1) {
		if (curWorld->map[x][y]->inhabitant == NULL) {
			curWorld->map[f->x][f->y]->inhabitant = 0;
			f->x = x;
			f->y = y;
			curWorld->map[x][y]->inhabitant = f;
		}
	}

}

Form_t *spawnForm(char obj, int xPos, int yPos)
{
	Form_t *tmp = (Form_t*)malloc(sizeof(Form_t));
	tmp->sprite = obj;
	tmp->x = xPos;
	tmp->y = yPos;
	tmp->color = 0;
	curWorld->map[xPos][yPos]->inhabitant = tmp;
	return tmp;
}


