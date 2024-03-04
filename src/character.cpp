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

    Requirements getRequirements( CharacterClass name )
    {
        Requirements require;
        switch ( name ) {
        case CharacterClass::MARTIAL_STR:
            require.stat.strength = 50;
            break;
        case CharacterClass::MARTIAL_STR_DEX:
            require.stat.strength = 50;
            require.stat.dexterity = 50;
            break;
        case CharacterClass::MARTIAL_STR_AGI:
            require.stat.strength = 50;
            require.stat.agility = 50;
            break;
        case CharacterClass::HYBRID_STR_LFE:
            require.stat.strength = 50;
            require.skill.life = 50;
            break;
        case CharacterClass::HYBRID_STR_SOR:
            require.stat.strength = 50;
            require.skill.sorcery = 50;
            break;
        case CharacterClass::HYBRID_STR_NAT:
            require.stat.strength = 50;
            require.skill.nature = 50;
            break;
        case CharacterClass::HYBRID_STR_CHA:
            require.stat.strength = 50;
            require.skill.chaos = 50;
            break;
        case CharacterClass::HYBRID_STR_DTH:
            require.stat.strength = 50;
            require.skill.death = 50;
            break;

        case CharacterClass::MARTIAL_CON:
            require.stat.constitution = 50;
            break;
        case CharacterClass::MARTIAL_CON_AGI:
            require.stat.constitution = 50;
            require.stat.agility = 50;
            break;
        case CharacterClass::MARTIAL_CON_DEX:
            require.stat.constitution = 50;
            require.stat.dexterity = 50;
            break;
        case CharacterClass::HYBRID_CON_LFE:
            require.stat.constitution = 50;
            require.skill.life = 50;
            break;
        case CharacterClass::HYBRID_CON_SOR:
            require.stat.constitution = 50;
            require.skill.sorcery = 50;
            break;
        case CharacterClass::HYBRID_CON_NAT:
            require.stat.constitution = 50;
            require.skill.nature = 50;
            break;
        case CharacterClass::HYBRID_CON_CHA:
            require.stat.constitution = 50;
            require.skill.chaos = 50;
            break;
        case CharacterClass::HYBRID_CON_DTH:
            require.stat.constitution = 50;
            require.skill.death = 50;
            break;

        case CharacterClass::MARTIAL_DEX:
            require.stat.dexterity = 50;
            break;
        case CharacterClass::HYBRID_DEX_LFE:
            require.stat.dexterity = 50;
            require.skill.life = 50;
            break;
        case CharacterClass::HYBRID_DEX_SOR:
            require.stat.dexterity = 50;
            require.skill.sorcery = 50;
            break;
        case CharacterClass::HYBRID_DEX_NAT:
            require.stat.dexterity = 50;
            require.skill.nature = 50;
            break;
        case CharacterClass::HYBRID_DEX_CHA:
            require.stat.dexterity = 50;
            require.skill.chaos = 50;
            break;
        case CharacterClass::HYBRID_DEX_DTH:
            require.stat.dexterity = 50;
            require.skill.death = 50;
            break;

        case CharacterClass::MARTIAL_AGI:
            require.stat.agility = 50;
            break;
        case CharacterClass::HYBRID_AGI_LFE:
            require.stat.agility = 50;
            require.skill.life = 50;
            break;
        case CharacterClass::HYBRID_AGI_SOR:
            require.stat.agility = 50;
            require.skill.sorcery = 50;
            break;
        case CharacterClass::HYBRID_AGI_NAT:
            require.stat.agility = 50;
            require.skill.nature = 50;
            break;
        case CharacterClass::HYBRID_AGI_CHA:
            require.stat.agility = 50;
            require.skill.chaos = 50;
            break;
        case CharacterClass::HYBRID_AGI_DTH:
            require.stat.agility = 50;
            require.skill.death = 50;
            break;

        case CharacterClass::MARTIAL_STR_CON:
            require.stat.strength = 50;
            require.stat.constitution = 50;
            break;
        case CharacterClass::ADVANCED_LFE_SOR_STRCON:
            require.stat.strength = 50;
            require.stat.constitution = 50;
            require.skill.life = 50;
            require.skill.sorcery = 50;
            break;
        case CharacterClass::ADVANCED_LFE_NAT_STRCON:
            require.stat.strength = 50;
            require.stat.constitution = 50;
            require.skill.life = 50;
            require.skill.nature = 50;
            break;
        case CharacterClass::ADVANCED_LFE_CHA_STRCON:
            require.stat.strength = 50;
            require.stat.constitution = 50;
            require.skill.life = 50;
            require.skill.chaos = 50;
            break;
        case CharacterClass::ADVANCED_LFE_DTH_STRCON:
            require.stat.strength = 50;
            require.stat.constitution = 50;
            require.skill.life = 50;
            require.skill.death = 50;
            break;
        case CharacterClass::ADVANCED_SOR_NAT_STRCON:
            require.stat.strength = 50;
            require.stat.constitution = 50;
            require.skill.sorcery = 50;
            require.skill.nature = 50;
            break;
        case CharacterClass::ADVANCED_SOR_CHA_STRCON:
            require.stat.strength = 50;
            require.stat.constitution = 50;
            require.skill.sorcery = 50;
            require.skill.chaos = 50;
            break;
        case CharacterClass::ADVANCED_SOR_DTH_STRCON:
            require.stat.strength = 50;
            require.stat.constitution = 50;
            require.skill.sorcery = 50;
            require.skill.death = 50;
            break;
        case CharacterClass::ADVANCED_NAT_CHA_STRCON:
            require.stat.strength = 50;
            require.stat.constitution = 50;
            require.skill.nature = 50;
            require.skill.chaos = 50;
            break;
        case CharacterClass::ADVANCED_NAT_DTH_STRCON:
            require.stat.strength = 50;
            require.stat.constitution = 50;
            require.skill.nature = 50;
            require.skill.death = 50;
            break;
        case CharacterClass::ADVANCED_CHA_DTH_STRCON:
            require.stat.strength = 50;
            require.stat.constitution = 50;
            require.skill.chaos = 50;
            require.skill.death = 50;
            break;

        case CharacterClass::MARTIAL_DEX_AGI:
            require.stat.dexterity = 50;
            require.stat.agility = 50;
            break;
        case CharacterClass::ADVANCED_LFE_SOR_AGIDEX:
            require.stat.dexterity = 50;
            require.stat.agility = 50;
            require.skill.life = 50;
            require.skill.sorcery = 50;
            break;
        case CharacterClass::ADVANCED_LFE_NAT_AGIDEX:
            require.stat.dexterity = 50;
            require.stat.agility = 50;
            require.skill.life = 50;
            require.skill.nature = 50;
            break;
        case CharacterClass::ADVANCED_LFE_CHA_AGIDEX:
            require.stat.dexterity = 50;
            require.stat.agility = 50;
            require.skill.life = 50;
            require.skill.chaos = 50;
            break;
        case CharacterClass::ADVANCED_LFE_DTH_AGIDEX:
            require.stat.dexterity = 50;
            require.stat.agility = 50;
            require.skill.life = 50;
            require.skill.death = 50;
            break;
        case CharacterClass::ADVANCED_SOR_NAT_AGIDEX:
            require.stat.dexterity = 50;
            require.stat.agility = 50;
            require.skill.sorcery = 50;
            require.skill.nature = 50;
            break;
        case CharacterClass::ADVANCED_SOR_CHA_AGIDEX:
            require.stat.dexterity = 50;
            require.stat.agility = 50;
            require.skill.sorcery = 50;
            require.skill.chaos = 50;
            break;
        case CharacterClass::ADVANCED_SOR_DTH_AGIDEX:
            require.stat.dexterity = 50;
            require.stat.agility = 50;
            require.skill.sorcery = 50;
            require.skill.death = 50;
            break;
        case CharacterClass::ADVANCED_NAT_CHA_AGIDEX:
            require.stat.dexterity = 50;
            require.stat.agility = 50;
            require.skill.nature = 50;
            require.skill.chaos = 50;
            break;
        case CharacterClass::ADVANCED_NAT_DTH_AGIDEX:
            require.stat.dexterity = 50;
            require.stat.agility = 50;
            require.skill.nature = 50;
            require.skill.death = 50;
            break;
        case CharacterClass::ADVANCED_CHA_DTH_AGIDEX:
            require.stat.dexterity = 50;
            require.stat.agility = 50;
            require.skill.chaos = 50;
            require.skill.death = 50;
            break;

        case CharacterClass::MAGICAL_LIFE:
            require.skill.life = 50;
            break;
        case CharacterClass::MAGICAL_LFE_SOR:
            require.skill.life = 50;
            require.skill.sorcery = 50;
            break;
        case CharacterClass::MAGICAL_LFE_NAT:
            require.skill.life = 50;
            require.skill.nature = 50;
            break;
        case CharacterClass::MAGICAL_LFE_CHA:
            require.skill.life = 50;
            require.skill.chaos = 50;
            break;
        case CharacterClass::MAGICAL_LFE_DTH:
            require.skill.life = 50;
            require.skill.death = 50;
            break;

        case CharacterClass::MAGICAL_SORCERY:
            require.skill.sorcery = 50;
            break;
        case CharacterClass::MAGICAL_SOR_NAT:
            require.skill.sorcery = 50;
            require.skill.nature = 50;
            break;
        case CharacterClass::MAGICAL_SOR_CHA:
            require.skill.sorcery = 50;
            require.skill.chaos = 50;
            break;
        case CharacterClass::MAGICAL_SOR_DTH:
            require.skill.sorcery = 50;
            require.skill.death = 50;
            break;

        case CharacterClass::MAGICAL_NATURE:
            require.skill.nature = 50;
            break;
        case CharacterClass::MAGICAL_NAT_CHA:
            require.skill.nature = 50;
            require.skill.chaos = 50;
            break;
        case CharacterClass::MAGICAL_NAT_DTH:
            require.skill.nature = 50;
            require.skill.death = 50;
            break;

        case CharacterClass::MAGICAL_CHAOS:
            require.skill.chaos = 50;
            break;
        case CharacterClass::MAGICAL_CHA_DTH:
            require.skill.chaos = 50;
            require.skill.death = 50;
            break;

        case CharacterClass::MAGICAL_DEATH:
            require.skill.death = 50;
            break;

        case CharacterClass::ADVANCED_LFE_SOR_CHA:
            require.skill.life = 50;
            require.skill.sorcery = 50;
            require.skill.chaos = 50;
            break;
        case CharacterClass::ADVANCED_LFE_NAT_DTH:
            require.skill.life = 50;
            require.skill.nature = 50;
            require.skill.death = 50;
            break;
        case CharacterClass::ADVANCED_LFE_CHA_NAT:
            require.skill.life = 50;
            require.skill.nature = 50;
            require.skill.chaos = 50;
            break;
        case CharacterClass::ADVANCED_LFE_DTH_SOR:
            require.skill.life = 50;
            require.skill.sorcery = 50;
            require.skill.death = 50;
            break;
        case CharacterClass::ADVANCED_SOR_NAT_LFE:
            require.skill.life = 50;
            require.skill.sorcery = 50;
            require.skill.nature = 50;
            break;
        case CharacterClass::ADVANCED_SOR_CHA_NAT:
            require.skill.sorcery = 50;
            require.skill.nature = 50;
            require.skill.chaos = 50;
            break;
        case CharacterClass::ADVANCED_SOR_DTH_CHA:
            require.skill.sorcery = 50;
            require.skill.chaos = 50;
            require.skill.death = 50;
            break;
        case CharacterClass::ADVANCED_NAT_CHA_DTH:
            require.skill.nature = 50;
            require.skill.chaos = 50;
            require.skill.death = 50;
            break;
        case CharacterClass::ADVANCED_NAT_DTH_SOR:
            require.skill.sorcery = 50;
            require.skill.nature = 50;
            require.skill.death = 50;
            break;
        case CharacterClass::ADVANCED_CHA_DTH_LFE:
            require.skill.life = 50;
            require.skill.chaos = 50;
            require.skill.death = 50;
            break;
        case CharacterClass::PRESTIGE_TITAN:
            require.stat.strength = 90;
            require.stat.constitution = 90;
            require.stat.dexterity = 90;
            require.stat.agility = 90;
            break;
        case CharacterClass::PRESTIGE_ARCHMAGE:
            require.skill.life = 90;
            require.skill.sorcery = 90;
            require.skill.nature = 90;
            require.skill.chaos = 90;
            require.skill.death = 90;
            break;
        case CharacterClass::PRESTIGE_DEMIGOD:
            require.stat.strength = 90;
            require.stat.constitution = 90;
            require.stat.dexterity = 90;
            require.stat.agility = 90;
            require.skill.life = 90;
            require.skill.sorcery = 90;
            require.skill.nature = 90;
            require.skill.chaos = 90;
            require.skill.death = 90;
            break;
        }
        return require;
    }
}
