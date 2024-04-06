#include "ui_base.h"

#include "renderer.h"
#include <SDL.h>

UIComponent::UIComponent( const Rect & dimensions )
    : _rect( dimensions )
{}

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

int UIContainer::handleEvent( const Point & click, int event )
{
    for ( auto & component : _items ) {
        if ( const int result = component->handleEvent( click, event ) ) {
            return result;
        }
    }
    return UIComponent::NO_EVENT;
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
        if ( dimensions.pos.x < _rect.pos.x ) {
            _rect.pos.x = dimensions.pos.x;
        }
        if ( dimensions.pos.y < _rect.pos.y ) {
            _rect.pos.y = dimensions.pos.y;
        }

        Point bottomRight = dimensions.pos + dimensions.size;
        Point diff = bottomRight - ( _rect.pos + _rect.size );
        if ( diff.x > 0 ) {
            _rect.size.x += diff.x;
        }
        if ( diff.y > 0 ) {
            _rect.size.y += diff.y;
        }
    }
}

void UIContainer::purgeHidden()
{
    std::vector<std::shared_ptr<UIComponent> > purged;
    for ( auto & item : _items ) {
        if ( !item->isHidden() ) {
            purged.push_back( std::move( item ) );
        }
    }
    _items = purged;
}

Button::Button( int x, int y, int width, int height, const std::string & label )
    : UIComponent( { x, y, width, height } )
{
    _label = label;
}

Button::Button( const Rect & dimensions, const std::string & label, const Style & style )
    : UIComponent( dimensions )
    , _style( style )
{
    _label = label;
}

Button::Button( const Point & position, int width, int height, const std::string & label, const Style & style )
    : UIComponent( { position.x, position.y, width, height } )
    , _style( style )
{
    _label = label;
}

int Button::handleEvent( const Point & click, int event )
{
    if ( _rect.contains( click ) ) {
        return UIComponent::BASIC_EVENT;
    }
    return UIComponent::NO_EVENT;
}

void Button::render()
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

    SDL_Surface * surface = RenderEngine::GetTextSurface( _label, _style.font, _style.textColor );
    if ( surface ) {
        Rect textRect = _rect;
        textRect.pos.x += ( _rect.size.x - surface->w ) / 2;
        textRect.pos.y += ( _rect.size.y - surface->h ) / 2;
        textRect.size.x = surface->w;
        textRect.size.y = surface->h;

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

    RenderEngine::DrawText( _text, _rect.pos, _font, _color );
}

CenteringLabel::CenteringLabel( const Point & position, const std::string & text, int width )
    : Label( position, text )
    , _expectedSize( width, 0 )
{}

CenteringLabel::CenteringLabel( const Rect & dimensions, const std::string & text )
    : Label( dimensions.pos, text )
    , _expectedSize( dimensions.size )
{}

CenteringLabel::CenteringLabel( const Rect & dimensions, const std::string & text, StandardFont font, StandardColor color )
    : Label( dimensions.pos, text, font, color )
    , _expectedSize( dimensions.size )
{}

void CenteringLabel::render()
{
    if ( _hidden ) {
        return;
    }

    SDL_Surface * surface = RenderEngine::GetTextSurface( _text, _font, _color );
    if ( surface ) {
        Rect textRect = _rect;
        if ( _expectedSize.x > 0 ) {
            textRect.pos.x += ( _expectedSize.x - surface->w ) / 2;
        }
        if ( _expectedSize.y > 0 ) {
            textRect.pos.y += ( _expectedSize.y - surface->h ) / 2;
        }
        textRect.size.x = surface->w;
        textRect.size.y = surface->h;

        RenderEngine::DrawDestroySurface( surface, textRect );
    }
}

Window::Window( Rect rect, const std::string & title )
    : UIComponent( rect )
    , _title( title )
{
    _style.font = StandardFont::REGULAR_BOLD;
    _style.borderWidth = 4;
    _style.borderColor = StandardColor::REALM_PRECISION;
    _style.paddingY = 5;
}

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
        innerArea.pos.x += _style.borderWidth;
        innerArea.pos.y += _style.borderWidth;
        innerArea.size.x -= _style.borderWidth * 2;
        innerArea.size.y -= _style.borderWidth * 2;
        RenderEngine::DrawRect( innerArea, _style.backgroundColor );
    }
    else {
        RenderEngine::DrawRect( _rect, _style.backgroundColor );
    }

    SDL_Surface * surface = RenderEngine::GetTextSurface( _title, _style.font, _style.textColor );
    if ( surface ) {
        Rect textRect = _rect;
        textRect.pos.x += ( _rect.size.x - surface->w ) / 2;
        textRect.pos.y += _style.paddingY;
        textRect.size.x = surface->w;
        textRect.size.y = surface->h;

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

FlyingText::FlyingText( const Point & position, const std::string & text, float delay )
    : Label( position, text )
    , toCompletion( delay )
{}

FlyingText::FlyingText( const Point & position, const std::string & text, float delay, StandardFont font, StandardColor color )
    : Label( position, text, font, color )
    , toCompletion( delay )
{}

void FlyingText::render()
{
    if ( !isDone() ) {
        const float progress = timer / toCompletion;

        SDL_Surface * surface = RenderEngine::GetTextSurface( _text, _font, _color );
        if ( surface ) {
            const int offset = surface->h + 20;
            const int alpha = 255 - ( 254 * progress );

            Rect textRect = _rect;
            textRect.pos.y -= offset * progress;
            textRect.size.x = surface->w;
            textRect.size.y = surface->h;

            RenderEngine::DrawDestroyAlphaSurface( surface, textRect, alpha );
        }
    }
}

void FlyingText::update( float deltaTime )
{
    timer += deltaTime;
    if ( isDone() ) {
        _hidden = true;
    }
}

bool FlyingText::isDone() const
{
    return timer > toCompletion;
}
