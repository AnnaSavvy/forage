#include "input.h"

#include <SDL.h>
#include <format>
#include <iostream>

InputHandler::InputHandler() {}

int InputHandler::getModes() const
{
    return _modes;
}

void InputHandler::reset()
{
    _modes = 0;
}

bool InputHandler::consume( InputToggle mode )
{
    const bool flag = _modes & mode;
    _modes &= ~mode;
    return flag;
}

char InputHandler::consumeKey( bool forceLowercase )
{
    char k = (char)_lastKeyPressed;
    if ( !forceLowercase && isSet( SHIFT ) && k >= SDLK_a && k <= SDLK_z ) {
        k -= 32;
    }
    _lastKeyPressed = SDLK_UNKNOWN;
    return k;
}

bool InputHandler::isSet( InputToggle mode ) const
{
    return _modes & mode;
}

const Point & InputHandler::getClickPosition() const
{
    return _mousePosition;
}

void InputHandler::setScaling( double windowScaling )
{
    _scaling = windowScaling;
}

bool InputHandler::handleEvent()
{
    static int modesToReset = KEY_PRESSED | MOUSE_CLICKED | MOUSE_MOVED | MOUSE_SCROLL;
    _modes &= ~modesToReset;

    SDL_Event event;
    while ( SDL_PollEvent( &event ) ) {
        switch ( event.type ) {
        case SDL_QUIT:
            return false;
        case SDL_WINDOWEVENT:
            if ( event.window.event == SDL_WINDOWEVENT_CLOSE ) {
                return false;
            }
            break;
        case SDL_KEYDOWN:
            switch ( event.key.keysym.sym ) {
            case SDLK_UP:
                _modes |= InputToggle::UP;
                break;
            case SDLK_DOWN:
                _modes |= InputToggle::DOWN;
                break;
            case SDLK_LEFT:
                _modes |= InputToggle::LEFT;
                break;
            case SDLK_RIGHT:
                _modes |= InputToggle::RIGHT;
                break;
            case SDLK_SPACE:
                _modes |= InputToggle::SPACE;
                break;
            case SDLK_LSHIFT:
            case SDLK_RSHIFT:
                _modes |= InputToggle::SHIFT;
                break;
            case SDLK_LALT:
            case SDLK_RALT:
                _modes |= InputToggle::ALT;
                break;
            case SDLK_LCTRL:
            case SDLK_RCTRL:
                _modes |= InputToggle::CONTROL;
                break;
            default:
                _modes |= InputToggle::KEY_PRESSED;
                _lastKeyPressed = event.key.keysym.sym;
                break;
            }
            break;
        case SDL_KEYUP:
            switch ( event.key.keysym.sym ) {
            case SDLK_UP:
                _modes &= ~InputToggle::UP;
                break;
            case SDLK_DOWN:
                _modes &= ~InputToggle::DOWN;
                break;
            case SDLK_LEFT:
                _modes &= ~InputToggle::LEFT;
                break;
            case SDLK_RIGHT:
                _modes &= ~InputToggle::RIGHT;
                break;
            case SDLK_SPACE:
                _modes &= ~InputToggle::SPACE;
                break;
            case SDLK_LSHIFT:
            case SDLK_RSHIFT:
                _modes &= ~InputToggle::SHIFT;
                break;
            case SDLK_LALT:
            case SDLK_RALT:
                _modes &= ~InputToggle::ALT;
                break;
            case SDLK_LCTRL:
            case SDLK_RCTRL:
                _modes &= ~InputToggle::CONTROL;
                break;
            default:
                _modes &= ~InputToggle::KEY_PRESSED;
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN: {
            switch ( event.button.button ) {
            case SDL_BUTTON_LEFT:
                _modes |= InputToggle::MOUSE_LEFT_CLICKED;
                break;
            case SDL_BUTTON_MIDDLE:
                _modes |= InputToggle::MOUSE_MIDDLE_CLICKED;
                break;
            case SDL_BUTTON_RIGHT:
                _modes |= InputToggle::MOUSE_RIGHT_CLICKED;
                break;
            }

            std::cout << std::format( "Click {} at {}, {}\n", (int)event.button.button, event.button.x, event.button.y );
            _mousePosition.x = event.button.x / _scaling;
            _mousePosition.y = event.button.y / _scaling;
            break;
        }
        default:
            break;
        }
    }
    return true;
}

InputHandler & InputHandler::Get()
{
    static InputHandler handler;
    return handler;
}
