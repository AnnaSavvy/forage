#pragma once
#include <cstdint>

/*
 * References:
 *
 * Gene database
 * https://www.ncbi.nlm.nih.gov/gene/6736
 * https://www.ncbi.nlm.nih.gov/gene?term=1%5BChr%5D%20AND%20%22Homo%20sapiens%22%5BOrganism%5D%20AND%20%28%22has%20ccds%22%5BProperties%5D%20AND%20alive%5Bprop%5D%29&cmd=DetailsSearch
 *
 * Protein database
 * https://www.uniprot.org/uniprotkb/Q05066/entry
 *
 * Widespread Expansion of Protein Interaction Capabilities by Alternative Splicing
 * https://www.cell.com/cell/fulltext/S0092-8674(16)30043-5
 *
 * Single Amino Acid Repeats in the Proteome World: Structural, Functional, and Evolutionary Insights
 * https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5125637/
 *
 * Analysis of the Whole-Genome Sequences from an Equus Parent-Offspring Trio Provides Insight into the Genomic Incompatibilities in the Hybrid Mule
 * https://www.mdpi.com/2073-4425/13/12/2188
 *
 * New insights into the generation and role of de novo mutations in health and disease
 * https://genomebiology.biomedcentral.com/articles/10.1186/s13059-016-1110-1
 *
 */

namespace Genetics
{

    enum Nucleotide : uint8_t
    {
        Guanine = 0b00,
        Adenine = 0b01,
        Cytosine = 0b10,
        Thymine = 0b11, // Uracil in RNA
    };

    // Alpha acids only
    enum class AminoAcid : uint8_t
    {
        Alanine, // A
        Cysteine, // C
        Aspartate, // D
        Glutamate, // E,
        Phenylalanine, // F
        Glycine, // G
        Isoleucine, // I
        Histidine, // H
        Lysine, // K
        Leucine, // L
        Methionine, // M, sequence start
        Asparagine, // N
        Pyrrolysine, // O, usually stop codon Amber
        Proline, // P
        Glutamine, // Q
        Arginine, // R
        Serine, // S
        Threonine, // T
        Selenocysteine, // U, usually stop codon Opal
        Valine, // V
        Tryptophan, // W
        Tyrosine, // Y
        STOP_Ochre, // E, not an amino acid, can be turned into Glutamate

        NON_GENETIC_ACID
    };

    enum GeneticCode : uint8_t
    {
        GGG = 0b00'00'00, // Glycine
        GGA = 0b00'00'01, // Glycine
        GGC = 0b00'00'10, // Glycine
        GGT = 0b00'00'11, // Glycine
        GAG = 0b00'01'00, // Glutamate
        GAA = 0b00'01'01, // Glutamate
        GAC = 0b00'01'10, // Aspartate
        GAT = 0b00'01'11, // Aspartate
        GCG = 0b00'10'00, // Alanine
        GCA = 0b00'10'01, // Alanine
        GCC = 0b00'10'10, // Alanine
        GCT = 0b00'10'11, // Alanine
        GTG = 0b00'11'00, // Valine
        GTA = 0b00'11'01, // Valine
        GTC = 0b00'11'10, // Valine
        GTT = 0b00'11'11, // Valine

        AGG = 0b01'00'00, // Arginine
        AGA = 0b01'00'01, // Arginine
        AGC = 0b01'00'10, // Serine
        AGT = 0b01'00'11, // Serine
        AAG = 0b01'01'00, // Lysine
        AAA = 0b01'01'01, // Lysine
        AAC = 0b01'01'10, // Asparagine
        AAT = 0b01'01'11, // Asparagine
        ACG = 0b01'10'00, // Threonine
        ACA = 0b01'10'01, // Threonine
        ACC = 0b01'10'10, // Threonine
        ACT = 0b01'10'11, // Threonine
        ATG = 0b01'11'00, // Methionine (Start codon AUG)
        ATA = 0b01'11'01, // Isoleucine
        ATC = 0b01'11'10, // Isoleucine
        ATT = 0b01'11'11, // Isoleucine

        CGG = 0b10'00'00, // Arginine
        CGA = 0b10'00'01, // Arginine
        CGC = 0b10'00'10, // Arginine
        CGT = 0b10'00'11, // Arginine
        CAG = 0b10'01'00, // Glutamine
        CAA = 0b10'01'01, // Glutamine
        CAC = 0b10'01'10, // Histidine
        CAT = 0b10'01'11, // Histidine
        CCG = 0b10'10'00, // Proline
        CCA = 0b10'10'01, // Proline
        CCC = 0b10'10'10, // Proline
        CCT = 0b10'10'11, // Proline
        CTG = 0b10'11'00, // Leucine
        CTA = 0b10'11'01, // Leucine
        CTC = 0b10'11'10, // Leucine
        CTT = 0b10'11'11, // Leucine

        TGG = 0b11'00'00, // Tryptophan
        TGA = 0b11'00'01, // Selenocysteine (Stop codon Opal)
        TGC = 0b11'00'10, // Cysteine
        TGT = 0b11'00'11, // Cysteine
        TAG = 0b11'01'00, // Pyrrolysine (Stop codon Amber)
        TAA = 0b11'01'01, // Glutamate (Stop codon Ochre)
        TAC = 0b11'01'10, // Tyrosine
        TAT = 0b11'01'11, // Tyrosine
        TCG = 0b11'10'00, // Serine
        TCA = 0b11'10'01, // Serine
        TCC = 0b11'10'10, // Serine
        TCT = 0b11'10'11, // Serine
        TTG = 0b11'11'00, // Leucine
        TTA = 0b11'11'01, // Leucine
        TTC = 0b11'11'10, // Phenylalanine
        TTT = 0b11'11'11, // Phenylalanine

        START_SEQUENCE = ATG,
        STOP_SEQUENCE = TAA,
        NON_GENETIC_CODE = 64
    };

    AminoAcid DecodeAminoAcid( uint8_t acid );
    uint8_t EncodeAminoAcid( AminoAcid acid );
    uint8_t ExtractNucleotide( uint8_t acid, uint8_t position );
    uint8_t ChangeNucleotide( uint8_t acid, uint8_t position, Nucleotide value );
    uint16_t EncodeBinary( uint8_t binaryValue );
    uint8_t DecodeBinary( uint16_t twoAcids );
};
