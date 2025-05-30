#include "Vaaben.h"
#include <iostream>
#include <string>

Vaaben::Vaaben(/* args */)
{
}
Vaaben::~Vaaben()
{
}

    
bool Vaaben::fjernholdbarhed()
{
    holdbarhed--;
    if (holdbarhed <= 0)
    {
        std::cout << "Dit våben " << navn << " er gået i stykker!" << std::endl;
        return true; // Return true if the weapon is broken
    }
    return false; // Return false if the weapon is still usable
}

int Vaaben::tilfoejSkade(int spillerskade)
{

    return skade + skadestyrke * spillerskade;


} 
