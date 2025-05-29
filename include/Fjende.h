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
    Fjende(int id, std::string name, int health, int attackPower, int experienceGiven);
    ~Fjende();
    int getExperienceGiven() const { return experienceGiven; }
    void changeAttackPower(int newAttackPower);
    int getLiv() const { return getHp(); }
    int getStyrke() const { return styrke; }
    void setLiv(int liv) { setHp(liv); }
    void setStyrke(int s) { styrke = s; }
};
