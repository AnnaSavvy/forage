#pragma once


class InputHandler
{
public:
    enum InputToggle : int
    {
        NONE = 0,
        BACKSPACE = 0x1,
        SHIFT = 0x2,
        CONTROL = 0x4,
        ALT = 0x8,
        UP = 0x10,
        DOWN = 0x20,
        LEFT = 0x40,
        RIGHT = 0x80,
        ALL = 0xFF
    };

    int getModes() const;
    bool isSet( InputToggle mode ) const;
    void handleEvent();

    static InputHandler & Get();

private:
    int _modes = InputToggle::NONE;
};