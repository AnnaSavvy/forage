#include "game.h"

int main(int argc, char* argv[]) {
    Game game = { { 1280, 720 } };
    game.init();
    game.run();

    return 0;
}
