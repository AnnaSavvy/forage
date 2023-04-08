#include "input.h"

#include <SDL.h>
#include <iostream>

int InputHandler::getModes() const
{
    return _modes;
}

bool InputHandler::isSet( InputToggle mode ) const
{
    return _modes & mode;
}

void InputHandler::handleEvent() {
    SDL_Event event;
    while ( SDL_PollEvent( &event ) ) {
        switch ( event.type ) {
        case SDL_QUIT:
            //_isRunning = false;
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
            // Handle any mouse button click events here
            std::cout << event.button.x << "," << event.button.y << std::endl;
            break;
        default:
            break;
        }
    }
}

InputHandler & InputHandler::Get()
{
    static InputHandler handler;
    return handler;
}
