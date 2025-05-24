#include "Character.h"
#include <iostream>

Character::Character(/* args */)
{
}

// Constructor for Character class
// Initializes the character with a name, maximum health, and attack power
Character::Character(std::string name, int maxhp, int styrke)
    : name(name), maxHp(maxhp), hp(maxhp), styrke(styrke)
{
}

Character::~Character()
{
}

// Attacks the target character and reduces its health by the attacker's strength
// Returns the target's remaining health
int Character::angrib(Character &target)
{
    target.setHp(target.getHp() - this->styrke);
    return target.getHp();
}

// Resets the character's health to its maximum value
// This function is called at the start of a battle
void Character::startKamp()
{
    hp = maxHp;
}