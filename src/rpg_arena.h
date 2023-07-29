#pragma once

#include "character.h"

namespace RPG
{
    class Force
    {
        enum Position
        {
            FRONT,
            CENTER,
            BACK,
            ALL
        };

        std::vector<std::pair<Position, Character> > chars;

    public:
        bool add( CharacterRef character, Position pos = FRONT );
        bool switchPosition( const CharacterRef character, Position to = FRONT );
        std::vector<CharacterRef> getCharacters( Position pos );
    };

    class Arena
    {
        Force attackers;
        Force defenders;

        std::pair<int, Character *> currentUnit;

    public:
        Arena( Force atk, Force def )
            : attackers( atk )
            , defenders( def )
        {}

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
