#pragma once

struct ValueBinding
{
    int & value;
    int minimum = 0;
    int maximum = 100;

    ValueBinding( int & input )
        : value( input )
    {}

    ValueBinding( int & input, int min, int max )
        : value( input )
        , minimum( min )
        , maximum( max )
    {}
};

class ValueComponent
{
    ValueBinding _binding;

public:
    ValueComponent( ValueBinding binding )
        : _binding( binding )
    {}

    const ValueBinding & get() const
    {
        return _binding;
    }

    ValueBinding & editValue()
    {
        return _binding;
    }
};
