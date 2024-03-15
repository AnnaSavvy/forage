#include "game.h"
#include "static.h"

int main( int argc, char * argv[] )
{
    const nlohmann::json & data = GetStaticData( DataFileName::OPTIONS );

    Game game = { { data["display"]["resolutionX"], data["display"]["resolutionY"] } };
    game.init();
    game.run();

    return 0;
}
