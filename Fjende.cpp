#include "Fjende.h"

Fjende::Fjende(/* args */)
{
}

Fjende::~Fjende()
{
}

// Constructor for Fjende class
// Initializes the enemy with a name, health, attack power, and experience given
Fjende::Fjende(int id, std::string name, int health, int attackPower, int experienceGiven) : Character(id, name, health, attackPower), experienceGiven(experienceGiven)
{
}

// Changes the enemy's attack power
// Changes the name of the enemy to include a prefix that indicates the change
void Fjende::changeAttackPower(int newAttackPower)
{
    int oldattackpower = getStyrke();
    setStyrke(newAttackPower);
    int diff = newAttackPower - oldattackpower;
    switch (diff)
    {
    case 1:
        setName("Stærk " + getName());
        break;
    case 2:
        setName("Meget stærk " + getName());
        break;
    case 3:
        setName("Ekstremt stærk " + getName());
        break;
    case 4:
        setName("Overmenneskelig " + getName());
        break;
    case 5:
        setName("Guddommelig " + getName());
        break;
    case -1:
        setName("Svag " + getName());
        break;
    case -2:
        setName("Meget svag " + getName());
        break;
    case -3:
        setName("Ekstremt svag " + getName());
        break;
    case -4:
        setName("Ynkelig " + getName());
        break;
    case -5:
        setName("Ubetydelig " + getName());
        break;
    default:
        if (diff > 0)
        {
            setName("Stærk " + getName());
        }
        else
        {
            setName("Svag " + getName());
        }
        break;
    }
}