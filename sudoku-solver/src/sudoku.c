#include "sudoku.h"

int main() {
	int ** puzzle;
	Square_t *** sudoku;	

	puzzle = createPuzzle();
	printPuzzle(puzzle);

	sudoku = setUpPuzzle(puzzle);

	free(puzzle);
	return 0;
	
}
