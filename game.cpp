#include "game.h"
#include "asset_loader.h"
#include "renderer.h"
#include "map.h"

#include <SDL.h>

bool Game::init()
{
    // Initialize any additional game state variables or components here
    RenderEngine::Get().Initialize();
    _map.updateMap();

    _mapView.setMap( &_map );

    return true;
}

void Game::handleEvents()
{
    SDL_Event event;
    while ( SDL_PollEvent( &event ) ) {
        switch ( event.type ) {
        case SDL_QUIT:
            _isRunning = false;
            break;
        case SDL_KEYDOWN:
            // Handle any key press events here
            std::cout << event.key.keysym.sym << std::endl;
            if (event.key.keysym.sym == SDLK_DOWN) {
                _scrollingDown = true;
            }
            else if ( event.key.keysym.sym == SDLK_UP ) {
                _scrollingUp = true;
            }
            else if ( event.key.keysym.sym == SDLK_LEFT ) {
                _scrollingLeft = true;
            }
            else if ( event.key.keysym.sym == SDLK_RIGHT ) {
                _scrollingRight = true;
            }
            break;
        case SDL_KEYUP:
            if ( event.key.keysym.sym == SDLK_DOWN ) {
                _scrollingDown = false;
            }
            else if ( event.key.keysym.sym == SDLK_UP ) {
                _scrollingUp = false;
            }
            else if ( event.key.keysym.sym == SDLK_LEFT ) {
                _scrollingLeft = false;
            }
            else if ( event.key.keysym.sym == SDLK_RIGHT ) {
                _scrollingRight = false;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            // Handle any mouse button click events here
            std::cout << event.button.x << "," << event.button.y << std::endl;
            break;
        default:
            break;
        }
    }
}

void Game::run()
{
    _isRunning = true;
    const int frameRate = 100;
    const float frameTime = 1000.0f / frameRate;

    Uint32 previousTime = SDL_GetTicks();

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
    // Camera update
    int xMove = _scrollingRight ? -2 : _scrollingLeft ? 2 : 0;
    int yMove = _scrollingDown ? -2 : _scrollingUp ? 2 : 0;
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
}

void Game::render()
{
    SDL_Renderer * renderer = RenderEngine::Get().GetRenderer();
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );
    SDL_RenderClear( renderer );

    // Render game objects here
    _mapView.render();

    SDL_RenderPresent( renderer );
}

void Game::cleanup()
{
    //SDL_DestroyRenderer( _renderer );
    //SDL_DestroyWindow( _window );
    SDL_Quit();
}
