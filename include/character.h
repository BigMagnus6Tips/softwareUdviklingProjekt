#pragma once
#include <string>
#include <vector>
class character
{
private:
    std::string name;
    int hp;
    int styrke;
    int maxHp;

public:
    character(/* args */);
    ~character();
    std::string getName() const { return name; }
    int getHp() const { return hp; }
    int getStyrke() const { return styrke; }
    void setName(const std::string& newName) { name = newName; }
    void setHp(int newHp) { hp = newHp; }
    void setStyrke(int newStyrke) { styrke = newStyrke; }
    int angrib(character& target);
    void startKamp();
};


