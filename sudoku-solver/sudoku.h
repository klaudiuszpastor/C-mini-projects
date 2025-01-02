#include <stdio.h>
#include <stdlib.h>

char POSSIBLE = 0x1FF;

typedef struct Box {

} Box_t;

typedef struct Square {
	int number;
	char code;
	Box_t *box;
	int row;
	int column;
} Square_t;

int ** createPuzzle(void);
void printPuzzle(int ** puzzle);
Square_t *** setUpPuzzle(int ** puzzle); 
