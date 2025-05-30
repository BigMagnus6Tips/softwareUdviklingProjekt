#pragma once
#include <string>
#include <vector>
#include "Character.h"
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class Hero : public Character
{
private:
    int level;
    int experience;
    int maxExperience;
    int gold = 0; // Initialize gold to 0
    
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
};


