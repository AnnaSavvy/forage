#include "static.h"
#include "dialog.h"
#include "character.h"

#include <fstream>
#include <iomanip>

namespace
{
    const struct
    {
        DataFileName type;
        const char * string;
    } dataFiles[] = { { DataFileName::GENERIC_DATA, "data.json" },
                      { DataFileName::PREGEN_NAMES, "assets/pregen_names.json" },
                      { DataFileName::OPTIONS, "options.json" },
                      { DataFileName::DIALOG, "assets/dialog.json" } };

    std::map<DataFileName, nlohmann::json> jsonCache;

    template <typename T>
    bool readNonEmpty( const nlohmann::json & jsonObject, std::string key, T & out )
    {
        if ( jsonObject.contains( key ) ) {
            jsonObject.at( key ).get_to( out );
            return true;
        }
        return false;
    }
}

const nlohmann::json & Data::GetStaticData( DataFileName file )
{
    auto it = jsonCache.find( file );
    if ( it != jsonCache.end() ) {
        return it->second;
    }

    static nlohmann::json emptyJson;
    std::ifstream dataStream( dataFiles[static_cast<int>( file )].string );
    if ( dataStream.good() ) {
        it = jsonCache.emplace( file, nlohmann::json::parse( dataStream, nullptr, true, true ) ).first;
        return it->second;
    }
    // missing a file, assert ?
    return emptyJson;
}

void to_json( nlohmann::json & j, const PregenCharacterName & p )
{
    j = nlohmann::json{ { "firstNames", p.firstNames }, { "address", p.lastNames } };
}

void from_json( const nlohmann::json & j, PregenCharacterName & p )
{
    readNonEmpty( j, "firstNames", p.firstNames );
    readNonEmpty( j, "lastNames", p.lastNames );
}

std::vector<PregenCharacterName> Data::GetPresets()
{
    std::vector<PregenCharacterName> retval;
    auto json = GetStaticData( DataFileName::PREGEN_NAMES );

    for ( auto & element : json.at( "characters" ) ) {
        retval.push_back( element.template get<PregenCharacterName>() );
    }

    return retval;
}

// have to forward declare it
void from_json( const nlohmann::json & j, DialogNode & n );

void to_json( nlohmann::json & j, const Reward & r )
{
    j = nlohmann::json{ { "type", r.type }, { "value", r.value }, { "metadata", r.metadata } };
}

void from_json( const nlohmann::json & j, Reward & r )
{
    readNonEmpty( j, "type", r.type );
    readNonEmpty( j, "value", r.value );
    readNonEmpty( j, "metadata", r.metadata );
}

void to_json( nlohmann::json & j, const DialogOption & o )
{
    j = nlohmann::json{ { "check", o.check }, { "difficulty", o.difficulty }, { "description", o.description } };
}

void from_json( const nlohmann::json & j, DialogOption & o )
{
    readNonEmpty( j, "check", o.check );
    readNonEmpty( j, "difficulty", o.difficulty );
    readNonEmpty( j, "description", o.description );

    auto good = j.find( "goodOutcome" );
    if ( good != j.end() ) {
        DialogNode node = good.value().template get<DialogNode>();
        o.goodOutcome = std::make_unique<DialogNode>();
        o.goodOutcome->text = std::move( node.text );
        o.goodOutcome->reward = std::move( node.reward );
        o.goodOutcome->options = std::move( node.options );
    }

    auto bad = j.find( "badOutcome" );
    if ( bad != j.end() ) {
        DialogNode node = bad.value().template get<DialogNode>();
        o.badOutcome = std::make_unique<DialogNode>();
        o.badOutcome->text = std::move( node.text );
        o.badOutcome->reward = std::move( node.reward );
        o.badOutcome->options = std::move( node.options );
    }
}

void to_json( nlohmann::json & j, const DialogNode & n )
{
    j = nlohmann::json{ { "text", n.text }, { "reward", n.reward }, { "options", n.options } };
}

void from_json( const nlohmann::json & j, DialogNode & n )
{
    readNonEmpty( j, "text", n.text );
    auto rewardIt = j.find( "reward" );
    if ( rewardIt != j.end() ) {
        n.reward = rewardIt.value().template get<Reward>();
    }

    for ( auto & element : j.at( "options" ) ) {
        n.options.push_back( element.template get<DialogOption>() );
    }
}

std::vector<CharacterPreset> Data::GetCharacterPresets()
{
    std::vector<CharacterPreset> retval;
    retval.push_back( {} );
    return retval;
}

DialogTree Data::GetDialogTree()
{
    DialogTree retval;
    auto json = GetStaticData( DataFileName::DIALOG );

    if ( json.contains( "encounters" ) ) {
        for ( auto & encounter : json.at( "encounters" ) ) {
            retval.root = encounter.template get<DialogNode>();
            break;
        }
    }

    return retval;
}
