#pragma once
#include "json.hpp"

struct DialogTree;
struct CharacterPreset;

enum class DataFileName
{
    GENERIC_DATA,
    PREGEN_NAMES,
    PREGEN_CHARACTERS,
    OPTIONS,
    DIALOG,
};

struct PregenCharacterName
{
    std::vector<std::string> firstNames;
    std::vector<std::string> lastNames;
};

namespace Data
{
    std::vector<CharacterPreset> GetCharacterPresets();
    DialogTree GetDialogTree();
    const nlohmann::json & GetStaticData( DataFileName file );
    std::vector<PregenCharacterName> GetPresets();
}
