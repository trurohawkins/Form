#include "ObjGraph.h"

ObjNode *setSquare(int x, int y, int size)
{
	// north east corner
	ObjNode *root = (ObjNode*)malloc(sizeof(ObjNode));
	root->x = x;
	root->y = y;
	// south east corner
	root->south = (ObjNode*)malloc(sizeof(ObjNode));
	root->south->x = x;
	root->south->y = y + size;
	root->south->north = root;
	// south west corner
	ObjNode *sw = root->south->west = (ObjNode*)malloc(sizeof(ObjNode));
	sw->x = x + size;
	sw->y = y + size;
	sw->east = root->south;
	// north west corner
	ObjNode *nw = sw->north = (ObjNode*)malloc(sizeof(ObjNode));
	nw->x = x + size;
	nw->y = y;
	nw->south = sw;
	nw->east = root;
	root->west = nw;
	return root;
}
