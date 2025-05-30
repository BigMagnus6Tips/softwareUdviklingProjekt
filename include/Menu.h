#pragma once
#include <string>
#include <vector>
#include "Character.h"
#include "Hero.h"
#include "Fjende.h"
#include "Kamp.h"
#include "Grotte.h"
#include "GrotteFabrik.h"
#include "Vaaben.h"
#include "VaabenFabrik.h"
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class Menu
{
private:
    QSqlDatabase db; // Database connection
    Hero spiller;
    std::vector<Fjende> fjender;
    GrotteFabrik grotteFabrik;
    VaabenFabrik vaabenFabrik = VaabenFabrik(db); // Initialize the weapon factory with the database connection

    /*
    Vis ”hero”s i alfabetisk rækkefølge
4
• Vis hvor mange monstre vær ”hero” har besejret
• For en given ”hero” vis hvor mange monstre vært v˚aben har besejret
• For hvert v˚aben vis hvilken ”hero” der har besejret flest monstre med
dette v˚aben
    */

    void analyserVisHeroer();
    void analyserHeroVedIndex(int index);
    void analyserVisVaaben();
    void analyserVaaben(int index);
    void analyserheroVaaben();


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
    void udfordreGrotte();

    void analyserDB();
};
