#include <iostream>

#include "../header/levelManager.hpp"

LevelManager::LevelManager(PlayerStats* stats, SkillManager* skillManager, Player* player) : stats(stats), skillManager(skillManager), player(player) {};
LevelManager::~LevelManager() {};

bool LevelManager::checkLevelUp(int experience) {
    return experience >= 15;
}

void LevelManager::addExperience(int experience) {
    int newXP = stats->getExperience() + experience;
    // Can change depending on how we do level ups
    // NOT A BUG. IT ONLY LEVELS UP A LOT OF LEVELS BECAUSE I MADE THE GOBLIN DROP A LOT OF EXP
    // TO DEMONSTRATE LEVEL UPS AND SKILL UNLOCKS
    // THE PLAYER WOULD NEVER ACTUALLY GET ABOVE 15 EXP AT ONCE, BUT STILL, JUST IN CASE
    // IT'S GOOD TO HAVE HERE BECAUSE IF IT'S NOT A WHILE LOOP, THEY'll HAVE SOMETHING LIKE 22/15 EXP
    while (newXP >= 15) {
        if (checkLevelUp(newXP)) {
            newXP -= 15;
            levelUp();
        }
    }
    stats->setExperience(newXP);
}

void LevelManager::levelUp() {
    // Can change depending on what values we want and how we balance it
    stats->setLevel(stats->getLevel() + 1);
    stats->setHealth(stats->getHealth() + 10);
    stats->setMaxHealth(stats->getMaxHealth() + 10);
    stats->setDefense(stats->getDefense() + 1);
    stats->setMana(stats->getMana() + 10);
    stats->setMaxMana(stats->getMaxMana() + 10);
    std::cout << "You leveled up!" << "\n";
    skillManager->unlockSkill(*stats, player->getClass());
}