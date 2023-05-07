#pragma once
#include "genetics.h"

#include <vector>

namespace Genetics
{
    enum class Neuromodulator
    {
        // Amino Acid-Derived Hormones
        Dopamine, // reward, cognition and motor systems (from Phenylalanine (F) -> Tyrosine (Y) OR Tyramine)
        Norepinephrine, // awareness and reward; both hormone & transmitter (from dopamine)
        Epinephrine, // heart output, blood sugar, stress (from Norepinephrine)
        Serotonin, // mood, satiety, temperature, pain (from Tryptophan (W))
        Melatonin, // sleep, immune system, free radical prevention (from Serotonin)

        // Peptide Hormones
        Insulin, // regulates metabolism, glucose production, fat sythesis, muscle blood flow
        Oxytocin, // bonding, fertility, response to sex, milk production
        Adrenomedullin, // blood vessels, cell tolerance to hypoxic injury (lack of oxygen)
        Granin, // neuropeptidene processing (i.e. insulin sensitivity), cardiac homeostasis and hypertension

        // Lipid-soluble Hormones (mostly steroids)
        // Slow to act since has to produce proteins within cell
        Cortisol,
        Estradiol,
        Testosterone,

        // Main neurotransmitter for cholinergic system, sometimes could act as a hormone
        // Covers muscle and motor control, learning, short-term memory, arousal
        // (made from Choline which is mostly synthesized by plants)
        Acetylcholine,
    };

    enum class Proteome
    {
        // Synthesis
        Histone, // group holding DNA; abundant in Lysine and Arginine
        Polymerase, // technically an enzyme but by function synthesizes DNA
        Helicase, // DNA replication

        // Enzymes
        Amylase,
        Lipase,
        Protease,
        Acetylcholinesterase, // muscles & nerves neurotrasmission
        ChAT, // Choline acetyltransferase, Acetylcholine production
        Melanocyte, // melanin production [euM/pheoM/neuroM] (from PMEL gene 10th chromosome)

        // Transporting & storage
        Ferritin, // both transports and safely hold the iron as it's toxic to cells

        // Signalling & hormones
        Insulin,
        Granin, // family that secretes hormones (lots of Aspartate & Glutamate)
        Adrenomedullin, // blood vessels, cell tolerance, hypoxic injury [localized to a single locus on Chromosome 11 with 4 exons and 3 introns]
        Calcitonin, // receptor CALCRL also uses Adrenomedullin
        OxytocinNeurophysin, // OXT produces Oxytocin & Neurophysin to carry it
        ADRB, // ADRB1/ADRB2 adrenergic receptors for nor/epinephrine

        // Structural
        Collagen,
        Keratin, // extremely insoluble; for hair, nails, horns, outer layer of skin
        Actin, // scaffolding for Myosin, signal support, cell movement
        Myosin, // ATP motor function & muscle contraction
        Troponin, // regulates Actin & Myosin

        INVALID_PROTEIN
    };

    enum class ProteinFunction
    {
        SYNTHESIS,
        CATALYST,
        TRANSPORT,
        SIGNAL,
        STRUCTURE,
        DAMAGE,
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
