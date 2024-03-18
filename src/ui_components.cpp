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
        innerArea._pos._x += _style.borderWidth;
        innerArea._pos._y += _style.borderWidth;
        innerArea._size._x -= _style.borderWidth * 2;
        innerArea._size._y -= _style.borderWidth * 2;
        RenderEngine::DrawRect( innerArea, _style.backgroundColor );
    }
    else {
        RenderEngine::DrawRect( _rect, _style.backgroundColor );
    }

    auto & binding = _binding.get();
    const double ratio = std::min( static_cast<double>( binding.value ) / binding.maximum, 1.0 );
    if ( ratio > 0.0001 ) {
        Rect barArea = _rect;
        barArea._pos._x += _style.borderWidth;
        barArea._pos._y += _style.borderWidth;
        barArea._size._y -= _style.borderWidth * 2;
        barArea._size._x -= _style.borderWidth * 2;
        barArea._size._x *= ratio;
        if ( barArea._size._x < 0 ) {
            barArea._size._x = 0;
        }
        RenderEngine::DrawRect( barArea, StandardColor::DARK_RED );
    }

    std::string str = std::format( "{} / {}", binding.value, binding.maximum );
    SDL_Surface * surface = RenderEngine::GetTextSurface( str, _style.font, _style.textColor );
    if ( surface ) {
        Rect textRect = _rect;
        textRect._pos._x += ( _rect._size._x - surface->w ) / 2;
        textRect._pos._y += ( _rect._size._y - surface->h ) / 2;
        textRect._size._x = surface->w;
        textRect._size._y = surface->h;

        RenderEngine::DrawDestroySurface( surface, textRect );
    }
}

SkillCounter::SkillCounter( Point position, int width, std::string description, ValueBinding binding )
    : UIContainer( { position._x, position._y, 0, 0 } )
    , _binding( binding )
{
    addElement( std::make_shared<CenteringLabel>( CenteringLabel( { position._x, position._y, 0, ROW_HEIGHT }, description ) ) );
    position.modAdd( 150, 0 );

    const Style buttonStyle{ StandardFont::REGULAR, StandardColor::WHITE, StandardColor::DARK_GREY, StandardColor::REALM_PRECISION, 2 };
    addElement( std::make_shared<Button>( Button( { position._x - ROW_HEIGHT - 5, position._y, ROW_HEIGHT, ROW_HEIGHT }, "-", buttonStyle ) ) );

    addElement( std::make_shared<ProgressBar>( ProgressBar( { position._x, position._y, width, ROW_HEIGHT }, binding, skillBarStyle ) ) );

    addElement( std::make_shared<Button>( Button( { position._x + width + 5, position._y, ROW_HEIGHT, ROW_HEIGHT }, "+", buttonStyle ) ) );
}

void SkillCounter::handleClickEvent( const Point & click, int modes )
{
    const ValueBinding & binding = _binding.get();
    if ( _items[1]->getRect().contains( click ) ) {
        const int change = modes & InputHandler::MOUSE_RIGHT_CLICKED ? 10 : 1;
        binding.value = std::max( binding.value - change, binding.minimum );
    }
    else if ( _items[3]->getRect().contains( click ) ) {
        const int big = binding.value == 1 ? 9 : 10;
        const int change = modes & InputHandler::MOUSE_RIGHT_CLICKED ? big : 1;
        binding.value = std::min( binding.value + change, binding.maximum );
    }
}

AttributeCounter::AttributeCounter( Point position, std::string description, ValueBinding binding )
    : UIContainer( { position._x, position._y, 0, 0 } )
    , _binding( binding )
{
    addElement( std::make_shared<CenteringLabel>( CenteringLabel( { position._x, position._y, 90, ROW_HEIGHT }, description ) ) );
    position.modAdd( 90, 0 );

    const Style buttonStyle{ StandardFont::REGULAR, StandardColor::WHITE, StandardColor::DARK_GREY, StandardColor::REALM_PRECISION, 2 };
    addElement( std::make_shared<Button>( Button( { position._x, position._y, ROW_HEIGHT, ROW_HEIGHT }, "-", buttonStyle ) ) );

    position.modAdd( 35, 0 );
    addElement( std::make_shared<CenteringLabel>( CenteringLabel( { position._x, position._y, 60, ROW_HEIGHT }, std::to_string( binding.value ) ) ) );
    _display = dynamic_cast<CenteringLabel *>( _items.back().get() );

    position.modAdd( 60, 0 );
    addElement( std::make_shared<Button>( Button( { position._x, position._y, ROW_HEIGHT, ROW_HEIGHT }, "+", buttonStyle ) ) );
}

void AttributeCounter::handleClickEvent( const Point & click, int modes )
{
    ValueBinding & binding = _binding.editValue();
    if ( _items[1]->getRect().contains( click ) ) {
        const int change = modes & InputHandler::MOUSE_RIGHT_CLICKED ? 10 : 1;
        binding.value = std::max( binding.value - change, binding.minimum );
    }
    else if ( _items[3]->getRect().contains( click ) ) {
        const int big = binding.value == 1 ? 9 : 10;
        const int change = modes & InputHandler::MOUSE_RIGHT_CLICKED ? big : 1;
        binding.value = std::min( binding.value + change, binding.maximum );
    }
}

void AttributeCounter::render()
{
    _display->setText( std::to_string( _binding.get().value ) );
    for ( auto & component : _items ) {
        component.get()->render();
    }
}
