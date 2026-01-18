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
* file for the leaderboard logic
*
*/
#include <iostream>
#include "leaderboard.h"
#include "utils.h"
#include <fstream>

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

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

static void load(unsigned dim, char names[TOP_RESULTS][MAX_NICKNAME_LEN], unsigned scores[TOP_RESULTS]) {
    for (unsigned i = 0; i < TOP_RESULTS; i++) {
        names[i][0] = '\0';
        scores[i] = 0;
    }
    char filename[32];
    buildFilename(dim, filename);
    ifstream in(filename);
    if (!in.is_open()) {
        return;
    }
    unsigned index = 0;
    while (index < TOP_RESULTS) {
        char nameLine[256];
        if (!in.getline(nameLine, sizeof(nameLine))) {
            break;
        }
        if (nameLine[0] == '\0') {
            continue;
        }
        unsigned score = 0;
        in >> score;
        if (in.fail()) {
            break;
        }
        in.ignore(MAX_INPUT_LINE, '\n');
        strCopy(nameLine, names[index], MAX_NICKNAME_LEN);
        scores[index] = score;
        index++;
    }
    in.close();
}

static void save(unsigned dim, char names[TOP_RESULTS][MAX_NICKNAME_LEN], unsigned scores[TOP_RESULTS]) {
    char filename[32];
    buildFilename(dim, filename);
    ofstream out(filename);
    if (!out.is_open()) {
        return;
    }
    for (unsigned i = 0; i < TOP_RESULTS; i++) {
        if (scores[i] > 0 && names[i][0] != '\0') {
            out << names[i] << endl;
            out << scores[i] << endl;
        }
    }
    out.close();
}

static bool qualifies(const unsigned scores[TOP_RESULTS], unsigned score) {
    for (unsigned i = 0; i < TOP_RESULTS; i++) {
        if (score > scores[i]) {
            return true;
        }
    }
    return (score == scores[TOP_RESULTS - 1]);
}

static void insertSorted(char names[TOP_RESULTS][MAX_NICKNAME_LEN], unsigned scores[TOP_RESULTS], const char* nickname, unsigned score) {
    if (score == scores[TOP_RESULTS - 1]) {
        scores[TOP_RESULTS - 1] = score;
        strCopy(nickname, names[TOP_RESULTS - 1], MAX_NICKNAME_LEN);
        return;
    }
    for (unsigned pos = 0; pos < TOP_RESULTS; pos++) {
        if (score > scores[pos]) {
            for (unsigned j = TOP_RESULTS - 1; j > pos; j--) {
                scores[j] = scores[j - 1];
                strCopy(names[j - 1], names[j], MAX_NICKNAME_LEN);
            }
            scores[pos] = score;
            strCopy(nickname, names[pos], MAX_NICKNAME_LEN);
            return;
        }
    }
}

void updateLeaderboard(unsigned dim, const char* nickname, unsigned score) {
    if (!nickname || score == 0 || dim < MIN_DIM || dim > MAX_DIM) {
        return;
    }
    char names[TOP_RESULTS][MAX_NICKNAME_LEN];
    unsigned scores[TOP_RESULTS];
    load(dim, names, scores);
    if (!qualifies(scores, score)) {
        return;
    }
    insertSorted(names, scores, nickname, score);
    save(dim, names, scores);
}

void printLeaderboard(unsigned dim) {
    if (dim < MIN_DIM || dim > MAX_DIM) {
        cout << "Invalid board size." << endl;
        return;
    }
    char names[TOP_RESULTS][MAX_NICKNAME_LEN];
    unsigned scores[TOP_RESULTS];
    load(dim, names, scores);
    cout << "Leaderboard for " << dim << "x" << dim << ":" << endl;
    bool empty = true;
    for (unsigned i = 0; i < TOP_RESULTS; i++) {
        if (scores[i] > 0 && names[i][0] != '\0') {
            cout << (i + 1) << ". " << names[i] << " - " << scores[i] << endl;
            empty = false;
        }
    }
    if (empty) {
        cout << "(empty)" << endl;
    }
}
