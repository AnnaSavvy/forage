#pragma once
#include "point.h"
#include <string>

struct Stats
{
    int strength = 40;
    int dexterity = 40;
    int agility = 40;
    int constitution = 40;
    int intelligence = 40;
    int willpower = 40;
    int charisma = 40;
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
