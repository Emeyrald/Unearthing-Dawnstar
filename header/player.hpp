#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <string>
#include "playerStats.hpp"
#include "skillManager.hpp"
#include "levelManager.hpp" 
#include "inventory.hpp"
#include "inventoryManager.hpp"
#include <nlohmann/json.hpp>
using nlohmann::json;

class LevelManager;

class Player {
private:
    std::string name; // this is const
    std::string race; // this is const
    std::string playerClass; //this is const
    PlayerStats stats;
    LevelManager* levelManager;
    SkillManager skillManager;
    Inventory inventory;
    InventoryManager* inventoryManager;
    
public:
    Player();
    virtual ~Player();
    
    std::string getName() const;
    void setName(const std::string& name);
    std::string getRace() const;
    void setRace(const std::string& race);
    std::string getClass() const;
    void setClass(const std::string& playerClass);
    PlayerStats& getStats();
    Inventory& getInventory();
    InventoryManager* getInventoryManager();
    LevelManager* getLevelManager();
    SkillManager& getSkillManager();
    void displayName();
    void displayStats();
    void displayRace();
    void displayClass();
    void displaySkills();

    json toJson() const;
    void fromJson(const json& j);
};

#endif // PLAYER_HPP