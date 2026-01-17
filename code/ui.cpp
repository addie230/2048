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

static void printHorizontalBorder(unsigned dim, int cellW) {
	cout << "+";
	for (unsigned c = 0; c < dim; c++) {
		for (int i = 0; i < cellW; i++) {
			cout << "-";
		}
		cout << "+";
	}
	cout << endl;
}

static void printCellValue(unsigned value, int cellW) {
	cout << "|";
	if (value == 0) {
		for (int i = 0; i < cellW; i++) {
			cout << " ";
		}
		return;
	}
	int digits = digitCount(value);
	int leftPad = (cellW - digits) / 2;
	int rightPad = cellW - digits - leftPad;
	for (int i = 0; i < leftPad; i++) {
		cout << " ";
	}
	cout << value;
	for (int i = 0; i < rightPad; i++) {
		cout << " ";
	}
}

static void renderBoard(const unsigned board[MAX_DIM][MAX_DIM], unsigned dim, const char* nickname) {
	clearScreen();
	unsigned scorePreview = sumBoard(board, dim);
	cout << "Player: " << nickname << endl;
	cout << "Current sum: " << scorePreview << endl;
	const int cellW = 8;
	printHorizontalBorder(dim, cellW);
	for (unsigned r = 0; r < dim; r++) {
		for (unsigned c = 0; c < dim; c++) {
			printCellValue(board[r][c], cellW);
		}
		cout << "|" << endl;
		printHorizontalBorder(dim, cellW);
	}
	cout << endl;
}
