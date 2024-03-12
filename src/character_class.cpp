#include "character_class.h"

std::string CharacterClassToString( CharacterClass name )
{
    switch ( name ) {
    case CharacterClass::DEFAULT:
        return "Adventurer";
    case CharacterClass::MARTIAL_STR:
        return "Warrior";
    case CharacterClass::MARTIAL_CON:
        return "Knight";
    case CharacterClass::MARTIAL_DEX:
        return "Hunter";
    case CharacterClass::MARTIAL_AGI:
        return "Scout";
    case CharacterClass::MARTIAL_STR_CON:
        return "Barbarian";
    case CharacterClass::MARTIAL_STR_DEX:
        return "Ranger";
    case CharacterClass::MARTIAL_STR_AGI:
        return "Raider";
    case CharacterClass::MARTIAL_CON_AGI:
        return "Dancer";
    case CharacterClass::MARTIAL_CON_DEX:
        return "Ranger";
    case CharacterClass::MARTIAL_DEX_AGI:
        return "Scoundrel";
    case CharacterClass::MAGICAL_LIFE:
        return "Priest";
    case CharacterClass::MAGICAL_SORCERY:
        return "Sorcerer";
    case CharacterClass::MAGICAL_NATURE:
        return "Druid";
    case CharacterClass::MAGICAL_CHAOS:
        return "Pyromancer";
    case CharacterClass::MAGICAL_DEATH:
        return "Necromancer";
    case CharacterClass::MAGICAL_LFE_SOR:
        return "Oracle";
    case CharacterClass::MAGICAL_LFE_NAT:
        return "Summoner";
    case CharacterClass::MAGICAL_LFE_CHA:
        return "Heretic";
    case CharacterClass::MAGICAL_LFE_DTH:
        return "Dark Priest";
    case CharacterClass::MAGICAL_SOR_NAT:
        return "Enchanter";
    case CharacterClass::MAGICAL_SOR_CHA:
        return "Wizard";
    case CharacterClass::MAGICAL_SOR_DTH:
        return "Sage";
    case CharacterClass::MAGICAL_NAT_CHA:
        return "Shaman";
    case CharacterClass::MAGICAL_NAT_DTH:
        return "Witch";
    case CharacterClass::MAGICAL_CHA_DTH:
        return "Warlock";
    case CharacterClass::HYBRID_STR_LFE:
        return "Crusader";
    case CharacterClass::HYBRID_STR_SOR:
        return "Battlemage";
    case CharacterClass::HYBRID_STR_NAT:
        return "Beastmaster";
    case CharacterClass::HYBRID_STR_CHA:
        return "Destroyer";
    case CharacterClass::HYBRID_STR_DTH:
        return "HYBRID_STR_DTH";
    case CharacterClass::HYBRID_CON_LFE:
        return "Martyr";
    case CharacterClass::HYBRID_CON_SOR:
        return "Eldritch Knight";
    case CharacterClass::HYBRID_CON_NAT:
        return "Wayfarer";
    case CharacterClass::HYBRID_CON_CHA:
        return "Fireguard";
    case CharacterClass::HYBRID_CON_DTH:
        return "Reaver";
    case CharacterClass::HYBRID_DEX_LFE:
        return "Silver Ranger";
    case CharacterClass::HYBRID_DEX_SOR:
        return "HYBRID_DEX_SOR";
    case CharacterClass::HYBRID_DEX_NAT:
        return "Hawkeye";
    case CharacterClass::HYBRID_DEX_CHA:
        return "HYBRID_DEX_CHA";
    case CharacterClass::HYBRID_DEX_DTH:
        return "HYBRID_DEX_DTH";
    case CharacterClass::HYBRID_AGI_LFE:
        return "Monk";
    case CharacterClass::HYBRID_AGI_SOR:
        return "Illusionist";
    case CharacterClass::HYBRID_AGI_NAT:
        return "Planeswalker";
    case CharacterClass::HYBRID_AGI_CHA:
        return "HYBRID_AGI_CHA";
    case CharacterClass::HYBRID_AGI_DTH:
        return "Assassin";
    case CharacterClass::ADVANCED_LFE_SOR_STRCON:
        return "ADVANCED_LFE_SOR_STRCON";
    case CharacterClass::ADVANCED_LFE_NAT_STRCON:
        return "Warden";
    case CharacterClass::ADVANCED_LFE_CHA_STRCON:
        return "Zealot";
    case CharacterClass::ADVANCED_LFE_DTH_STRCON:
        return "ADVANCED_LFE_DTH_STRCON";
    case CharacterClass::ADVANCED_SOR_NAT_STRCON:
        return "ADVANCED_SOR_NAT_STRCON";
    case CharacterClass::ADVANCED_SOR_CHA_STRCON:
        return "ADVANCED_SOR_CHA_STRCON";
    case CharacterClass::ADVANCED_SOR_DTH_STRCON:
        return "ADVANCED_SOR_DTH_STRCON";
    case CharacterClass::ADVANCED_NAT_CHA_STRCON:
        return "ADVANCED_NAT_CHA_STRCON";
    case CharacterClass::ADVANCED_NAT_DTH_STRCON:
        return "Witcher";
    case CharacterClass::ADVANCED_CHA_DTH_STRCON:
        return "Dark Lord";
    case CharacterClass::ADVANCED_LFE_SOR_AGIDEX:
        return "ADVANCED_LFE_SOR_AGIDEX";
    case CharacterClass::ADVANCED_LFE_NAT_AGIDEX:
        return "ADVANCED_LFE_NAT_AGIDEX";
    case CharacterClass::ADVANCED_LFE_CHA_AGIDEX:
        return "ADVANCED_LFE_CHA_AGIDEX";
    case CharacterClass::ADVANCED_LFE_DTH_AGIDEX:
        return "ADVANCED_LFE_DTH_AGIDEX";
    case CharacterClass::ADVANCED_SOR_NAT_AGIDEX:
        return "ADVANCED_SOR_NAT_AGIDEX";
    case CharacterClass::ADVANCED_SOR_CHA_AGIDEX:
        return "ADVANCED_SOR_CHA_AGIDEX";
    case CharacterClass::ADVANCED_SOR_DTH_AGIDEX:
        return "Phantom";
    case CharacterClass::ADVANCED_NAT_CHA_AGIDEX:
        return "ADVANCED_NAT_CHA_AGIDEX";
    case CharacterClass::ADVANCED_NAT_DTH_AGIDEX:
        return "Alchemist";
    case CharacterClass::ADVANCED_CHA_DTH_AGIDEX:
        return "ADVANCED_CHA_DTH_AGIDEX";
    case CharacterClass::ADVANCED_LFE_SOR_CHA:
        return "Wizard King";
    case CharacterClass::ADVANCED_LFE_NAT_DTH:
        return "Soultaker";
    case CharacterClass::ADVANCED_LFE_CHA_NAT:
        return "Overlord";
    case CharacterClass::ADVANCED_LFE_DTH_SOR:
        return "ADVANCED_LFE_DTH_SOR";
    case CharacterClass::ADVANCED_SOR_NAT_LFE:
        return "Saint";
    case CharacterClass::ADVANCED_SOR_CHA_NAT:
        return "Elementalist";
    case CharacterClass::ADVANCED_SOR_DTH_CHA:
        return "Lich";
    case CharacterClass::ADVANCED_NAT_CHA_DTH:
        return "Demonologist";
    case CharacterClass::ADVANCED_NAT_DTH_SOR:
        return "Thaumaturge";
    case CharacterClass::ADVANCED_CHA_DTH_LFE:
        return "Inquisitor";
    case CharacterClass::PRESTIGE_TITAN:
        return "Titan";
    case CharacterClass::PRESTIGE_ARCHMAGE:
        return "Archmage";
    case CharacterClass::PRESTIGE_DEMIGOD:
        return "Demigod";
    }
    return "Missing class";
}

Requirements Requirements::BuildForClass( CharacterClass name )
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
