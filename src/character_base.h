#pragma once
#include "point.h"
#include <string>

struct Stats
{
    int strength = 0;
    int dexterity = 0;
    int agility = 0;
    int constitution = 0;
    int intelligence = 0;
    int willpower = 0;
    int charisma = 0;
};

struct Skills
{
    int combat = 0;
    int ranged = 0;
    int dodge = 0;
    int block = 0;
    int stealth = 0;

    int life = 0;
    int sorcery = 0;
    int nature = 0;
    int chaos = 0;
    int death = 0;

    enum Enum
    {
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
        MAGIC_DIVINITY,

        INVALID_SKILL
    };

    static std::string GetSkillName( Skills::Enum skill )
    {
        switch ( skill ) {
        case CLOSE_COMBAT:
            return "Melee";
        case RANGED_COMBAT:
            return "Ranged";
        case DODGE:
            return "Dodge";
        case BLOCK:
            return "Block";
        case STEALTH:
            return "Stealth";
        case LIFE:
            return "Life";
        case ARCANA:
            return "Arcana";
        case NATURE:
            return "Nature";
        case CHAOS:
            return "Chaos";
        case DEATH:
            return "Death";
        case MAGIC_FIRE:
            return "Fire";
        case MAGIC_WATER:
            return "Water";
        case MAGIC_AIR:
            return "Air";
        case MAGIC_EARTH:
            return "Earth";
        case MAGIC_MENTAL:
            return "Mental";
        case MAGIC_DIVINITY:
            return "Divinity";
        }
        return "Unknown";
    }
};

struct Unit
{
    int id = 0;
    Point position;
    int currentHealth = 0;
};
