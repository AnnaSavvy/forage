#pragma once
#include "genetics.h"

namespace Genetics
{
    enum class Proteome
    {
        INVALID_PROTEIN
    };

    enum class ProteinFunction
    {
        DNA_SYNTHESIS,
        CATALYST,
        TRANSPORT,
        SIGNAL,
        STRUCTURE,
        NONE
    };

    // Not including splicing variants
    class Protein
    {};
}
