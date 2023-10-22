#include "chart.h"
#include "renderer.h"

Chart::Pie::Pie( const Point & center, const Point & size, const std::vector<DataPoint> & data )
    : UIComponent( { center, size } )
    , _data(data)
{}

void Chart::Pie::render()
{
    if ( _hidden ) {
        return;
    }

    double startAngle = 0.0;
    for ( DataPoint & dp : _data ) {
        const double endAngle = startAngle + dp.value * 360;
        RenderEngine::DrawPieSlice( _rect, startAngle, endAngle, dp.color );
        startAngle = endAngle;
    }
}
