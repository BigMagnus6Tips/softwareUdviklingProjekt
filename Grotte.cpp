#include "Grotte.h"
#include <iostream>
#include <vector>
#include <string>
#include "Fjende.h"
#include "Hero.h"
#include "Kamp.h"

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

void Grotte::udfordreGrotte(Hero& spiller)
{
    std::cout << "Du udfordrer grotten: " << navn << std::endl;
    std::cout << "Der er " << fjender.size() << " fjender i grotten." << std::endl;
    for (size_t i = 0; i < fjender.size(); i++)
    {
        std::cout << "Den " << i + 1 << ". fjende er: " << fjender[i].getName() << std::endl;

        Kamp kamp(spiller, fjender[i]);
        kamp.startKamp();
        
        if (spiller.getHp() > 0)
        {
            std::cout << "Du besejrede den " << i + 1 << ". fjende!" << std::endl;
            std::cout << "Du mangler " << fjender.size() - i - 1 << " fjender." << std::endl;
            
        }
        else 
        {
            std::cout << "Du er død!" << std::endl;
            std::cout << "Spillet er slut." << std::endl;
            return;
        }

    }

    std::cout << "Du har besejret grotten" << std::endl;
    std::cout << "Du får " << grotteGuld << " guld" << std::endl;

    return;

}
