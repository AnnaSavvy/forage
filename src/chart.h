#pragma once

#include "ui.h"

namespace Chart
{
    struct DataPoint
    {
        bool active = false;
        std::string label;
        double value = 0.0;
        StandardColor color;

        DataPoint( StandardColor col, double val )
            : color( col )
            , value( val )
        {}
    };

    class Pie : public UIComponent
    {
    public:
        Pie( const Point & center, const Point & size, const std::vector<DataPoint> & data );

        virtual void update( float deltaTime ) override {}
        virtual void render() override;

    private:
        StandardFont _font = StandardFont::REGULAR;
        std::vector<DataPoint> _data;
    };
}