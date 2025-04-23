#pragma once
#include <string>
#include <vector>
#include "character.h"
#include "hero.h"
#include "fjende.h"
#include "kamp.h"
class menu
{
private:
    /* data */
    hero spiller;
    std::vector<fjende> fjender;

public:
    menu(/* args */);
    ~menu();
    void start();
    void visMenu();
    void vælgKamp();
    void loadFjender();
    void chooseHero();
    void newHero();
    void loadHero();


};

