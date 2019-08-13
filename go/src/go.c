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
        game->stack_end = game->stack;
        for (game->adj_iter = game->adj;
             game->adj_iter != game->adj_end;
             game->adj_iter++) {
            if (!((*(game->adj_iter))->visited)) {
                for (*((game->stack_end)++) = *(game->adj_iter);
                     game->stack_end != game->stack;) {
                    game->stack_end--;
                    int row, col, ind;
                    ind = *(game->stack_end) - game->board;
                    row = ind / 19;
                    col = ind % 19;
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
