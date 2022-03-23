#include <string.h>
#include <gb/gb.h>
#include <rand.h>
#include "core.h"

const uint16_t tetriminoes[28] = {
    0x0660,
    0x0660,
    0x0660,
    0x0660,
    0x00f0,
    0x2222,
    0x00f0,
    0x2222,
    0x0e20,
    0x44c0,
    0x8e00,
    0x6440,
    0x0e80,
    0xc440,
    0x2e00,
    0x2260,
    0x06c0,
    0x4620,
    0x06c0,
    0x4620,
    0x0e40,
    0x4c40,
    0x4e00,
    0x4640,
    0x0c60,
    0x2640,
    0x0c60,
    0x2640
};
uint16_t board[18];
uint8_t tetrimino_idx, msg;
int8_t tetrimino_row, tetrimino_col;

void core_initialize(void) {
    static uint16_t seed;
    seed = LY_REG;
    seed |= (uint16_t)DIV_REG << 8;
    initrand(seed);
}

static inline void generate_tetrimino(void) {
    tetrimino_idx = (rand() % 7) << 2;
    tetrimino_row = 0;
    tetrimino_col = 0;
}

void core_reset(void) {
    memset(board, 0, 36);
    generate_tetrimino();
}

static inline void place_tetrimino(void) {
    static uint16_t msk;
    static uint8_t i, j;
    msk = 0x8000;
    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 4; ++j, msk >>= 1) {
            if (tetriminoes[tetrimino_idx] & msk) {
                board[tetrimino_row + i] |= 0x200 >> (tetrimino_col + j);
            }
        }
    }
}

void core_drop(void) {
    static uint16_t msk;
    static uint8_t i, j;
    msk = 0x8000;
    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 4; ++j, msk >>= 1) {
            if (
                (tetriminoes[tetrimino_idx] & msk) &&
                (
                    tetrimino_row + i == 17 ||
                    (
                        board[tetrimino_row + i + 1] &
                        (0x200 >> (tetrimino_col + j))
                    )
                )
            ) {
                place_tetrimino();
                generate_tetrimino();
                msg |= RENDER_FLAG;
                return;
            }
        }
    }
    ++tetrimino_row;
}
