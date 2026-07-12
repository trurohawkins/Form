#include "GameCore.h"
#include "TUI.h"
#include "AudioMan.h"

#include "form.h"
#include "cell.h"
#include "world.h"
#include "WorldManager.h"

bool runGraphics = true;
bool runAudio = true;

pthread_t gameThread;
pthread_t outputThread;

bool startWorld(int graphics, int audio) {
	srand(time(NULL));
	initDirections();

	initCore();

	initGame();

	initTermInput();
	if (graphics > 0) {
		initScreen();
	}
	runGraphics = graphics;
	if (audio > 0) {
		initAudio();
	}
	runAudio = audio;

	return true;
}

void runWorld() {
	gameLoop = &formLoop;
	resizeScreen = &screenChanged;
	gameThread = createThread(runGame, NULL, false);
	outputThread = 0;
	if (runGraphics > 0) {
		 outputThread = createThread(outputLoop, NULL, false);
	}

	coreLoop();
}


void formLoop(float delta) {
	parseAudioEvents();
	if (runGraphics) {
		renderWorld();
	}
}

void screenChanged(int x, int y) {
	worldChanged = true;
}

bool endWorld() {
	pthread_join(gameThread, NULL);
	if (runGraphics > 0) {
		pthread_join(outputThread, NULL);
	}
	
	exitCore();
	closeGame();
	exitTermInput();
	if (runGraphics > 0) {
		exitScreen();
	}
	if (runAudio > 0) {
		endAudio();
	}
	freeWorld();
	return true;
}

