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
    vaabenFabrik.loadVaabenSkabeloner(); // Load weapon templates from the database
    grotteFabrik = GrotteFabrik(vaabenFabrik);
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
    vaelganalyser();
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
        Kamp kamp(spiller, valgtFjende, db);
        kamp.startKamp();
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

    // check databasen for ledigt id
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
    insertQuery.prepare("INSERT INTO Hero (heroID, navn, hp, styrke, level, xp, guld) VALUES (?, ?, ?, ?, ?, ?, ?)");
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

    spiller = Hero(id, navn, 10, 2, 1, 0, 1000);                    // Create a new hero with default values
    spiller.giveWeapon(vaabenFabrik.bygVaabenEfterSkabelon(1), db); // Give the hero a weapon
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
        std::string navn = query.value("navn").toString().toStdString();
        int liv = query.value("hp").toInt();
        int styrke = query.value("styrke").toInt();
        int level = query.value("level").toInt();
        int experience = query.value("xp").toInt();
        int guld = query.value("guld").toInt();

        Hero hero(id, navn, liv, styrke, level, experience, 1000, guld);
        // Load the hero's weapons
        hero.loadWeapons(db);

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
        std::cin.clear();                                                   // Clear the input stream
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
        std::cout << "Ugyldigt valg, prøv igen." << std::endl;
        vaelgHero(); // Recursively call to allow the user to try again
        return;      // Exit the current function to prevent further execution
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

// Analyserer databasen for at vise helte, fjender og våben
void Menu::analyserDB()
{
    std::cout << "Analyserer databasen..." << std::endl;
    int valg;
    std::cout << "Vælg en analyse:" << std::endl;
    std::cout << "1. Analyser helte og vis dem i alfabestisk rækkefølge" << std::endl;
    std::cout << "2. Analyser Våben og vis dem" << std::endl;
    std::cout << "3. Forlad til hovedmenu" << std::endl;
    std::cout << "Indtast dit valg (1-3): ";

    // Check if input is valid
    std::cin >> valg;
    if (std::cin.fail() || valg < 1 || valg > 3)
    {
        std::cin.clear();                                                   // Clear the input stream
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
        std::cout << "Ugyldigt valg, prøv igen." << std::endl;
        analyserDB(); // Recursively call to allow the user to try again
        return;       // Exit the current function to prevent further execution
    }

    switch (valg)
    {
    case 1:
        analyserVisHeroer();
        break;
    case 2:
        analyserVisVaaben();
        break;
    case 3:
        std::cout << "Start spillet..." << std::endl;
        return; // Exit the function to return to the main menu
    default:
        std::cout << "Ugyldigt valg, prøv igen." << std::endl;
        analyserDB();
        break;
    }
}

