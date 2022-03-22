#ifndef _CORE_H_
#define _CORE_H_

#define MINE_FLAG 0x80
#define CHECK_FLAG 0x40
#define MARK_FLAG 0x20

#define CNT_FLAG 0xf

#include <stdint.h>

extern const uint16_t tetriminoes[28];
extern uint16_t board[18];
extern uint8_t tetrimino_idx;
extern int8_t tetrimino_row, tetrimino_col;

void core_initialize(void);
void core_reset(void);

#endif
