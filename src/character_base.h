#pragma once
#include "point.h"
#include <string>

struct Stats
{
    int strength = 0;
    int dexterity = 0;
    int agility = 0;
    int constitution = 0;
    int intelligence = 0;
    int willpower = 0;
    int charisma = 0;
};

struct Skills
{
    int combat = 0;
    int ranged = 0;
    int dodge = 0;
    int block = 0;
    int stealth = 0;

    int life = 0;
    int sorcery = 0;
    int nature = 0;
    int chaos = 0;
    int death = 0;
};

struct Unit
{
    int id = 0;
    Point position;
    int currentHealth = 0;
};
