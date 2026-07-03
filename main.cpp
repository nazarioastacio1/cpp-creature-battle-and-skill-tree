#include <iostream>
#include "Wizard.hpp"
#include "Firecat.hpp"
#include "Banshee.hpp"
#include "CatThug.hpp"
#include "Tavern.hpp"
#include "Battle.hpp"

int main(){
    // Create wizard
    Wizard merlin("Merlin", Creature::Category::HUMANOID, Creature::School::FIRE, 1, false, 10, 100);

    // Create enemies
    Firecat blaze("Blaze", Creature::Category::ANIMAL, Creature::School::FIRE, 30, 1, true, Firecat::ORANGE, 1, false, 3);
    Banshee ghostly("Ghostly", Creature::Category::UNDEAD, Creature::School::DEATH, 25, 1, true, Banshee::RED, 1, false, 5);
    CatThug spike("Spike", Creature::Category::HUMANOID, Creature::School::MYTH, 20, 1, true, {}, CatThug::ROOKIE, false, 2);

    // Create tavern and add enemies
    Tavern enemies;
    enemies.enterTavern(&blaze);
    enemies.enterTavern(&ghostly);
    enemies.enterTavern(&spike);

    // Start battle
    Battle battle(&merlin, enemies);
    battle.simulate();

    return 0;
}