#pragma once
#include <string>
#include <vector>
#include "Fjende.h"
#include "Hero.h"

class Grotte
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
public:
    Grotte(/* args */);
    ~Grotte();

    // Constructor
    Grotte(std::string navn, int grotteLevel, int grotteType, int grotteSize);
    void tilfojFjende(Fjende fjende) { fjender.push_back(fjende); }
    void setGrotteGuld(int guld) { grotteGuld = guld; }
    void setGrotteId(int id) { grotteId = id; }
    void setGrotteLevel(int level) { grotteLevel = level; }
    void setGrotteType(int type) { grotteType = type; }
    void setGrotteSize(int size) { grotteSize = size; }
    void setNavn(const std::string& newNavn) { navn = newNavn; }
    std::string getNavn() const { return navn; }
    int getGrotteGuld() const { return grotteGuld; }

    // For fighting
    Fjende getFjendeVed(int index) const { return fjender.at(index); }
    Fjende getForsteFjende() const { return fjender.at(0); }
    int getAntalFjender() const { return fjender.size(); }
    void VisGrotteInfo() const;
    void udfordreGrotte(Hero& spiller);
    
};


