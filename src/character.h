#pragma once
#include "binding.h"
#include "character_attributes.h"
#include "character_class.h"
#include "equipment.h"
#include "point.h"
#include "spell.h"

struct CharacterPreset
{
    int startingLevel = 1;
    int levelLimit = 1;
    WeaponType weapon = WeaponType::MELEE;
    std::string name;
    Stats statsOverride;
    Skills skillsOverride;
};

namespace RPG
{
    const int PlayerLevelLimit = 20;

    enum class AttackSource
    {
        PHYSICAL,
        MAGIC
    };

    class Character : protected Unit
    {
        Stats stats;
        Skills skills;
        Skills minSkills;
        int level = 0;

        std::string name;

        double _pointsStats = 0;
        double _pointsSkills = 0;

        WeaponType weapon = WeaponType::MELEE;

        static int lastID;

    public:
        Character();
        Character( CharacterPreset preset );

        CharacterClass getClass() const;

        void applyChanges();

        void levelUp();

        double & statPoints()
        {
            return _pointsStats;
        }

        double & skillPoints()
        {
            return _pointsSkills;
        }

        int getId() const
        {
            return id;
        }

        std::string getName() const
        {
            return name;
        }

        int getLevel() const
        {
            return level;
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

        int getWeaponDamage() const
        {
            const int effectiveLevel = std::min( level, PlayerLevelLimit );
            const double levelCurve = ( sqrt( effectiveLevel * PlayerLevelLimit ) + effectiveLevel * 9 ) / 10;

            const int weaponPower = levelCurve * 2.5 + 1;
            const int skillValue = 100; // skills.combat;

            const int statValue = weapon == WeaponType::RANGED ? ( stats.strength + stats.dexterity ) / 2 : stats.strength;
            const int statBonus = statValue / 10 - 5;

            return std::max( 1, statBonus + weaponPower * skillValue / 100 );
        }

        int getMagicDamage() const
        {
            const int effectiveLevel = std::min( level, PlayerLevelLimit );
            return 1 + ( stats.intelligence + stats.willpower ) * effectiveLevel / 45 + effectiveLevel * 3 / 2;
        }

        double calcMagicSuccessChance( Spell spell, int power ) const
        {
            const int difficulty = spell.level * 20 + power * 10;
            const int skill = skills.life; //+ getRealmSkill( spell.realm );
            return skill / difficulty;
        }

        int getCurrentHealth() const
        {
            return currentHealth;
        }

        int getMaxHealth() const
        {
            const int effectiveLevel = std::min( level, PlayerLevelLimit );
            const int firstLevelHP = 2 + stats.constitution / 5;
            return firstLevelHP + stats.constitution * effectiveLevel / 7 + effectiveLevel;
        }

        bool isDead() const
        {
            return currentHealth <= 0;
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

        bool changeAttribute( CharacterAttributes::Enum attribute, int value );

        static std::string GetSkillName( CharacterAttributes::Enum skill );

        ValueBinding getBinding( CharacterAttributes::Enum attribute );
    };

    using CharacterRef = std::reference_wrapper<Character>;
}
