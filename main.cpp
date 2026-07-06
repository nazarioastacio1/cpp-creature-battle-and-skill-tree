#include <iostream>
#include "SkillTree.hpp"

int main(){
    // Test parameterized constructor with CSV file
    SkillTree tree("skills.csv");
    
    // Test preorderDisplay
    std::cout << "=== Preorder Display ===" << std::endl;
    tree.preorderDisplay();
    
    // Test findSkill
    std::cout << "\n=== Find Skill ===" << std::endl;
    auto skill = tree.findSkill(1);
    if(skill != nullptr){
        std::cout << "Found: " << skill->getItem().name_ << std::endl;
    } else {
        std::cout << "Skill not found" << std::endl;
    }
    
    // Test calculateSkillPoints
    std::cout << "\n=== Calculate Skill Points ===" << std::endl;
    std::cout << "Skill points for id 1: " << tree.calculateSkillPoints(1) << std::endl;
    
    // Test addSkill
    std::cout << "\n=== Add Skill ===" << std::endl;
    Skill newSkill(999, "TestSkill", "A test skill");
    std::cout << "Added: " << tree.addSkill(newSkill) << std::endl;
    
    // Test removeSkill
    std::cout << "\n=== Remove Skill ===" << std::endl;
    std::cout << "Removed: " << tree.removeSkill("TestSkill") << std::endl;
    
    // Test balance
    std::cout << "\n=== Balance ===" << std::endl;
    tree.balance();
    tree.preorderDisplay();
    
    // Test clear
    std::cout << "\n=== Clear ===" << std::endl;
    tree.clear();
    std::cout << "Tree is empty: " << tree.isEmpty() << std::endl;
    
    return 0;
}