#include "character_attributes.h"

bool CharacterAttributes::IsPrimaryAttribute( Enum attribute )
{
    switch ( attribute ) {
    case CharacterAttributes::STRENGTH:
    case CharacterAttributes::DEXTERITY:
    case CharacterAttributes::AGILITY:
    case CharacterAttributes::CONSTITUTION:
    case CharacterAttributes::INTELLIGENCE:
    case CharacterAttributes::WILLPOWER:
    case CharacterAttributes::CHARISMA:
        return true;
    }
    return false;
}

bool CharacterAttributes::IsSkillAttribute( Enum attribute )
{
    switch ( attribute ) {
    case CharacterAttributes::CLOSE_COMBAT:
    case CharacterAttributes::RANGED_COMBAT:
    case CharacterAttributes::DODGE:
    case CharacterAttributes::BLOCK:
    case CharacterAttributes::STEALTH:
    case CharacterAttributes::LIFE:
    case CharacterAttributes::ARCANA:
    case CharacterAttributes::NATURE:
    case CharacterAttributes::CHAOS:
    case CharacterAttributes::DEATH:
        return true;
    }
    return false;
}
