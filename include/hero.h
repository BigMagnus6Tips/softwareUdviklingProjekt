#pragma once
#include <string>
#include <vector>
#include "include/character.h"
class hero : public character
{
private:
    int level;
    int experience;
    int maxExperience;
    
public:
    hero(/* args */);
    hero(std::string name, int health, int attackPower);
    ~hero();
    void levelUp();

};


