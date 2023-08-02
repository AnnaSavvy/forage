#pragma once
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
        int vitality = 0;
        int perception = 0;
        int intelligence = 0;
        int wisdom = 0;
    };

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
            STEALTH,

            WIZARDRY,
            ALCHEMY,
            DIVINITY,

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
            const int statValue = isRanged ? ( stats.strength + stats.perception ) / 2 : stats.strength;
            return 1 + statValue / 10;
        }

        int getMagicDamage() const
        {
            return 1 + ( stats.intelligence + stats.perception ) / 20;
        }

        double calcMagicSuccessChance( Spell spell, int power ) const
        {
            const int difficulty = spell.level * 20 + power * 10;
            const int skill = skills[WIZARDRY] + getRealmSkill( spell.realm );
            return skill / difficulty;
        }

        int getCurrentHealth() const
        {
            return currentHealth;
        }

        int getMaxHealth() const
        {
            return 1 + ( stats.vitality / 6 + 1 ) * level;
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