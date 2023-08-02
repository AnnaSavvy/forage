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
    };

    using BattleUnitRef = std::reference_wrapper<BattleUnit>;

    class Force
    {
    public:
        enum Position
        {
            FRONT,
            CENTER,
            BACK,
            ALL
        };

    private:

        std::vector<std::pair<Position, BattleUnit> > chars;

    public:
        bool add( CharacterRef character, Position pos = FRONT );
        bool switchPosition( const CharacterRef character, Position to = FRONT );
        std::vector<BattleUnitRef> getCharacters( Position pos );
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
