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
	char buf[2];
	cin.getline(buf, 2);
}

static void printMenu() {
	printTitle("Main Menu");
	cout << "1. Start Game" << endl;
	cout << "2. Leaderboard" << endl;
	cout << "3. Exit" << endl;
	cout << "Choice: ";
}

static bool isAllSpaces(const char* s) {
	if (!s) {
		return true;
	}
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

static bool isValidCommand(char cmd) {
	return cmd == CMD_UP || cmd == CMD_LEFT || cmd == CMD_DOWN || cmd == CMD_RIGHT || cmd == CMD_QUIT;
}

static char readCommand() {
	char buf[32];
	cin.getline(buf, 32);
	if (cin.fail()) {
		clearInputLine();
		return 0;
	}
	if (buf[0] == '\0' || buf[1] != '\0') {
		return 0;
	}
	return buf[0];
}

static void initNewGame(unsigned board[MAX_DIM][MAX_DIM], unsigned dim) {
	initBoard(board, dim);
	addRandomTile(board, dim);
	addRandomTile(board, dim);
}

static bool handleTurn(unsigned board[MAX_DIM][MAX_DIM], unsigned dim, const char* nickname, bool& quitByUser) {
	renderBoard(board, dim, nickname);
	cout << endl << "Enter w/a/s/d or q to quit: ";
	char cmd = readCommand();
	if (!isValidCommand(cmd)) {
		cout << "Invalid command." << endl;
		waitEnterToContinue();
		return false; 
	}
	if (cmd == CMD_QUIT) {
		quitByUser = true;
		return true;
	}
	bool moved = applyMove(board, dim, cmd);
	if (moved) {
		addRandomTile(board, dim);
	}
	else {
		cout << "Move not possible." << endl;
		waitEnterToContinue();
	}
	return false; 
}

static void finishGame(unsigned dim, const char* nickname, const unsigned board[MAX_DIM][MAX_DIM], bool quitByUser) {
	unsigned finalScore = sumBoard(board, dim);
	clearScreen();
	if (quitByUser) {
		cout << "You quit the game." << endl;
	}
	else {
		cout << "Game over (no valid moves)." << endl;
	}
	cout << "Final score: " << finalScore << endl << endl;
	updateLeaderboard(dim, nickname, finalScore);
	waitEnterToContinue();
}

static void playGame() {
	char nickname[MAX_NICKNAME_LEN];
	readNickname(nickname);
	unsigned dim = readDimension();
	unsigned board[MAX_DIM][MAX_DIM];
	initNewGame(board, dim);
	bool quitByUser = false;
	while (hasAnyMoves(board, dim)) {
		if (handleTurn(board, dim, nickname, quitByUser)) {
			break;
		}
	}
	finishGame(dim, nickname, board, quitByUser);
}

static void showLeaderboard() {
	clearScreen();
	printTitle("Leaderboard");
	unsigned dim = readDimension();
	clearScreen();
	printTitle("Leaderboard");
	printLeaderboard(dim);
	waitEnterToContinue();
}

void runApplication() {
	while (true) {
		clearScreen();
		printMenu();
		int choice = 0;
		cin >> choice;
		if (cin.fail()) {
			clearInputLine();
			cout << "Invalid choice." << endl;
			waitEnterToContinue();
			continue;
		}
		clearInputLine();
		if (choice == 1) {
			playGame();
		}
		else if (choice == 2) {
			showLeaderboard();
		}
		else if (choice == 3) {
			return;
		}
		else {
			cout << "Invalid choice." << endl;
			waitEnterToContinue();
		}
	}
}

