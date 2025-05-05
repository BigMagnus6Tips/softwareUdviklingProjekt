#pragma once
#include <string>
#include <vector>
#include "Character.h"
#include "Hero.h"
#include "Fjende.h"
#include "Kamp.h"
class Menu
{
private:
    /* data */
    Hero spiller;
    std::vector<Fjende> fjender;

public:
    Menu(/* args */);
    ~Menu();
    void start();
    void visMenu();
    void vaelgKamp();
    void loadFjender();
    void vaelgHero();
    void newHero();
    void loadHero();


};

