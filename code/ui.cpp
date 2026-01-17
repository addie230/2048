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
