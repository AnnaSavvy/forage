#include "game.h"
#include "asset_loader.h"
#include "game_battle.h"
#include "game_build_calc.h"
#include "game_mainmenu.h"
#include "game_strategic.h"
#include "map.h"
#include "renderer.h"

#include <SDL.h>

Game::Game()
    : _map( 32 )
{}

Game::~Game()
{
    cleanup();
}

bool Game::init()
{
    // Initialize any additional game state variables or components here
    RenderEngine::Get().Initialize();
    _map.updateMap();

    return true;
}

void Game::handleEvents()
{
    auto currentMode = _modeStack.top();
    const GameModeName next = currentMode->handleEvents();
    if ( next == currentMode->getName() ) {
        return;
    }

    switch ( next ) {
    case GameModeName::CANCEL:
        _modeStack.pop();
        break;
    case GameModeName::QUIT_GAME:
        _isRunning = false;
        break;
    case GameModeName::MAIN_MENU:
        _modeStack = {}; // clear
        _modeStack.push( std::make_shared<ModeMainMenu>());
        break;
    case GameModeName::NEW_GAME:
        _modeStack.push( std::make_shared<ModeStrategicView>() );
        break;
    case GameModeName::LOAD_GAME:
        break;
    case GameModeName::BATTLE:
        _modeStack.push( std::make_shared<ModeBattle>() );
        break;
    case GameModeName::BUILD_CALCULATOR:
        _modeStack.push( std::make_shared<ModeBuildCalculator>() );
        break;
    case GameModeName::OPTIONS_SCREEN:
        break;
    case GameModeName::HIGHSCORES:
        break;
    case GameModeName::CREDITS:
        break;
    case GameModeName::GAME_ONGOING:
        break;
    default:
        break;
    }
}

void Game::run()
{
    _isRunning = true;
    const int frameRate = 100;
    const float frameTime = 1000.0f / frameRate;

    Uint32 previousTime = SDL_GetTicks();

    _modeStack.push( std::make_shared<ModeMainMenu>() );

    while ( _isRunning ) {
        Uint32 currentTime = SDL_GetTicks();
        Uint32 elapsedTime = currentTime - previousTime;
        previousTime = currentTime;

        handleEvents();
        update( elapsedTime / 1000.0f );
        render();

        Uint32 frameTimeMs = SDL_GetTicks() - currentTime;
        if ( frameTimeMs < frameTime ) {
            SDL_Delay( static_cast<Uint32>( frameTime - frameTimeMs ) );
        }
    }
}

void Game::update( float deltaTime )
{
    _modeStack.top()->update( deltaTime );
}

void Game::render()
{
    SDL_Renderer * renderer = RenderEngine::Get().GetRenderer();
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );
    SDL_RenderClear( renderer );

    // Render game objects here
    _modeStack.top()->render();

    SDL_RenderPresent( renderer );
}

void Game::cleanup()
{
    // SDL_DestroyRenderer( _renderer );
    // SDL_DestroyWindow( _window );
    SDL_Quit();
}
