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



