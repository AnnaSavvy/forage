#include "ui_style.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <cassert>
#include <iostream>
#include <vector>

namespace StandardStyles
{
    static std::vector<SDL_Color> colors;
    static std::vector<FontPtr> fonts;

    bool ttfInit = false;

    ColorPtr getColor( StandardColor color )
    {
        int index = static_cast<int>( color );
        assert( index < colors.size() );
        return &colors[index];
    }

    FontPtr getFont( StandardFont font )
    {
        int index = static_cast<int>( font );
        assert( index < fonts.size() );
        return fonts[index];
    }

    bool loadAssets()
    {
        if ( !ttfInit && TTF_Init() < 0 ) {
            std::cout << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
            return false;
        }
        ttfInit = true;

        for ( FontPtr font : fonts ) {
            TTF_Font * sdlFont = static_cast<TTF_Font *>( font );
            if ( sdlFont ) {
                TTF_CloseFont( sdlFont );
            }
        }

        fonts.clear();
        fonts.resize( static_cast<int>( StandardFont::END ) );
        colors.clear();
        colors.resize( static_cast<int>( StandardColor::END ) );

        TTF_Font * font = TTF_OpenFont( "assets/font/Roboto-Bold.ttf", 24 );
        if ( !font ) {
            std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
            return false;
        }
        fonts[static_cast<int>( StandardFont::REGULAR )] = font;

        font = TTF_OpenFont( "assets/font/Deutsch Gothic.ttf", 32 );
        if ( !font ) {
            std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
            return false;
        }
        fonts[static_cast<int>( StandardFont::REGULAR_BOLD )] = font;

        font = TTF_OpenFont( "assets/font/Deutsch Gothic.ttf", 72 );
        if ( !font ) {
            std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
            return false;
        }
        fonts[static_cast<int>( StandardFont::MENU_HUGE_TITLE )] = font;

        colors[static_cast<int>( StandardColor::WHITE )] = { 255, 255, 255 };
        colors[static_cast<int>( StandardColor::BLACK )] = { 0, 0, 0 };
        colors[static_cast<int>( StandardColor::DARK_GREY )] = { 50, 47, 50 };
        colors[static_cast<int>( StandardColor::DARK_RED )] = { 100, 0, 10 };
        colors[static_cast<int>( StandardColor::DARK_BLUE )] = { 0, 20, 100 };
        colors[static_cast<int>( StandardColor::HIGHLIGHT_RED )] = { 200, 40, 50 };

        return true;
    }
}
