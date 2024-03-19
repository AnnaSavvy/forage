#pragma once

namespace CharacterAttributes
{
    enum Enum : size_t
    {
        HEALTH = 0,
        LEVEL,

        STRENGTH,
        DEXTERITY,
        AGILITY,
        CONSTITUTION,
        INTELLIGENCE,
        WILLPOWER,
        CHARISMA,

        CLOSE_COMBAT,
        RANGED_COMBAT,
        DODGE,
        BLOCK,
        STEALTH,

        LIFE,
        ARCANA,
        NATURE,
        CHAOS,
        DEATH,

        MAGIC_FIRE,
        MAGIC_WATER,
        MAGIC_AIR,
        MAGIC_EARTH,
        MAGIC_MENTAL,
        MAGIC_DIVINITY
    };

    bool IsPrimaryAttribute( Enum attribute );
    bool IsSkillAttribute( Enum attribute );
}
