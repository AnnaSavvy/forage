#include "genetics.h"

#include <array>
#include <cassert>
#include <utility>

namespace Genetics
{
    AminoAcid DecodeAminoAcid( uint8_t acid )
    {
        switch ( acid ) {
        case GeneticCode::ATG:
            return AminoAcid::Methionine;
        case GeneticCode::GGG:
        case GeneticCode::GGA:
        case GeneticCode::GGC:
        case GeneticCode::GGT:
            return AminoAcid::Glycine;
        case GeneticCode::GAG:
        case GeneticCode::GAA:
            return AminoAcid::Glutamate;
        case GeneticCode::GAC:
        case GeneticCode::GAT:
            return AminoAcid::Aspartate;
        case GeneticCode::GCG:
        case GeneticCode::GCA:
        case GeneticCode::GCC:
        case GeneticCode::GCT:
            return AminoAcid::Alanine;
        case GeneticCode::GTG:
        case GeneticCode::GTA:
        case GeneticCode::GTC:
        case GeneticCode::GTT:
            return AminoAcid::Valine;
        case GeneticCode::AGG:
        case GeneticCode::AGA:
        case GeneticCode::CGG:
        case GeneticCode::CGA:
        case GeneticCode::CGC:
        case GeneticCode::CGT:
            return AminoAcid::Arginine;
        case GeneticCode::AGC:
        case GeneticCode::AGT:
        case GeneticCode::TCG:
        case GeneticCode::TCA:
        case GeneticCode::TCC:
        case GeneticCode::TCT:
            return AminoAcid::Serine;
        case GeneticCode::AAG:
        case GeneticCode::AAA:
            return AminoAcid::Lysine;
        case GeneticCode::AAC:
        case GeneticCode::AAT:
            return AminoAcid::Asparagine;
        case GeneticCode::ACG:
        case GeneticCode::ACA:
        case GeneticCode::ACC:
        case GeneticCode::ACT:
            return AminoAcid::Threonine;
        case GeneticCode::ATA:
        case GeneticCode::ATC:
        case GeneticCode::ATT:
            return AminoAcid::Isoleucine;
        case GeneticCode::CAG:
        case GeneticCode::CAA:
            return AminoAcid::Glutamine;
        case GeneticCode::CAC:
        case GeneticCode::CAT:
            return AminoAcid::Histidine;
        case GeneticCode::CCG:
        case GeneticCode::CCA:
        case GeneticCode::CCC:
        case GeneticCode::CCT:
            return AminoAcid::Proline;
        case GeneticCode::CTG:
        case GeneticCode::CTA:
        case GeneticCode::CTC:
        case GeneticCode::CTT:
            return AminoAcid::Leucine;
        case GeneticCode::TGG:
            return AminoAcid::Tryptophan;
        case GeneticCode::TGA:
            return AminoAcid::Selenocysteine;
        case GeneticCode::TGC:
        case GeneticCode::TGT:
            return AminoAcid::Cysteine;
        case GeneticCode::TAG:
            return AminoAcid::Pyrrolysine;
        case GeneticCode::TAA:
            return AminoAcid::STOP_Ochre;
        case GeneticCode::TAC:
        case GeneticCode::TAT:
            return AminoAcid::Tyrosine;
        case GeneticCode::TTG:
        case GeneticCode::TTA:
            return AminoAcid::Leucine;
        case GeneticCode::TTC:
        case GeneticCode::TTT:
            return AminoAcid::Phenylalanine;
        default:
            break;
        }
        return AminoAcid::NON_GENETIC_ACID;
    }

    uint8_t EncodeAminoAcid( AminoAcid acid )
    {
        switch ( acid ) {
        case AminoAcid::Glycine:
            return GGG;
        case AminoAcid::Glutamate:
            return GAG;
        case AminoAcid::Aspartate:
            return GAC;
        case AminoAcid::Alanine:
            return GCG;
        case AminoAcid::Valine:
            return GTG;
        case AminoAcid::Arginine:
            return AGG;
        case AminoAcid::Serine:
            return AGC;
        case AminoAcid::Lysine:
            return AAG;
        case AminoAcid::Asparagine:
            return AAC;
        case AminoAcid::Threonine:
            return ACT;
        case AminoAcid::Methionine:
            return ATG;
        case AminoAcid::Isoleucine:
            return ATA;
        case AminoAcid::Glutamine:
            return CAG;
        case AminoAcid::Histidine:
            return CAC;
        case AminoAcid::Proline:
            return CCG;
        case AminoAcid::Leucine:
            return CTA;
        case AminoAcid::Tryptophan:
            return TGG;
        case AminoAcid::Cysteine:
            return TGC;
        case AminoAcid::Selenocysteine:
            return TGA;
        case AminoAcid::Pyrrolysine:
            return TAG;
        case AminoAcid::Tyrosine:
            return TAC;
        case AminoAcid::Phenylalanine:
            return TTC;
        case AminoAcid::STOP_Ochre:
            return TAA;
        default:
            break;
        }
        return GeneticCode::NON_GENETIC_CODE;
    }

