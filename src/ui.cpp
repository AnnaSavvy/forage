#include "ui.h"

#include "renderer.h"
#include <SDL.h>

UIComponent::UIComponent( const Rect & dimensions )
    : rect( dimensions )
{}

Button::Button( int x, int y, int width, int height, const std::string & label )
    : UIComponent( { x, y, width, height } )
{
    rect._pos._x = x;
    rect._pos._y = y;
    rect._size._x = width;
    rect._size._y = height;
    _label = label;
}

Button::Button( const Rect & dimensions, const std::string & label, const Style & style )
    : UIComponent( dimensions )
    , _style( style )
{
    _label = label;
}

void Button::handleEvent() {}

void Button::update( float deltaTime ) {}

void Button::render()
{
    if ( _style.borderWidth && ( _style.borderColor != _style.backgroundColor ) ) {
        RenderEngine::DrawRect( rect, _style.borderColor );

        Rect innerArea = rect;
        innerArea._pos._x += _style.borderWidth;
        innerArea._pos._y += _style.borderWidth;
        innerArea._size._x -= _style.borderWidth * 2;
        innerArea._size._y -= _style.borderWidth * 2;
        RenderEngine::DrawRect( innerArea, _style.backgroundColor );
    }
    else {
        RenderEngine::DrawRect( rect, _style.backgroundColor );
    }

    SDL_Surface * surface = RenderEngine::GetTextSurface( _label, _style.font, _style.textColor );
    if ( surface ) {
        Rect textRect = rect;
        textRect._pos._x += ( rect._size._x - surface->w ) / 2;
        textRect._pos._y += ( rect._size._y - surface->h ) / 2;
        textRect._size._x = surface->w;
        textRect._size._y = surface->h;

        RenderEngine::DrawDestroySurface( surface, textRect );
    }
}

void Button::setStyle( const Style & style )
{
    _style = style;
}

void Button::setLabel( const std::string & label )
{
    _label = label;
}

Label::Label( const Point & position, const std::string & text )
    : UIComponent( { position, { 0, 0 } } )
    , _text( text )
{}

Label::Label( const Point & position, const std::string & text, StandardFont font, StandardColor color )
    : UIComponent( { position, { 0, 0 } } )
    , _text( text )
    , _font( font )
    , _color( color )
{}

void Label::setText( const std::string & text )
{
    _text = text;
}

void Label::setColor( StandardColor color )
{
    _color = color;
}

void Label::render()
{
    RenderEngine::DrawText( _text, rect._pos, _font, _color );
}
