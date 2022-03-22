#include <string.h>
#include <gb/gb.h>
#include "controller.h"
#include "../core/core.h"
#include "../assets/tiles.h"

#define CNT_START 2

static unsigned char background[360];

static inline void set_sprites(void) {
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

    set_sprites();

    wait_vbl_done();
}

void controller_main_loop(void) {
    static unsigned char keys, prev, finished;
    prev = 0;
    for (uint8_t f_cnt = 0;; ++f_cnt) {
        keys = joypad();
        if (!(f_cnt % 30)) {
        }
        prev = keys;
        wait_vbl_done();
    }
}
