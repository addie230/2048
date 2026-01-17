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
* header file for leaderboard functions
*
*/
#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include "constants.h"

void updateLeaderboard(unsigned dim, const char* nickname, unsigned score);
void printLeaderboard(unsigned dim);

#endif