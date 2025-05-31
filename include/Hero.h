#pragma once
#include <string>
#include <vector>
#include "Character.h"
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "Vaaben.h"

class Hero : public Character
{
private:
    int level;
    int experience;
    int maxExperience;
    int gold = 0; // Initialize gold to 0
    std::vector<Vaaben> inventar; // Vector to hold the hero's weapons
    int valgtVaaben; // The weapon currently selected by the hero
public:
    Hero(/* args */);
    Hero(int id, std::string name, int health, int attackPower, int level, int experience, int maxExperience, int gold = 0)
        : Character(id, name, health, attackPower), level(level), experience(experience), maxExperience(maxExperience), gold(gold) {}
    ~Hero();
    void levelUp(QSqlDatabase db);
    void printHero();
    void giveExperience(int exp, QSqlDatabase db);
    int getLevel() const { return level; }
    void giveGold(int guld, QSqlDatabase db);
    void giveWeapon(const Vaaben &vaaben, QSqlDatabase db);
    Vaaben getWeapon(int index) const { return inventar.at(index); }
    void loadWeapons(QSqlDatabase db);
    int angrib(Character &target) override;
    std::vector<Vaaben> getInventar() const { return inventar; }
    void startKamp() override;
};


