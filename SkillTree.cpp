/**
 * Title: SkillTree.cpp
 * Author: Jonathan Nazario
 * Date: 07/05/2026
 * Description: The Implementation of the SkillTree class
 */
#include "SkillTree.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stack>

/**
Default constructor
Default-initializes all private members
*/
Skill::Skill(){
    id_ = 0;
    name_ = "";
    description_ = "";
}

/**
@param: The unique identifier for the Skill (an integer)
@param: The name of the Skill (a string)
@param: The description of the Skill (a string)
*/
Skill::Skill(const int& id, const std::string& name, const std::string& description){
    id_ = id;
    name_ = name;
    description_ = description;
}

/**
@param: A const reference to a Skill
@return: true if the id
_
otherwise
of the Skill is equal to that of the argument, false
*/
bool Skill::operator==(const Skill& skill) const{
    return id_ == skill.id_;
}

/**
@param: A const reference to a Skill
@return: true if the id
_
otherwise
*/
bool Skill::operator<(const Skill& skill) const{
    return id_ < skill.id_;
}

/**
@param: A const reference to a Skill
@return: true if the id
_
otherwise
of the Skill is greater than that of the argument, false
*/
bool Skill::operator>(const Skill& skill) const{
    return id_ > skill.id_;
}

/**
Default constructor.
Default-initializes all private members.
*/
SkillTree::SkillTree() : BinarySearchTree<Skill>(){

}

/**
Parameterized constructor.
@param: The name of a csv file (A string)
@post: The SkillTree is populated with Skills from the csv file. The file
format is as follows:
id, name, description
Ignore the first line
*/
SkillTree::SkillTree(const std::string& filename) : BinarySearchTree<Skill>(){
    std::ifstream file(filename);
    std::string line;
    std::getline(file, line);
    while(std::getline(file, line)){
        std::stringstream ss(line);
        std::string token;
        int id;
        std::string name, description;
        std::getline(ss, token, ',');
        id = std::stoi(token);
        std::getline(ss, token, ',');
        name = token;
        std::getline(ss, token, ',');
        description = token;
        Skill skill(id, name, description);
        addSkill(skill);
    }
    file.close();
}

/**
@param: The id of the Skill to be found (an integer)
@return: A pointer to the node containing the Skill with the given id, or
nullptr if the Skill is not found
*/
std::shared_ptr<BinaryNode<Skill>> SkillTree::findSkill(const int& id){
    std::shared_ptr<BinaryNode<Skill>> current = getRoot();
    while (current != nullptr){
        if(current->getItem().id_ == id){
            return current;
        } else if(id < current->getItem().id_){
            current = current->getLeftChildPtr();
        } else {
            current = current->getRightChildPtr();
        }
    }
    return nullptr;
}

/**
@param: A Skill to be added
@post: Thee skill is added to the tree (in BST order) only if it was not
already in the tree
@return: true if the Skill is successfully added to the SkillTree, false
otherwise
*/
bool SkillTree::addSkill(const Skill& skill){
    if(contains(skill)){
        return false;
    }
    add(skill);
    return true;
}

/**
@param: The name of a Skill
@return: true if the Skill is successfully removed from the SkillTree, false
otherwise
*/
bool SkillTree::removeSkill(const std::string& skill){
    std::vector<Skill> nodes;
    inorderTraversal(getRoot(), nodes);
    for(int i = 0; i < nodes.size(); i ++ ){
        if(nodes[i].name_ == skill){
            remove(nodes[i]);
            return true;
        }
    }
    return false;
}

/**
@post: Clears the tree
*/
void SkillTree::clear(){
    root_ptr_ = nullptr;
}

/**
@param: The id of the Skill (an integer)
Note: For a Skill to be leveled up, its parent Skill must also be leveled up,
thus the Skill points are the number of Skills that must be leveled up before
and including the Skill with the given id.
@return: an integer: the number of skill points needed to level up the Skill
with the given id, starting from the root (i.e. the number of nodes from root
to the given Skill).
Include the Skill with the given id in the count. For example, if the tree
contains the following Skills (represented by their ids):
5
/ \
1 8
and the function parameter queries for id 8, the function should return 2.
If the Skill with the given id is not found, return -1
*/
int SkillTree::calculateSkillPoints(const int& id){
    int count = 0;
    std::shared_ptr<BinaryNode<Skill>> current = getRoot();
    while(current != nullptr){
        count++;
        if(current->getItem().id_ == id){
            return count;
        }else if (id < current->getItem().id_){
            current = current->getLeftChildPtr();
        }else{
            current = current->getRightChildPtr();
        }
    }
    return -1;
}

/**
@post: Balances the tree
Hint: Recall the definition of a balanced tree:
A tree is balanced if for any node, its left and right subtrees differ in height
by no more than 1.
Hint: You may sort the elements and built the tree recursively using a divide
and conquer approach
*/
void SkillTree::balance(){
    std::vector<Skill> nodes;
    inorderTraversal(getRoot(), nodes);
    root_ptr_ = buildTree(nodes, 0, nodes.size() - 1);
}

/**
@param: Root node
@param: Vector for you to store your nodes while traversal
@post: nodes contain skills from the tree in order recursively
*/
void SkillTree::inorderTraversal(std::shared_ptr<BinaryNode<Skill>> root, std::vector<Skill>& nodes){
    if(root == nullptr){
        return;
    }
    inorderTraversal(root->getLeftChildPtr(), nodes);
    nodes.push_back(root->getItem());
    inorderTraversal(root->getRightChildPtr(), nodes);
}

/**
@param: Skills from the tree stored as nodes in a vector
@param: Integer representing the start id
@param: Integer representing the final id
*/
std::shared_ptr<BinaryNode<Skill>> SkillTree::buildTree(const std::vector<Skill>& nodes, int start, int finish){
    if(start > finish){
        return nullptr;
    }
    int mid = (start + finish) / 2;
    std::shared_ptr<BinaryNode<Skill>> node = std::make_shared<BinaryNode<Skill>>(nodes[mid]);
    node->setLeftChildPtr(buildTree(nodes, start, mid - 1));
    node->setRightChildPtr(buildTree(nodes, mid + 1, finish));
    return node;
}

/**
@post: Prints the tree in preorder:
[id
_] [name
_]\n
[description
_]\n
*/
void SkillTree::preorderDisplay() const{
    if(getRoot() == nullptr) return;
    std::stack<std::shared_ptr<BinaryNode<Skill>>> stack;
    stack.push(getRoot());
    while(!stack.empty()){
        std::shared_ptr<BinaryNode<Skill>> current = stack.top();
        stack.pop();
        std::cout << current->getItem().id_ << " " << current->getItem().name_ << "\n";
        std::cout << current->getItem().description_ << "\n";
        if(current->getRightChildPtr()) stack.push(current->getRightChildPtr());
        if(current->getLeftChildPtr()) stack.push(current->getLeftChildPtr());
    }
}