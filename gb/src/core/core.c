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
uint8_t tetrimino_idx;

void core_initialize(void) {
    static uint16_t seed;
    seed = LY_REG;
    seed |= (uint16_t)DIV_REG << 8;
    initrand(seed);
}

void core_reset(void) {
    tetrimino_idx = (rand() % 7) << 2;
    tetrimino_idx = (rand() % 7) << 2;
    memset(board, 0, 128);
}
