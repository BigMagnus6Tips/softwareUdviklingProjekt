#pragma once
#include <string>
#include <vector>
#include "Character.h"
#include "Hero.h"
#include "Fjende.h"
class Kamp
{
private:
    Hero& spiller;
    Fjende& modstander;
    
public:
    Kamp();
    Kamp(Hero& spiller, Fjende& modstander);
    ~Kamp();
    void startKamp();
    void spillerAngrib();
    void fjendeAngrib();
    void visStatus();
    void slutKamp();
};


