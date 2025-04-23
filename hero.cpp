#include "hero.h"
#include <iostream>
#include <string>
#include <vector>
#include "character.h"

hero::hero(/* args */)
{
}

hero::hero(std::string name, int health, int attackPower) : character(name, health, attackPower), level(1), experience(0), maxExperience(1000)
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

void hero::printHero()
{
    std::cout << "Navn: " << getName() << std::endl;
    std::cout << "Niveau: " << level << std::endl;
    std::cout << "Liv: " << getHp() << std::endl;
    std::cout << "Styrke: " << getStyrke() << std::endl;
    std::cout << "Experience: " << experience << "/" << maxExperience << std::endl;
}

void hero::giveExperience(int exp)
{
    experience += exp;
    std::cout << getName() << " har modtaget " << exp << " erfaring!" << std::endl;
    if (experience >= maxExperience)
    {
        levelUp();
        experience -= maxExperience; // Reset experience after leveling up
    }
}