    uint8_t ExtractNucleotide( uint8_t acid, uint8_t position )
    {
        assert( position < 4 );

        const uint8_t extract = acid >> ( position * 2 );

        return extract & 0b11;
    }

    uint8_t ChangeNucleotide( uint8_t acid, uint8_t position, Nucleotide value )
    {
        assert( position < 4 );

        const uint8_t mask = 0b11 >> ( position * 2 );
        const uint8_t newValue = value >> ( position * 2 );

        return ( acid & ~mask ) | newValue;
    }

    uint16_t EncodeBinary( uint8_t binaryValue )
    {
        const uint16_t left = ( binaryValue << 8 ) & 0xF00;
        const uint16_t right = ( binaryValue >> 4 ) & 0xF;
        return left | right;
    }

    uint8_t DecodeBinary( uint16_t twoAcids )
    {
        const uint8_t left = ( twoAcids >> 4 ) & 0xF0;
        return left | ( twoAcids & 0xF );
    }

    const AminoAcidProperties & GetAminoAcidProperties( AminoAcid acid )
    {
        static std::array<AminoAcidProperties, std::to_underlying( AminoAcid::NON_GENETIC_ACID )> library = { {
            { ChemicalCompound::Aliphatic, ChemicalPolarity::NONPOLAR, 89, 1.8 }, // Alanine
            { ChemicalCompound::Thiol, ChemicalPolarity::BASE, 121, 2.5 }, // Cysteine
            { ChemicalCompound::Anion, ChemicalPolarity::ACID, 133, -3.5 }, // Aspartate
            { ChemicalCompound::Anion, ChemicalPolarity::ACID, 147, -3.5 }, // Glutamate
            { ChemicalCompound::Aromatic, ChemicalPolarity::NONPOLAR, 165, 2.8 }, // Phenylalanine
            { ChemicalCompound::Aliphatic, ChemicalPolarity::NONPOLAR, 75, -0.4 }, // Glycine
            { ChemicalCompound::Aromatic, ChemicalPolarity::BASE, 155, -3.2 }, // Histidine, can be considered acidic/cation sometimes
            { ChemicalCompound::Aliphatic, ChemicalPolarity::NONPOLAR, 131, 4.5 }, // Isoleucine
            { ChemicalCompound::Cation, ChemicalPolarity::BASE, 146, -3.9 }, // Lysine
            { ChemicalCompound::Aliphatic, ChemicalPolarity::NONPOLAR, 131, 3.8 }, // Leucine
            { ChemicalCompound::Thioether, ChemicalPolarity::NONPOLAR, 149, 1.9 }, // Methionine
            { ChemicalCompound::Amide, ChemicalPolarity::POLAR, 132, -3.5 }, // Asparagine
            { ChemicalCompound::Cation, ChemicalPolarity::BASE, 255, -3.5 }, // Pyrrolysine, non-essential rare; similar to Lysine
            { ChemicalCompound::Cyclic, ChemicalPolarity::NONPOLAR, 115, -1.6 }, // Proline
            { ChemicalCompound::Amide, ChemicalPolarity::POLAR, 146, -3.5 }, // Glutamine
            { ChemicalCompound::Cation, ChemicalPolarity::BASE, 174, -4.5 }, // Arginine
            { ChemicalCompound::Hydroxylic, ChemicalPolarity::POLAR, 105, -0.8 }, // Serine
            { ChemicalCompound::Hydroxylic, ChemicalPolarity::POLAR, 119, -0.7 }, // Threonine
            { ChemicalCompound::Thiol, ChemicalPolarity::ACID, 168, 2.1 }, // Selenocysteine, rare but stronger than Cysteine
            { ChemicalCompound::Aliphatic, ChemicalPolarity::NONPOLAR, 117, 4.2 }, // Valine
            { ChemicalCompound::Aromatic, ChemicalPolarity::NONPOLAR, 204, -0.9 }, // Tryptophan
            { ChemicalCompound::Aromatic, ChemicalPolarity::BASE, 181, -1.3 }, // Tyrosine
            { ChemicalCompound::Anion, ChemicalPolarity::ACID, 147, -3.5 } // STOP_Ochre, Glutamate again
        } };

        const uint8_t index = std::to_underlying( acid );
        if ( index < library.size() ) {
            return library[index];
        }

        return AminoAcidProperties();
    }
}
