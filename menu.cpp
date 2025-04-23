#include "include/menu.h"
#include "character.h"
#include "hero.h"
#include "fjende.h"
#include "kamp.h"
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
    chooseHero();
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
    // hero har 10 hp og 2 skade
    fjender.push_back(fjende("Goblin", 15, 3, 500));
    fjender.push_back(fjende("Ork", 25, 5, 800));
    fjender.push_back(fjende("Drage", 40, 8, 1000));
    fjender.push_back(fjende("Vampyr", 20, 4, 350));
    fjender.push_back(fjende("Zombie", 12, 2, 150));
    fjender.push_back(fjende("Trold", 30, 6, 700));
    fjender.push_back(fjende("Spøgelse", 10, 1, 200));
    fjender.push_back(fjende("Mumie", 35, 7, 900));
    fjender.push_back(fjende("Varulv", 45, 9, 1100));
    fjender.push_back(fjende("Skelet", 8, 2, 200));

}

void menu::newHero()
{
    std::string navn;
    int hp, styrke;
    std::cout << "Indtast din helts navn: ";
    std::cin >> navn;

    spiller = hero(navn, 10, 2);
}
void menu::loadHero()
{
    std::vector<hero> preloadedHeroes;
    preloadedHeroes.push_back(hero("Tim den Store", 20, 6));
    preloadedHeroes.push_back(hero("Mester Jacob", 12, 3));
    preloadedHeroes.push_back(hero("Fantino den Majestætiske", 15, 3));
    preloadedHeroes.push_back(hero("Bob fra smeden", 8, 1));
    preloadedHeroes.push_back(hero("Lille Lars", 25, 1));

    std::cout << "Vælg en forudindlæst helt:" << std::endl;
    for (size_t i = 0; i < preloadedHeroes.size(); i++)
    {
        std::cout << i + 1 << ". " << preloadedHeroes[i].getName() << std::endl;
    }
    int valg;
    std::cin >> valg;
    if (valg < 1 || valg > preloadedHeroes.size())
    {
        std::cout << "Ugyldigt valg, prøv igen." << std::endl;
        loadHero();
        return;
    }
    spiller = preloadedHeroes[valg - 1];
    std::cout << "Du har valgt " << spiller.getName() << "!" << std::endl;
    std::cout << "Liv: " << spiller.getHp() << std::endl;
    std::cout << "Styrke: " << spiller.getStyrke() << std::endl;
}

void menu::chooseHero()
{
    std::cout << "Vil du lave en ny helt (1) eller vælge en forudindlæst helt (2)?" << std::endl;
    int valg;
    std::cin >> valg;
    switch (valg)
    {
    case 1:
        newHero();
        break;
    case 2:
        loadHero();
        break;
    default:
        std::cout << "Ugyldigt valg, prøv igen." << std::endl;
        chooseHero();
        break;
    }
}