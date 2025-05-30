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
    query.prepare("UPDATE Hero SET level = :level, hp = :hp, styrke = :styrke WHERE id = :id");
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
        experience -= maxExperience * (level-1); // Reset experience after leveling up
    }
    // Update the hero's experience in the database
    QSqlQuery query(db);
    query.prepare("UPDATE Hero SET xp = :xp WHERE id = :id");
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
    query.prepare("UPDATE Hero SET guld = :guld WHERE id = :id");
    query.bindValue(":guld", gold);
    query.bindValue(":id", id);
    if (!query.exec())
    {
        std::cerr << "Fejl ved opdatering af helten i databasen: " << query.lastError().text().toStdString() << std::endl;
    }
}