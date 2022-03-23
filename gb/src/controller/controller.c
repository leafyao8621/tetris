#include <string.h>
#include <gb/gb.h>
#include "controller.h"
#include "../core/core.h"
#include "../assets/tiles.h"

static uint8_t background[360], field[180];

static inline void render_tetrimino(void) {
    uint16_t tetrimino = tetriminoes[tetrimino_idx];
    uint16_t msk = 0x8000;
    for (uint8_t i = 0, ii = 0; i < 4; ++i) {
        for (uint8_t j = 0; j < 4; ++j, ++ii, msk >>= 1) {
            set_sprite_tile(ii, (tetrimino & msk) != 0);
            move_sprite(
                ii,
                8 + (tetrimino_col << 3) + (j << 3),
                16 + (tetrimino_row << 3) + (i << 3)
            );
        }
    }
}

static inline void render_field(void) {
    static uint8_t *iter_field, i, j;
    static uint16_t *iter_board, buf, msk;
    iter_field = field;
    iter_board = board;
    for (i = 0; i < 18; ++i, ++iter_board) {
        buf = *iter_board;
        msk = 0x200;
        for (j = 0; j < 10; ++j, ++iter_field, msk >>= 1) {
            *iter_field = (buf & msk) != 0;
        }
    }
    set_bkg_tiles(0, 0, 10, 18, field);
}

void controller_initialize(void) {
    set_bkg_data(0, 1, tiles);

    memset(background, 1, 360);
    set_bkg_tiles(0, 0, 20, 18, background);

    SPRITES_8x8;
    set_sprite_data(0, 1, tiles);

    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    waitpad(J_START);
    core_initialize();
    core_reset();

    memset(background, 0, 360);
    set_bkg_tiles(0, 0, 20, 18, background);

    render_tetrimino();

    wait_vbl_done();
}

void controller_main_loop(void) {
    static uint8_t keys, prev, finished;
    prev = 0;
    for (uint8_t f_cnt = 0;; ++f_cnt) {
        keys = joypad();
        if (!(f_cnt % 30)) {
            core_drop();
            render_tetrimino();
            if (msg & RENDER_FLAG) {
                render_field();
            }
        }
        prev = keys;
        wait_vbl_done();
    }
}
