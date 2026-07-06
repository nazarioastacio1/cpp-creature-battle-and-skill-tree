/**
 * Title: SkillTree.hpp
 * Author: Jonathan Nazario
 * Date: 07/05/2026
 * Description: The Declaration of the SkillTree class
 */
#ifndef SKILLTREE_H_
#define SKILLTREE_H_

#include <string>
#include "BinarySearchTree.hpp"
#include <vector>
#include <memory>


struct Skill{
    //A unique identifier for the Skill
    int id_;
    //The name of the Skill
    std::string name_;
    //The description of the Skill
    std::string description_;

    /**
    Default constructor
    Default-initializes all private members
    */
   Skill();

    /**
    @param: The unique identifier for the Skill (an integer)
    @param: The name of the Skill (a string)
    @param: The description of the Skill (a string)
    */
    Skill(const int& id, const std::string& name, const std::string& description);

    /**
    @param: A const reference to a Skill
    @return: true if the id
    _
    otherwise
    of the Skill is equal to that of the argument, false
    */
    bool operator==(const Skill& skill) const;

    /**
    @param: A const reference to a Skill
    @return: true if the id
    _
    otherwise
    of the Skill is less than that of the argument, false
    */
    bool operator<(const Skill& skill) const;

    /**
    @param: A const reference to a Skill
    @return: true if the id
    _
    otherwise
    of the Skill is greater than that of the argument, false
    */
    bool operator>(const Skill& skill) const; 
};

class SkillTree : public BinarySearchTree<Skill> {
    public:
    /**
    Default constructor.
    Default-initializes all private members.
    */
    SkillTree();

    /**
    Parameterized constructor.
    @param: The name of a csv file (A string)
    @post: The SkillTree is populated with Skills from the csv file. The file
    format is as follows:
    id, name, description
    Ignore the first line
    */
    SkillTree(const std::string& filename);

    /**
    @param: The id of the Skill to be found (an integer)
    @return: A pointer to the node containing the Skill with the given id, or
    nullptr if the Skill is not found
    */
    std::shared_ptr<BinaryNode<Skill>> findSkill(const int& id);

    /**
    @param: A Skill to be added
    @post: Thee skill is added to the tree (in BST order) only if it was not
    already in the tree
    @return: true if the Skill is successfully added to the SkillTree, false
    otherwise
    */
    bool addSkill(const Skill& skill);

    /**
    @param: The name of a Skill
    @return: true if the Skill is successfully removed from the SkillTree, false
    otherwise
    */
    bool removeSkill(const std::string& skill);

    /**
    @post: Clears the tree
    */
    void clear();

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
    int calculateSkillPoints(const int& id);

    /**
    @post: Balances the tree
    Hint: Recall the definition of a balanced tree:
    A tree is balanced if for any node, its left and right subtrees differ in height
    by no more than 1.
    Hint: You may sort the elements and built the tree recursively using a divide
    and conquer approach
    */
    void balance();

    /**
    @post: Prints the tree in preorder:
    [id
    _] [name
    _]\n
    [description
    _]\n
    */
    void preorderDisplay() const;

    /**
    @param: Root node
    @param: Vector for you to store your nodes while traversal
    @post: nodes contain skills from the tree in order recursively
    */
    void inorderTraversal(std::shared_ptr<BinaryNode<Skill>> root,
    std::vector<Skill>& nodes);

    /**
    @param: Skills from the tree stored as nodes in a vector
    @param: Integer representing the start id
    @param: Integer representing the final id
    */
    std::shared_ptr<BinaryNode<Skill>> buildTree(const std::vector<Skill>& nodes,
    int start, int finish);

    private:

};

#endif