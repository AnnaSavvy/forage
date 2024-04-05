#include "game.h"
#include "static.h"

int main( int argc, char * argv[] )
{
    const nlohmann::json & data = GetStaticData( DataFileName::OPTIONS );

    Point resolution = { 1280, 720 };
    if ( data.is_object() ) {
        resolution.x = data["display"]["resolutionX"];
        resolution.y = data["display"]["resolutionY"];
    }

    Game game = { resolution };
    game.init();
    game.run();

    return 0;
}
