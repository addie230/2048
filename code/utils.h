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
* header file for helper functions
*
*/
#ifndef UTILS_H
#define UTILS_H

#include "constants.h"

void clearInputLine();
void clearScreen();
unsigned strLen(const char* s);
void strCopy(const char* src, char* dest, unsigned destSize);
unsigned randomTileValue(unsigned maxTileOnBoard);
int digitCount(unsigned value);

#endif
