#include "../../go/go.h"


int main(void) {
    struct GoGame game;
    init(&game);
    play(&game, 18, 18);
    play(&game, 17, 18);
    play(&game, 0, 0);
    play(&game, 18, 17);
    // print_board(&game);
    pass(&game);
    pass(&game);
    print_board(&game);
}
