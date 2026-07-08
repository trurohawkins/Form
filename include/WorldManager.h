#ifndef WORLDMANAGER
#define WORLDMANAGER

bool startWorld(int graphics, int audio);
void runWorld();
void formLoop(float delta);
void screenChanged(int x, int y);
bool endWorld();
#endif
