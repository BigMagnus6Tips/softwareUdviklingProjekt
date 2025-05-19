#include "Hero.h"
#include <iostream>
#include <string>
#include <vector>
#include "Character.h"

Hero::Hero(/* args */)
{
}

// Constructor for Hero class
// Initializes the hero with a name, health, and attack power
Hero::Hero(std::string name, int health, int attackPower) : Character(name, health, attackPower), level(1), experience(0), maxExperience(1000)
{
}

Hero::~Hero()
{
}

// Increases the hero's level, health, and attack power
// Prints a message indicating the hero has leveled up
void Hero::levelUp()
{
    level++;
    setHp(getHp() + 2);
    setStyrke(getStyrke() + 1);
    std::cout << getName() << " er steget til niveau " << level << "!" << std::endl;
    
}

// Prints the hero's name, level, health, strength, and experience
// Displays the current experience and maximum experience required for the next level
void Hero::printHero()
{
    std::cout << "Navn: " << getName() << std::endl;
    std::cout << "Niveau: " << level << std::endl;
    std::cout << "Liv: " << getHp() << std::endl;
    std::cout << "Styrke: " << getStyrke() << std::endl;
    std::cout << "Experience: " << experience << "/" << maxExperience << std::endl;
}

// Increases the hero's experience by a specified amount
// If the experience exceeds the maximum, the hero levels up
void Hero::giveExperience(int exp)
{
    experience += exp;
    std::cout << getName() << " har modtaget " << exp << " erfaring!" << std::endl;
    if (experience >= maxExperience * level)
    {
        levelUp();
        experience -= maxExperience; // Reset experience after leveling up
    }
}