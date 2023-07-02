#include "static.h"

#include <fstream>
#include <iomanip>

namespace
{
    const struct
    {
        DataFileName type;
        const char * string;
    } dataFiles[] = { { DataFileName::GENERIC_DATA, "data.json" }, { DataFileName::PREGEN_NAMES, "assets/pregen_names.json" } };
}

const nlohmann::json & GetStaticData( DataFileName file )
{
    static nlohmann::json j;
    if ( j.empty() ) {
        std::ifstream dataStream( dataFiles[static_cast<int>( file )].string );
        dataStream >> j;
    }
    return j;
}

void to_json( nlohmann::json & j, const PregenCharacterName & p )
{
    j = nlohmann::json{ { "firstNames", p.firstNames }, { "address", p.lastNames } };
}

void from_json( const nlohmann::json & j, PregenCharacterName & p )
{
    j.at( "firstNames" ).get_to( p.firstNames );
    j.at( "lastNames" ).get_to( p.lastNames );
}

std::vector<PregenCharacterName> PregenCharacterName::GetPresets()
{
    std::vector<PregenCharacterName> retval;
    auto json = GetStaticData( DataFileName::PREGEN_NAMES );

    for ( auto & element : json.at( "characters" ) ) {
        retval.push_back( element.template get<PregenCharacterName>() );
    }

    return retval;
}
