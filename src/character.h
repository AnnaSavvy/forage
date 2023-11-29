#pragma once
#include "character_class.h"
#include "point.h"
#include "spell.h"
#include <cassert>

namespace RPG
{
    enum class AttackSource
    {
        PHYSICAL,
        MAGIC
    };

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
    };

    struct Requirements
    {
        Stats stat;
        Skills skill;
    };

    Requirements getRequirements( CharacterClass name );

    struct Unit
    {
        int id = 0;
        Point position;
        int currentHealth = 0;
    };

    class Character : protected Unit
    {
    public:
        enum Skills
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

    private:

        Stats stats;
        int skills[INVALID_SKILL] = { 0 };
        int level = 0;

    public:

        int getId() const {
            return id;
        }

        int getInitiative() const
        {
            return 100 + ( stats.agility + stats.dexterity ) / 2;
        }

        int getAttackCount( bool isRanged ) const
        {
            const int statValue = isRanged ? stats.strength + stats.agility : stats.agility + stats.dexterity;
            const int count = statValue / 33;
            return ( count > 0 ) ? count : 1;
        }

        int getAttackDamage( bool isRanged ) const
        {
            const int statValue = isRanged ? ( stats.strength + stats.dexterity ) / 2 : stats.strength;
            return 1 + statValue / 10;
        }

        int getMagicDamage() const
        {
            return 1 + ( stats.intelligence + stats.willpower ) / 20;
        }

        double calcMagicSuccessChance( Spell spell, int power ) const
        {
            const int difficulty = spell.level * 20 + power * 10;
            const int skill = skills[LIFE] + getRealmSkill( spell.realm );
            return skill / difficulty;
        }

        int getCurrentHealth() const
        {
            return currentHealth;
        }

        int getMaxHealth() const
        {
            return 1 + ( stats.constitution / 6 + 1 ) * level;
        }

        bool isDead() const
        {
            return currentHealth <= 0;
        }

        int getRealmSkill( Spell::Realm realm ) const
        {
            assert( MAGIC_FIRE + realm < INVALID_SKILL );
            return skills[MAGIC_FIRE + realm];
        }

        bool recieveDamage( AttackSource source, int damage )
        {
            currentHealth -= damage;
            if ( currentHealth < 0 ) {
                currentHealth = 0;
            }
            return isDead();
        }

        bool recieveHealing( int amount )
        {
            currentHealth += amount;

            const int max = getMaxHealth();
            if ( currentHealth > max ) {
                currentHealth = max;
                return true;
            }
            return false;
        }
    };

    using CharacterRef = std::reference_wrapper<Character>;
}