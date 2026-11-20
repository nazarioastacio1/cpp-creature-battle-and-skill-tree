# C++ Creature Battle and Skill Tree

This is a project I worked on for my C++ class at Hunter College. It started with a basic `Creature` class, and each assignment added something new. By the end, I had classes for different creatures, a tavern to manage them, a turn-based battle system, and a skill tree.

## What I worked on

- **Creatures:** Used inheritance to create different creature types, including Firecat, Banshee, CatThug, and Wizard.
- **Tavern:** Used a templated bag to store and manage creatures.
- **Battle system:** Used a stack to organize turns based on each character's speed. The wizard can attack or heal during a turn.
- **Skill tree:** Used a binary search tree to add, find, and remove skills. It also reads skills from a CSV file and includes a way to balance the tree.

## Running the project

The current `main.cpp` tests the **skill tree**, using data from `skills.csv`. It shows how to search for skills, add or remove them, calculate skill points, and balance the tree.

The battle system is also in the repository (`Battle.cpp` and `Battle.hpp`), but the current `main.cpp` doesn't launch it.

## What I learned

This project gave me more practice with C++ classes, inheritance, polymorphism, templates, stacks, binary search trees, smart pointers, and file handling.
