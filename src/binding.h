#pragma once

struct ValueBinding
{
    int & value;
    int minimum = 0;
    int maximum = 100;

    ValueBinding( int & input )
        : value( input )
    {}
};
