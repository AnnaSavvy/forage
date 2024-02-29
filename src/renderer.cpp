#include "renderer.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

#include "SDL2_gfx.h"
#include "ui_style.h"

namespace
{
    RenderEngine engine;
}

SDL_Rect convertRect( const Rect & rect )
{
    return { rect._pos._x, rect._pos._y, rect._size._x, rect._size._y };
}

bool RenderEngine::Initialize( Point logicalSize, double scaling )
{
    _logicalSize = logicalSize;

    // Initialize SDL2 and create window/renderer
    if ( SDL_Init( SDL_INIT_VIDEO ) != 0 ) {
        std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
        return false;
    }

    _window = SDL_CreateWindow( "Card Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _logicalSize._x * scaling, _logicalSize._y * scaling, SDL_WINDOW_SHOWN );
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

    SDL_RenderSetScale( _renderer, scaling, scaling );

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

Point RenderEngine::GetScreenSize()
{
    return engine._logicalSize;
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

bool RenderEngine::DrawRect( const Rect & target, StandardColor color )
{
    SDL_Color * sdlColor = static_cast<SDL_Color *>( StandardStyles::getColor( color ) );
    if ( !sdlColor ) {
        return false;
    }

    if ( SDL_SetRenderDrawColor( engine._renderer, sdlColor->r, sdlColor->g, sdlColor->b, sdlColor->a ) ) {
        return false;
    }

    SDL_Rect rect = convertRect( target );

    return SDL_RenderFillRect( engine._renderer, &rect ) == 0;
}

bool RenderEngine::DrawStyledRect( const Rect & target, const Style & style )
{
    SDL_Color * sdlColor = static_cast<SDL_Color *>( StandardStyles::getColor( style.backgroundColor ) );
    if ( !sdlColor ) {
        return false;
    }

    if ( SDL_SetRenderDrawColor( engine._renderer, sdlColor->r, sdlColor->g, sdlColor->b, sdlColor->a ) ) {
        return false;
    }

    SDL_Rect rect = convertRect( target );

    return SDL_RenderFillRect( engine._renderer, &rect ) == 0;
}

bool RenderEngine::DrawText( const std::string & text, const Point & target )
{
    return DrawText( text, target, StandardFont::REGULAR, StandardColor::WHITE );
}

bool RenderEngine::DrawText( const std::string & text, const Point & target, StandardFont font )
{
    return DrawText( text, target, font, StandardColor::WHITE );
}

bool RenderEngine::DrawText( const std::string & text, const Point & target, StandardFont font, StandardColor color )
{
    SDL_Surface * textSurface = GetTextSurface( text, font, color );
    if ( !textSurface ) {
        return false;
    }

    SDL_Texture * textTexture = SDL_CreateTextureFromSurface( engine._renderer, textSurface );

    SDL_Rect textRect = { target._x, target._y, textSurface->w, textSurface->h };
    const bool success = SDL_RenderCopy( engine._renderer, textTexture, NULL, &textRect ) == 0;
    SDL_FreeSurface( textSurface );
    SDL_DestroyTexture( textTexture );

    return success;
}

SDL_Surface * RenderEngine::GetTextSurface( const std::string & text, StandardFont font, StandardColor color )
{
    SDL_Color * textColor = static_cast<SDL_Color *>( StandardStyles::getColor( color ) );
    if ( !textColor ) {
        return nullptr;
    }

    TTF_Font * fontPtr = static_cast<TTF_Font *>( StandardStyles::getFont( font ) );
    if ( !fontPtr ) {
        return nullptr;
    }

    return TTF_RenderText_Solid( fontPtr, text.c_str(), *textColor );
}

bool RenderEngine::DrawDestroySurface( SDL_Surface * surface, const Rect & target )
{
    if ( !surface ) {
        return false;
    }

    SDL_Texture * textTexture = SDL_CreateTextureFromSurface( engine._renderer, surface );

    SDL_Rect textRect = { target._pos._x, target._pos._y, target._size._x, target._size._y };
    const bool success = SDL_RenderCopy( engine._renderer, textTexture, NULL, &textRect ) == 0;
    SDL_FreeSurface( surface );
    SDL_DestroyTexture( textTexture );

    return success;
}

bool RenderEngine::DrawPieSlice( const Rect & target, double startAngle, double endAngle, StandardColor color )
{
    SDL_Color * pieColor = static_cast<SDL_Color *>( StandardStyles::getColor( color ) );
    if ( !pieColor ) {
        return false;
    }
    return SDL::aaFilledPieRGBA( engine._renderer, target._pos._x, target._pos._y, target._size._x, target._size._y, startAngle, endAngle, false, pieColor->r,
                                 pieColor->g, pieColor->b, pieColor->a )
           == 0;
}
