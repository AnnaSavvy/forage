#include "rpg_arena.h"

namespace RPG
{
    bool Force::add( CharacterRef character, Position pos )
    {
        chars.emplace_back( pos, character );
        return true;
    }

    bool Force::switchPosition( const CharacterRef character, Position to )
    {
        for ( auto & [position, unit] : chars ) {
            if ( unit.getId() == character.get().getId()) {
                position = to;
                return true;
            }
        }
        return false;
    }

    std::vector<CharacterRef> Force::getCharacters( Position pos )
    {
        std::vector<CharacterRef> retval;
        for ( auto &[position, character] : chars ) {
            if ( pos == Force::ALL || pos == position ) {
                retval.push_back( character );
            }
        }

        return retval;
    }
}
