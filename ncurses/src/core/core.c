#include "core.h"
#include "pieces.h"
#include "../util/generator.h"

signed char type, row, col;
char start, offset;
char grid[200] = {0};

void core_initialize(void) {
    generator_initialize();
}

void core_generate(void) {
    row = 0;
    col = 0;
    type = generator_generate();
}

char core_check_drop(void) {
    char len = 3 + ((type >> 2) < 2);
    const char *iter = pieces[type];
    for (char i = 0; i < len; ++i) {
        for (char j = 0; j < len; ++j, ++iter) {
            if (*iter == '*') {
                if ((row + i + 1) >= 0 &&
                    ((row + i + 1) < 20) &&
                    (col + j) >= 0 &&
                    ((col + j) < 10) &&
                    grid[(row + i + 1) * 10 + col + j]) {
                    return 1;
                } else if (row + i == 19) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

char core_drop_tetrimino(void) {
    char len = 3 + ((type >> 2) < 2);
    const char *iter = pieces[type];
    char ret = core_check_drop();
    if (ret) {
        iter = pieces[type];
        for (char i = 0; i < len; ++i) {
            for (char j = 0; j < len; ++j, ++iter) {
                if (*iter == '*' &&
                    (row + i) >= 0 &&
                    ((row + i) < 20) &&
                    (col + j) >= 0 &&
                    ((col + j) < 10)) {
                    grid[(row + i) * 10 + col + j] = 1;
                }
            }
        }
        return 1;
    }
    ++row;
    return 0;
}

char core_rotate_tetrimino(void) {
    char len = 3 + ((type >> 2) < 2);
    char temp = (type & 0xFC) | ((type + 1) & 3);
    const char *iter = pieces[temp];
    for (char i = 0; i < len; ++i) {
        for (char j = 0; j < len; ++j, ++iter) {
            if (*iter == '*') {
                if ((row + i) >= 0 &&
                    ((row + i) < 20) &&
                    (col + j) >= 0 &&
                    ((col + j) < 10) &&
                    grid[(row + i) * 10 + col + j]) {
                    return 1;
                } else if ((row + i) < 0 ||
                           ((row + i) >= 20) ||
                           (col + j) < 0 ||
                           ((col + j) >= 10)) {
                    return 1;
                }
            }
        }
    }
    type = temp;
    return 0;
}

char core_move_left_tetrimino(void) {
    char len = 3 + ((type >> 2) < 2);
    const char *iter = pieces[type];
    for (char i = 0; i < len; ++i) {
        for (char j = 0; j < len; ++j, ++iter) {
            if (*iter == '*') {
                if ((row + i) >= 0 &&
                    ((row + i) < 20) &&
                    (col + j - 1) >= 0 &&
                    ((col + j - 1) < 10) &&
                    grid[(row + i) * 10 + col + j - 1]) {
                    return 1;
                } else if (!(col + j)) {
                    return 1;
                }
            }
        }
    }
    --col;
    return 0;
}

char core_move_right_tetrimino(void) {
    char len = 3 + ((type >> 2) < 2);
    const char *iter = pieces[type];
    for (char i = 0; i < len; ++i) {
        for (char j = 0; j < len; ++j, ++iter) {
            if (*iter == '*') {
                if ((row + i) >= 0 &&
                    ((row + i) < 20) &&
                    (col + j + 1) >= 0 &&
                    ((col + j + 1) < 10) &&
                    grid[(row + i) * 10 + col + j + 1]) {
                    return 1;
                } else if (col + j == 9) {
                    return 1;
                }
            }
        }
    }
    ++col;
    return 0;
}

void core_clear(void) {
    char len = 3 + ((type >> 2) < 2);
    char *iter = grid + row * 10;
    offset = 0;
    for (char i = 0, ii = row; i < len && ii < 20; ++i, ++ii) {
        char cnt = 0;
        for (char j = 0; j < 10; ++j, ++iter) {
            cnt += *iter;
        }
        if (cnt == 10) {
            if (!offset) {
                start = ii;
            }
            ++offset;
        }
    }
    char *st = grid + start * 10;
    for (char i = start; i < start + offset; ++i) {
        for (char j = 0; j < 10; ++j, ++st) {
            for (char k = i, *kk = st; k > 0; --k, kk -= 10) {
                *kk = kk[-10];
                kk[-10] = 0;
            }
        }
    }
}
