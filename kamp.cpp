#include "include/kamp.h"
#include "include/character.h"
#include "include/hero.h"
#include "include/fjende.h"
#include <iostream>
#include <string>




kamp::~kamp()
{
}

kamp::kamp(hero& spiller, fjende& modstander) : spiller(spiller), modstander(modstander)
{
}

void kamp::startKamp()
{
    std::cout << "Kamp starter!" << std::endl;
    spiller.startKamp();
    modstander.startKamp();

    while (spiller.getHp() > 0 && modstander.getHp() > 0)
    {
        std::cout << "Din tur!" << std::endl;
        visStatus();
        spillerAngrib();
        if (modstander.getHp() <= 0) 
        {
            break;
        }
        std::cout << "Fjendens tur!" << std::endl;
        visStatus();
        fjendeAngrib();
    }
    
}

void kamp::spillerAngrib()
{
    std::cout << spiller.getName() << " angriber " << modstander.getName() << "!" << std::endl;
    if (spiller.angrib(modstander) <= 0) 
    {
        slutKamp();
    }    
    
}
void kamp::fjendeAngrib()
{
    std::cout << modstander.getName() << " angriber " << spiller.getName() << "!" << std::endl;
    if (modstander.angrib(spiller)<= 0) 
    {
        slutKamp();
    }
    
}
void kamp::visStatus()
{
    std::cout << spiller.getName() << " HP: " << spiller.getHp() << std::endl;
    std::cout << modstander.getName() << " HP: " << modstander.getHp() << std::endl;
}
void kamp::slutKamp()
{
    if (spiller.getHp() <= 0)
    {
        std::cout << spiller.getName() << " er død!" << std::endl;
        
    }
    else if (modstander.getHp() <= 0)
    {
        std::cout << modstander.getName() << " er død!" << std::endl;
        std::cout << spiller.getName() << " vinder kampen!" << std::endl;
        std::cout << "Du får " << modstander.getExperienceGiven() << " XP!" << std::endl;
        spiller.giveExperience(modstander.getExperienceGiven());
        spiller.printHero();
    }

    
}