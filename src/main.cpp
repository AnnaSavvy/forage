#include "game.h"

#include <chrono>
#include <iostream>
#include <thread>

int main(int argc, char* argv[]) {
    Game game;
    game.init();
    game.run();

    return 0;
}
