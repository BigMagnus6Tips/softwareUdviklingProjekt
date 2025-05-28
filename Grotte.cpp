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

Grotte::Grotte(std::string navn, int grotteLevel, int grotteType, int grotteSize) : navn(navn), grotteId(grotteId), grotteLevel(grotteLevel), grotteType(grotteType), grotteSize(grotteSize)
{
    // Initialize the Grotte object with the given parameters
    this->grotteGuld = 0; // Default value for gold
}

void Grotte::VisGrotteInfo() const
{
    std::cout << navn << " har " << fjender.size() << " fjender." << std::endl;
    for (size_t i = 0; i < fjender.size(); i++)
    {
        std::cout << "Fjende " << i + 1 << ": " << fjender[i].getName() << std::endl;
        std::cout << "Liv: " << fjender[i].getLiv() << ", Styrke: " << fjender[i].getStyrke() << std::endl;
    }
    
}

void Grotte::udfordreGrotte(Hero &spiller)
{
    std::cout << "Du udfordrer grotten: " << navn << std::endl;

    VisGrotteInfo();


    for (size_t i = 0; i < fjender.size(); i++)
    {
        std::cout << "Den " << i + 1 << ". fjende er: " << fjender[i].getName() << std::endl;

        std::cout << "er du klar til at kæmpe? (tryk): " << std::endl;
        char tryk;
        std::cin >> tryk;


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
    spiller.giveGold(grotteGuld);
    return;
}
