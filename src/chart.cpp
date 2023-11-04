#include "chart.h"
#include "renderer.h"


Chart::Pie::Pie( const Point & center, const Point & size )
    : UIComponent( { center, size } )
{}

Chart::Pie::Pie( const Point & center, const Point & size, const std::vector<DataPoint> & data )
    : UIComponent( { center, size } )
    , _data(data)
{}

void Chart::Pie::setData( const std::vector<DataPoint> & data )
{
    _data = data;
}

void Chart::Pie::render()
{
    if ( _hidden ) {
        return;
    }

    double startAngle = -90.0;
    if ( _data.size() % 2 ) {
        startAngle -= 180 / _data.size();
    }

    for ( DataPoint & dp : _data ) {
        const double endAngle = startAngle + dp.value * 360;
        RenderEngine::DrawPieSlice( _rect, startAngle, endAngle, dp.color );
        startAngle = endAngle;
    }
}
