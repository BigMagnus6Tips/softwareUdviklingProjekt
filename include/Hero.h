#pragma once
#include <string>
#include <vector>
#include "Character.h"
class Hero : public Character
{
private:
    int level;
    int experience;
    int maxExperience;
    
public:
    Hero(/* args */);
    Hero(std::string name, int health, int attackPower);
    ~Hero();
    void levelUp();
    void printHero();
    void giveExperience(int exp);
};


