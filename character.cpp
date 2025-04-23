#include "include/character.h"
#include <iostream>

character::character(/* args */)
{
}

character::character(std::string name, int maxhp, int styrke)
    : name(name), maxHp(maxhp), hp(maxhp), styrke(styrke)
{
}

character::~character()
{
}

int character::angrib(character& target)
{
    target.setHp(target.getHp() - this->styrke);
    return target.getHp();
}
void character::startKamp()
{
    hp = maxHp;
}