#include "game.h"
#include "asset_loader.h"

#define TILESIZE 64
#define MAPSIZE 16

bool Game::init()
{
    // Initialize SDL2 and create window/renderer
    if ( SDL_Init( SDL_INIT_VIDEO ) != 0 ) {
        std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
        return false;
    }

    _window = SDL_CreateWindow( "Card Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 1024, SDL_WINDOW_SHOWN );
    if ( !_window ) {
        std::cerr << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    _renderer = SDL_CreateRenderer( _window, -1, SDL_RENDERER_ACCELERATED );
    if ( !_renderer ) {
        std::cerr << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow( _window );
        SDL_Quit();
        return false;
    }

    // Initialize any additional game state variables or components here
    _assets.initRenderer( _renderer );
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
    SDL_SetRenderDrawColor( _renderer, 0, 0, 0, 0 );
    SDL_RenderClear( _renderer );

    // Render game objects here
    SDL_Rect target;

    target.x = 0;
    target.y = 0;
    target.h = TILESIZE;
    target.w = TILESIZE;

    SDL_Texture * water = _assets.loadTexture( "assets/water.png" );
    SDL_Texture * plains = _assets.loadTexture( "assets/plains.png" );
    SDL_Texture * forest = _assets.loadTexture( "assets/forest.png" );
    SDL_Texture * mountain = _assets.loadTexture( "assets/mountain.png" );
    SDL_Texture * swamp = _assets.loadTexture( "assets/swamp.png" );

    for ( int y = 0; y < MAPSIZE; y++ ) {
        for ( int x = 0; x < MAPSIZE; x++ ) {
            const int offset = ( x % 2 ) ? TILESIZE / 2 : 0;

            target.x = x * TILESIZE;
            target.y = y * TILESIZE + offset;

            auto & tile = _map.getTile( y * MAPSIZE + x );
            SDL_Texture * texture = water;
            switch ( tile.type ) {
            case FOREST:
                texture = mountain;
                break;
            case TREES:
                texture = forest;
                break;
            case GRASS:
                texture = plains;
                break;
            case SAND:
                texture = swamp;
                break;
            case LAKE:
                texture = water;
                break;
            default:
                texture = water;
                break;
            }
            SDL_RenderCopy( _renderer, texture, NULL, &target );
        }
    }

    SDL_RenderPresent( _renderer );
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
    SDL_DestroyRenderer( _renderer );
    SDL_DestroyWindow( _window );
    SDL_Quit();
}
