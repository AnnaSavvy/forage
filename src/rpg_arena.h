#pragma once

#include "character.h"

namespace RPG
{
    struct Action
    {
        enum ActionType
        {
            MELEE,
            RANGED,
            SKILL,
            SPELL
        };

        ActionType type = MELEE;
        int target = -1;
        int extra = -1;
    };

    class BattleUnit : public Character
    {


    public:
        BattleUnit( CharacterRef unit ) {}

        Action getAction() const;

        inline std::string getSprite() const {
            return "char_orc.png";
        }
    };

    using BattleUnitRef = std::reference_wrapper<BattleUnit>;
    using BattleUnitConst = std::reference_wrapper<const BattleUnit>;

    class Force
    {
    public:
        /*
        *     D2/KB
        *   5 2  2 5   DD 5 4 2 1   1 2 4 5
        *   4 1  1 4
        *   6 3  3 6   
        */

        enum Position
        {
            RESERVE,
            FRONT,
            SIDE,
            CENTER,
            BACK,
            ALL
        };

    private:

        std::vector<std::pair<Position, BattleUnit> > units;

    public:
        bool add( CharacterRef character, Position pos = FRONT );
        bool switchPosition( const CharacterRef character, Position to = FRONT );
        bool isAnyAlive() const;
        std::vector<BattleUnitRef> modifyCharacters( Position pos );
        std::vector<BattleUnitConst> getCharacters( Position pos ) const;
    };

    class Arena
    {
        Force attackers;
        Force defenders;

        std::pair<int, Character *> currentUnit;
        bool complete = false;

    public:
        Arena( Force atk, Force def )
            : attackers( atk )
            , defenders( def )
        {}

        bool executeTurn();
        bool executeAction( Action action );

        std::vector<BattleUnitRef> getInitiativeList();
        bool checkIfCombatEnded() const;

        inline Force & getAttackers()
        {
            return attackers;
        }

        inline Force & getDefenders()
        {
            return defenders;
        }
    };
}
