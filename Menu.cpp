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
#include <limits>

// Constructor for menu class
Menu::Menu(/* args */)
{
    // Initialize the database connection
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("projectDatabase.db");

    if (!db.open())
    {
        std::cerr << "Kunne ikke åbne databasen: " << db.lastError().text().toStdString() << std::endl;
        return;
    }

    // Initialize the GrotteFabrik
    grotteFabrik = GrotteFabrik();
}

Menu::~Menu()
{
    // Close the database connection
    if (db.isOpen())
    {
        db.close();
    }
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

        // Check if input is valid
        if (std::cin.fail() || valg < 1 || valg > 3)
        {
            std::cin.clear();                                                   // Clear the input stream
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
            std::cout << "Ugyldigt valg, prøv igen." << std::endl;
            continue; // Skip to the next iteration of the loop
        }

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

    while (true)
    {

        // Check if input is valid
        if (std::cin.fail() || valg < 1 || valg > 3)
        {
            std::cin.clear();                                                   // Clear the input stream
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
            std::cout << "Ugyldigt valg, prøv igen." << std::endl;
            continue; // Skip to the next iteration of the loop
        }

        if (valg < 1 || valg > fjender.size())
        {
            std::cout << "Ugyldigt valg, prøv igen." << std::endl;
            vaelgKamp();
            return;
        }
        Fjende valgtFjende = fjender[valg - 1];
        Kamp kamp(spiller, valgtFjende);
        kamp.startKamp(db);
        return;
    }
}

// loads the enemies
void Menu::loadFjender()
{

    // Loader fjender fra databasen
    fjender.clear(); // tømmer fjender vektoren
    QSqlQuery query(db);
    if (!query.exec("SELECT * FROM fjende"))
    {
        std::cerr << "Kunne ikke hente fjender: " << query.lastError().text().toStdString() << std::endl;
        return;
    }

    while (query.next())
    {
        int id = query.value("fjendeID").toInt();
        std::string navn = query.value("navn").toString().toStdString();
        int liv = query.value("hp").toInt();
        int styrke = query.value("styrke").toInt();
        int experienceGiven = query.value("xpGivet").toInt();

        Fjende fjende(id, navn, liv, styrke, experienceGiven);
        fjender.push_back(fjende);
    }
    


}

// creates a new Hero
// the player has to enter a name
void Menu::newHero()
{
    std::string navn;
    int hp, styrke;
    std::cout << "Indtast din helts navn: ";
    std::cin >> navn;

    //check databasen for ledigt id
    QSqlQuery query(db);
    if (!query.exec("SELECT MAX(heroID) FROM Hero"))
    {
        std::cerr << "Kunne ikke hente ledigt id: " << query.lastError().text().toStdString() << std::endl;
        return;
    }
    int id = 1; // Default id
    if (query.next())
    {
        id = query.value(0).toInt() + 1; // Get the next available id
    }

    // add the new hero to the database
    QSqlQuery insertQuery(db);
    insertQuery.prepare("INSERT INTO Hero (heroID, name, hp, styrke, level, xp, guld) VALUES (?, ?, ?, ?, ?, ?, ?)");
    insertQuery.addBindValue(id);
    insertQuery.addBindValue(QString::fromStdString(navn));
    insertQuery.addBindValue(10); // Default hp
    insertQuery.addBindValue(2);  // Default styrke
    insertQuery.addBindValue(1);  // Default level
    insertQuery.addBindValue(0);  // Default experience
    insertQuery.addBindValue(0);  // Default gold
    if (!insertQuery.exec())
    {
        std::cerr << "Kunne ikke indsætte ny helt: " << insertQuery.lastError().text().toStdString() << std::endl;
        return;
    }

    spiller = Hero(id, navn, 10, 2, 1, 0, 1000); // Create a new hero with default values
}

// loads a preloaded hero
// the player has to choose a hero from a list
void Menu::loadHero()
{
    std::vector<Hero> preloadedHeroes;
    // Load preloaded heroes from the database
    QSqlQuery query(db);
    if (!query.exec("SELECT * FROM Hero"))
    {
        std::cerr << "Kunne ikke hente forudindlæste helte: " << query.lastError().text().toStdString() << std::endl;
        return;
    }
    while (query.next())
    {
        int id = query.value("heroID").toInt();
        std::string navn = query.value("name").toString().toStdString();
        int liv = query.value("hp").toInt();
        int styrke = query.value("styrke").toInt();
        int level = query.value("level").toInt();
        int experience = query.value("xp").toInt();
        int guld = query.value("guld").toInt();

        Hero hero(id, navn, liv, styrke, level, experience, 1000, guld);
        preloadedHeroes.push_back(hero);
    }

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
    // Check if input is valid
    if (std::cin.fail() || valg < 1 || valg > 3)
    {
        std::cin.clear(); // Clear the input stream
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
        std::cout << "Ugyldigt valg, prøv igen." << std::endl;
        vaelgHero(); // Recursively call to allow the user to try again
        return; // Exit the current function to prevent further execution
    }
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
    Grotte grotte1 = grotteFabrik.bygTilfældigGrotte(spiller.getLevel(), 0, 1, fjender);
    Grotte grotte2 = grotteFabrik.bygTilfældigGrotte(spiller.getLevel(), 0, 3, fjender);
    Grotte grotte3 = grotteFabrik.bygTilfældigGrotte(spiller.getLevel(), 0, 6, fjender);
    std::cout << "1. " << grotte1.getNavn() << " (" << grotte1.getGrotteGuld() << " guld)" << std::endl;
    std::cout << "2. " << grotte2.getNavn() << " (" << grotte2.getGrotteGuld() << " guld)" << std::endl;
    std::cout << "3. " << grotte3.getNavn() << " (" << grotte3.getGrotteGuld() << " guld)" << std::endl;
    int valg;
    std::cin >> valg;
    Grotte valgtGrotte;
    while (valg < 1 || valg > 3)
    {
        std::cin.clear();                                                   // Clear the input stream
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
        std::cout << "Vælg en gyldig grotte (1-3): ";
        valg = 0; // Reset valg to ensure it is re-entered
        std::cin >> valg;
    }
    switch (valg)
    {
    case 1:
        valgtGrotte = grotte1;
        break;
    case 2:
        valgtGrotte = grotte2;
        break;
    case 3:
        valgtGrotte = grotte3;
        break;
    default:
        std::cout << "Ugyldigt valg, prøv igen." << std::endl;
        udfordreGrotte();
        return;
    }

    valgtGrotte.udfordreGrotte(spiller, db);
}