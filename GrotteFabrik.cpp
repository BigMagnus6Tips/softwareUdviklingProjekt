#include "GrotteFabrik.h"
#include "Grotte.h"
#include <iostream>
#include <string>
#include <vector>
#include "Fjende.h"
#include <cstdlib>
#include <vector>

GrotteFabrik::GrotteFabrik(/* args */)
{
}

GrotteFabrik::~GrotteFabrik()
{
}

// Method to create a random Grotte

void GrotteFabrik::bygTilfældigGrotte(int grotteLevel, int grotteType, int grotteSize, std::vector<Fjende>& fjender)
{
    std::string navn;
    // Generate a random name for the Grotte
    navn = "Den " + randomPrefixNames[rand() % 10] + " " + randomSuffixNames[rand() % 10];

    // Create a random Grotte with the given parameters
    this->grotte = Grotte(navn, grotteLevel, grotteType, grotteSize);
    // Set the Grotte's gold amount based on its size
    switch (grotteSize)
    {
    case 0: // small
        grotte.setGrotteGuld(rand() % 100 + 50); // Random gold between 50 and 150
        break;
    case 1: // medium
        grotte.setGrotteGuld(rand() % 200 + 100); // Random gold between 100 and 300
        break;
    case 2: // large
        grotte.setGrotteGuld(rand() % 500 + 200); // Random gold between 200 and 700
        break;
    default:
        std::cout << "Ugyldig grotte størrelse!" << std::endl;
        break;
    }

    // Add random enemies to the Grotte
    for (int i = 0; i < grotteSize + rand() % 5 - 2; i++)
    {
        int randomIndex = rand() % fjender.size();
        Fjende fjende = fjender[randomIndex];

        // Set the enemy's health and attack power based on the Grotte's level
        // A hero of equal level will have a 100% chance to defeat the enemy

        int fjendeHealth = fjende.getLiv();
        int fjendeAttackPower = fjende.getStyrke();
        int playerhealth = 10 + (grotteLevel * 2);
        int playerattackpower = 5 + (grotteLevel * 1);
        // insure the enemy is not stronger than the player
        int newAttackPower = playerhealth * fjendeAttackPower / playerattackpower;
        fjende.changeAttackPower(newAttackPower);

        grotte.tilfojFjende(fjende);
    }

    
}


