#ifndef _GO_H_
#define _GO_H_

struct GoGame {
    struct {
        unsigned stone : 8;
        unsigned capture : 8;
        unsigned visited : 8;
        unsigned teritory : 8;
    } board[361],
      *board_iter,
      *board_end,
      *adj[4],
      *stack[361],
      *visited[361],
      **adj_iter,
      **adj_end,
      **stack_iter,
      **stack_end,
      **visited_iter,
      **visited_end;
    _Bool turn, pass;
};

void init(struct GoGame* game);
void play(struct GoGame* game, int row, int col);
_Bool pass(struct GoGame* game);
void print_board(struct GoGame* game);
#endif
