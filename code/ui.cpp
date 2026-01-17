#include <iostream>
#include "ui.h"
#include "constants.h"
#include "utils.h"
#include "game.h"
#include "leaderboard.h"

using std::cin;
using std::cout;
using std::endl;

static void printTitle(const char* title) {
	cout << "-====- " << title << " -====-" << endl;
}

static void waitEnterToContinue() {
	cout << endl << "Press ENTER to continue...";
	char dummy[2];
	cin.getline(dummy, 2);
}

static void printMenu() {
	printTitle("Main Menu");
	cout << "1. Start Game" << endl;
	cout << "2. Leaderboard" << endl;
	cout << "3. Exit" << endl;
	cout << "Choice: ";
}

static bool isAllSpaces(const char* s) {
	if (!s) return true;
	for (unsigned i = 0; s[i] != '\0'; i++) {
		if (s[i] != ' ' && s[i] != '\t') {
			return false;
		}
	}
	return true;
}

static void readNickname(char nickname[MAX_NICKNAME_LEN]) {
	while (true) {
		cout << "Enter nickname (max 100 chars): ";
		cin.getline(nickname, MAX_NICKNAME_LEN);
		if (cin.fail()) {
			cin.clear();
			clearInputLine();
			cout << "Nickname too long. Try again." << endl;
			continue;
		}
		if (nickname[0] == '\0' || isAllSpaces(nickname)) {
			cout << "Invalid nickname. Try again." << endl;
			continue;
		}
		return;
	}
}

static unsigned readDimension() {
	unsigned dim = 0;
	cout << "Enter board size (4..10): ";
	cin >> dim;
	while (cin.fail() || dim < MIN_DIM || dim > MAX_DIM) {
		clearInputLine();
		cout << "Invalid size. Enter board size (4..10): ";
		cin >> dim;
	}
	clearInputLine();
	return dim;
}
