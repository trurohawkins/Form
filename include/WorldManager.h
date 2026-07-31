#ifndef WORLDMANAGER
#define WORLDMANAGER

bool startWorld(int graphics, int audio);
void runWorld();
void formLoop(float delta);
void screenChanged(int x, int y);
bool endWorld();

#define MAX_AUDIO_EVENTS 256
bool addTimedEvent(void (*func)(void *), void *data, double frequency);
void pauseSet(bool value);

#define MAX_UI 32
//returns place in activeUI queue, -1 if full
int addUI(int ui, int screenX, int screenY);
void renderUI();
#endif
