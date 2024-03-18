#pragma once

#include "ui_base.h"

namespace Chart
{
    struct DataPoint
    {
        bool active = false;
        double offset = 0.0;
        std::string label;
        double value = 0.0;
        StandardColor color;

        DataPoint( StandardColor col, double val, bool isActive = false )
            : color( col )
            , value( val )
            , active( isActive )
        {}
    };

    class Pie : public UIComponent
    {
    public:
        Pie( const Point & center, const Point & size );
        Pie( const Point & center, const Point & size, const std::vector<DataPoint> & data );

        bool handleClick( const Point & target );
        std::vector<DataPoint> & getData();
        void setData( const std::vector<DataPoint> & data );
        virtual void update( float deltaTime ) override;
        virtual void render() override;

    private:
        StandardFont _font = StandardFont::REGULAR;
        std::vector<DataPoint> _data;
    };
}