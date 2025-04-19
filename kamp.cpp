#include "include/kamp.h"
#include "include/character.h"
#include <iostream>
#include <string>


kamp::kamp(/* args */)
{
}

kamp::~kamp()
{
}

kamp::kamp(character& spiller, character& fjende) : spiller(spiller), fjende(fjende)
{
}

void kamp::startKamp()
{
    std::cout << "Kamp starter!" << std::endl;
    spiller.startKamp();
    fjende.startKamp();
}

void kamp::spillerAngrib()
{
    std::cout << spiller.getName() << " angriber " << fjende.getName() << "!" << std::endl;
    if (spiller.angrib(fjende) <= 0) 
    {
        slutKamp();
    }    
    
}
void kamp::fjendeAngrib()
{
    std::cout << fjende.getName() << " angriber " << spiller.getName() << "!" << std::endl;
    if (fjende.angrib(spiller)<= 0) 
    {
        slutKamp();
    }
    
}
void kamp::visStatus()
{
    std::cout << spiller.getName() << " HP: " << spiller.getHp() << std::endl;
    std::cout << fjende.getName() << " HP: " << fjende.getHp() << std::endl;
}
void kamp::slutKamp()
{
    if (spiller.getHp() <= 0)
    {
        std::cout << spiller.getName() << " er død!" << std::endl;
    }
    else if (fjende.getHp() <= 0)
    {
        std::cout << fjende.getName() << " er død!" << std::endl;
    }
    else
    {
        std::cout << "Kampen