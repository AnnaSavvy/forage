#pragma once
#include "json.hpp"

struct DialogTree;

enum class DataFileName
{
    GENERIC_DATA,
    PREGEN_NAMES,
    OPTIONS,
    DIALOG,
};

struct PregenCharacterName
{
    std::vector<std::string> firstNames;
    std::vector<std::string> lastNames;

    static std::vector<PregenCharacterName> GetPresets();
};

const nlohmann::json & GetStaticData( DataFileName file );
DialogTree GetDialogTree();
