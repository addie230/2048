#include "utils.h"
#include <iostream>
#include <cstdlib>

using std::cin;
using std::cout;

void clearInputLine() {
	cin.clear();
	cin.ignore(MAX_INPUT_LINE, '\n');
}

void clearScreen() {
	cout << "\x1b[2J\x1b[H";
	cout.flush();
}

unsigned strLen(const char* s) {
	if (!s) {
		return 0;
	}
	unsigned len = 0;
	while (s[len] != '\0') {
		len++;
	}
	return len;
}

void strCopy(const char* src, char* dest, unsigned destSize) {
	if (!src || !dest || destSize == 0) {
		return;
	}
	unsigned i = 0;
	while (src[i] != '\0' && i + 1 < destSize) {
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

static unsigned pickByChance(int r, int p2, int p4) {
	if (r < p2) return TILE_2;
	if (r < p2 + p4) return TILE_4;
	return TILE_8;
}

unsigned randomTileValue(unsigned maxTileOnBoard) {
	int r = rand() % 100;
	if (maxTileOnBoard < EARLY_GAME_MAX_TILE) {
		return (r < 90) ? TILE_2 : TILE_4;
	}
	if (maxTileOnBoard < MID_GAME_MAX_TILE) {
		return pickByChance(r, 75, 20);
	}
	return pickByChance(r, 60, 30);
}



