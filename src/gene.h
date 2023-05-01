#pragma once

#include "genetics.h"
#include <vector>

namespace Genetics
{
    // Does not cover noncoding DNA cases
    class Gene
    {
    public:
        size_t locus = 0; // location
        std::vector<GeneticCode> raw; // no introns since protein slicing isn't supported
    };
}
