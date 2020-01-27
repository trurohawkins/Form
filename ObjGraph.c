#include "ObjGraph.h"

void printNode(ObjNode o)
{
	if (o.north != 0) {
		printf("    %d,%d\n", o.north->x, o.north->y);
	} else {
		printf("    -,-   \n");
	}
	if (o.east != 0) {
		printf("%d,%d", o.east->x, o.east->y);
	} else {
		printf("-,-");
	}
	printf(" %d,%d ", o.x, o.y);
	if (o.west != 0) {
		printf("%d,%d\n", o.west->x, o.west->y);
	} else {
		printf("-,-\n");
	}
	if (o.south != 0) {
		printf("    %d,%d\n", o.south->x, o.south->y);
	} else {
		printf("    -,-\n");
	}
	printf("\n");
}

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

ObjNode *makeNodeArray(int arr[], int size) 
{
	ObjNode *nodes = (ObjNode*)malloc(sizeof(ObjNode) * (size / 2));
	int count = 0;
	for (int i = 0; i < size; i+=2) {
		nodes[count].x = arr[i];
		nodes[count].y = arr[i + 1];
		count++;
	}
	return nodes;
}

void graphNodes(ObjNode nodes[], int size)
{
	for (int i = 0; i < size; i++) {
		int nx, ny, sx, sy, wx, wy, ex, ey;
		nx = ny = sx = sy = wx = wy = ex = ey = 2147483647;
		for (int j = 0; j < size; j++) {
			if (j != i) {
				//north
				//printf("%d < %d \n", nodes[i].y, nodes[j].y);
				if (nodes[i].y < nodes[j].y) {
					int yd = nodes[j].y - nodes[i].y;
					//printf("%d\n",xd);
					if (yd < sy) {
						int xd = abs(nodes[i].x - nodes[j].x);
						if (xd <= sx) {
							sx = xd;
							nodes[i].south = &nodes[j];
						}
					}
				} else if (nodes[i].y > nodes[j].y) {
					int yd = nodes[i].y - nodes[j].y;
					//printf("%d\n",xd);
					if (yd < ny) {
						int xd = abs(nodes[i].x - nodes[j].x);
						if (xd <= nx) {
							nx = xd;
							nodes[i].north = &nodes[j];
						}
					}

				}

				if (nodes[i].x < nodes[j].x) {
					int xd = nodes[j].x - nodes[i].x;
					//printf("%d\n",xd);
					if (xd < wx) {
						int yd = abs(nodes[i].y - nodes[j].y);
						if (yd <= wy) {
							wy = yd;
							nodes[i].west = &nodes[j];
						}
					}
				} else if (nodes[i].x > nodes[j].x) {
					int xd = nodes[i].x - nodes[j].x;
					//printf("%d\n",xd);
					if (xd < ex) {
						int yd = abs(nodes[i].y - nodes[j].y);
						if (yd <= ey) {
							ey = yd;
							nodes[i].east = &nodes[j];
						}
					}

				}

			}	
		}
	}
}

