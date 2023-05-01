#include "genetics_protein.h"

namespace Genetics
{
    Protein::Protein( const std::vector<GeneticCode> mRNA, GeneticCode ignore )
    {
        for ( const GeneticCode & codon : mRNA ) {
            sequence.push_back( DecodeAminoAcid( codon ) );
        }

        // Determine function based on sequence
    }
}
