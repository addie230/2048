#include <iostream>
#include "leaderboard.h"

using std::cout;
using std::endl;

static unsigned writeUnsigned(unsigned value, char out[32], unsigned pos) {
    char buf[10];
    unsigned len = 0;
    if (value == 0) {
        out[pos++] = '0';
        return pos;
    }
    while (value > 0) {
        buf[len++] = (char)('0' + (value % 10));
        value /= 10;
    }
    while (len > 0) {
        out[pos++] = buf[--len];
    }
    return pos;
}

static void buildFilename(unsigned dim, char out[32]) {
    const char* prefix = "leaderboard_";
    const char* suffix = ".txt";
    unsigned p = 0;
    while (prefix[p] != '\0') {
        out[p] = prefix[p];
        p++;
    }
    p = writeUnsigned(dim, out, p);
    out[p++] = 'x';
    p = writeUnsigned(dim, out, p);
    unsigned s = 0;
    while (suffix[s] != '\0') {
        out[p++] = suffix[s++];
    }
    out[p] = '\0';
}
