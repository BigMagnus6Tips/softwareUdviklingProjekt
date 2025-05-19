#include "Grotte.h"
#include <iostream>
#include <vector>
#include <string>

Grotte::Grotte(/* args */)
{
}

Grotte::~Grotte()
{
}

Grotte::Grotte(std::string navn, int grotteId, int grotteLevel, int grotteType, int grotteSize) : navn(navn), grotteId(grotteId), grotteLevel(grotteLevel), grotteType(grotteType), grotteSize(grotteSize)
{
    // Initialize the Grotte object with the given parameters
    this->grotteGuld = 0; // Default value for gold
}

void Grotte::VisGrotteInfo() const
{
    std::cout << "Grotte Navn: " << navn << std::endl;
    std::cout << "Grotte ID: " << grotteId << std::endl;
    std::cout << "Grotte Level: " << grotteLevel << std::endl;
    std::cout << "Grotte Type: " << (grotteType == 0 ? "Normal" : "Boss") << std::endl;
    std::cout << "Grotte Størrelse: " << (grotteSize == 0 ? "Lille" : (grotteSize == 1 ? "Medium" : "Stor")) << std::endl;
    std::cout << "Guld i Grotte: " << grotteGuld << std::endl;
}
void Grotte::setNavn(const std::string& newNavn)
{
    navn = newNavn;
}
void Grotte::setGrotteId(int id)
{
    grotteId = id;
}
void Grotte::setGrotteLevel(int level)
{
    grotteLevel = level;
}
void Grotte::setGrotteType(int type)
{
    grotteType = type;
}
void Grotte::setGrotteSize(int size)
{
    grotteSize = size;
}
void Grotte::setGrotteGuld(int guld)
{
    grotteGuld = guld;
}
void Grotte::tilfojFjende(Fjende fjende)
{
    fjender.push_back(fjende);
}
