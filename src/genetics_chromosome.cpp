#include "genetics_chromosome.h"

#include <random>

namespace
{
    std::random_device dev;
    std::mt19937 rng( dev() );
}

namespace Genetics
{
    void Chromosome::crossingOver( Chromosome & other )
    {
        std::uniform_int_distribution<std::mt19937::result_type> where( 0, 1 );
        size_t totalLength = genes.size();
        if ( totalLength == other.genes.size() ) {
            auto itFrom = genes.begin();
            auto otherFrom = other.genes.begin();

            while ( itFrom != genes.end() ) {
                const size_t leftoverLength = totalLength - ( itFrom - genes.begin() );
                if ( leftoverLength < 2 ) {
                    // nothing to copy
                    break;
                }

                std::uniform_int_distribution<std::mt19937::result_type> distribution( 0, leftoverLength );
                const size_t chunkLength = distribution( dev );
                if ( chunkLength == 0 ) {
                    continue;
                }

                auto itTo = itFrom + chunkLength;
                auto otherTo = otherFrom + chunkLength;

                std::vector<Gene> buffer;
                buffer.reserve( chunkLength );

                // This will leave a chunk of other.genes in undefined state
                buffer.insert( buffer.end(), std::make_move_iterator( otherFrom ), std::make_move_iterator( otherTo ) );

                // Move genes from our chromosome to the other
                other.genes.insert( otherFrom, std::make_move_iterator( itFrom ), std::make_move_iterator( itTo ) );

                // Move genes from our chromosome to the other
                genes.insert( itFrom, std::make_move_iterator( buffer.begin() ), std::make_move_iterator( buffer.end() ) );

                itFrom = itTo;
                otherFrom = otherTo;
            }
        }
    }

    void Chromosome::crossingOverRaw( Chromosome & other )
    {
        // not implemented, need memcpy
    }

    void ChromosomePair::mitosisMutation( double mutationChance )
    {
        // Do nothing for now
    }

    Chromosome Genetics::ChromosomePair::meiosis() const
    {
        Chromosome gametes[4] = { female, male, female, male };

        gametes[0].crossingOver( gametes[1] );
        gametes[2].crossingOver( gametes[3] );

        std::uniform_int_distribution<std::mt19937::result_type> distribution( 1, 4 );
        const uint32_t choice = distribution( dev );

        return gametes[choice];
    }
}
