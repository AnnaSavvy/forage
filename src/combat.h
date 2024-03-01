#pragma once
#include "rng.h"
#include <math.h>
#include <iostream>

class CombatCharacter
{
public:
    enum class HitResult
    {
        MISS,
        HIT,
        CRIT,
        FAILURE
    };

    virtual HitResult isHit( int attack )
    {
        return HitResult::HIT;
    }

    virtual int rollDamage() const = 0;
    virtual int recieveDamage( int amount ) = 0;
    virtual int getHealth() const = 0;
    virtual bool isDead() const = 0;
    virtual int getAttack() const = 0;
};

class DnDCharacter : public CombatCharacter
{
    int health = 0;
    int bonusAttack = 0;
    int ac = 0;
    int weaponDamage = 0;
    int bonusDamage = 0;

public:
    int getHealth() const
    {
        return health;
    }

    HitResult isHit( int bonusAttack )
    {
        const int diceRoll = RandomGenerator::Get().next( 1, 20 );
        if ( diceRoll == 20 ) {
            return HitResult::CRIT;
        }
        if ( diceRoll == 1 ) {
            return HitResult::FAILURE;
        }
        return ( diceRoll + bonusAttack > ac ) ? HitResult::HIT : HitResult::MISS;
    }

    int rollDamage() const
    {
        const int diceRoll = RandomGenerator::Get().next( 1, weaponDamage );
        return diceRoll + bonusDamage;
    }

    int recieveDamage( int amount )
    {
        if ( amount > 0 ) {
            health -= amount;
        }
        return amount;
    }

    bool isDead() const
    {
        return health < 0;
    }

    int getAttack() const
    {
        return bonusAttack;
    }
};

class HnHCharacter : public CombatCharacter
{
    int health = 0;
    int skill = 0;
    int weaponDamage = 0;
    int strength = 0;
    int armor = 0;
    int opening = 0;

public:
    HnHCharacter( int newHealth, int newSkill, int damage )
    {
        health = newHealth;
        skill = newSkill;
        weaponDamage = damage;
        strength = 10;
    }

    int getHealth() const
    {
        return health;
    }

    HitResult isHit( int attack )
    {
        const double ratio = sqrt( (double) attack / skill );
        opening += ( 100 - opening ) / 100.0 * ratio * 15;

        if ( opening > 100 ) {
            opening = 100;
            return HitResult::CRIT;
        }
        else if ( opening > 50 ) {
            return HitResult::HIT;
        }
        return HitResult::MISS;
    }

    int rollDamage() const
    {
        return sqrt( (double) weaponDamage * strength );
    }

    int recieveDamage( int amount )
    {
        int damage = amount - armor;
        if ( damage > 0 ) {
            health -= damage;
        }
        return damage;
    }

    bool isDead() const
    {
        return health < 0;
    }

    int getAttack() const
    {
        return skill;
    }
};

class CombatSystem
{
private:
    std::shared_ptr<CombatCharacter> left;
    std::shared_ptr<CombatCharacter> right;

public:
    void combatAction( std::shared_ptr<CombatCharacter> attacker, std::shared_ptr<CombatCharacter> defender )
    {
        auto hitResult = defender->isHit( attacker->getAttack() );
        if ( hitResult == CombatCharacter::HitResult::HIT || hitResult == CombatCharacter::HitResult::CRIT ) {
            int damage = right->recieveDamage( attacker->rollDamage() );
            std::cout << "Player deals " << damage << " to the enemy"
                      << "\n";
        }
    }

    void run()
    {
        left = std::make_shared<HnHCharacter>( 100, 100, 65 );
        right = std::make_shared<HnHCharacter>( 800, 35, 45 );

        while ( !left->isDead() && !right->isDead() ) {
            combatAction( left, right );

            if ( right->isDead() ) {
                break;
            }
            combatAction( right, left );
        }

        if ( right->isDead() ) {
            std::cout << "Player wins!"
                      << "\n";
        }
        if ( left->isDead() ) {
            std::cout << "Enemy monster wins!"
                      << "\n";
        }
    }
};
