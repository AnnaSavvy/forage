#pragma once

namespace RPG
{
    struct Spell
    {
        enum Name
        {
            INVALID,
            FIRE_ARROW,
            FIREBALL,
            FIREWALL,
            FROST,
            ACID_SPLASH,
            ACID_FOG,
            MIND_STAB,
            MAGIC_MISSILE,
            HEAL_WOUNDS,
            HEAL_ALL,
            BLIND,
            PARALYZE,

            SPELL_NAME_LAST
        };

        enum Book
        {
            ALCHEMIST = 0b1,
            MAGE = 0b10,
            PRIEST = 0b100,
            PSIONIC = 0b1000,
        };

        enum Realm
        {
            FIRE,
            WATER,
            AIR,
            EARTH,
            MENTAL,
            DIVINITY,
        };

        Name name = INVALID;
        int books = MAGE;
        Realm realm = FIRE;
        int level = 0;
        int effect = 0;
        int cost = 0;

        Spell() = default;
        Spell( Name name, int bookFlags, Realm realm, int level, int effect, int cost )
            : name( name )
            , books( bookFlags )
            , realm( realm )
            , level( level )
            , effect( effect )
            , cost( cost )
        {}

        static const Spell & Get( Name name );
    };
}