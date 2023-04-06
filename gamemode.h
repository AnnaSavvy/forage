#pragma once

enum class GameModeName : int
{
    CANCEL = 0,
    QUIT_GAME,
    MAIN_MENU,
    NEW_GAME,
    LOAD_GAME,
    HIGHSCORES,
    CREDITS,
    GAME_ONGOING
};

class GameMode
{
    GameModeName name = GameModeName::CANCEL;

    virtual GameModeName run() = 0;
};
