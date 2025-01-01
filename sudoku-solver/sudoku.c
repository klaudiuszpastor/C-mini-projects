#include "sudoku.h"

int main() {
	int ** puzzle;

	puzzle = createPuzzle();
	printPuzzle(puzzle);
	free(puzzle);
	return 0;
	
}
