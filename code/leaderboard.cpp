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

static bool parseEntryLine(const char* line, char nameOut[MAX_NICKNAME_LEN], unsigned& scoreOut) {
	if (!line) {
		return false;
	}
	int sep = -1;
	for (int i = 0; line[i] != '\0'; i++) {
		if (line[i] == '|') {
			sep = i;
			break;
		}
	}
	if (sep <= 0) {
		return false;
	}
	int i = 0;
	for (; i < sep && i < (int)MAX_NICKNAME_LEN - 1; i++) {
		nameOut[i] = line[i];
	}
	nameOut[i] = '\0';
	unsigned value = 0;
	bool hasDigit = false;
	for (int j = sep + 1; line[j] != '\0'; j++) {
		if (line[j] < '0' || line[j] > '9') {
			break;
		}
		hasDigit = true;
		value = value * 10u + (unsigned)(line[j] - '0');
	}
	if (!hasDigit) {
		return false;
	}
	scoreOut = value;
	return true;
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
	char line[256];
	unsigned index = 0;
	while (index < TOP_RESULTS && in.getline(line, sizeof(line))) {
		char nameBuf[MAX_NICKNAME_LEN];
		unsigned scoreBuf = 0;
		if (parseEntryLine(line, nameBuf, scoreBuf)) {
			strCopy(nameBuf, names[index], MAX_NICKNAME_LEN);
			scores[index] = scoreBuf;
			index++;
		}
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
			out << names[i] << "|" << scores[i] << endl;
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
	return false;
}

static void insertSorted(char names[TOP_RESULTS][MAX_NICKNAME_LEN], unsigned scores[TOP_RESULTS], const char* nickname, unsigned score) {
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