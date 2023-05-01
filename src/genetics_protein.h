#pragma once
#include "genetics.h"

#include <vector>

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

    // Not supporting splicing variants
    class Protein
    {
        Proteome type = Proteome::INVALID_PROTEIN;
        ProteinFunction function = ProteinFunction::NONE;
        std::vector<AminoAcid> sequence;

    public:
        Protein( const std::vector<GeneticCode> mRNA, GeneticCode ignore );
    };
}
