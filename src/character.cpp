#include "character.h"
#include "rpg_generation.h"

namespace RPG
{
    int Character::lastID = 0;

    Character::Character()
    {
        id = lastID++;
        currentHealth = getMaxHealth();
    }

    Character::Character( CharacterPreset preset )
    {
        id = lastID++;

        name = Generator::GetCharacterName();

        stats.agility = 50;
        stats.charisma = 50;
        stats.constitution = 50;
        stats.dexterity = 50;
        stats.intelligence = 50;
        stats.strength = 50;
        stats.willpower = 50;
        level = 2;

        switch ( preset ) {
        case CharacterPreset::MELEE:
            stats.strength = 80;
            stats.agility = 60;
            stats.constitution = 60;
            stats.dexterity = 60;
            stats.charisma = 30;
            stats.intelligence = 20;

            skills.combat = 30;
            skills.block = 20;
            break;
        case CharacterPreset::AGILE:
            stats.agility = 70;
            stats.dexterity = 70;
            stats.charisma = 40;
            stats.intelligence = 30;

            skills.combat = 25;
            skills.dodge = 20;
            skills.stealth = 20;
            break;
        case CharacterPreset::WIZARD:
            stats.strength = 30;
            stats.constitution = 30;
            stats.dexterity = 60;
            stats.intelligence = 80;

            skills.life = 25;
            skills.sorcery = 25;
            skills.nature = 25;
            skills.chaos = 25;
            skills.death = 25;
            break;
        case CharacterPreset::MONSTER:
            stats.strength = 90;
            stats.constitution = 90;
            stats.dexterity = 40;
            stats.charisma = 20;
            stats.intelligence = 10;

            skills.combat = 20;
            break;
        default:
            break;
        }

        applyChanges();
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

    void Character::applyChanges()
    {
        currentHealth = getMaxHealth();
        minSkills = skills;
    }

    void Character::levelUp()
    {
        if ( level < 20 ) {
            level++;
            _pointsStats += 10;
            _pointsSkills += 15 + stats.intelligence / 10;
        }
    }

    std::string Character::GetSkillName( CharacterAttributes::Enum skill )
    {
        switch ( skill ) {
        case CharacterAttributes::STRENGTH:
            return "STR";
        case CharacterAttributes::DEXTERITY:
            return "DEX";
        case CharacterAttributes::AGILITY:
            return "AGI";
        case CharacterAttributes::CONSTITUTION:
            return "CON";
        case CharacterAttributes::INTELLIGENCE:
            return "INT";
        case CharacterAttributes::WILLPOWER:
            return "WIL";
        case CharacterAttributes::CHARISMA:
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

    ValueBinding Character::getBinding( CharacterAttributes::Enum attribute )
    {
        switch ( attribute ) {
        case CharacterAttributes::HEALTH:
            return { currentHealth, -100, getMaxHealth() };
        case CharacterAttributes::LEVEL:
            return { level, 1, 100 };
        case CharacterAttributes::STRENGTH:
            return { stats.strength, 1, 100 };
        case CharacterAttributes::DEXTERITY:
            return { stats.dexterity, 1, 100 };
        case CharacterAttributes::AGILITY:
            return { stats.agility, 1, 100 };
        case CharacterAttributes::CONSTITUTION:
            return { stats.constitution, 1, 100 };
        case CharacterAttributes::INTELLIGENCE:
            return { stats.intelligence, 1, 100 };
        case CharacterAttributes::WILLPOWER:
            return { stats.willpower, 1, 100 };
        case CharacterAttributes::CHARISMA:
            return { stats.charisma, 1, 100 };
        case CharacterAttributes::CLOSE_COMBAT:
            return { skills.combat, minSkills.combat, 100 };
        case CharacterAttributes::RANGED_COMBAT:
            return { skills.ranged, minSkills.ranged, 100 };
        case CharacterAttributes::DODGE:
            return { skills.dodge, minSkills.dodge, 100 };
        case CharacterAttributes::BLOCK:
            return { skills.block, minSkills.block, 100 };
        case CharacterAttributes::STEALTH:
            return { skills.stealth, minSkills.stealth, 100 };
        case CharacterAttributes::LIFE:
            return { skills.life, minSkills.life, 100 };
        case CharacterAttributes::ARCANA:
            return { skills.sorcery, minSkills.sorcery, 100 };
        case CharacterAttributes::NATURE:
            return { skills.nature, minSkills.nature, 100 };
        case CharacterAttributes::CHAOS:
            return { skills.chaos, minSkills.chaos, 100 };
        case CharacterAttributes::DEATH:
            return { skills.death, minSkills.death, 100 };
        case CharacterAttributes::MAGIC_FIRE:
            return { skills.chaos, minSkills.chaos, 100 };
        case CharacterAttributes::MAGIC_WATER:
            return { skills.sorcery, minSkills.sorcery, 100 };
        case CharacterAttributes::MAGIC_AIR:
            return { skills.sorcery, minSkills.sorcery, 100 };
        case CharacterAttributes::MAGIC_EARTH:
            return { skills.nature, minSkills.nature, 100 };
        case CharacterAttributes::MAGIC_MENTAL:
            return { skills.death, minSkills.death, 100 };
        case CharacterAttributes::MAGIC_DIVINITY:
            return { skills.life, minSkills.life, 100 };
        default:
            break;
        }
        return { level };
    }

    bool Character::changeAttribute( CharacterAttributes::Enum attribute, int change )
    {
        ValueBinding binding = getBinding( attribute );

        const int newValue = std::max( std::min( binding.value + change, binding.maximum ), binding.minimum );
        int valueChange = newValue - binding.value;
        if ( valueChange == 0 ) {
            return false;
        }

        if ( CharacterAttributes::IsPrimaryAttribute( attribute ) ) {
            valueChange = std::min( valueChange, static_cast<int>( _pointsStats ) );
            _pointsStats -= valueChange;
            binding.value += valueChange;
        }
        else if ( CharacterAttributes::IsSkillAttribute( attribute ) ) {
            const int direction = valueChange < 0 ? - 1 : 1;

            while ( valueChange != 0 ) {
                const int next = ( direction > 0 ) ? binding.value : binding.value + direction;
                const int pointCost = ( 1 + next / 20 ) * direction;
                if ( pointCost > _pointsSkills ) {
                    break;
                }
                valueChange -= direction;
                _pointsSkills -= pointCost;
                binding.value += direction;
            }
        }
        else {
            binding.value += valueChange;
        }
        return true;
    }
}
