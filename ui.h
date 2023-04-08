#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

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
    int _x = 0;
    int _y = 0;
    int _width = 0;
    int _height = 0;

public:
    virtual ~UIComponent() = default;

    virtual void handleEvent() = 0;
    virtual void update( float deltaTime ) = 0;
    virtual void render() = 0;

    void setX( int x )
    {
        _x = x;
    }
    void setY( int y )
    {
        _y = y;
    }
    void setWidth( int width )
    {
        _width = width;
    }
    void setHeight( int height )
    {
        _height = height;
    }
    int getX() const
    {
        return _x;
    }
    int getY() const
    {
        return _y;
    }
    int getWidth() const
    {
        return _width;
    }
    int getHeight() const
    {
        return _height;
    }
};

class Button : public UIComponent
{
    int _id;
    std::vector<std::shared_ptr<EventListener> > _listeners;
    std::string _label;
    bool _isHovered;

public:
    Button() = default;
    Button( int x, int y, int width, int height, const std::string & label );
    virtual ~Button() = default;

    void handleEvent() override;
    void update( float deltaTime ) override;
    void render() override;

    void setLabel( const std::string & label );
    void addEventListener( std::shared_ptr<EventListener> listener );
    void removeEventListener( std::shared_ptr<EventListener> listener );
    void handleClickEvent();
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
            //neighbor->handleEvent();
        }
    }

private:
    int _width;
    int _height;
    std::string _title;
    std::vector<std::shared_ptr<UIComponent> > _components;
    std::vector<Window *> neighbors;
};
