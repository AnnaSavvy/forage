#include "static.h"
#include "dialog.h"

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
}

const nlohmann::json & GetStaticData( DataFileName file )
{
    static nlohmann::json j;
    std::ifstream dataStream( dataFiles[static_cast<int>( file )].string );
    dataStream >> j;
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

// have to forward declare it
void from_json( const nlohmann::json & j, DialogNode & n );

void to_json( nlohmann::json & j, const Reward & r )
{
    j = nlohmann::json{ { "type", r.type }, { "value", r.value }, { "metadata", r.metadata } };
}

void from_json( const nlohmann::json & j, Reward & r )
{
    j.at( "type" ).get_to( r.type );
    j.at( "value" ).get_to( r.value );
    j.at( "metadata" ).get_to( r.metadata );
}

void to_json( nlohmann::json & j, const DialogOption & o )
{
    j = nlohmann::json{ { "check", o.check }, { "difficulty", o.difficulty }, { "description", o.description } };
}

void from_json( const nlohmann::json & j, DialogOption & o )
{
    j.at( "check" ).get_to( o.check );
    j.at( "difficulty" ).get_to( o.difficulty );
    j.at( "description" ).get_to( o.description );

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
    j.at( "text" ).get_to( n.text );
    auto rewardIt = j.find( "reward" );
    if ( rewardIt != j.end() ) {
        n.reward = rewardIt.value().template get<Reward>();
    }

    for ( auto & element : j.at( "options" ) ) {
        n.options.push_back( element.template get<DialogOption>() );
    }
}

DialogTree GetDialogTree()
{
    DialogTree retval;
    auto json = GetStaticData( DataFileName::DIALOG );

    for ( auto & encounter : json.at( "encounters" ) ) {
        retval.root = encounter.template get<DialogNode>();
        break;
    }

    return retval;
}
