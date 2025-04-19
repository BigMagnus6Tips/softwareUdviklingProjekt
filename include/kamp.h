#pragma once
#include <string>
#include <vector>
#include "character.h"
class kamp
{
private:
    character& spiller;
    character& fjende;
    
public:
    kamp();
    kamp(character& spiller, character& fjende);
    ~kamp();
    void startKamp();
    void spillerAngrib();
    void fjendeAngrib();
    void visStatus();
    void slutKamp();
};


