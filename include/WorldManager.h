#ifndef WORLDMANAGER
#define WORLDMANAGER

bool startWorld(int graphics, int audio);
void runWorld();
void formLoop(float delta);
void screenChanged(int x, int y);
bool endWorld();

#define CUR_AUDIO_EVENTS 256
void addTimedEvent(void (*func)(void *), void *data, double frequency);
void pauseSet(bool value);
#endif
