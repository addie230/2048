#ifndef GAME_H
#define GAME_H

#include "constants.h"

void initBoard(unsigned board[MAX_DIM][MAX_DIM], unsigned dim);
unsigned maxTile(const unsigned board[MAX_DIM][MAX_DIM], unsigned dim);
unsigned sumBoard(const unsigned board[MAX_DIM][MAX_DIM], unsigned dim);
unsigned countEmpty(const unsigned board[MAX_DIM][MAX_DIM], unsigned dim);
void addRandomTile(unsigned board[MAX_DIM][MAX_DIM], unsigned dim);
bool hasAnyMoves(const unsigned board[MAX_DIM][MAX_DIM], unsigned dim);
bool applyMove(unsigned board[MAX_DIM][MAX_DIM], unsigned dim, char command);

#endif