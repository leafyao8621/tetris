#ifndef _CORE_H_
#define _CORE_H_

#define RENDER_FLAG 0x1
#define UPDATE_FLAG 0x2
#define RESET_FLAG 0x4

#include <stdint.h>

extern const uint16_t tetriminoes[28];
extern uint16_t board[18];
extern uint8_t tetrimino_idx, msg;
extern int8_t tetrimino_row, tetrimino_col;

void core_initialize(void);
void core_reset(void);
void core_drop(void);
void core_rotate(void);
void core_move_right(void);
void core_move_left(void);

#endif
