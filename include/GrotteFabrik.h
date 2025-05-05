#pragma once
#include <string>
#include <vector>
#include "Fjende.h"
#include "Grotte.h"

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
public:
    GrotteFabrik(/* args */);
    ~GrotteFabrik();

    // Method to create a random Grotte
    void bygTilfældigGrotte(std::string navn, int grotteId, int grotteLevel, int grotteType, int grotteSize);
    Grotte getGrotte() const { return grotte; }

    // Method to create a Grotte with specific parameters
    void bygGrotte(std::string navn, int grotteId, int grotteLevel, int grotteType, int grotteSize);
    void tilfojFjende(Fjende fjende);
    void setGrotteGuld(int guld) { grotteGuld = guld; }
    void visFjender() const;
};


