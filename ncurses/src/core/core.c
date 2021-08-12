#include "core.h"
#include "pieces.h"
#include "../util/generator.h"

char type, row, col;
char grid[200];

void core_initialize(void) {
    generator_initialize();
}

void core_generate(void) {
    row = 0;
    col = 0;
    type = generator_generate();
}

char core_drop_tetrimino(void) {
    char len = 3 + ((type >> 2) < 2);
    const char *iter = pieces[type];
    char ret = 0;
    for (char i = 0; i < len; ++i) {
        for (char j = 0; j < len; ++j, ++iter) {
            if (*iter == '*') {
                if ((row + i + 1) >= 0 &&
                    ((row + i + 1) < 20) &&
                    (col + j) >= 0 &&
                    ((col + j) < 10) &&
                    grid[(row + i + 1) * 10 + col + j] == '*') {
                    ret = 1;
                    break;
                } else if (row + i == 19) {
                    ret = 1;
                    break;
                }
            }
        }
    }
    if (ret) {
        iter = pieces[type];
        for (char i = 0; i < len; ++i) {
            for (char j = 0; j < len; ++j, ++iter) {
                if (*iter == '*' &&
                    (row + i) >= 0 &&
                    ((row + i) < 20) &&
                    (col + j) >= 0 &&
                    ((col + j) < 10)) {
                    grid[(row + i) * 10 + col + j] = *iter;
                }
            }
        }
        return 1;
    }
    ++row;
    return 0;
}
