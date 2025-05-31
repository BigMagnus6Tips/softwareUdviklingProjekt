#include "VaabenFabrik.h"


void VaabenFabrik::loadVaabenSkabeloner()
{
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Vaaben ORDER BY VaabenID ASC"); 
    
    if (!query.exec())
    {
        std::cerr << "Fejl ved hentning af våben fra databasen: " << query.lastError().text().toStdString() << std::endl;
        return; // Exit if there's an error
    }
    
    vaabenSkabeloner.clear(); // Clear existing templates
    
    while (query.next())
    {
        // Create a weapon object from the database record
        Vaaben vaaben(
            query.value("VaabenID").toInt(),
            query.value("navn").toString().toStdString(),
            query.value("skade").toInt(),
            query.value("skadestyrke").toInt(),
            query.value("holdbarhed").toInt(),
            query.value("pris").toInt()
        );
        
        vaabenSkabeloner.push_back(vaaben); // Add to the vector of templates
    }
}

Vaaben VaabenFabrik::bygVaabenEfterSkabelon(int id)
{
    // Find the weapon template by ID
    for (const Vaaben &skabelon : vaabenSkabeloner)
    {
        if (skabelon.getTypeID() == id)
        {
            // Create a new weapon based on the template
            Vaaben nytVaaben = skabelon;
            nytVaaben.setId(0); // Reset ID for the new weapon instance

            // search for the highest existing ID in the database
            QSqlQuery query(db);
            query.prepare("SELECT MAX(HeroVaabenID) FROM HeroVaaben");
            if (!query.exec())
            {
                std::cerr << "Fejl ved hentning af højeste HeroVaabenID: " << query.lastError().text().toStdString() << std::endl;
                return Vaaben(); // Return an empty weapon if there's an error
            }
            int maxId = 0;
            if (query.next())
            {
                maxId = query.value(0).toInt();
            }

            nytVaaben.setId(maxId + 1); // Set a new ID for the weapon

            return nytVaaben; // Return the new weapon
        }
    }
    
    std::cerr << "Våben med ID " << id << " ikke fundet." << std::endl;
    return Vaaben(); // Return an empty weapon if not found
}