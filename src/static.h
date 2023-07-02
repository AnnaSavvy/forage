#pragma once
#include "json.hpp"

enum class DataFileName
{
    GENERIC_DATA,
    PREGEN_NAMES,
};

const nlohmann::json & GetStaticData( DataFileName file );

struct PregenCharacterName
{
    std::vector<std::string> firstNames;
    std::vector<std::string> lastNames;

    static std::vector<PregenCharacterName> GetPresets();
};
