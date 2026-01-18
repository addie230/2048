/**
*
* Solution to course project # 8
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2025/2026
*
* @author Adriana Maslarova
* @idnumber 0MI0600610
* @compiler VC
*
* file with main game logic
*
*/
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

bool hasAnyMoves(const unsigned board[MAX_DIM][MAX_DIM], unsigned dim) {
	if (countEmpty(board, dim) > 0) {
		return true;
	}
	for (unsigned r = 0; r < dim; r++) {
		for (unsigned c = 0; c + 1 < dim; c++) {
			if (board[r][c] == board[r][c + 1]) {
				return true;
			}
		}
	}
	for (unsigned c = 0; c < dim; c++) {
		for (unsigned r = 0; r + 1 < dim; r++) {
			if (board[r][c] == board[r + 1][c]) {
				return true;
			}
		}
	}
	return false;
}

static bool compressLine(const unsigned in[MAX_DIM], unsigned out[MAX_DIM], unsigned dim) {
	unsigned len = 0;
	for (unsigned i = 0; i < dim; i++) {
		if (in[i] != 0) {
			out[len++] = in[i];
		}
	}
	for (unsigned i = len; i < dim; i++) {
		out[i] = 0;
	}
	for (unsigned i = 0; i < dim; i++) {
		if (out[i] != in[i]) {
			return true;
		}
	}
	return false;
}


static bool mergeAdjacent(unsigned line[MAX_DIM], unsigned dim) {
	bool merged = false;
	for (unsigned i = 0; i + 1 < dim; i++) {
		if (line[i] != 0 && line[i] == line[i + 1]) {
			line[i] *= 2;
			line[i + 1] = 0;
			merged = true;
			i++;
		}
	}
	return merged;
}

static bool buildShiftedLine(const unsigned in[MAX_DIM], unsigned out[MAX_DIM], unsigned dim)
{
	unsigned tmp[MAX_DIM];
	bool changed = false;
	changed |= compressLine(in, tmp, dim);
	changed |= mergeAdjacent(tmp, dim);
	changed |= compressLine(tmp, out, dim);
	return changed;
}

static void shiftRow(unsigned board[MAX_DIM][MAX_DIM], unsigned dim, unsigned row, char cmd, bool& changed)
{
	unsigned line[MAX_DIM];
	unsigned shifted[MAX_DIM];
	for (unsigned i = 0; i < dim; i++) {
		unsigned col = (cmd == CMD_LEFT) ? i : (dim - 1u - i);
		line[i] = board[row][col];
	}
	bool localChanged = buildShiftedLine(line, shifted, dim);
	for (unsigned i = 0; i < dim; i++) {
		unsigned col = (cmd == CMD_LEFT) ? i : (dim - 1u - i);
		board[row][col] = shifted[i];
	}
	changed |= localChanged;
}

static void shiftCol(unsigned board[MAX_DIM][MAX_DIM], unsigned dim, unsigned col, char cmd, bool& changed)
{
	unsigned line[MAX_DIM];
	unsigned shifted[MAX_DIM];
	for (unsigned i = 0; i < dim; i++) {
		unsigned row = (cmd == CMD_UP) ? i : (dim - 1u - i);
		line[i] = board[row][col];
	}
	bool localChanged = buildShiftedLine(line, shifted, dim);
	for (unsigned i = 0; i < dim; i++) {
		unsigned row = (cmd == CMD_UP) ? i : (dim - 1u - i);
		board[row][col] = shifted[i];
	}
	changed |= localChanged;
}

bool applyMove(unsigned board[MAX_DIM][MAX_DIM], unsigned dim, char command) {
	if (command != CMD_LEFT && command != CMD_RIGHT && command != CMD_UP && command != CMD_DOWN) {
		return false;
	}
	bool changed = false;
	if (command == CMD_LEFT || command == CMD_RIGHT) {
		for (unsigned r = 0; r < dim; r++) {
			shiftRow(board, dim, r, command, changed);
		}
	}
	else {
		for (unsigned c = 0; c < dim; c++) {
			shiftCol(board, dim, c, command, changed);
		}
	}
	return changed;
}
