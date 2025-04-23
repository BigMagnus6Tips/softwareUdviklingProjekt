#pragma once
#include <string>
#include <vector>
#include "character.h"
#include "hero.h"
#include "fjende.h"
class kamp
{
private:
    hero& spiller;
    fjende& modstander;
    
public:
    kamp();
    kamp(hero& spiller, fjende& modstander);
    ~kamp();
    void startKamp();
    void spillerAngrib();
    void fjendeAngrib();
    void visStatus();
    void slutKamp();
};


