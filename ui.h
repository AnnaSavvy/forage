#pragma once
#include <SDL.h>

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

class UIComponent
{
public:
    virtual ~UIComponent() = default;

    virtual void handleEvent( const SDL_Event & event ) = 0;
    virtual void update( float deltaTime ) = 0;
    virtual void render( SDL_Renderer * renderer ) = 0;

    void setX( int x )
    {
        m_x = x;
    }
    void setY( int y )
    {
        m_y = y;
    }
    void setWidth( int width )
    {
        m_width = width;
    }
    void setHeight( int height )
    {
        m_height = height;
    }
    int getX() const
    {
        return m_x;
    }
    int getY() const
    {
        return m_y;
    }
    int getWidth() const
    {
        return m_width;
    }
    int getHeight() const
    {
        return m_height;
    }

protected:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
};

class Button : public UIComponent
{
public:
    Button();
    Button( int x, int y, int width, int height, const std::string & label );
    virtual ~Button() = default;

    void handleEvent( const SDL_Event & event ) override;
    void update( float deltaTime ) override;
    void render( SDL_Renderer * renderer ) override;

    void setLabel( const std::string & label )
    {
        m_label = label;
    }

    void addEventListener( std::shared_ptr<EventListener> listener )
    {
        m_listeners.push_back( listener );
    }
    void removeEventListener( std::shared_ptr<EventListener> listener )
    {
        m_listeners.erase( std::remove( m_listeners.begin(), m_listeners.end(), listener ), m_listeners.end() );
    }
    void handleClickEvent()
    {
        const ButtonClickEvent event( m_id );
        for ( const auto & listener : m_listeners ) {
            listener->onEvent( event );
        }
    }

private:
    int m_id;
    std::shared_ptr<Window> m_parent;
    std::vector<std::shared_ptr<EventListener> > m_listeners;
    std::string m_label;
    bool m_isHovered;
};

class Window
{
public:
    Window( int width, int height, const std::string & title );
    ~Window();

    void handleEvent( const SDL_Event & event );
    void update( float deltaTime );
    void addComponent( std::shared_ptr<UIComponent> component )
    {
        m_components.push_back( component );
    }

    void addNeighbor( Window * neighbor )
    {
        neighbors.push_back( neighbor );
    }

    void render( SDL_Renderer * renderer )
    {
        for ( auto component : m_components ) {
            component->render( renderer );
        }
    }

    bool containsPoint( int x, int y )
    {
        for ( auto component : m_components ) {
            if ( component->containsPoint( x, y ) ) {
                return true;
            }
        }
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
    int m_width;
    int m_height;
    std::string m_title;
    SDL_Window * m_window;
    SDL_Renderer * m_renderer;
    std::vector<std::shared_ptr<UIComponent> > m_components;
    std::vector<Window *> neighbors;
};

class Event
{
public:
    virtual ~Event() {}
};

class ButtonClickEvent : public Event
{
public:
    ButtonClickEvent( int id )
        : m_id( id )
    {}
    int getId() const
    {
        return m_id;
    }

private:
    int m_id;
};

class EventListener
{
public:
    virtual ~EventListener() {}
    virtual void onEvent( const Event & event ) = 0;
};
