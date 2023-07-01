#include "spell.h"

namespace RPG
{
    const Spell & Spell::Get( RPG::Spell::Name name )
    {
        static const Spell spells[Spell::Name::SPELL_NAME_LAST]
            = { { FIRE_ARROW, ALCHEMIST, FIRE, 1, 8, 3 },  { FIREBALL, MAGE, FIRE, 1, 8, 3 },          { FIREWALL, MAGE, FIRE, 1, 8, 3 },
                { FROST, MAGE, WATER, 1, 8, 3 },           { ACID_SPLASH, ALCHEMIST, WATER, 1, 8, 3 }, { ACID_FOG, ALCHEMIST, WATER, 1, 8, 3 },
                { MIND_STAB, PSIONIC, MENTAL, 1, 8, 3 },   { MAGIC_MISSILE, MAGE, DIVINITY, 1, 8, 3 }, { HEAL_WOUNDS, PRIEST, DIVINITY, 1, 10, 3 },
                { HEAL_ALL, PRIEST, DIVINITY, 6, 10, 10 }, { BLIND, ALCHEMIST, FIRE, 1, 1, 3 },        { PARALYZE, PSIONIC, MENTAL, 2, 1, 5 } };

        return spells[name];
    }
}