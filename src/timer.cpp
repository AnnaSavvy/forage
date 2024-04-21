#include "timer.h"

#include <SDL.h>

template <typename F>
Timer<F>::Timer( int milliseconds )
    : time( milliseconds )
    , callback()
{}

template <typename F>
Timer<F>::Timer( int milliseconds, F callback )
    : time( milliseconds )
    , callback( callback )
{}

template <typename F>
void Timer<F>::run( int interval )
{
    SDL_Delay( interval );
    time -= interval;
}

template <typename F>
bool Timer<F>::isRunning() const
{
    return time > 0;
}

template class Timer<void *>;
