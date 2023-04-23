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

void Button::setLabel( const std::string & label )
{
    _label = label;
}

void Button::addEventListener( std::shared_ptr<EventListener> listener )
{
    _listeners.push_back( listener );
}

void Button::removeEventListener( std::shared_ptr<EventListener> listener )
{
    _listeners.erase( std::remove( _listeners.begin(), _listeners.end(), listener ), _listeners.end() );
}

void Button::handleClickEvent()
{
    const ButtonClickEvent event( 0 );
    for ( const auto & listener : _listeners ) {
        listener->onEvent( event );
    }
}
