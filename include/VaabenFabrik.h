#pragma once
#include <string>
#include <vector>
#include "Vaaben.h"
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>


class VaabenFabrik
{
private:
    QSqlDatabase db; // Database connection
    std::vector<Vaaben> vaabenSkabeloner; // Vector to hold weapon templates
public:
    VaabenFabrik(QSqlDatabase database) : db(database) {}
    ~VaabenFabrik() {}
    // Loads weapon templates from the database
    void loadVaabenSkabeloner();


    // Builds a random weapon based on the player's level
    Vaaben bygVaabenEfterSkabelon(int id);

};