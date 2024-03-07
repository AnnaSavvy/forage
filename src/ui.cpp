#include "ui.h"

#include "renderer.h"
#include <SDL.h>

UIComponent::UIComponent( const Rect & dimensions )
    : _rect( dimensions )
{}

Button::Button( int x, int y, int width, int height, const std::string & label )
    : UIComponent( { x, y, width, height } )
{
    _label = label;
}

Button::Button( const Point & position, int width, int height, const std::string & label )
    : UIComponent( { position._x, position._y, width, height } )
{
    _label = label;
}

Button::Button( const Rect & dimensions, const std::string & label, const Style & style )
    : UIComponent( dimensions )
    , _style( style )
{
    _label = label;
}

void Button::update( float deltaTime ) {}

void Button::render()
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

    SDL_Surface * surface = RenderEngine::GetTextSurface( _label, _style.font, _style.textColor );
    if ( surface ) {
        Rect textRect = _rect;
        textRect._pos._x += ( _rect._size._x - surface->w ) / 2;
        textRect._pos._y += ( _rect._size._y - surface->h ) / 2;
        textRect._size._x = surface->w;
        textRect._size._y = surface->h;

        RenderEngine::DrawDestroySurface( surface, textRect );
    }
}

void Button::setPressed( bool value )
{
    _isPressed = value;
}

void Button::setHovered( bool value )
{
    _isPressed = value;
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
    if ( _hidden ) {
        return;
    }

    RenderEngine::DrawText( _text, _rect._pos, _font, _color );
}

Window::Window( Rect rect, const std::string & title )
    : UIComponent( rect )
    , _title( title )
{}

Window::~Window() {}

void Window::update( float deltaTime )
{
    for ( auto component : _components ) {
        component->update( deltaTime );
    }
}

void Window::render()
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

    SDL_Surface * surface = RenderEngine::GetTextSurface( _title, _style.font, _style.textColor );
    if ( surface ) {
        Rect textRect = _rect;
        textRect._pos._x += ( _rect._size._x - surface->w ) / 2;
        textRect._pos._y += _style.paddingY;
        textRect._size._x = surface->w;
        textRect._size._y = surface->h;

        RenderEngine::DrawDestroySurface( surface, textRect );
    }

    for ( auto component : _components ) {
        component->render();
    }
}

void Window::setStyle( const Style & style )
{
    _style = style;
}

void Window::addComponent( std::shared_ptr<UIComponent> component )
{
    _components.push_back( component );
}

std::shared_ptr<UIComponent> Window::getElement( const Point & click )
{
    if ( _rect.contains( click ) ) {
        for ( auto component : _components ) {
            if ( component->getRect().contains( click ) ) {
                return component;
            }
        }
    }
    return nullptr;
}

ProgressBar::ProgressBar( const Rect & dimensions, int max )
    : UIComponent( dimensions )
    , _maximum( max )
{}

ProgressBar::ProgressBar( const Rect & dimensions, int max, const Style & style )
    : UIComponent( dimensions )
    , _maximum( max )
    , _style( style )
{}

void ProgressBar::setValue( int newValue )
{
    _value = newValue;
    if ( _value > _maximum ) {
        _value = _maximum;
    }
}

int ProgressBar::getValue() const
{
    return _value;
}

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

    const double ratio = std::min( static_cast<double>( _value ) / _maximum, 1.0 );
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
        RenderEngine::DrawRect( barArea, StandardColor::HIGHLIGHT_RED );
    }

    std::string str = std::to_string( _value ) + " / " + std::to_string( _maximum );
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

UIContainer::UIContainer( const Rect & dimensions )
    : UIComponent( dimensions )
{}

void UIContainer::update( float deltaTime )
{
    for ( auto & component : _items ) {
        component.get()->update( deltaTime );
    }
}

void UIContainer::render()
{
    for ( auto & component : _items ) {
        component.get()->render();
    }
}

void UIContainer::handleClickEvent( const Point & click )
{
    for ( auto & component : _items ) {
        if ( component->getRect().contains( click ) ) {
            component->handleClickEvent( click );
            break;
        }
    }
}

void UIContainer::addElement( std::shared_ptr<UIComponent> element )
{
    _items.push_back( element );
    updateRect();
}

std::shared_ptr<UIComponent> UIContainer::getElement( const Point & click )
{
    for ( auto & component : _items ) {
        if ( component.get()->getRect().contains( click ) ) {
            return component;
        }
    }
    return nullptr;
}

void UIContainer::updateRect()
{
    for ( const auto & component : _items ) {
        const Rect & dimensions = component.get()->getRect();
        if ( dimensions._pos._x < _rect._pos._x ) {
            _rect._pos._x = dimensions._pos._x;
        }
        if ( dimensions._pos._y < _rect._pos._y ) {
            _rect._pos._y = dimensions._pos._y;
        }

        Point bottomRight = dimensions._pos + dimensions._size;
        Point diff = bottomRight - ( _rect._pos + _rect._size );
        if ( diff._x > 0 ) {
            _rect._size._x += diff._x;
        }
        if ( diff._y > 0 ) {
            _rect._size._y += diff._y;
        }
    }
}
