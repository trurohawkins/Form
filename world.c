#include "GameCore.h"
#include "form.h"
#include "cell.h"
#include "world.h"

int frameDim[2] = {0, 0};
int framePos[2] = {0, 0};
bool worldChanged = false;

World theWorld = {
	.x = 0,
	.y = 0,
	.map = 0
};

void makeWorld(int x, int y) {
	theWorld.x = x;
	theWorld.y = y;
	theWorld.map = calloc(x * y, sizeof(Cell));
}

World *getWorld() {
	return &theWorld;
}

void setFrameDimension(int x, int y) {
	frameDim[0] = x;
	frameDim[1] = y;
	worldChanged = true;
}

void setFramePosition(int x, int y) {
	int oldX = framePos[0];
	int oldY = framePos[1];
	framePos[0] = clamp(x - frameDim[0]/2, 0, theWorld.x - frameDim[0]);
	framePos[1] = clamp(y - frameDim[1]/2, 0, theWorld.y - frameDim[1]);
	if (oldX != framePos[0] || oldY != framePos[1]) {
		worldChanged = true;
	}
}

void moveFrame(int xd, int yd) {
	setFramePosition(framePos[0] + frameDim[0]/2  + xd, framePos[1] + frameDim[1] / 2 + yd);
}

void freeWorld() {
	linkedList *forms = 0;
	for (int i = 0; i < theWorld.x * theWorld.y; i++) {
		Cell c = theWorld.map[i];
		for (int j = 0; j < FORMS_PER_CELL; j++) {
			if (c.within[j] != 0) {
				addToListSingle(&forms, c.within[j]);
			}
		}
	}
	if (forms) {
		deleteList(&forms, &freeForm);
	}
}

bool placeForm(Form *f, int x, int y) {
	if (x >= 0 && y >= 0 && x < theWorld.x && y < theWorld.y) {
		Cell *c = &theWorld.map[(y*theWorld.x) + x];
		if (addToCell(f, c)) {
			f->pos[0] = x;
			f->pos[1] = y;
			worldChanged = true;
			return true;
		}
	}
	return false;
}

bool removeForm(Form *f, int x, int y) {
	if (x >= 0 && y >= 0 && x < theWorld.x && y < theWorld.y) {
		Cell *c = &theWorld.map[(y*theWorld.x) + x];
		if (removeFromCell(f, c)) {
			worldChanged = true;
		}
	}
	return false;
}

bool moveForm(Form *f, int xd, int yd) {
	int xp = f->pos[0] + xd;
	int yp = f->pos[1] + yd;
	if (xp >= 0 && yp >=0 && xp < theWorld.x && yp < theWorld.y) {
		removeForm(f, f->pos[0], f->pos[1]);
		placeForm(f, xp, yp);
		return true;
	}
	return false;
}

Cell *getCell(int x, int y) {
	if (x >= 0 && y >= 0 && x < theWorld.x && y < theWorld.y) {
		return &theWorld.map[(y * theWorld.x) + x];
	} else {
		return 0;
	}
}

bool checkFormID(int x, int y, int id) {
	Cell *c = getCell(x, y);
	if (c) {
		for (int i = 0; i < FORMS_PER_CELL; i++) {
			if (c->within[i] && c->within[i]->id == id) {
				return true;
			}
		}
	}
	return false;
}

int worldXToScreenX(int wx) {
	return wx + screenX/2 - frameDim[0]/2;
}

int worldYToScreenY(int wy) {
	wy = frameDim[1] - wy;
	return wy + screenY/2 - frameDim[1]/2;
}

void renderWorld() {
	if (!worldChanged) {
		return;
	}
	startRendering();
	for (int y = 0; y < frameDim[1]; y++) {
		for (int x = 0; x < frameDim[0]; x++) {
			int xp = x + framePos[0];
			int yp = y + framePos[1];
			int w = yp * theWorld.x + xp;
			Cell c = theWorld.map[w];
			for (int i = 0; i < FORMS_PER_CELL; i++) {
				if (c.within[i]) {
					Nub *skin = findNub(c.within[i], 1);
					if (skin) {
						RenderObject *rob = skin->data;
						if (rob->render) {
							rob->render(rob->data);
						}
					}
				}						
			}
		}
	}
	sendRenderFrame();
	worldChanged = false;
}

