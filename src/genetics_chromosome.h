#pragma once

#include "gene.h"

namespace Genetics
{
    // Assuming both chromatids are perfect duplicates of each other
    class Chromosome
    {
    public:
        int id = 0;
        std::vector<Gene> genes;

        // Mutates the data but keeps genes intact
        void crossingOver( Chromosome & other );

        // Raw copy that can break up genes
        void crossingOverRaw( Chromosome & other );
    };

    class ChromosomePair
    {
        Chromosome female; // inherited from female ancestor
        Chromosome male; // inherited from male ancestor

    public:
        void mitosisMutation( double mutationChance );
        Chromosome meiosis() const;
    };
}
