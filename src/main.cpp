#include "game.h"

int main(int argc, char* argv[]) {
    Game game = { { 768, 768 } };
    game.init();
    game.run();

    return 0;
}
