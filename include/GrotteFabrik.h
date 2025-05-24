#pragma once
#include <string>
#include <vector>
#include "Fjende.h"
#include "Grotte.h"
#include <cstdlib>
#include <vector>

class GrotteFabrik
{
private:
    /* data */
    std::string navn;
    std::vector<Fjende> fjender;
    int grotteId;
    int grotteLevel;
    int grotteType; // 0 = normal, 1 = boss
    int grotteSize; // 0 = small, 1 = medium, 2 = large
    int grotteGuld;
    Grotte grotte; // Grotte object to be created
    // Factory method to create a Grotte

    // Array of random prefix names for the Grotte
    std::string randomPrefixNames[10] = { "Mystiske", "Skjulte", "Gammle", "Forladte", "Udfordrende", "dødbringende", "mørke", "farlige", "magiske", "fortryllede" };

    // Array of random suffix names for the Grotte
    std::string randomSuffixNames[10] = { "Hule", "Grotte", "Ruin", "Labyrint", "Krypt", "Grav", "Borg", "Tempel", "Bunker", "Helligdom" };

public:
    GrotteFabrik(/* args */);
    ~GrotteFabrik();

    // Method to create a random Grotte
    Grotte bygTilfældigGrotte(int grotteLevel, int grotteType, int grotteSize, std::vector<Fjende>& fjender);
    Grotte getGrotte() const { return grotte; }

    // Method to create a Grotte with specific parameters
    void bygGrotte(std::string navn, int grotteLevel, int grotteType, int grotteSize, std::vector<Fjende>& fjender);
    void tilfojFjende(Fjende fjende);
    void setGrotteGuld(int guld) { grotteGuld = guld; }
    void visFjender() const;
};


