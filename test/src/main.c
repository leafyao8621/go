#include "../../go/go.h"


int main(void) {
    struct GoGame game;
    init(&game);
    play(&game, 0, 0);
    play(&game, 0, 9);
    play(&game, 0, 1);
    play(&game, 0, 2);
    play(&game, 1, 9);
    play(&game, 1, 1);
    play(&game, 2, 9);
    play(&game, 3, 9);
    play(&game, 2, 10);
    play(&game, 1, 0);
    play(&game, 1, 10);
    play(&game, 0, 10);
    play(&game, 9, 9);
    play(&game, 1, 11);
    play(&game, 10, 10);
    play(&game, 2, 11);
    play(&game, 8, 8);
    play(&game, 3, 10);
    play(&game, 7, 7);
    play(&game, 1, 8);
    play(&game, 6, 6);
    play(&game, 2, 8);
    print_board(&game);
}
