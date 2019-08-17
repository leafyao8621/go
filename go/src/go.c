#include <stdio.h>
#include <string.h>
#include "go.h"

void init(struct GoGame* game) {
    memset(game, 0, sizeof(struct GoGame));
}

static inline _Bool check_suicide(struct GoGame* game,
                                  int row, int col, int ind) {
    game->stack_end = game->stack;
    game->visited_end = game->visited;
    game->board[ind].visited = 1;
    *((game->visited_end)++) = game->board + ind;
    int cur_ind, cur_row, cur_col;
    _Bool out = 1;
    for (*((game->stack_end)++) = game->board + ind;
         game->stack_end != game->stack;) {
        game->stack_end--;
        cur_ind = *(game->stack_end) - game->board;
        cur_row = cur_ind / 19;
        cur_col = cur_ind % 19;
        if (cur_row) {
            if (game->board[ind - 19].stone) {
                if (game->board[ind - 19].stone == game->turn + 1 &&
                    !(game->board[ind - 19].visited)) {
                    game->board[ind - 19].visited = 1;
                    *((game->visited_end)++) = game->board + cur_ind - 19;
                    *((game->stack_end)++) = game->board + cur_ind - 19;
                }
            } else {
                out = 0;
                break;
            }
        }
        if (cur_row < 18) {
            if (game->board[ind + 19].stone) {
                if (game->board[ind + 19].stone == game->turn + 1 &&
                    !(game->board[ind + 19].visited)) {
                    game->board[ind + 19].visited = 1;
                    *((game->visited_end)++) = game->board + cur_ind + 19;
                    *((game->stack_end)++) = game->board + cur_ind + 19;
                }
            } else {
                out = 0;
                break;
            }
        }
        if (cur_col) {
            if (game->board[ind - 1].stone) {
                if (game->board[ind - 1].stone == game->turn + 1 &&
                    !(game->board[ind - 1].visited)) {
                    game->board[ind - 1].visited = 1;
                    *((game->visited_end)++) = game->board + cur_ind - 1;
                    *((game->stack_end)++) = game->board + cur_ind - 1;
                }
            } else {
                out = 0;
                break;
            }
        }
        if (cur_col < 18) {
            if (game->board[ind + 1].stone) {
                if (game->board[ind + 1].stone == game->turn + 1 &&
                    !(game->board[ind + 1].visited)) {
                    game->board[ind + 1].visited = 1;
                    *((game->visited_end)++) = game->board + cur_ind + 1;
                    *((game->stack_end)++) = game->board + cur_ind + 1;
                }
            } else {
                out = 0;
                break;
            }
        }
    }
    for (game->visited_iter = game->visited;
         game->visited_iter != game->visited_end;
         (*((game->visited_iter)++))->visited = 0);
    return out;
}

static inline void check_capture(struct GoGame* game,
                                 int row,
                                 int col,
                                 int ind) {
    game->adj_end = game->adj;
    if (row &&
        game->board[ind - 19].stone &&
        game->board[ind - 19].stone != (game->turn + 1)) {
        *((game->adj_end)++) = game->board + ind - 19;
    }
    if (row < 18 &&
        game->board[ind + 19].stone &&
        game->board[ind + 19].stone != (game->turn + 1)) {
        *((game->adj_end)++) = game->board + ind + 19;
    }
    if (col &&
        game->board[ind - 1].stone &&
        game->board[ind - 1].stone != (game->turn + 1)) {
        *((game->adj_end)++) = game->board + ind - 1;
    }
    if (col < 18 &&
        game->board[ind + 1].stone &&
        game->board[ind + 1].stone != (game->turn + 1)) {
        *((game->adj_end)++) = game->board + ind + 1;
    }
    if (game->adj_end != game->adj) {
        int row, col, ind;
        _Bool success = 1;
        for (game->adj_iter = game->adj;
             game->adj_iter != game->adj_end;
             game->adj_iter++) {
            game->stack_end = game->stack;
            game->visited_end = game->visited;
            if (!((*(game->adj_iter))->visited)) {
                (*(game->adj_iter))->visited = 1;
                *((game->visited_end)++) = *(game->adj_iter);
                for (*((game->stack_end)++) = *(game->adj_iter);
                     game->stack_end != game->stack;) {
                    game->stack_end--;
                    ind = *(game->stack_end) - game->board;
                    row = ind / 19;
                    col = ind % 19;
                    if (row) {
                        if (game->board[ind - 19].stone) {
                            if (game->board[ind - 19].stone !=
                                game->turn + 1 &&
                                !(game->board[ind - 19].visited)) {
                                game->board[ind - 19].visited = 1;
                                *((game->visited_end)++) =
                                game->board + ind - 19;
                                *((game->stack_end)++) =
                                game->board + ind - 19;
                            }
                        } else {
                            success = 0;
                            break;
                        }
                    }
                    if (row < 18) {
                        if (game->board[ind + 19].stone) {
                            if (game->board[ind + 19].stone !=
                                game->turn + 1 &&
                                !(game->board[ind + 19].visited)) {
                                game->board[ind + 19].visited = 1;
                                *((game->visited_end)++) =
                                game->board + ind + 19;
                                *((game->stack_end)++) =
                                game->board + ind + 19;
                            }
                        } else {
                            success = 0;
                            break;
                        }
                    }
                    if (col) {
                        if (game->board[ind - 1].stone) {
                            if (game->board[ind - 1].stone !=
                                game->turn + 1 &&
                                !(game->board[ind - 1].visited)) {
                                game->board[ind - 1].visited = 1;
                                *((game->visited_end)++) =
                                game->board + ind - 1;
                                *((game->stack_end)++) =
                                game->board + ind - 1;
                            }
                        } else {
                            success = 0;
                            break;
                        }
                    }
                    if (col < 18) {
                        if (game->board[ind + 1].stone) {
                            if (game->board[ind + 1].stone !=
                                game->turn + 1 &&
                                !(game->board[ind + 1].visited)) {
                                game->board[ind + 1].visited = 1;
                                *((game->visited_end)++) =
                                game->board + ind + 1;
                                *((game->stack_end)++) =
                                game->board + ind + 1;
                            }
                        } else {
                            success = 0;
                            break;
                        }
                    }
                }
                for (game->visited_iter = game->visited;
                     game->visited_iter != game->visited_end;
                     game->visited_iter++) {
                    (*(game->visited_iter))->visited = 0;
                    if (success) {
                        (*(game->visited_iter))->stone = 0;
                        (*(game->visited_iter))->capture = game->turn + 1;
                    }
                }
            }
        }
    }
}

 int play(struct GoGame* game, int row, int col) {
    int ind = row * 19 + col;
    if (game->board[ind].stone) return 0;
    game->pass = 0;
    if (check_suicide(game, row, col, ind)) {
        return pass(game);
    }
    game->board[ind].stone = game->turn + 1;
    check_capture(game, row, col, ind);
    game->turn = !(game->turn);
    return 0;
}

