#include "include/hero.h"
#include <iostream>
#include <string>
#include <vector>
#include "include/character.h"

hero::hero(/* args */)
{
}

hero::hero(std::string name, int health, int attackPower) : character(name, health, attackPower), level(1), experience(0), maxExperience(100)
{
}

hero::~hero()
{
}

void hero::levelUp()
{
    level++;
    setHp(getHp() + 20);
    setStyrke(getStyrke() + 5);
    std::cout << getName() << " er steget til niveau " << level << "!" << std::endl;
}

