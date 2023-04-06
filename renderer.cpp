#include "renderer.h"

#include <iostream>

namespace
{
    RenderEngine engine;
}

bool RenderEngine::Initialize()
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

    return false;
}

SDL_Renderer * RenderEngine::GetRenderer()
{
    return _renderer;
}

RenderEngine & RenderEngine::Get()
{
    return engine;
}

bool RenderEngine::Draw( const std::string & image, const SDL_Rect & target )
{
    SDL_Texture * texture = engine._assets.loadTexture( image );
    if ( !texture ) {
        return false;
    }

    return SDL_RenderCopy( engine._renderer, texture, NULL, &target ) == 0;
}
