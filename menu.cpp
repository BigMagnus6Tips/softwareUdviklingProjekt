#include "include/menu.h"
#include "include/character.h"
#include "include/hero.h"
#include "include/fjende.h"
#include "include/kamp.h"
#include <iostream>
#include <string>
#include <vector>


menu::menu(/* args */)
{
}

menu::~menu()
{
}

void menu::start()
{
    std::cout << "Velkommen til kampen!" << std::endl;
    loadFjender();
    visMenu();
}

void menu::visMenu()
{
    std::cout << "1. Start kamp" << std::endl;
    std::cout << "2. Afslut" << std::endl;
    int valg;
    std::cin >> valg;
    switch (valg)
    {
    case 1:
        vælgKamp();
        break;
    case 2:
        std::cout << "Farvel!" << std::endl;
        break;
    default:
        std::cout << "Ugyldigt valg, prøv igen." << std::endl;
        visMenu();
        break;
    }
}
void menu::vælgKamp()
{
    std::cout << "Vælg fjende:" << std::endl;
    for (size_t i = 0; i < fjender.size(); i++)
    {
        std::cout << i + 1 << ". " << fjender[i].getName() << std::endl;
    }
    int valg;
    std::cin >> valg;
    if (valg < 1 || valg > fjender.size())
    {
        std::cout << "Ugyldigt valg, prøv igen." << std::endl;
        vælgKamp();
        return;
    }
    fjende valgtFjende = fjender[valg - 1];
    kamp kamp(spiller, valgtFjende);
    kamp.startKamp();
}
void menu::loadFjender()
{

    // kan udbyttes med en database eller json fil
    fjender.push_back(fjende("Goblin", 50, 10, 20));
    fjender.push_back(fjende("Ork", 80, 15, 30));
    fjender.push_back(fjende("Drage", 150, 25, 50));
    fjender.push_back(fjende("Vampyr", 60, 12, 25));
    fjender.push_back(fjende("Zombie", 40, 8, 15));
    fjender.push_back(fjende("Trold", 70, 18, 35));
    fjender.push_back(fjende("Spøgelse", 30, 5, 10));
    fjender.push_back(fjende("Mumie", 90, 20, 40));
    fjender.push_back(fjende("Varulv", 110, 22, 45));
    fjender.push_back(fjende("Skelet", 20, 6, 12));

}