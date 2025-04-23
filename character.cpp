#include "character.h"
#include <iostream>

character::character(/* args */)
{
}

// Constructor for character class
// Initializes the character with a name, maximum health, and attack power
character::character(std::string name, int maxhp, int styrke)
    : name(name), maxHp(maxhp), hp(maxhp), styrke(styrke)
{
}

character::~character()
{
}

// Attacks the target character and reduces its health by the attacker's strength
// Returns the target's remaining health
int character::angrib(character& target)
{
    target.setHp(target.getHp() - this->styrke);
    return target.getHp();
}

// Resets the character's health to its maximum value
// This function is called at the start of a battle
void character::startKamp()
{
    hp = maxHp;
}