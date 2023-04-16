#include "renderer.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

#include "ui_style.h"

namespace
{
    RenderEngine engine;
}

SDL_Rect convertRect( const Rect & rect )
{
    return { rect.pos.x, rect.pos.y, rect.size.x, rect.size.y };
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

    if ( !StandardStyles::loadAssets() ) {
        std::cout << "Error initializing standard fonts and colors" << std::endl;
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

bool RenderEngine::DrawRect( const Rect & target, ColorPtr color )
{
    SDL_Color * sdlColor = static_cast<SDL_Color *>( color );
    if ( !sdlColor ) {
        return false;
    }

    if ( SDL_SetRenderDrawColor( engine._renderer, sdlColor->r, sdlColor->g, sdlColor->b, sdlColor->a ) ) {
        return false;
    }

    SDL_Rect rect = convertRect( target );

    return SDL_RenderFillRect( engine._renderer, &rect ) == 0;
}

bool RenderEngine::DrawText( const std::string & text, const Rect & target )
{
    SDL_Color * textColor = static_cast<SDL_Color *>( StandardStyles::getColor( StandardColor::HIGHLIGHT_RED ) );
    if ( !textColor ) {
        return false;
    }

    TTF_Font * font = static_cast<TTF_Font *>( StandardStyles::getFont( StandardFont::REGULAR ) );
    if ( !font ) {
        return false;
    }

    SDL_Surface * textSurface = TTF_RenderText_Solid( font, text.c_str(), *textColor );
    SDL_Texture * textTexture = SDL_CreateTextureFromSurface( engine._renderer, textSurface );

    SDL_Rect textRect = { target.pos.x, target.pos.y, textSurface->w, textSurface->h };
    const bool success = SDL_RenderCopy( engine._renderer, textTexture, NULL, &textRect ) == 0;
    SDL_FreeSurface( textSurface );
    SDL_DestroyTexture( textTexture );

    return success;
}
