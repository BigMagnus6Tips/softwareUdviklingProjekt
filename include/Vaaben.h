#pragma once
#include <string>
#include <vector>
#include <iostream>

class Vaaben
{
private:
    std::string navn;
    int typeID;
    int id = 0;
    int skade;
    int skadestyrke;
    int holdbarhed;
    int pris;
public:
    Vaaben(/* args */);
    ~Vaaben();
    Vaaben(int typeID, std::string navn, int skade, int skadestyrke, int holdbarhed, int pris)
        : typeID(typeID), navn(navn), skade(skade), skadestyrke(skadestyrke), holdbarhed(holdbarhed), pris(pris) {}
    std::string getNavn() const { return navn; }
    int getSkade() const { return skade; }
    int getSkadestyrke() const { return skadestyrke; }
    int getHoldbarhed() const { return holdbarhed; }
    int getPris() const { return pris; }
    int getId() const { return id; }
    void setId(int newId) { id = newId; }
    int getTypeID() const { return typeID; }
    void setTypeID(int newTypeID) { typeID = newTypeID; }
    

    bool fjernholdbarhed(); // Decrease durability and check if the weapon is broken
    int tilfoejSkade(int spillerskade); // Calculate the damage dealt by the weapon

};


