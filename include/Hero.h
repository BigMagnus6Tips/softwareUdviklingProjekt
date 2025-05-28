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
    int gold = 0; // Initialize gold to 0
    
public:
    Hero(/* args */);
    Hero(std::string name, int health, int attackPower);
    Hero(std::string name, int health, int attackPower, int level, int experience, int maxExperience)
        : Character(name, health, attackPower), level(level), experience(experience), maxExperience(maxExperience) {}
    ~Hero();
    void levelUp();
    void printHero();
    void giveExperience(int exp);
    int getLevel() const { return level; }
    void giveGold(int guld);
};


