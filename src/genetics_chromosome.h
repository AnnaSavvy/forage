#pragma once

#include "gene.h"

namespace Genetics
{
    // Assuming both chromatids are perfect duplicates of each other
    class Chromosome
    {
        int id = 0;
        std::vector<Gene> genes;
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
