#include "character.h"

namespace RPG
{
    int Character::lastID = 0;

    Character::Character() {
        id = lastID++;
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
