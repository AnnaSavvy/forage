#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "point.h"
#include "ui_style.h"

class UIComponent
{
protected:
    Rect _rect;
    bool _hidden = false;

public:
    UIComponent( const Rect & dimensions );
    virtual ~UIComponent() = default;

    virtual void update( float deltaTime ) = 0;
    virtual void render() = 0;

    bool isHidden() const
    {
        return _hidden;
    }

    void setHidden( bool isHidden )
    {
        _hidden = isHidden;
    }

    const Rect & getRect() const
    {
        return _rect;
    }
};

// A basic text label element
class Label : public UIComponent
{
public:
    Label( const Point & position, const std::string & text );
    Label( const Point & position, const std::string & text, StandardFont font, StandardColor color );

    void setText( const std::string & text );
    void setColor( StandardColor color );

    virtual void update( float deltaTime ) override {}
    virtual void render() override;

private:
    std::string _text;
    StandardFont _font = StandardFont::REGULAR;
    StandardColor _color = StandardColor::WHITE;
};

class Button : public UIComponent
{
    std::string _label;
    Style _style;
    bool _isHovered = false;
    bool _isPressed = false;

public:
    Button( int x, int y, int width, int height, const std::string & label );
    Button( const Rect & dimensions, const std::string & label, const Style & style );
    virtual ~Button() = default;

    void update( float deltaTime ) override;
    void render() override;

    void setPressed( bool value );
    void setHovered( bool value );
    void setStyle( const Style & style );
    void setLabel( const std::string & label );
};

class ProgressBar : public UIComponent
{
public:
    ProgressBar( const Rect & dimensions, int max, const Style & style );

    void setValue( int newValue );
    int getValue() const;

    virtual void update( float deltaTime ) override {}
    virtual void render() override;

private:
    Style _style;
    int _value = 0;
    int _maximum = 0;
};

// A basic menu element
class Menu : public UIComponent
{
public:
    Menu();

    void addElement( UIComponent * element );

    virtual void render();

private:
    std::vector<UIComponent *> _elements;
    Point _spacing;
};

class Window : public UIComponent
{
public:
    Window( Rect rect, const std::string & title );
    ~Window();

    void update( float deltaTime );
    void render();

    void setStyle( const Style & style );
    void addComponent( std::shared_ptr<UIComponent> component );

    std::shared_ptr<UIComponent> processClickEvent( const Point & click );

private:
    Style _style;
    std::string _title;
    std::vector<std::shared_ptr<UIComponent> > _components;
};
