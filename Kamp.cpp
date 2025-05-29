#include "Kamp.h"
#include "Character.h"
#include "Hero.h"
#include "Fjende.h"
#include <iostream>
#include <string>




Kamp::~Kamp()
{
}

// Constructor for the Kamp class
// Initializes the player and enemy characters
Kamp::Kamp(Hero& spiller, Fjende& modstander) : spiller(spiller), modstander(modstander)
{
}

// Starts the battle between the player and the enemy
// Displays a message indicating the battle has started
// Player and enemy take turns attacking each other
// The battle continues until one of them is dead
void Kamp::startKamp(QSqlDatabase db)
{
    std::cout << "Kamp starter!" << std::endl;
    spiller.startKamp();
    modstander.startKamp();

    while (spiller.getHp() > 0 && modstander.getHp() > 0)
    {
        std::cout << "Din tur!" << std::endl;
        visStatus();
        spillerAngrib();
        if (modstander.getHp() <= 0) 
        {
            break;
        }
        std::cout << "Fjendens tur!" << std::endl;
        visStatus();
        fjendeAngrib();
    }
    
}

// The player attacks the enemy
// Displays a message indicating the player is attacking
void Kamp::spillerAngrib()
{
    std::cout << spiller.getName() << " angriber " << modstander.getName() << "!" << std::endl;
    if (spiller.angrib(modstander) <= 0) 
    {
        slutKamp();
    }    
    
}

// The enemy attacks the player
// Displays a message indicating the enemy is attacking
void Kamp::fjendeAngrib()
{
    std::cout << modstander.getName() << " angriber " << spiller.getName() << "!" << std::endl;
    if (modstander.angrib(spiller)<= 0) 
    {
        slutKamp();
    }
    
}

// Displays the status of both the player and the enemy
// Shows their names and current health points
void Kamp::visStatus()
{
    std::cout << spiller.getName() << " HP: " << spiller.getHp() << std::endl;
    std::cout << modstander.getName() << " HP: " << modstander.getHp() << std::endl;
}

// Ends the battle and checks if the player or enemy is dead
// If the player wins, they gain experience
// If the enemy wins, the player is dead
void Kamp::slutKamp()
{
    if (spiller.getHp() <= 0)
    {
        std::cout << spiller.getName() << " er død!" << std::endl;
        
    }
    else if (modstander.getHp() <= 0)
    {
        std::cout << modstander.getName() << " er død!" << std::endl;
        std::cout << spiller.getName() << " vinder kampen!" << std::endl;
        std::cout << "Du får " << modstander.getExperienceGiven() << " XP!" << std::endl;
        spiller.giveExperience(modstander.getExperienceGiven());
        spiller.printHero();
    }

    
}