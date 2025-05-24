#include "GrotteFabrik.h"
#include "Grotte.h"
#include <iostream>
#include <string>
#include <vector>
#include "Fjende.h"
#include <cstdlib>
#include <vector>
#include <chrono>

GrotteFabrik::GrotteFabrik(/* args */)
{
}

GrotteFabrik::~GrotteFabrik()
{
}

// Method to create a random Grotte

Grotte GrotteFabrik::bygTilfældigGrotte(int grotteLevel, int grotteType, int grotteSize, std::vector<Fjende> &fjender)
{
    srand(time(0) + grotteSize + grotteLevel); // Seed the random number generator with the current time

    std::string navn;
    // Generate a random name for the Grotte
    navn = "Den " + randomPrefixNames[rand() % 10] + " " + randomSuffixNames[rand() % 10];

    // Create a random Grotte with the given parameters
    this->grotte = Grotte(navn, grotteLevel, grotteType, grotteSize);
    // Set the Grotte's gold amount based on its size
    grotte.setGrotteGuld(grotteSize * 10 + grotteLevel * 5 + rand() % 200); // Example: gold increases with size and level

    // Add random enemies to the Grotte
    for (int i = 0; i < grotteSize + rand() % 5; i++)
    {

        int randomIndex = rand() % fjender.size();
        Fjende fjende = fjender.at(randomIndex);
        // Set the enemy's health and attack power based on the Grotte's level
        // A hero of equal level will have a 100% chance to defeat the enemy

        int fjendeHealth = fjende.getLiv();
        int fjendeAttackPower = fjende.getStyrke();
        int playerhealth = 10 + ((grotteLevel-1) * 2);
        int playerattackpower = 2 + ((grotteLevel-1) * 1);
        // insure the enemy is not stronger than the player
        int newAttackPower = playerattackpower * playerhealth / fjendeHealth - 1;
        fjende.changeAttackPower(newAttackPower);

        grotte.tilfojFjende(fjende);
    }

    return grotte;
}
