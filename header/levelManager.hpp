#ifndef LEVELMANAGER_HPP
#define LEVELMANAGER_HPP

#include "playerStats.hpp"
#include "player.hpp"
#include "skillManager.hpp"

class Player;
class SkillManager;

class LevelManager {
private:
    PlayerStats* stats;
    SkillManager* skillManager;
    Player* player;
public:
    LevelManager(PlayerStats* stats, SkillManager* skillManager, Player* player);
    virtual ~LevelManager();
    
    void addExperience(int amount);
    bool checkLevelUp(int amount);
    void levelUp();
};

#endif // LEVELMANAGER_HPP