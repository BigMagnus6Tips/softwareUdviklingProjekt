#pragma once
#include <string>
#include <vector>
#include "Character.h"
class Fjende : public Character
{
private:
    /* data */
    int experienceGiven;

public:
    Fjende(/* args */);
    Fjende(std::string name, int health, int attackPower, int experienceGiven);
    ~Fjende();
    int getExperienceGiven() const { return experienceGiven; }
    void changeAttackPower(int newAttackPower);
};

