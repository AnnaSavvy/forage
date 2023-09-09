#pragma once

namespace RPG
{
    // Abstract representation of any in game character regardless of the system
    class UnitBase
    {
    public:
        // attributes
        virtual int getHealth() const = 0;

        // helpers
        virtual bool canUseAbility( const AbilityBase & ability ) const = 0;

        // events / mutating state
        virtual bool takeDamage() = 0;
    };

    class AbilityBase
    {
    public:

    };

    class SimpleUnit : public UnitBase
    {
        enum Perks
        {
            SWORDS,
            AXES,
            DAGGERS,
            SPEARS,
            BLUDGEON,
            BOW,
            CROSSBOW,

            FIRE,
            LIGHTNING,
            ACID,
            DIVINATION,
            ASTRAL,

            HEALTH,
            MANA,
            VITALITY,
            SPIRIT,
            QUICKNESS,
            LIFT,
            BACKSTAB,
            STRENGTH,
            DEXTERITY,
            INTELLIGENCE,
            INVALID
        };

        int strength = 0;
        int dexterity = 0;
        int intelligence = 0;

        int exp = 0;

        int melee = 0;
        int ranged = 0;
        int thivery = 0;
        int elemental = 0;
        int divination = 0;
        int astral = 0;

        int perks[INVALID];

    public:

    };
}