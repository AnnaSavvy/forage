#include "ui.h"

#include "renderer.h"

Button::Button( int x, int y, int width, int height, const std::string & label ) {
    _x = x;
    _x = y;
    _width = width;
    _height = height;
    _label = label;
}

void Button::handleEvent() {}

void Button::update( float deltaTime ) {}

void Button::render() {
    RenderEngine::Draw( "", Rect() );
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
    const ButtonClickEvent event( _id );
    for ( const auto & listener : _listeners ) {
        listener->onEvent( event );
    }
}
