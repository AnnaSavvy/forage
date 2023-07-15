#pragma once

enum class GameModeName : int
{
    CANCEL = 0,
    QUIT_GAME,
    MAIN_MENU,
    NEW_GAME,
    LOAD_GAME,
    BATTLE,
    BUILD_CALCULATOR,
    OPTIONS_SCREEN,
    HIGHSCORES,
    CREDITS,
    GAME_ONGOING
};

class GameMode
{
protected:
    GameModeName name = GameModeName::CANCEL;

public:
    GameModeName getName() const;

    virtual GameModeName handleEvents() = 0;
    virtual void update( float deltaTime ) = 0;
    virtual void render() = 0;
};
