#include "FormEngine.h"
#include "TUI.h"
#include "AudioMan.h"

int worldX = 40;
int worldY = 50;

typedef struct {
	Form *self;
	int moveX;
	int moveY;

	int speed;
	int speedCounter;
} moveVar;

int sound0;

void moveGuy(void *move) {
	moveVar *mv = move;
	Form *f = mv->self;
	if (mv->moveX != 0 || mv->moveY != 0) {
		moveForm(f, mv->moveX, mv->moveY);
		setFramePosition(f->pos[0], f->pos[1]);
	}
}

int move(void *form, Action *act) {
	return 0;
	moveVar *mv = act->data;
	Form *f = form;
	if (mv->speedCounter >= mv->speed) {
		if (mv->moveX != 0 || mv->moveY != 0) {
			moveForm(f, mv->moveX, mv->moveY);
			setFramePosition(f->pos[0], f->pos[1]);
		}
		mv->speedCounter = 0;
	} else {
		mv->speedCounter++;
	}
	return 0;
}

void moveUp(void *actor, float val) {
	Action *move = findAction(actor, 0);
	if (move) {
		moveVar *mv = move->data;
		if (val == 1) {
			mv->moveY = 1;
		} else {
			//mv->moveY = 0;
		}
	}
}

void moveLeft(void *actor, float val) {
	Action *move = findAction(actor, 0);
	if (move) {
		moveVar *mv = move->data;
		if (val == 1) {
			mv->moveX = -1;
		} else {
			//mv->moveX = 0;
		}
	}
}

void moveDown(void *actor, float val) {
	Action *move = findAction(actor, 0);
	if (move) {
		moveVar *mv = move->data;
		if (val == 1) {
			mv->moveY = -1;
		} else {
			//mv->moveY = 0;
		}
	}
}

void moveRight(void *actor, float val) {
	Action *move = findAction(actor, 0);
	if (move) {
		moveVar *mv = move->data;
		if (val == 1) {
			mv->moveX = 1;
		} else {
			//mv->moveX = 0;
		}
	}
}

void moveFrameUp(void *actor, float val) {
	if (val == 1) {
		moveFrame(0, 1);
	}
}
void moveFrameLeft(void *actor, float val) {
	if (val == 1) {
		moveFrame(-1, 0);
	}
}
void moveFrameDown(void *actor, float val) {
	if (val == 1) {
		moveFrame(0, -1);
	}
}
void moveFrameRight(void *actor, float val) {
	if (val == 1) {
		moveFrame(1, 0);
	}
}


int main() {
	startWorld(true, true);
	sound0 = processAudioFile("resources/a1.wav", false);
	//scheduleAudio(sound0, 1.0);

	makeWorld(worldX, worldY);
	setFrameDimension(20, 10);
	setFramePosition(worldX/2, worldY/2);

	Form *f = makeForm(0);
	Sigil *skin = createSigil(f)->data;
	skin->symbol = '@';
	skin->figure = true;
	skin->r = 128;
	skin->g = 128;
	skin->b = 128;

	Actor *actor = makeFormActor(f);
	addActor(actor);
	moveVar mv = {
		.self = f,
		.moveX = 0,
		.moveY = 0,
		.speed = 10,
		.speedCounter = 0,
	};
	Action *m = makeAction(0, &move, &mv);
	addAction(actor, m);
	scheduleEvent(0, moveGuy, &mv, 3.0);
	Player *p = makePlayer(actor, 0, 0);
	addControl(p, "K0W", moveUp);
	addControl(p, "K0A", moveLeft);
	addControl(p, "K0S", moveDown);
	addControl(p, "K0D", moveRight);
	addControl(p, "K0I", moveFrameUp);
	addControl(p, "K0J", moveFrameLeft);
	addControl(p, "K0K", moveFrameDown);
	addControl(p, "K0L", moveFrameRight);
	addPlayer(p);

	placeForm(f, worldX/2, worldY/2);

	Form *checker0 = makeForm(1);
	Sigil *chk0 = createSigil(checker0)->data;
	chk0->r = 0;
	chk0->g = 64;
	chk0->b = 0;
	Form *checker1 = makeForm(1);
	Sigil *chk1 = createSigil(checker1)->data;
	chk1->r = 0;
	chk1->g = 0;
	chk1->b = 64;
	for (int x = 0; x < worldX; x++) {
		for (int y = 0; y < worldY; y++) {
			if (randPercent() > 0.5) {
				placeForm(checker0, x ,y);
			} else {
				placeForm(checker1, x, y);
			}
		}
	}
	printForm(f);
	runWorld();
	endWorld();
	return 0;
}

