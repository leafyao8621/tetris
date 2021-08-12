#ifndef _CORE_H_
#define _CORE_H_

extern char type, row, col;
extern char grid[200];

void core_initialize(void);
void core_generate(void);
char core_drop_tetrimino(void);

#endif
