#include "include/fjende.h"

fjende::fjende(/* args */)
{
}

fjende::~fjende()
{
}

fjende::fjende(std::string name, int health, int attackPower, int experienceGiven) : character(name, health, attackPower), experienceGiven(experienceGiven)
{
}
