#ifndef UTILS_H
#define UTILS_H

#include "constants.h"

void clearInputLine();
void clearScreen();

unsigned strLen(const char* s);
void strCopy(const char* src, char* dest, unsigned destSize);

#endif
