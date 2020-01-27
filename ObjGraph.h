#include<stdlib.h>

typedef struct ObjNode
{
	int x;
	int y;
	struct ObjNode *north;
	struct ObjNode *east;
	struct ObjNode *south;
	struct ObjNode *west;
} ObjNode;
