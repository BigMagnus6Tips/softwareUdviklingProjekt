#pragma once
#include <string>
#include <vector>
#include <iostream>

class Vaaben
{
private:
    std::string navn;
    int id;
    int skade;
    int skadestyrke;
    int holdbarhed;
    int pris;
public:
    Vaaben(/* args */);
    ~Vaaben();
    Vaaben(int id, std::string navn, int skade, int skadestyrke, int holdbarhed, int pris)
        : id(id), navn(navn), skade(skade), skadestyrke(skadestyrke), holdbarhed(holdbarhed), pris(pris) {}
    std::string getNavn() const { return navn; }
    int getSkade() const { return skade; }
    int getSkadestyrke() const { return skadestyrke; }
    int getHoldbarhed() const { return holdbarhed; }
    int getPris() const { return pris; }
    int getId() const { return id; }

    bool fjernholdbarhed(); // Decrease durability and check if the weapon is broken
    int tilfoejSkade(int spillerskade); // Calculate the damage dealt by the weapon

};