static inline int check_winner(struct GoGame* game) {
    int cnt1 = 0;
    int cnt2 = 0;
    game->board_iter = game->board;
    char flags = 0;
    int row, col, ind;
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++, game->board_iter++) {
            switch (game->board_iter->stone) {
            case 1:
                cnt1++;
                break;
            case 2:
                cnt2++;
                break;
            default:
                game->stack_end = game->stack;
                game->visited_end = game->visited;
                game->board_iter->visited = 1;
                *((game->visited_end)++) = game->board_iter;
                flags = 0;
                for (*((game->stack_end)++) = game->board_iter;
                    game->stack_end != game->stack;) {
                    (game->stack_end)--;
                    ind = *(game->stack_end) - game->board;
                    row = ind / 19;
                    col = ind % 19;
                    if (row) {
                        if (!(game->board[ind - 19].visited)) {
                            if (game->board[ind - 19].stone) {
                                flags |= 1 << (game->board[ind - 19].stone);
                            } else {
                                game->board[ind - 19].visited = 1;
                                *((game->stack_end)++) = game->board + ind - 19;
                                *((game->visited_end)++) = game->board + ind - 19;
                            }
                        }
                    }
                    if (row < 18) {
                        if (!(game->board[ind + 19].visited)) {
                            if (game->board[ind + 19].stone) {
                                flags |= 1 << (game->board[ind + 19].stone);
                            } else  {
                                game->board[ind + 19].visited = 1;
                                *((game->stack_end)++) = game->board + ind + 19;
                                *((game->visited_end)++) = game->board + ind + 19;
                            }
                        }
                    }
                    if (col) {
                        if (!(game->board[ind - 1].visited)) {
                            if (game->board[ind - 1].stone) {
                                flags |= 1 << (game->board[ind - 1].stone);
                            } else  {
                                game->board[ind - 1].visited = 1;
                                *((game->stack_end)++) = game->board + ind - 1;
                                *((game->visited_end)++) = game->board + ind - 1;
                            }
                        }
                    }
                    if (col < 18) {
                        if (!(game->board[ind + 1].visited)) {
                            if (game->board[ind + 1].stone) {
                                flags |= 1 << (game->board[ind + 1].stone);
                            } else  {
                                game->board[ind + 1].visited = 1;
                                *((game->stack_end)++) = game->board + ind + 1;
                                *((game->visited_end)++) = game->board + ind + 1;
                            }
                        }
                    }
                }
                switch (flags) {
                case 0x2:
                    cnt1++;
                    game->board_iter->teritory = 1;
                    break;
                case 0x4:
                    cnt2++;
                    game->board_iter->teritory = 1;
                    break;
                }
                for (game->visited_iter = game->visited;
                    game->visited_iter != game->visited_end;
                    (*((game->visited_iter)++))->visited = 0);
            }
        }
    }
    return cnt1 > cnt2 ? 1 : (cnt1 == cnt2 ? 3 : 2);
}

int pass(struct GoGame* game) {
    if (game->pass) {
        return check_winner(game);
    } else {
        game->pass = 1;
        game->turn = !game->turn;
        return 0;
    }
}

void print_board(struct GoGame* game) {
    game->board_iter = game->board;
    game->board_end = game->board + 361;
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++, game->board_iter++) {
            switch (game->board_iter->stone) {
            case 0:
                switch (game->board_iter->capture) {
                case 0:
                    switch (game->board_iter->teritory) {
                    case 0:
                        printf("%c ", '_');
                        break;
                    case 1:
                        printf("%c ", 'B');
                        break;
                    case 2:
                        printf("%c ", 'W');
                    }
                    break;
                case 1:
                    printf("%c ", '1');
                    break;
                case 2:
                    printf("%c ", '2');
                    break;
                }
                break;
            case 1:
                printf("%c ", 'O');
                break;
            case 2:
                printf("%c ", 'X');
                break;
            }
        }
        putchar(10);
    }
}
