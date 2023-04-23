#include "ui.h"

#include "renderer.h"

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
    Point target = rect._pos;
    target.modAdd( _style.padding, _style.padding );

    RenderEngine::DrawRect( rect, _style.backgroundColor );
    RenderEngine::DrawText( _label, target, _style.font, _style.textColor );
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
