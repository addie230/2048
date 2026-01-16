#include "game.h"
#include "utils.h"

void initBoard(unsigned board[MAX_DIM][MAX_DIM], unsigned dim) {
	for (unsigned r = 0; r < dim; r++) {
		for (unsigned c = 0; c < dim; c++) {
			board[r][c] = 0;
		}
	}
}

unsigned maxTile(const unsigned board[MAX_DIM][MAX_DIM], unsigned dim) {
	unsigned m = 0;
	for (unsigned r = 0; r < dim; r++) {
		for (unsigned c = 0; c < dim; c++) {
			if (board[r][c] > m) {
				m = board[r][c];
			}
		}
	}
	return m;
}

unsigned sumBoard(const unsigned board[MAX_DIM][MAX_DIM], unsigned dim) {
	unsigned sum = 0;
	for (unsigned r = 0; r < dim; r++) {
		for (unsigned c = 0; c < dim; c++) {
			sum += board[r][c];
		}
	}
	return sum;
}