#include "game.h"
#include "asset_loader.h"
#include "renderer.h"

#include <SDL.h>

#define TILESIZE 64
#define MAPSIZE 16

bool Game::init()
{
    // Initialize any additional game state variables or components here
    RenderEngine::Get().Initialize();
    _map.updateMap();

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

void Game::run() {
    realtimeLoop();
}

void Game::update( float deltaTime )
{
    // Update the game state here
}

void Game::render()
{
    SDL_Renderer * renderer = RenderEngine::Get().GetRenderer();
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );
    SDL_RenderClear( renderer );

    // Render game objects here
    SDL_Rect target;

    target.x = 0;
    target.y = 0;
    target.h = TILESIZE;
    target.w = TILESIZE;

    for ( int y = 0; y < MAPSIZE; y++ ) {
        for ( int x = 0; x < MAPSIZE; x++ ) {
            const int offset = ( x % 2 ) ? TILESIZE / 2 : 0;

            target.x = x * TILESIZE;
            target.y = y * TILESIZE + offset;

            auto & tile = _map.getTile( y * MAPSIZE + x );
            std::string texture = "assets/water.png";
            switch ( tile.type ) {
            case FOREST:
                texture = "assets/mountain.png";
                break;
            case TREES:
                texture = "assets/forest.png";
                break;
            case GRASS:
                texture = "assets/plains.png";
                break;
            case SAND:
                texture = "assets/swamp.png";
                break;
            case LAKE:
                texture = "assets/water.png";
                break;
            default:
                texture = "assets/water.png";
                break;
            }
            RenderEngine::Draw( texture, target );
        }
    }

    SDL_RenderPresent( renderer );
}

void Game::realtimeLoop()
{
    _isRunning = true;
    const int frameRate = 60;
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

void Game::cleanup()
{
    //SDL_DestroyRenderer( _renderer );
    //SDL_DestroyWindow( _window );
    SDL_Quit();
}
