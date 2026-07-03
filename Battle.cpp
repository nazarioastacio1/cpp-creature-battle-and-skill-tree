/**
 * Title: Battle.cpp
 * Author: Jonathan Nazario
 * Date: 07/01/2026
 * Description: The Implementation of the Battle class
 */
#include "Battle.hpp"
#include <iostream>
#include "Firecat.hpp"
#include "Banshee.hpp"
#include "CatThug.hpp"

/**
Parameterized constructor
@param: The wizard involved in the battle
@param: The tavern of creatures involved in the battle
*/
Battle::Battle(Wizard* wizard, Tavern enemies ){
    wizard_ = wizard;
    enemies_ = enemies;
}

/**
@return: true if the wizard is still alive (health > 0), false otherwise
*/
bool Battle::isWizardAlive() const{
    if (wizard_-> getHealth() > 0){
        return true;
    }else{
        return false;
    }
}

/**
@return: true if there are remaining enemies, false if all have been defeated
*/
bool Battle::enemiesRemain() const{
    if(enemies_.getCreatureCount() > 0){
        return true;
    }else{
        return false;
    }
}

/**
@post: Displays the current status of all combatants at the start of a round.
The output should include:
The Wizard’s name and current health.
A numbered list of all enemies still in the battle, showing:
- Name
- Current health
- Speed
Example output:
=== Round Status ===
Wizard: Merlin
Health: 72
Enemies:
1. Lado - Health: 25, Speed: 4
2. Meheraan - Health: 30, Speed: 3
3. Ank - Health: 18, Speed: 2
=====================
*/
void Battle::displayRoundStatus() const{
    std::cout << " === Round Status ===" << "\n";
    std::cout << "Wizard: " << wizard_->getName() << "\n";
    std::cout << "Health: " << wizard_->getHealth() << "\n";
    std::cout << " Enemies: " << "\n";
    std::vector <Creature*> enemies = enemies_.getAllCreatures();
    for(int i = 0; i < enemies.size(); i++){
        std::cout << i+1 << ". " << enemies[i]->getName() << " - Health: " << enemies[i]->getHealth() << ", Speed:  " << enemies[i]->getSpeed() << "\n";
    }
    std::cout << "  ==================== "<< "\n";
}

/**
@post: Populates the turnStack
_
with all current combatants (wizard and all
enemies from the tavern) sorted by ascending speed (the faster the speed the
earlier you go)
*/
void Battle::buildTurnStack(){
    while(!turnStack_.empty()){
        turnStack_.pop();
    }
    std::vector<Creature*> creatures = enemies_.getAllCreatures();
    creatures.push_back(wizard_);

    for(int i = 0; i < creatures.size(); i++){
        for(int j = i+1; j < creatures.size(); j++){
            if (creatures[i]->getSpeed() > creatures[j]->getSpeed()){
                Creature* temp = creatures[i];
                creatures[i] = creatures[j];
                creatures[j] = temp;
            }

        }
    }
        for (int i = 0; i < creatures.size(); i++){
            turnStack_.push(creatures[i]);
        }
}

/**
@post: Removes any enemies whose health has dropped to 0 or below from
the tavern after turn execution
*/
void Battle::removeDefeatedEnemy(){
    std::vector<Creature*> enemies = enemies_.getAllCreatures();
    for(int i = 0; i < enemies.size(); i++){
        if(enemies[i]->getHealth() <= 0){
            enemies_.exitTavern(enemies[i]);
            i--;
        }
    }
}

/**
@param: Pointer to the creature taking a turn
@post: Executees the turn of a given creature. If the attacker is an enemy
they will perform an attack on the Wizard. If the attacker is a wizard, the
wizard chooses and casts a spell (either offensive or defensive) on a chosen
target (indexed from your tavern)
*/
void Battle::executeTurn(Creature* attacker){
    if(attacker == wizard_){
        int choice;
        std::cout << "1. Attack\n2. Heal\n ";
        std::cin >> choice;
        if(choice == 1){
            std::vector<Creature*> enemies = enemies_.getAllCreatures();
            for (int i = 0; i < enemies.size(); i++ ){
                std::cout << i + 1 << ". " << enemies[i]->getName() << " - Health: " << enemies[i]->getHealth() << "\n";
            }
            std::cout << "Choose a target: ";
            int target;
            std::cin >> target;
            wizard_-> attackSpell(enemies[target-1]);
        }else{
            wizard_->healSpell();
        }
    } else {
        Firecat* f = dynamic_cast<Firecat*>(attacker);
        if(f != nullptr){
            f->attack(wizard_);
        }
        Banshee* b = dynamic_cast<Banshee*>(attacker);
        if(b != nullptr){
            b->attack(wizard_);
        }
        CatThug* c = dynamic_cast<CatThug*>(attacker);
        if(c != nullptr){
            c->attack(wizard_);
        }
    }
}

/**
@post: Simulates the entire combat between the wizard and the enemy
creatures
Steps:
Display round status
Adds creatures into your turnStack
_
based on speed. The higher the speed
the earlier the creature will go (Remember how stacks work)
Executes the turn of the creature at the top of the stack. If the creature is a
wizard, you will gather user input to dictate whether the wizard will attack
or heal. If the creature is an enemy they will do their standard attack
When the wizard attacks, display all of the creatures in the tavern and gather
user input to decide who the wizard attacks
If the creature’s health falls below zero, remove them from the tavern
Check to see if the wizard is still alive or if there are still any enemies left in
the tavern. If either of the conditions are not true, print an action message to
signal that the battle is over and who came out victorious. If neither of the
conditions are true, build the stack once again and continue to simulate the
battle
Hint: Keep in mind that when a creature is attacking, they need to be popped
out of the stack. Because of this reason you need to build your stack every
time a full turn occurs
*/
void Battle::simulate(){
    while(isWizardAlive() && enemiesRemain()){
        displayRoundStatus();
        buildTurnStack();
        while(!turnStack_.empty()){
            executeTurn(turnStack_.top());
            turnStack_.pop();
            removeDefeatedEnemy();
            if(!isWizardAlive() || !enemiesRemain()){
                break;
            }
        }
    }
    if(isWizardAlive()){
        std::cout << wizard_->getName() << " wins!\n";
    } else {
        std::cout << "The enemies win!\n";
    }
}