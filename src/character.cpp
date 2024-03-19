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

    std::string Character::GetSkillName( CharacterAttributes skill )
    {
        switch ( skill ) {
        case RPG::CharacterAttributes::STRENGTH:
            return "STR";
        case RPG::CharacterAttributes::DEXTERITY:
            return "DEX";
        case RPG::CharacterAttributes::AGILITY:
            return "AGI";
        case RPG::CharacterAttributes::CONSTITUTION:
            return "CON";
        case RPG::CharacterAttributes::INTELLIGENCE:
            return "INT";
        case RPG::CharacterAttributes::WILLPOWER:
            return "WIL";
        case RPG::CharacterAttributes::CHARISMA:
            return "CHA";
        case CharacterAttributes::CLOSE_COMBAT:
            return "Melee";
        case CharacterAttributes::RANGED_COMBAT:
            return "Ranged";
        case CharacterAttributes::DODGE:
            return "Dodge";
        case CharacterAttributes::BLOCK:
            return "Block";
        case CharacterAttributes::STEALTH:
            return "Stealth";
        case CharacterAttributes::LIFE:
            return "Life";
        case CharacterAttributes::ARCANA:
            return "Arcana";
        case CharacterAttributes::NATURE:
            return "Nature";
        case CharacterAttributes::CHAOS:
            return "Chaos";
        case CharacterAttributes::DEATH:
            return "Death";
        case CharacterAttributes::MAGIC_FIRE:
            return "Fire";
        case CharacterAttributes::MAGIC_WATER:
            return "Water";
        case CharacterAttributes::MAGIC_AIR:
            return "Air";
        case CharacterAttributes::MAGIC_EARTH:
            return "Earth";
        case CharacterAttributes::MAGIC_MENTAL:
            return "Mental";
        case CharacterAttributes::MAGIC_DIVINITY:
            return "Divinity";
        }
        return "Unknown";
    }

    ValueBinding Character::getBinding( CharacterAttributes attribute )
    {
        switch ( attribute ) {
        case RPG::CharacterAttributes::HEALTH:
            return { currentHealth, -100, getMaxHealth() };
        case RPG::CharacterAttributes::LEVEL:
            return { level, 1, 100 };
        case RPG::CharacterAttributes::STRENGTH:
            return { stats.strength, 1, 100 };
        case RPG::CharacterAttributes::DEXTERITY:
            return { stats.dexterity, 1, 100 };
        case RPG::CharacterAttributes::AGILITY:
            return { stats.agility, 1, 100 };
        case RPG::CharacterAttributes::CONSTITUTION:
            return { stats.constitution, 1, 100 };
        case RPG::CharacterAttributes::INTELLIGENCE:
            return { stats.intelligence, 1, 100 };
        case RPG::CharacterAttributes::WILLPOWER:
            return { stats.willpower, 1, 100 };
        case RPG::CharacterAttributes::CHARISMA:
            return { stats.charisma, 1, 100 };
        case RPG::CharacterAttributes::CLOSE_COMBAT:
            return { skills[Skills::CLOSE_COMBAT] };
        case RPG::CharacterAttributes::RANGED_COMBAT:
            return { skills[Skills::RANGED_COMBAT] };
        case RPG::CharacterAttributes::DODGE:
            return { skills[Skills::DODGE] };
        case RPG::CharacterAttributes::BLOCK:
            return { skills[Skills::BLOCK] };
        case RPG::CharacterAttributes::STEALTH:
            return { skills[Skills::STEALTH] };
        case RPG::CharacterAttributes::LIFE:
            return { skills[Skills::LIFE] };
        case RPG::CharacterAttributes::ARCANA:
            return { skills[Skills::ARCANA] };
        case RPG::CharacterAttributes::NATURE:
            return { skills[Skills::NATURE] };
        case RPG::CharacterAttributes::CHAOS:
            return { skills[Skills::CHAOS] };
        case RPG::CharacterAttributes::DEATH:
            return { skills[Skills::DEATH] };
        case RPG::CharacterAttributes::MAGIC_FIRE:
            return { skills[Skills::MAGIC_FIRE] };
        case RPG::CharacterAttributes::MAGIC_WATER:
            return { skills[Skills::MAGIC_WATER] };
        case RPG::CharacterAttributes::MAGIC_AIR:
            return { skills[Skills::MAGIC_AIR] };
        case RPG::CharacterAttributes::MAGIC_EARTH:
            return { skills[Skills::MAGIC_EARTH] };
        case RPG::CharacterAttributes::MAGIC_MENTAL:
            return { skills[Skills::MAGIC_MENTAL] };
        case RPG::CharacterAttributes::MAGIC_DIVINITY:
            return { skills[Skills::MAGIC_DIVINITY] };
        default:
            break;
        }
        return { level };
    }

    bool Character::changeAttribute( CharacterAttributes attribute, int change )
    {
        ValueBinding binding = getBinding( attribute );
        binding.value = std::max( std::min( binding.value + change, binding.maximum ), binding.minimum );
        return true;
    }
}
