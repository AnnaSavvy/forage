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

void Chart::Pie::update( float deltaTime ) {
    for ( DataPoint & dp : _data ) {
        if (dp.active) {
            if ( dp.offset < 20 ) {
                dp.offset += deltaTime * 30;
            }
            else {
                dp.offset = 20;
                dp.active = false;
            }
        }
        else {
            if ( dp.offset > 0 ) {
                dp.offset -= deltaTime * 30;
            }
            else {
                dp.offset = 0;
                dp.active = true;
            }
        }
    }
}

void Chart::Pie::render()
{
    if ( _hidden || _data.empty() ) {
        return;
    }

    const double angleOffset = 180.0 / _data.size();
    double startAngle = ( angleOffset + 90 ) * -1;

    for ( size_t id = 0; id < _data.size(); id++ ) {
        DataPoint & dp = _data[id];
        const double endAngle = startAngle + dp.value * 360;
        Rect target = _rect;
        if ( dp.active ) {
            //const double rotation = -90 + angleOffset * id * 2;
            //const double radians = rotation / ( 180 / MPI );
            //target._pos._x += dp.offset * cos( radians );
            //target._pos._y += dp.offset * sin( radians );
        }
        target._size._x += dp.offset;
        target._size._y += dp.offset;
        RenderEngine::DrawPieSlice( target, startAngle, endAngle, dp.color );
        startAngle = endAngle;
    }
}
