#include "GrotteFabrik.h"
#include "Grotte.h"
#include <iostream>
#include <string>
#include <vector>
#include "Fjende.h"
#include <cstdlib>
#include <vector>
#include <chrono>
#include <random>

GrotteFabrik::GrotteFabrik(VaabenFabrik vaabenFabrik) : vaabenFabrik(vaabenFabrik)
{
    
}


GrotteFabrik::~GrotteFabrik()
{
}

// Method to create a random Grotte

Grotte GrotteFabrik::bygTilfældigGrotte(int grotteLevel, int grotteType, int grotteSize, std::vector<Fjende> &fjender)
{
    // Use a random device and Mersenne Twister engine for randomness
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> prefixDist(0, 9);
    std::uniform_int_distribution<> suffixDist(0, 9);
    std::uniform_int_distribution<> goldDist(0, 199);
    std::uniform_int_distribution<> extraFjenderDist(0, 4);
    std::uniform_int_distribution<> fjendeIndexDist(0, fjender.size() - 1);
    std::uniform_int_distribution<> grottePraemieDist(2, vaabenFabrik.getVaabenSkabelonCount() - 1);

    std::string navn;
    // Generate a random name for the Grotte
    navn = "Den " + randomPrefixNames[prefixDist(gen)] + " " + randomSuffixNames[suffixDist(gen)];

    // Create a random Grotte with the given parameters
    this->grotte = Grotte(navn, grotteLevel, grotteType, grotteSize);
    // Set the Grotte's gold amount based on its size
    grotte.setGrotteGuld(grotteSize * 10 + grotteLevel * 5 + goldDist(gen)); // Example: gold increases with size and level

    // Add random enemies to the Grotte
    int antalFjender = grotteSize + extraFjenderDist(gen);
    for (int i = 0; i < antalFjender; i++)
    {
        int randomIndex = fjendeIndexDist(gen);
        Fjende fjende = fjender.at(randomIndex);
        // Set the enemy's health and attack power based on the Grotte's level
        // A hero of equal level will have a 100% chance to defeat the enemy

        int fjendeHealth = fjende.getLiv();
        int fjendeAttackPower = fjende.getStyrke();
        int playerhealth = 10 + ((grotteLevel-1) * 2);
        int playerattackpower = 2 + ((grotteLevel-1) * 1);
        // insure the enemy is not stronger than the player
        int newAttackPower = playerattackpower * playerhealth / fjendeHealth;
        fjende.changeAttackPower(newAttackPower);

        grotte.tilfojFjende(fjende);
    }
    
    // Set a random weapon as the Grotte's prize
    int randomPraemieIndex = grottePraemieDist(gen);
    Vaaben praemie = vaabenFabrik.bygVaabenEfterSkabelon(randomPraemieIndex);
    grotte.setPraemie(praemie);

    return grotte;
}
