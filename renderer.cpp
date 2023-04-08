#include "renderer.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

namespace
{
    RenderEngine engine;
    TTF_Font * font;
}

SDL_Rect convertRect( const Rect & rect )
{
    SDL_Rect sdlRect;
    sdlRect.x = rect.x;
    sdlRect.y = rect.y;
    sdlRect.w = rect.width;
    sdlRect.h = rect.height;
    return sdlRect;
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

    if ( TTF_Init() < 0 ) {
        std::cout << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
        return false;
    }

    font = TTF_OpenFont( "arial.ttf", 24 );
    if ( !font ) {
        std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
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

bool RenderEngine::Draw( const std::string & image, const Rect & target )
{
    SDL_Texture * texture = engine._assets.loadTexture( image );
    if ( !texture ) {
        return false;
    }

    SDL_Rect rect = convertRect( target );
    return SDL_RenderCopy( engine._renderer, texture, NULL, &rect ) == 0;
}

bool RenderEngine::DrawRect( const Rect & target, const Color & color )
{
    if ( SDL_SetRenderDrawColor( engine._renderer, color.red, color.green, color.blue, color.alpha ) ) {
        return false;
    }

    SDL_Rect rect = convertRect( target );

    return SDL_RenderFillRect( engine._renderer, &rect ) == 0;
}

bool RenderEngine::DrawText( const std::string & text, const Rect & target )
{
    SDL_Color textColor = { 255,255,255 };

    SDL_Surface * textSurface = TTF_RenderText_Solid( font, text.c_str(), textColor );
    SDL_Texture * textTexture = SDL_CreateTextureFromSurface( engine._renderer, textSurface );

    SDL_Rect textRect = { target.x, target.y, textSurface->w, textSurface->h };
    return SDL_RenderCopy( engine._renderer, textTexture, NULL, &textRect ) == 0;
}
