#include "fjende.h"

fjende::fjende(/* args */)
{
}

fjende::~fjende()
{
}

// Constructor for fjende class
// Initializes the enemy with a name, health, attack power, and experience given
fjende::fjende(std::string name, int health, int attackPower, int experienceGiven) : character(name, health, attackPower), experienceGiven(experienceGiven)
{
}
