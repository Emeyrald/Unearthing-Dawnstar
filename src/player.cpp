#include <iostream>
#include "../header/player.hpp"
#include "../header/playerStats.hpp"
#include "../header/levelManager.hpp"
#include "../header/skillManager.hpp"
#include "../header/inventory.hpp"
#include "../header/inventoryManager.hpp"
#include <nlohmann/json.hpp>
using nlohmann::json;
using std::cout;

Player::Player() : name(""), race(""), playerClass(""), stats(), skillManager(), inventory(), inventoryManager(nullptr), levelManager(nullptr) {
    inventoryManager = new InventoryManager(this);
    levelManager = new LevelManager(&stats, &skillManager, this);
};

Player::~Player() {
    delete inventoryManager;
    delete levelManager;
};

std::string Player::getName() const {
    return name;
}

void Player::setName(const std::string& name) {
    this->name = name;
}

std::string Player::getRace() const {
    return this->race;
}

void Player::setRace(const std::string& race) {
    this->race = race;
}

std::string Player::getClass() const {
    return this->playerClass;
}

void Player::setClass(const std::string& playerClass) {
    this->playerClass = playerClass;
}

PlayerStats& Player::getStats() {
    return stats;
}

void Player::displayName() {
    cout << this->name;
}

void Player::displayRace() {
    cout << this->race;
}

void Player::displayClass() {
    cout << this->playerClass;
}

void Player::displayStats() {
    cout << "\n=== Stats ===\n";
    cout << "Level: " << this->stats.getLevel() << "\n";
    cout << "Health: " << this->stats.getHealth() << "/" << this->stats.getMaxHealth() << "\n";
    cout << "Mana: " << this->stats.getMana() << "/" << this->stats.getMaxMana() << "\n";
    cout << "Defense: " << this->stats.getDefense() << "\n";
    cout << "Experience: " << this->stats.getExperience() << "/" << this->stats.getExpToNext() << "\n";    
    cout << "Gold: " << this->stats.getGold() << "\n";
}

Inventory& Player::getInventory() {
    return this->inventory;
}

InventoryManager* Player::getInventoryManager() {
    return this->inventoryManager;
}

LevelManager* Player::getLevelManager() {
    return this->levelManager;
}

SkillManager& Player::getSkillManager() {
    return skillManager;
}

json Player::toJson() const {
    return {
        {"name", name},
        {"race", race},
        {"playerClass", playerClass},
        {"stats", stats.toJson()},
        {"inventory", inventory.toJson()},
        {"skillManager", skillManager.toJson()}
    };
}

void Player::fromJson(const json& j) {
    name = j.at("name");
    race = j.at("race");
    playerClass = j.at("playerClass");

    stats.fromJson(j.at("stats"));
    inventory.fromJson(j.at("inventory"));
    skillManager.fromJson(j.at("skillManager"));
}
