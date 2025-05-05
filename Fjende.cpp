#include "Fjende.h"

Fjende::Fjende(/* args */)
{
}

Fjende::~Fjende()
{
}

// Constructor for Fjende class
// Initializes the enemy with a name, health, attack power, and experience given
Fjende::Fjende(std::string name, int health, int attackPower, int experienceGiven) : Character(name, health, attackPower), experienceGiven(experienceGiven)
{
}
