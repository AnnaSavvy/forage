#pragma once
#include "point.h"

enum class InputEvent : int
{
    NO_EVENT = 0,
    QUIT_GAME
};

class InputHandler
{
public:
    enum InputToggle : int
    {
        NONE = 0,
        MOUSE_MOVED = 0x1,
        MOUSE_LEFT_CLICKED = 0x2,
        MOUSE_MIDDLE_CLICKED = 0x4,
        MOUSE_RIGHT_CLICKED = 0x8,
        MOUSE_CLICKED = MOUSE_LEFT_CLICKED | MOUSE_MIDDLE_CLICKED | MOUSE_RIGHT_CLICKED,
        MOUSE_SCROLL = 0x10,
        UNKNOWN20 = 0x20,
        UNKNOWN40 = 0x40,
        KEY_PRESSED = 0x80,
        BACKSPACE = 0x100,
        SHIFT = 0x200,
        CONTROL = 0x400,
        ALT = 0x800,
        UP = 0x1000,
        DOWN = 0x2000,
        LEFT = 0x4000,
        RIGHT = 0x8000,
        ALL = 0xFFFF
    };
    InputHandler();
    InputHandler( const InputHandler & ) = delete;
    InputHandler & operator=( const InputHandler & ) = delete;

    int getModes() const;
    bool isSet( InputToggle mode ) const;
    const Point & getClickPosition() const;
    void setScaling( double windowScaling );
    bool handleEvent();

    static InputHandler & Get();

private:
    int _modes = InputToggle::NONE;
    Point _mousePosition;
    double _scaling = 1.0;
};
