game: main.c World.c Form.c ObjGraph.c
	gcc -Wall -g -std=c99 -Wextra -o $@ main.c -lncurses
