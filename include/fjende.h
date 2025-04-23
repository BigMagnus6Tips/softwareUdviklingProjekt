#pragma once
#include <string>
#include <vector>
#include "include/character.h"
class fjende : public character
{
private:
    /* data */
    int experienceGiven;

public:
    fjende(/* args */);
    fjende(std::string name, int health, int attackPower, int experienceGiven);
    ~fjende();
};

