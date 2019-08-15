#include <ncurses.h>
#include "../../go/go.h"

static struct GoGame game;
static int r, c, cur_r, cur_c;

static inline void move_cursor(void) {
    move(cur_r + ((r - 19) >> 1), (cur_c << 1) + ((c - 37) >> 1));
}

static inline void show_turn(void) {
    mvprintw(0, (c - 7) >> 1, "Turn: %c", game.turn ? 'X' : 'O');
    move_cursor();
}

void initialize(void) {
    init(&game);
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    getmaxyx(stdscr, r, c);
    show_turn();
    mvhline(1, 0, 0, c);
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            mvprintw(i + ((r - 19) >> 1), (j << 1) + ((c - 37) >> 1),
                     "%s", "_ ");
        }
    }
    cur_r = 0;
    cur_c = 0;
    move_cursor();
}

static inline void render(void) {
    game.board_iter = game.board;
    game.board_end = game.board + 361;
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++, game.board_iter++) {
            switch (game.board_iter->stone) {
            case 0:
                mvprintw(i + ((r - 19) >> 1), (j << 1) + ((c - 37) >> 1),
                         "%s", "_ ");
                break;
            case 1:
                mvprintw(i + ((r - 19) >> 1), (j << 1) + ((c - 37) >> 1),
                         "%s", "O ");
                break;
            case 2:
                mvprintw(i + ((r - 19) >> 1), (j << 1) + ((c - 37) >> 1),
                         "%s", "X ");
                break;
            }
        }
    }
    move_cursor();
}

void main_loop(void) {
    for (;;) {
        switch (getch()) {
        case 'Q':
        case 'q':
            return;
        case KEY_DOWN:
            if (cur_r < 18) {
                cur_r++;
            } else {
                cur_r = 0;
            }
            move_cursor();
            break;
        case KEY_LEFT:
            if (cur_c) {
                cur_c--;
            } else {
                cur_c = 18;
            }
            move_cursor();
            break;
        case KEY_RIGHT:
            if (cur_c < 18) {
                cur_c++;
            } else {
                cur_c = 0;
            }
            move_cursor();
            break;
        case KEY_UP:
            if (cur_r) {
                cur_r--;
            } else {
                cur_r = 18;
            }
            move_cursor();
            break;
        case 'Z':
        case 'z':
            play(&game, cur_r, cur_c);
            render();
            show_turn();
            break;
        }
    }
}

void cleanup(void) {
    clear();
    mvprintw(r >> 1, (c - 13) >> 1, "%s", "Press Any Key");
    getch();
    endwin();
}
