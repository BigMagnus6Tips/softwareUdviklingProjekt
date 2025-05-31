#include "Hero.h"
#include <iostream>
#include <string>
#include <vector>
#include "Character.h"

Hero::Hero(/* args */)
{
}

// Constructor for Hero class
// Initializes the hero with a name, health, and attack power

Hero::~Hero()
{
}

// Increases the hero's level, health, and attack power
// Prints a message indicating the hero has leveled up
void Hero::levelUp(QSqlDatabase db)
{
    level++;
    setMaxHp(getMaxHp() + 2);
    setStyrke(getStyrke() + 1);
    std::cout << getName() << " er steget til niveau " << level << "!" << std::endl;

    // Update the hero's level in the database
    QSqlQuery query(db);
    query.prepare("UPDATE Hero SET level = :level, hp = :hp, styrke = :styrke WHERE heroID = :id");
    query.bindValue(":level", level);
    query.bindValue(":hp", getMaxHp());
    query.bindValue(":styrke", getStyrke());
    query.bindValue(":id", id);
    if (!query.exec())
    {
        std::cerr << "Fejl ved opdatering af helten i databasen: " << query.lastError().text().toStdString() << std::endl;
    }
}

// Prints the hero's name, level, health, strength, and experience
// Displays the current experience and maximum experience required for the next level
void Hero::printHero()
{
    std::cout << "Navn: " << getName() << std::endl;
    std::cout << "Niveau: " << level << std::endl;
    std::cout << "Liv: " << getHp() << std::endl;
    std::cout << "Styrke: " << getStyrke() << std::endl;
    std::cout << "Experience: " << experience << "/" << maxExperience * level << std::endl;
}

// Increases the hero's experience by a specified amount
// If the experience exceeds the maximum, the hero levels up
void Hero::giveExperience(int exp, QSqlDatabase db)
{
    experience += exp;
    std::cout << getName() << " har modtaget " << exp << " erfaring!" << std::endl;
    if (experience >= maxExperience * level)
    {
        levelUp(db);
        experience -= maxExperience * (level - 1); // Reset experience after leveling up
    }
    // Update the hero's experience in the database
    QSqlQuery query(db);
    query.prepare("UPDATE Hero SET xp = :xp WHERE heroID = :id");
    query.bindValue(":xp", experience);
    query.bindValue(":id", id);
    if (!query.exec())
    {
        std::cerr << "Fejl ved opdatering af helten i databasen: " << query.lastError().text().toStdString() << std::endl;
    }
}

void Hero::giveGold(int guld, QSqlDatabase db)
{
    std::cout << getName() << " har modtaget " << guld << " guld!" << std::endl;
    gold += guld;
    std::cout << "Total guld: " << gold << std::endl;

    // Update the hero's gold in the database
    QSqlQuery query(db);
    query.prepare("UPDATE Hero SET guld = :guld WHERE heroID = :id");
    query.bindValue(":guld", gold);
    query.bindValue(":id", id);
    if (!query.exec())
    {
        std::cerr << "Fejl ved opdatering af helten i databasen: " << query.lastError().text().toStdString() << std::endl;
    }
}

void Hero::giveWeapon(const Vaaben &vaaben, QSqlDatabase db)
{
    inventar.push_back(vaaben);
    std::cout << getName() << " har fået et nyt våben: " << vaaben.getNavn() << "!" << std::endl;

    // Update the HeroVaaben link in the database
    QSqlQuery query(db);
    query.prepare("INSERT INTO HeroVaaben (heroVaabenID, heroID, vaabenID, holdbarhed) VALUES (:heroVaabenID, :heroID, :vaabenID, :holdbarhed)");
    query.bindValue(":heroVaabenID", vaaben.getId()); // Assuming getId() returns a unique ID for the weapon
    query.bindValue(":heroID", id);
    query.bindValue(":vaabenID", vaaben.getId());
    query.bindValue(":holdbarhed", vaaben.getHoldbarhed()); // Assuming getHoldbarhed() returns the durability of the weapon

    if (!query.exec())
    {
        std::cerr << "Fejl ved indsættelse af våben i databasen: " << query.lastError().text().toStdString() << std::endl;
    }
}

void Hero::loadWeapons(QSqlDatabase db)
{
    QSqlQuery query(db);
    query.prepare("SELECT v.vaabenID, v.navn, v.skade, v.skadestyrke, hv.holdbarhed, v.pris FROM Vaaben v "
                  "JOIN HeroVaaben hv ON v.vaabenID = hv.vaabenID "
                  "WHERE hv.heroID = :heroID");
    query.bindValue(":heroID", id);

    if (!query.exec())
    {
        std::cerr << "Fejl ved hentning af våben fra databasen: " << query.lastError().text().toStdString() << std::endl;
        return;
    }

    while (query.next())
    {
        int vaabenId = query.value(0).toInt();
        std::string navn = query.value(1).toString().toStdString();
        int skade = query.value(2).toInt();
        int skadestyrke = query.value(3).toInt();
        int holdbarhed = query.value(4).toInt();
        int pris = query.value(5).toInt();

        Vaaben vaaben(vaabenId, navn, skade, skadestyrke, holdbarhed, pris);
        inventar.push_back(vaaben);
    }
}

int Hero::angrib(Character &target)
{

    int spillerskade = getStyrke();
    if (inventar[valgtVaaben].fjernholdbarhed())
    {
        valgtVaaben = 0; // Default to haender if the selected one is broken
    }
    
    int skade = inventar[valgtVaaben].tilfoejSkade(spillerskade);
    target.setHp(target.getHp() - skade);
    return target.getHp();
}

void Hero::startKamp()
{
    hp = maxHp;

    // allow the player to choose a weapon from the inventory for the fight
    while (true)
    {
        std::cout << "Vælg et våben fra dit inventar (0-" << inventar.size() - 1 << "): ";
        for (size_t i = 0; i < inventar.size(); ++i)
        {
            std::cout << i << ": " << inventar[i].getNavn() << " (Holdbarhed: " << inventar[i].getHoldbarhed() << ") ";
        }
        std::cout << std::endl;

        int choice;
        std::cin >> choice;

        if (choice >= 0 && choice < static_cast<int>(inventar.size()))
        {
            if (inventar[choice].getHoldbarhed() <= 0)
            {
                std::cout << "Dette våben er ødelagt. Vælg et andet våben." << std::endl;
                continue; // Skip to the next iteration if the weapon is broken
            }
            valgtVaaben = choice;
            std::cout << "Du har valgt: " << inventar[valgtVaaben].getNavn() << std::endl;
            break;
        }
        else
        {
            std::cout << "Ugyldigt valg. Prøv igen." << std::endl;
        }
    }
}