#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "point.h"
#include "ui_style.h"

class Event
{
public:
    virtual ~Event() {}
};

class ButtonClickEvent : public Event
{
public:
    ButtonClickEvent( int id )
        : _id( id )
    {}
    int getId() const
    {
        return _id;
    }

private:
    int _id;
};

class EventListener
{
public:
    virtual ~EventListener() {}
    virtual void onEvent( const Event & event ) = 0;
};

class UIComponent
{
protected:
    Rect rect;

public:
    UIComponent( const Rect & dimensions );
    virtual ~UIComponent() = default;

    virtual void handleEvent() = 0;
    virtual void update( float deltaTime ) = 0;
    virtual void render() = 0;

    const Rect & getRect() const
    {
        return rect;
    }

    void setX( int x )
    {
        rect._pos._x = x;
    }
    void setY( int y )
    {
        rect._pos._y = y;
    }
    void setWidth( int width )
    {
        rect._size._x = width;
    }
    void setHeight( int height )
    {
        rect._size._y = height;
    }
    int getX() const
    {
        return rect._pos._x;
    }
    int getY() const
    {
        return rect._pos._y;
    }
    int getWidth() const
    {
        return rect._size._x;
    }
    int getHeight() const
    {
        return rect._size._y;
    }
};

// A basic text label element
class Label : public UIComponent
{
public:
    Label( const std::string & text, Rect area );

    void setText( const std::string & text );
    void setPosition( int x, int y );
    void setSize( int w, int h );

    virtual void render() override;
    virtual void handleEvent() override {}

private:
    std::string _text;
};

class Button : public UIComponent
{
    std::vector<std::shared_ptr<EventListener> > _listeners;
    std::string _label;
    Style _style;
    bool _isHovered = false;
    bool _isPressed = false;

public:
    Button() = default;
    Button( int x, int y, int width, int height, const std::string & label );
    Button( const Rect & dimensions, const std::string & label, const Style & style );
    virtual ~Button() = default;

    void handleEvent() override;
    void update( float deltaTime ) override;
    void render() override;

    void setStyle(const Style& style) {
        _style = style;
    }
    void setLabel( const std::string & label );
    void addEventListener( std::shared_ptr<EventListener> listener );
    void removeEventListener( std::shared_ptr<EventListener> listener );
    void handleClickEvent();
};

// A basic menu element
class Menu : public UIComponent
{
public:
    Menu();

    void addElement( UIComponent * element );

    virtual void render();
    virtual void handleEvent();

private:
    std::vector<UIComponent *> _elements;
    Point _spacing;
};

class Window
{
public:
    Window( int width, int height, const std::string & title );
    ~Window();

    void handleEvent();
    void update( float deltaTime );
    void addComponent( std::shared_ptr<UIComponent> component )
    {
        _components.push_back( component );
    }

    void addNeighbor( Window * neighbor )
    {
        neighbors.push_back( neighbor );
    }

    void render()
    {
        for ( auto component : _components ) {
            component->render();
        }
    }

    bool containsPoint( int x, int y )
    {
        return false;
    }

    void onButtonClicked()
    {
        for ( auto neighbor : neighbors ) {
            // simulate event by rendering neighbor window
            // neighbor->handleEvent();
        }
    }

private:
    int _width;
    int _height;
    std::string _title;
    std::vector<std::shared_ptr<UIComponent> > _components;
    std::vector<Window *> neighbors;
};
