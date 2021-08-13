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

static void clear_rows(void) {
    char *iter = grid;
    for (char i = 0; i < 20; ++i) {
        for (char j = 0; j < 10; ++j, ++iter) {
            mvaddch(i + 1, j + 1, *iter ? '*' : ' ');
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
    char threshold = 30;
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
        case KEY_LEFT:
            clear_tetrimino();
            core_move_left_tetrimino();
            draw_tetrimino();
            break;
        case KEY_RIGHT:
            clear_tetrimino();
            core_move_right_tetrimino();
            draw_tetrimino();
            break;
        case KEY_DOWN:
            threshold = 10;
            break;
        case KEY_UP:
            fcnt = 0;
            clear_tetrimino();
            for (; !core_drop_tetrimino(););
            draw_tetrimino();
            core_clear();
            if (offset) {
                clear_rows();
            }
            core_generate();
            if (core_check_drop()) {
                cond = 0;
            }
            break;
        }
        if (fcnt >= threshold) {
            fcnt = 0;
            threshold = 30;
            clear_tetrimino();
            char ret = core_drop_tetrimino();
            draw_tetrimino();
            if (ret) {
                core_clear();
                if (offset) {
                    clear_rows();
                }
                core_generate();
                if (core_check_drop()) {
                    cond = 0;
                }
            }
        }
        usleep(16667);
    }
}

void controller_finalize(void) {
    nodelay(w, 0);
    clear();
    mvaddstr(0, 0, "TETRIS");
    mvaddstr(1, 0, "Game Over");
    getch();
    endwin();
}
