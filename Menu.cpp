#include "Menu.h"
#include "Character.h"
#include "Hero.h"
#include "Fjende.h"
#include "Kamp.h"
#include "Grotte.h"
#include "GrotteFabrik.h"
#include <iostream>
#include <string>
#include <vector>


// Constructor for menu class
Menu::Menu(/* args */)
{
}

Menu::~Menu()
{
}

// Starts the game by loading enemies, choosing a hero, and displaying the menu
// Prints a welcome message
void Menu::start()
{
    std::cout << "Velkommen til eventyret!" << std::endl;
    loadFjender();
    vaelgHero();
    visMenu();
}

// Displays the menu options for the player
// Allows the player to start a battle or exit the game
void Menu::visMenu()
{
    while (spiller.getHp() > 0)
    {
        std::cout << "Vælg en mulighed:" << std::endl;
        std::cout << "1. Start kamp" << std::endl;
        std::cout << "2. Udfordre en grotte" << std::endl;
        std::cout << "3. Afslut" << std::endl;
        int valg;
        std::cin >> valg;
        switch (valg)
        {
        case 1:
            vaelgKamp();
            break;
        case 2:
            udfordreGrotte();
            break;
        case 3:
            std::cout << "Farvel!" << std::endl;
            return;
        default:
            std::cout << "Ugyldigt valg, prøv igen." << std::endl;
            break;
        }
    }
    std::cout << "Du er død! Spillet er slut." << std::endl;
    
}

// allows the player to chose an enemy to fight
// the player has to choose an enemy
void Menu::vaelgKamp()
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
        vaelgKamp();
        return;
    }
    Fjende valgtFjende = fjender[valg - 1];
    Kamp kamp(spiller, valgtFjende);
    kamp.startKamp();
}

// loads the enemies
void Menu::loadFjender()
{

    // kan udbyttes med en database eller json fil
    // hero har 10 hp og 2 skade
    fjender.push_back(Fjende("Goblin", 15, 3, 500));
    fjender.push_back(Fjende("Ork", 25, 5, 800));
    fjender.push_back(Fjende("Drage", 40, 8, 1000));
    fjender.push_back(Fjende("Vampyr", 20, 4, 350));
    fjender.push_back(Fjende("Zombie", 12, 2, 150));
    fjender.push_back(Fjende("Trold", 30, 6, 700));
    fjender.push_back(Fjende("Spøgelse", 10, 1, 200));
    fjender.push_back(Fjende("Mumie", 35, 7, 900));
    fjender.push_back(Fjende("Varulv", 45, 9, 1100));
    fjender.push_back(Fjende("Skelet", 8, 2, 200));

}

// creates a new Hero
// the player has to enter a name
void Menu::newHero()
{
    std::string navn;
    int hp, styrke;
    std::cout << "Indtast din helts navn: ";
    std::cin >> navn;

    spiller = Hero(navn, 10, 2);
}

// loads a preloaded hero
// the player has to choose a hero from a list
void Menu::loadHero()
{
    std::vector<Hero> preloadedHeroes;
    preloadedHeroes.push_back(Hero("Tim den Store", 20, 6));
    preloadedHeroes.push_back(Hero("Mester Jacob", 12, 3));
    preloadedHeroes.push_back(Hero("Fantino den Majestætiske", 15, 3));
    preloadedHeroes.push_back(Hero("Bob fra smeden", 8, 1));
    preloadedHeroes.push_back(Hero("Lille Lars", 25, 1));

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

// allows the player to choose between creating a new hero or loading a preloaded hero
void Menu::vaelgHero()
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
        vaelgHero();
        break;
    }
}

void Menu::udfordreGrotte()
{
    std::cout << "Vælg en grotte:" << std::endl;
    Grotte grotte1 = grotteFabrik.bygTilfældigGrotte(spiller.getLevel(), 1, 0, fjender);



}