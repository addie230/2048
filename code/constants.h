#ifndef CONSTANTS_H
#define CONSTANTS_H

const char CMD_UP = 'w';
const char CMD_LEFT = 'a';
const char CMD_DOWN = 's';
const char CMD_RIGHT = 'd';
const char CMD_QUIT = 'q';

const unsigned MIN_DIM = 4;
const unsigned MAX_DIM = 10;
const unsigned MAX_INPUT_LINE = 1024;

const unsigned MAX_NICKNAME_LEN = 101;
const unsigned TOP_RESULTS = 5;

const unsigned TILE_2 = 2;
const unsigned TILE_4 = 4;
const unsigned TILE_8 = 8;

const unsigned EARLY_GAME_MAX_TILE = 128; //early game limit
const unsigned MID_GAME_MAX_TILE = 512; //late game limit

#endif
