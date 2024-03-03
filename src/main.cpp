#include "game.h"

int main(int argc, char* argv[]) {
    Game game = { { 1024, 1024 } };
    game.init();
    game.run();

    return 0;
}