// Displays heroes in alphabetical order with an id and the number of monsters defeated by each hero, then gives the option to view a specific hero's details
void Menu::analyserVisHeroer()
{
    QSqlQuery query(db);
    if (!query.exec(R"(
    SELECT Hero.heroID, Hero.navn, COUNT(Kamp.kampID) AS antalBesejredeMonstre
    FROM Hero
    LEFT JOIN Kamp ON Hero.heroID = Kamp.heroID
    GROUP BY Hero.heroID, Hero.navn
    ORDER BY Hero.navn ASC
    )"))
    {
        std::cerr << "Kunne ikke hente helte: " << query.lastError().text().toStdString() << std::endl;
        return;
    }

    std::cout << "Helte i alfabestisk rækkefølge:" << std::endl;
    std::cout << "ID\tNavn\tAntal besejrede monstre" << std::endl;
    while (query.next())
    {
        int id = query.value("heroID").toInt();
        std::string navn = query.value("navn").toString().toStdString();
        int antalBesejredeMonstre = query.value("antalBesejredeMonstre").toInt();

        std::cout << id << "\t" << navn << "\t" << antalBesejredeMonstre << std::endl;
    }
    std::cout << "Vælg en helt for at se detaljer (indtast ID): ";
    int id;
    std::cin >> id;
    if (std::cin.fail())
    {
        std::cin.clear();                                                   // Clear the input stream
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
        std::cout << "Ugyldigt ID, prøv igen." << std::endl;
        analyserVisHeroer(); // Recursively call to allow the user to try again
        return;              // Exit the current function to prevent further execution
    }
    QSqlQuery heroQuery(db);
    heroQuery.prepare("SELECT * FROM Hero WHERE heroID = ?");
    heroQuery.addBindValue(id);
    if (!heroQuery.exec())
    {
        std::cerr << "Kunne ikke hente helt: " << heroQuery.lastError().text().toStdString() << std::endl;
        return;
    }
    if (heroQuery.next())
    {
        std::string navn = heroQuery.value("navn").toString().toStdString();
        int hp = heroQuery.value("hp").toInt();
        int styrke = heroQuery.value("styrke").toInt();
        int level = heroQuery.value("level").toInt();
        int experience = heroQuery.value("xp").toInt();
        int guld = heroQuery.value("guld").toInt();

        std::cout << "Detaljer for helt " << navn << ":" << std::endl;
        std::cout << "HP: " << hp << std::endl;
        std::cout << "Styrke: " << styrke << std::endl;
        std::cout << "Level: " << level << std::endl;
        std::cout << "Experience: " << experience << std::endl;
        std::cout << "Guld: " << guld << std::endl;
    }
    else
    {
        std::cout << "Ingen helt fundet med ID: " << id << std::endl;
    }

    std::cout << "Vil du se våben brugt af denne helt? (1 for ja, 2 for nej): ";
    int valg;
    std::cin >> valg;
    if (std::cin.fail() || (valg != 1 && valg != 2))
    {
        std::cin.clear();                                                   // Clear the input stream
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
        std::cout << "Ugyldigt valg, prøv igen." << std::endl;
        analyserVisHeroer(); // Recursively call to allow the user to try again
        return;              // Exit the current function to prevent further execution
    }
    if (valg == 1)
    {
        // Display weapons used by the hero
        QSqlQuery weaponQuery(db);
        weaponQuery.prepare(R"(
        SELECT 
            Vaaben.vaabenID,
            Vaaben.navn,
            COUNT(Kamp.kampID) AS antalBesejredeMonstre
        FROM 
            Vaaben
        JOIN 
            HeroVaaben ON Vaaben.vaabenID = HeroVaaben.vaabenID
        LEFT JOIN 
            Kamp ON Kamp.heroVaabenID = HeroVaaben.heroVaabenID
        WHERE 
            HeroVaaben.heroID = ?
        GROUP BY 
            Vaaben.vaabenID, Vaaben.navn
        ORDER BY 
            Vaaben.navn ASC
        )");

        weaponQuery.addBindValue(id);
        if (!weaponQuery.exec())
        {
            std::cerr << "Kunne ikke hente våben: " << weaponQuery.lastError().text().toStdString() << std::endl;
            return;
        }
        std::cout << "Våben brugt af denne helt:" << std::endl;
        std::cout << "ID\tNavn\tAntal besejrede monstre" << std::endl;
        while (weaponQuery.next())
        {
            int vaabenId = weaponQuery.value("vaabenID").toInt();
            std::string vaabenNavn = weaponQuery.value("navn").toString().toStdString();
            int antalBesejredeMonstre = weaponQuery.value("antalBesejredeMonstre").toInt();

            std::cout << vaabenId << "\t" << vaabenNavn << "\t" << antalBesejredeMonstre << std::endl;
        }
    }

    std::cout << "Tryk på Enter for at fortsætte..." << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the newline character left in the input buffer
    std::cin.get();                                                     // Wait for the user to press Enter
    analyserDB();                                                       // Return to the main analysis menu
}

// Displays weapons and allows the user to view details of a specific weapon

void Menu::analyserVisVaaben()
{
    QSqlQuery query(db);
    query.prepare(R"(
        WITH KillsPerWeaponHero AS (
            SELECT 
                HeroVaaben.vaabenID,
                Hero.navn AS heroNavn,
                COUNT(Kamp.kampID) AS killCount,
                ROW_NUMBER() OVER (
                    PARTITION BY HeroVaaben.vaabenID 
                    ORDER BY COUNT(Kamp.kampID) DESC
                ) AS rank
            FROM HeroVaaben
            LEFT JOIN Kamp ON Kamp.heroVaabenID = HeroVaaben.heroVaabenID
            LEFT JOIN Hero ON HeroVaaben.heroID = Hero.heroID
            GROUP BY HeroVaaben.vaabenID, HeroVaaben.heroID
        ),
        TopUserPerWeapon AS (
            SELECT 
                vaabenID,
                heroNavn,
                killCount
            FROM KillsPerWeaponHero
            WHERE rank = 1
        )
        SELECT 
            Vaaben.vaabenID,
            Vaaben.navn AS vaabenNavn,
            Vaaben.skade,
            Vaaben.skadestyrke,
            Vaaben.pris,
            COALESCE(TopUserPerWeapon.heroNavn, 'Ingen bruger') AS heroNavn,
            COALESCE(TopUserPerWeapon.killCount, 0) AS killCount
        FROM Vaaben
        LEFT JOIN TopUserPerWeapon ON Vaaben.vaabenID = TopUserPerWeapon.vaabenID
        ORDER BY Vaaben.vaabenID ASC;
    )");

    if (!query.exec())
    {
        std::cerr << "Kunne ikke hente våben: " << query.lastError().text().toStdString() << std::endl;
        return;
    }

    std::cout << "Våben:" << std::endl;
    std::cout << "ID\tNavn\tSkade\tStyrke\tPris\tHyppigst anvendt af:" << std::endl;
    while (query.next())
    {
        int id = query.value("vaabenID").toInt();
        std::string navn = query.value("vaabenNavn").toString().toStdString();
        int skade = query.value("skade").toInt();
        int styrke = query.value("skadestyrke").toInt();
        int pris = query.value("pris").toInt();
        std::string heroNavn = query.value("heroNavn").toString().toStdString();
        int kills = query.value("killCount").toInt();

        std::cout << id << "\t" << navn << "\t" << skade << "\t" << styrke << "\t" << pris
                  << "\t" << heroNavn << " (" << kills << " kills)" << std::endl;
    }

}

void Menu::vaelganalyser()
{
    std::cout << "Vil du analysere databasen? (1 for ja, 2 for nej): ";
    int valg;
    std::cin >> valg;
    if (std::cin.fail() || (valg != 1 && valg != 2))
    {
        std::cin.clear();                                                   // Clear the input stream
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
        std::cout << "Ugyldigt valg, prøv igen." << std::endl;
        vaelganalyser(); // Recursively call to allow the user to try again
        return;          // Exit the current function to prevent further execution
    }
    if (valg == 1)
    {
        analyserDB();
    }
}