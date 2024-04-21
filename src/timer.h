#pragma once

template <typename F>
class Timer
{
    int time;
    F callback;

public:
    Timer( int milliseconds );
    Timer( int milliseconds, F callback );

    void run( int interval );
    bool isRunning() const;
};

using SimpleTimer = Timer<void *>;
