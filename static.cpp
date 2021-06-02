#include "static.h"

#include <iomanip>
#include <fstream>

const nlohmann::json & getStaticData()
{
    static nlohmann::json j;
    if ( j.empty() ) {
        std::ifstream dataStream( "data.json" );
        dataStream >> j;
    }
    return j;
}
