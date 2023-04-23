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
        KEY_PRESSED = 0x1,
        MOUSE_CLICKED = 0x2,
        MOUSE_MOVED = 0x4,
        MOUSE_WHEEL = 0x8,
        BACKSPACE = 0x10,
        SHIFT = 0x20,
        CONTROL = 0x40,
        ALT = 0x80,
        UP = 0x100,
        DOWN = 0x200,
        LEFT = 0x400,
        RIGHT = 0x800,
        ALL = 0xFFF
    };
    InputHandler();
    InputHandler( const InputHandler & ) = delete;
    InputHandler & operator=( const InputHandler & ) = delete;

    int getModes() const;
    bool isSet( InputToggle mode ) const;
    const Point & getClickPosition() const;
    bool handleEvent();

    static InputHandler & Get();

private:
    int _modes = InputToggle::NONE;
    Point _mouseClick;
};
