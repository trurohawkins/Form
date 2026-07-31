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


int audioEvents[MAX_AUDIO_EVENTS];
RenderCommand activeUI[MAX_UI];

bool startWorld(int graphics, int audio) {
	srand(time(NULL));
	initDirections();

	initCore();

	initGame();

	initTermInput();
	if (graphics > 0) {
		initScreen();
		for (int i = 0; i < MAX_UI; i++) {
			activeUI[i].type = 1;
			activeUI[i].index = -1;
		}
	}
	runGraphics = graphics;
	if (audio > 0) {
		initAudio();
		for (int i = 0; i < MAX_AUDIO_EVENTS; i++) {
			audioEvents[i] = -1;
		}
	}
	runAudio = audio;
	pauseFunc = pauseSet;

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
	if (runGraphics && worldChanged) {
		startRendering();
		renderWorld();
		renderUI();
		sendRenderFrame();
		worldChanged = false;
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

bool addTimedEvent(void (*func)(void *), void *data, double frequency) {
	int event = scheduleEvent(func, data, frequency);
	for (int i = 0; i < MAX_AUDIO_EVENTS; i++) {
		if (audioEvents[i] == -1) {
			audioEvents[i] = event;
			return true;
		}
	}
	return false;
}

void pauseSet(bool value) {
	for (int i = 0; i < MAX_AUDIO_EVENTS; i++) {
		if (audioEvents[i] != -1) {
			if (value) {
				pauseAudioEvent(audioEvents[i]);
			} else {
				unpauseAudioEvent(audioEvents[i]);
			}
		}
	}
}

int addUI(int ui, int screenX, int screenY) {
	for (int i = 0; i < MAX_UI; i++) {
		if (activeUI[i].index == -1) {
			activeUI[i].index = ui;
			activeUI[i].screenPos[0] = screenX;
			activeUI[i].screenPos[1] = screenY;
			activeUI[i].layer = 10;
			return i;
		}
	}
	return -1;
}

void renderUI() {
	for (int i = 0; i < MAX_UI; i++) {
		if (activeUI[i].index != -1) {
			addRenderCommand(activeUI[i]);
		}
	}
}
