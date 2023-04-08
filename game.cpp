#include "game.h"
#include "asset_loader.h"
#include "gamemode.h"
#include "map.h"
#include "renderer.h"

#include <SDL.h>

bool Game::init()
{
    // Initialize any additional game state variables or components here
    RenderEngine::Get().Initialize();
    _map.updateMap();

    _mapView.setMap( _map );

    return true;
}

void Game::handleEvents()
{
    if ( _currentMode->handleEvents() == GameModeName::QUIT_GAME ) {
        _isRunning = false;
    }
}

void Game::run()
{
    _isRunning = true;
    const int frameRate = 100;
    const float frameTime = 1000.0f / frameRate;

    Uint32 previousTime = SDL_GetTicks();

    ModeMainMenu mode;
    _currentMode = &mode;

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
    InputHandler & input = InputHandler::Get();

    // Camera update
    int xMove = input.isSet( InputHandler::RIGHT ) ? -2 : input.isSet( InputHandler::LEFT ) ? 2 : 0;
    int yMove = input.isSet( InputHandler::DOWN ) ? -2 : input.isSet( InputHandler::UP ) ? 2 : 0;
    int cameraSpeed = 2;
    if ( xMove != 0 || yMove != 0 ) {
        _scrollTimer += deltaTime;
        if ( _scrollTimer > 1.5 ) {
            cameraSpeed = ( _scrollTimer > 3 ) ? 4 : 3;
        }
    }
    else {
        _scrollTimer = 0.0f;
    }
    _mapView.moveCamera( xMove * cameraSpeed, yMove * cameraSpeed );

    _currentMode->update( deltaTime );
}

void Game::render()
{
    SDL_Renderer * renderer = RenderEngine::Get().GetRenderer();
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );
    SDL_RenderClear( renderer );

    // Render game objects here
    // _mapView.render();
    _currentMode->render();

    SDL_RenderPresent( renderer );
}

void Game::cleanup()
{
    //SDL_DestroyRenderer( _renderer );
    //SDL_DestroyWindow( _window );
    SDL_Quit();
}
