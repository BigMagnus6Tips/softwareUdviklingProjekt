#pragma once
#include <string>
#include <vector>
#include "Character.h"
#include "Hero.h"
#include "Fjende.h"
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class Kamp
{
private:
    Hero& spiller;
    Fjende& modstander;
    QSqlDatabase db;
    int id = 0;
public:
    Kamp();
    Kamp(Hero& spiller, Fjende& modstander, QSqlDatabase db);
    ~Kamp();
    int startKamp();
    void spillerAngrib();
    void fjendeAngrib();
    void visStatus();
    void slutKamp();
};


