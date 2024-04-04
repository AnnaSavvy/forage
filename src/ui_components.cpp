#include "ui_components.h"
#include "input.h"
#include "renderer.h"

#include <SDL.h>
#include <format>

namespace
{
    const Style skillBarStyle{ StandardFont::SMALL, StandardColor::WHITE, StandardColor::DARK_GREY, StandardColor::REALM_PRECISION, 2 };

    constexpr int ROW_HEIGHT = 31;
}

ProgressBar::ProgressBar( const Rect & dimensions, ValueBinding binding )
    : UIComponent( dimensions )
    , _binding( binding )
{}

ProgressBar::ProgressBar( const Rect & dimensions, ValueBinding binding, const Style & style )
    : UIComponent( dimensions )
    , _binding( binding )
    , _style( style )
{}

void ProgressBar::setStyle( const Style & style )
{
    _style = style;
}

void ProgressBar::render()
{
    if ( _hidden ) {
        return;
    }

    if ( _style.borderWidth && ( _style.borderColor != _style.backgroundColor ) ) {
        RenderEngine::DrawRect( _rect, _style.borderColor );

        Rect innerArea = _rect;
        innerArea.pos.x += _style.borderWidth;
        innerArea.pos.y += _style.borderWidth;
        innerArea.size.x -= _style.borderWidth * 2;
        innerArea.size.y -= _style.borderWidth * 2;
        RenderEngine::DrawRect( innerArea, _style.backgroundColor );
    }
    else {
        RenderEngine::DrawRect( _rect, _style.backgroundColor );
    }

    auto & binding = _binding.get();
    const double ratio = std::min( static_cast<double>( binding.value ) / binding.maximum, 1.0 );
    if ( ratio > 0.0001 ) {
        Rect barArea = _rect;
        barArea.pos.x += _style.borderWidth;
        barArea.pos.y += _style.borderWidth;
        barArea.size.y -= _style.borderWidth * 2;
        barArea.size.x -= _style.borderWidth * 2;
        barArea.size.x *= ratio;
        if ( barArea.size.x < 0 ) {
            barArea.size.x = 0;
        }
        RenderEngine::DrawRect( barArea, StandardColor::DARK_RED );
    }

    std::string str = std::format( "{} / {}", binding.value, binding.maximum );
    SDL_Surface * surface = RenderEngine::GetTextSurface( str, _style.font, _style.textColor );
    if ( surface ) {
        Rect textRect = _rect;
        textRect.pos.x += ( _rect.size.x - surface->w ) / 2;
        textRect.pos.y += ( _rect.size.y - surface->h ) / 2;
        textRect.size.x = surface->w;
        textRect.size.y = surface->h;

        RenderEngine::DrawDestroySurface( surface, textRect );
    }
}
