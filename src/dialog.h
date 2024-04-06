#pragma once
#include <memory>
#include <string>
#include <vector>

struct DialogNode;

struct Reward
{
    enum class Type
    {
        NONE,
        EXPERIENCE,
        RESOURCES,
        BATTLE,
        ITEMS,
        QUEST,
        LOCATION
    } type
        = Type::NONE;

    int value = 0; // amount or distance
    int metadata = 0; // resource id or item id or location type or quest type
};

struct DialogOption
{
    int check = 0;
    int difficulty = 10;
    std::string description;
    std::unique_ptr<DialogNode> goodOutcome = nullptr; // default
    std::unique_ptr<DialogNode> badOutcome = nullptr; // can be null, then there's no check
};

struct DialogNode // also Outcome
{
    std::string text;
    Reward reward;
    std::vector<DialogOption> options; // limit to 5, regular is 3, can be 0
};

struct DialogTree
{
    std::string id;
    DialogNode root;
};
