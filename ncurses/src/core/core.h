#ifndef _CORE_H_
#define _CORE_H_

extern signed char type, row, col;
extern char start, offset;
extern char grid[200];

void core_initialize(void);
void core_generate(void);
char core_check_drop(void);
char core_drop_tetrimino(void);
char core_rotate_tetrimino(void);
char core_move_left_tetrimino(void);
char core_move_right_tetrimino(void);
void core_clear(void);

#endif
