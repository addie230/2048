#ifndef GAME_H
#define GAME_H

#include "constants.h"

void initBoard(unsigned board[MAX_DIM][MAX_DIM], unsigned dim);
unsigned maxTile(const unsigned board[MAX_DIM][MAX_DIM], unsigned dim);
unsigned sumBoard(const unsigned board[MAX_DIM][MAX_DIM], unsigned dim);

#endif