#include "VaabenFabrik.h"


void VaabenFabrik::loadVaabenSkabeloner()
{
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Vaaben");
    
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
            query.value("id").toInt(),
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
        if (skabelon.getId() == id)
        {
            // Create a new weapon based on the template
            Vaaben nytVaaben = skabelon;
            return nytVaaben; // Return the new weapon
        }
    }
    
    std::cerr << "Våben med ID " << id << " ikke fundet." << std::endl;
    return Vaaben(); // Return an empty weapon if not found
}