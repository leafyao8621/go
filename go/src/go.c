#include <stdio.h>
#include <string.h>
#include "go.h"

void init(struct GoGame* game) {
    memset(game, 0, sizeof(struct GoGame));
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
                for (*((game->stack_end)++) = *(game->adj_iter);
                     game->stack_end != game->stack;) {
                    game->stack_end--;
                    if (!((*(game->stack_end))->visited)) {
                        (*(game->stack_end))->visited = 1;
                        *((game->visited_end)++) = *(game->stack_end);
                        ind = *(game->stack_end) - game->board;
                        row = ind / 19;
                        col = ind % 19;
                        if (row) {
                            if (game->board[ind - 19].stone) {
                                if (game->board[ind - 19].stone !=
                                    game->turn + 1) {
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
                                    game->turn + 1) {
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
                                    game->turn + 1) {
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
                                    game->turn + 1) {
                                    *((game->stack_end)++) =
                                    game->board + ind + 1;
                                }
                            } else {
                                success = 0;
                                break;
                            }
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

void play(struct GoGame* game, int row, int col) {
    int ind = row * 19 + col;
    if (!(game->board[ind].stone) &&
        !(game->board[ind].capture)) {
        game->board[ind].stone = game->turn + 1;
        check_capture(game, row, col, ind);
        game->turn = !(game->turn);
    }
}

static inline int check_winner(struct GoGame* game) {
    int cnt1 = 0;
    int cnt2 = 0;
    game->board_iter = game->board;
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++, game->board_iter++) {
            printf("%d %d\n", i, j);
            if (game->board_iter->stone == 1 ||
                game->board_iter->capture == 1) {
                cnt1++;
            } else {
                if (!(game->board_iter->stone) &&
                    !(game->board_iter->capture)) {
                    game->stack_end = game->stack;
                    game->visited_end = game->visited;
                    int teritory = 0;
                    int row, col, ind;
                    for (*((game->stack_end)++) = game->board_iter;
                         game->stack_end != game->stack;) {
                        game->stack_end--;
                        (*(game->stack_end))->visited = 1;
                        *((game->visited_end)++) = *(game->stack_end);
                        ind = *(game->stack_end) - game->board;
                        row = ind / 19;
                        col = ind % 19;
                        if (row) {
                            if (!(game->board[ind - 19].stone) &&
                                !(game->board[ind - 19].capture) &&
                                !(game->board[ind - 19].visited)) {
                                *((game->stack_end)++) = game->board + ind - 19;
                            } else {
                                if (game->board[ind - 19].stone) {
                                    if (!teritory) {
                                        teritory = game->board[ind - 19].stone;
                                    } else if (teritory !=
                                            game->board[ind - 19].stone){
                                        teritory = 0;
                                        break;
                                    }
                                }
                            }
                        }
                        if (row < 18) {
                            if (!(game->board[ind + 19].stone) &&
                                !(game->board[ind + 19].capture) &&
                                !(game->board[ind + 19].visited)) {
                                *((game->stack_end)++) = game->board + ind + 19;
                            } else {
                                if (game->board[ind + 19].stone) {
                                    if (!teritory) {
                                        teritory = game->board[ind + 19].stone;
                                    } else if (teritory !=
                                            game->board[ind + 19].stone){
                                        teritory = 0;
                                        break;
                                    }
                                }
                            }
                        }
                        if (col) {
                            if (!(game->board[ind - 1].stone) &&
                                !(game->board[ind - 1].capture) &&
                                !(game->board[ind - 1].visited)) {
                                *((game->stack_end)++) = game->board + ind - 1;
                            } else {
                                if (game->board[ind - 1].stone) {
                                    if (!teritory) {
                                        teritory = game->board[ind - 1].stone;
                                    } else if (teritory !=
                                            game->board[ind - 1].stone) {
                                        teritory = 0;
                                        break;
                                    }
                                }
                            }
                        }
                        if (col < 18) {
                            if (!(game->board[ind + 1].stone) &&
                                !(game->board[ind + 1].capture) &&
                                !(game->board[ind + 1].visited)) {
                                *((game->stack_end)++) = game->board + ind + 1;
                            } else {
                                if (game->board[ind + 1].stone) {
                                    if (!teritory) {
                                        teritory = game->board[ind + 1].stone;
                                    } else if (teritory !=
                                            game->board[ind + 1].stone) {
                                        teritory = 0;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    for (game->visited_iter = game->visited;
                         game->visited_iter != game->visited_end;
                         (*((game->visited_iter)++))->visited = 0);
                    if (teritory) {
                        game->board_iter->teritory = teritory;
                        switch (teritory) {
                        case 1:
                            cnt1++;
                            break;
                        case 2:
                            cnt2++;
                            break;
                        }
                    }
                    
                } else {
                    cnt2++;
                }
            }
        }
    }
    printf("%d %d\n", cnt1, cnt2);
    return cnt1 > cnt2;
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
