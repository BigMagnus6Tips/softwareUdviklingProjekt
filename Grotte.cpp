#include "Grotte.h"
#include <iostream>
#include <vector>
#include <string>
#include "Fjende.h"
#include "Hero.h"
#include "Kamp.h"

Grotte::Grotte(/* args */)
{
}

Grotte::~Grotte()
{
}

Grotte::Grotte(std::string navn, int grotteLevel, int grotteType, int grotteSize) : navn(navn), grotteId(grotteId), grotteLevel(grotteLevel), grotteType(grotteType), grotteSize(grotteSize)
{
    // Initialize the Grotte object with the given parameters
    this->grotteGuld = 0; // Default value for gold
}

void Grotte::VisGrotteInfo() const
{
    std::cout << navn << " har " << fjender.size() << " fjender." << std::endl;
    for (size_t i = 0; i < fjender.size(); i++)
    {
        std::cout << "Fjende " << i + 1 << ": " << fjender[i].getName() << std::endl;
        std::cout << "Liv: " << fjender[i].getLiv() << ", Styrke: " << fjender[i].getStyrke() << std::endl;
    }
    std::cout << "Grotte niveau: " << grotteLevel << std::endl;
    std::cout << "Præmie våben: " << praemie.getNavn() << std::endl;
    std::cout << "Guld i grotten: " << grotteGuld << std::endl;
}

void Grotte::udfordreGrotte(Hero &spiller, QSqlDatabase db)
{
    std::cout << "Du udfordrer grotten: " << navn << std::endl;

    

    // find the highest id of the grotte in the database
    QSqlQuery lastQueryGrotte(db);
    lastQueryGrotte.exec("SELECT MAX(grotteID) AS grotteID FROM Grotte");
    int grotteId = 0;
    if (lastQueryGrotte.next())
    {
        grotteId = lastQueryGrotte.value("grotteID").toInt();
    }
    else
    {
        std::cerr << "Error fetching last Grotte ID: " << lastQueryGrotte.lastError().text().toStdString() << std::endl;
        return;
    }

    VisGrotteInfo();

    // insert the Grotte into the database
    QSqlQuery query(db);
    query.prepare("INSERT INTO Grotte (grotteID, navn, svaerhedsgrad, guld) VALUES (:grotteID, :navn, :level, :guld)");
    query.bindValue(":grotteID", grotteId + 1);
    query.bindValue(":navn", QString::fromStdString(navn));
    query.bindValue(":level", grotteLevel);
    query.bindValue(":guld", grotteGuld);
    if (!query.exec())
    {
        std::cerr << "Error inserting Grotte into database: " << query.lastError().text().toStdString() << std::endl;
        return;
    }

    // find the highest id of the grotteKamp in the database
    QSqlQuery lastQueryGrotteKamp(db);
    lastQueryGrotteKamp.exec("SELECT MAX(grotteKampID) AS grotteKampID FROM GrotteKamp");
    int grotteKampID = 0;
    if (lastQueryGrotteKamp.next())
    {
        grotteKampID = lastQueryGrotteKamp.value("grotteKampID").toInt();
    }
    else
    {
        std::cerr << "Error fetching last GrotteKamp ID: " << lastQueryGrotteKamp.lastError().text().toStdString() << std::endl;
        return;
    }

    for (size_t i = 0; i < fjender.size(); i++)
    {
        std::cout << "Den " << i + 1 << ". fjende er: " << fjender[i].getName() << std::endl;

        std::cout << "er du klar til at kæmpe? (tryk): " << std::endl;
        char tryk;
        std::cin >> tryk;

        Kamp kamp(spiller, fjender[i], db);
        int kampID = kamp.startKamp();
        if (kampID > 0)
        {
            std::cout << "KampID: " << kampID << std::endl;
            // insert grotteKamp into the database
            QSqlQuery grotteKampQuery(db);
            grotteKampQuery.prepare("INSERT INTO GrotteKamp (grotteKampID, grotteID, kampID) VALUES (:grotteKampID, :grotteID, :kampID)");
            int ID = grotteKampID + i + 1;
            grotteKampQuery.bindValue(":grotteKampID", ID); // Assuming grotteKampID is auto-incremented
            grotteKampQuery.bindValue(":grotteID", grotteId);
            grotteKampQuery.bindValue(":kampID", kampID);
            if (!grotteKampQuery.exec())
            {
                std::cerr << "Error inserting GrotteKamp into database: " << grotteKampQuery.lastError().text().toStdString() << std::endl;
                return;
            }
        }

        if (spiller.getHp() > 0)
        {
            std::cout << "Du besejrede den " << i + 1 << ". fjende!" << std::endl;
            std::cout << "Du mangler " << fjender.size() - i - 1 << " fjender." << std::endl;
        }
        else
        {
            std::cout << "Du er død!" << std::endl;
            std::cout << "Spillet er slut." << std::endl;
            return;
        }
    }

    std::cout << "Du har besejret grotten" << std::endl;
    std::cout << "Du får " << grotteGuld << " guld" << std::endl;
    spiller.giveGold(grotteGuld, db);
    spiller.giveWeapon(praemie, db);
    return;
}
