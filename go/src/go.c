#include "go.h"

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
                        if (row) {
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
                    (*(game->visited_iter))->visited = 1;
                    if (success) {
                        (*(game->visited_iter))->capture = game->turn + 1;
                    }
                }
            }
        }
    }
}

void play(struct GoGame* game, int row, int col) {
    int ind = row * 19 + col;
    if (!(game->board[ind].stone)) {
        game->board[ind].stone = game->turn + 1;
        game->turn = !(game->turn);
        check_capture(game, row, col, ind);
    }
}
