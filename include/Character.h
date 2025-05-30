#pragma once
#include <string>
#include <vector>
class Character
{
protected:
    std::string name;
    int hp;
    int styrke;
    int maxHp;
    int id;

public:
    Character(/* args */);
    Character(int id, std::string name, int maxhp, int styrke);
    ~Character();
    std::string getName() const { return name; }
    int getHp() const { return hp; }
    int getMaxHp() const { return maxHp; }
    int getStyrke() const { return styrke; }
    int getId() const { return id; }
    void setName(const std::string &newName) { name = newName; }
    void setHp(int newHp) { hp = newHp; }
    void setMaxHp(int newMaxHp) { maxHp = newMaxHp; }
    void setStyrke(int newStyrke) { styrke = newStyrke; }
    int angrib(Character &target);
    void startKamp();
};
