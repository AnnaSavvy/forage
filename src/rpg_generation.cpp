#include "rpg_generation.h"
#include "rng.h"
#include "static.h"

std::string RPG::Generator::GetCharacterName()
{
    std::string name;
    auto presets = PregenCharacterName::GetPresets();

    if ( presets.empty() )
        return name;

    auto & rng = RandomGenerator::Get();

    auto preset = rng.randomElement( presets );
    if ( preset.firstNames.empty() )
        return name;

    name = rng.randomElement( preset.firstNames );

    if ( !preset.lastNames.empty() ) {
        name += " " + rng.randomElement( preset.lastNames );
    }

    return name;
}
