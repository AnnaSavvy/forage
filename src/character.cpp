#include "character.h"

namespace RPG
{
    int Character::lastID = 0;

    Character::Character()
    {
        id = lastID++;
        currentHealth = getMaxHealth();
    }

    CharacterClass Character::getClass() const
    {
        if ( stats.strength > 60 ) {
            return CharacterClass::MARTIAL_STR;
        }
        else if ( stats.agility > 60 ) {
            return CharacterClass::MARTIAL_AGI;
        }
        return CharacterClass::MAGICAL_NATURE;
    }

    Character::Character( CharacterPreset preset )
    {
        id = lastID++;

        stats.agility = 50;
        stats.charisma = 50;
        stats.constitution = 50;
        stats.dexterity = 50;
        stats.intelligence = 50;
        stats.strength = 50;
        stats.willpower = 50;
        level = 4;

        switch ( preset ) {
        case RPG::CharacterPreset::MELEE:
            stats.strength = 80;
            stats.agility = 60;
            stats.constitution = 65;
            stats.dexterity = 60;
            stats.charisma = 30;
            stats.intelligence = 20;

            skills[Skills::CLOSE_COMBAT] = 30;
            skills[Skills::BLOCK] = 20;
            break;
        case RPG::CharacterPreset::AGILE:
            stats.agility = 70;
            stats.dexterity = 70;
            stats.charisma = 40;
            stats.intelligence = 30;

            skills[Skills::CLOSE_COMBAT] = 25;
            skills[Skills::DODGE] = 20;
            skills[Skills::STEALTH] = 20;
            break;
        case RPG::CharacterPreset::WIZARD:
            stats.strength = 25;
            stats.agility = 30;
            stats.constitution = 30;
            stats.dexterity = 60;
            stats.intelligence = 80;

            skills[Skills::LIFE] = 25;
            skills[Skills::ARCANA] = 25;
            skills[Skills::NATURE] = 25;
            skills[Skills::CHAOS] = 25;
            skills[Skills::DEATH] = 25;
            break;
        case RPG::CharacterPreset::MONSTER:
            stats.strength = 90;
            stats.constitution = 90;
            stats.dexterity = 40;
            stats.charisma = 10;
            stats.intelligence = 10;

            skills[Skills::CLOSE_COMBAT] = 20;
            break;
        default:
            break;
        }

        currentHealth = getMaxHealth();
    }

    ValueBinding Character::getBinding( Skills::Enum skill )
    {
        return { skills[skill] };
    }
}
