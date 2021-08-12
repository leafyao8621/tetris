#include <unistd.h>
#include <ncurses.h>
#include "../core/core.h"
#include "../core/pieces.h"

WINDOW *w;

static void draw_tetrimino(void) {
    char len = 3 + ((type >> 2) < 2);
    const char *iter = pieces[type];
    for (char i = 0; i < len; ++i) {
        for (char j = 0; j < len; ++j, ++iter) {
            if (*iter == '*' &&
                (row + i) >= 0 &&
                ((row + i) < 20) &&
                (col + j) >= 0 &&
                ((col + j) < 10)) {
                mvaddch(row + i + 1, col + j + 1, *iter);
            }
        }
    }
}

static void clear_tetrimino(void) {
    char len = 3 + ((type >> 2) < 2);
    const char *iter = pieces[type];
    for (char i = 0; i < len; ++i) {
        for (char j = 0; j < len; ++j, ++iter) {
            if (*iter == '*' &&
                (row + i) >= 0 &&
                ((row + i) < 20) &&
                (col + j) >= 0&&
                ((col + j) < 10)) {
                mvaddch(row + i + 1, col + j + 1, ' ');
            }
        }
    }
}

void controller_initialize(void) {
    w = initscr();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    cbreak();
    nodelay(w, 1);
    core_initialize();
    mvaddstr(0, 0, "TETRIS");
    for (char i = 0; i < 21; ++i) {
        for (char j = 0; j < 12; ++j) {
            mvaddch(i + 1, j, i < 20 ? (!j || j == 11 ? '*' : ' ') : '*');
        }
    }
    core_generate();
    draw_tetrimino();
}

void controller_main(void) {
    int c;
    char cond = 1;
    char fcnt = 0;
    for (; cond; ++fcnt) {
        c = getch();
        switch (c) {
        case 'Q':
        case 'q':
            cond = 0;
            break;
        case 'Z':
        case 'z':
            clear_tetrimino();
            core_rotate_tetrimino();
            draw_tetrimino();
            break;
        }
        if (fcnt == 30) {
            fcnt = 0;
            clear_tetrimino();
            char ret = core_drop_tetrimino();
            draw_tetrimino();
            if (ret) {
                core_generate();
            }
        }
        usleep(16667);
    }
}

void controller_finalize(void) {
    nodelay(w, 0);
    clear();
    endwin();
}
