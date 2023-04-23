#include "input.h"

#include <SDL.h>
#include <iostream>

InputHandler::InputHandler() {}

int InputHandler::getModes() const
{
    return _modes;
}

bool InputHandler::isSet( InputToggle mode ) const
{
    return _modes & mode;
}

const Point & InputHandler::getClickPosition() const
{
    return _mouseClick;
}

bool InputHandler::handleEvent()
{
    static int modesToReset = KEY_PRESSED | MOUSE_CLICKED | MOUSE_MOVED | MOUSE_WHEEL;
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
            _modes |= InputToggle::KEY_PRESSED;

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
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            _modes |= InputToggle::MOUSE_CLICKED;

            std::cout << event.button.x << "," << event.button.y << std::endl;
            _mouseClick._x = event.button.x;
            _mouseClick._y = event.button.y;
            break;
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
