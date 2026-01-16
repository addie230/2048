#include "game.h"
#include "utils.h"
#include <cstdlib>

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

unsigned countEmpty(const unsigned board[MAX_DIM][MAX_DIM], unsigned dim) {
	unsigned cnt = 0;
	for (unsigned r = 0; r < dim; r++) {
		for (unsigned c = 0; c < dim; c++) {
			if (board[r][c] == 0) {
				cnt++;
			}
		}
	}
	return cnt;
}

void addRandomTile(unsigned board[MAX_DIM][MAX_DIM], unsigned dim) {
	unsigned empty = countEmpty(board, dim);
	if (empty == 0) {
		return;
	}
	unsigned pick = (unsigned)(rand() % (int)empty);
	unsigned seen = 0;
	for (unsigned r = 0; r < dim; r++) {
		for (unsigned c = 0; c < dim; c++) {
			if (board[r][c] == 0) {
				if (seen == pick) {
					unsigned m = maxTile(board, dim);
					board[r][c] = randomTileValue(m);
					return;
				}
				seen++;
			}
		}
	}
}