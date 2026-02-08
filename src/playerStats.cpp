#include "../header/playerStats.hpp"
#include <nlohmann/json.hpp>
using nlohmann::json;

PlayerStats::PlayerStats() : experience(0), expToNext(15), gold(0), equippedWeaponBonus(0), equippedArmorBonus(0) {};
PlayerStats::~PlayerStats() {};

int PlayerStats::getExperience() const {
    return this->experience;
}
void PlayerStats::setExperience(int experience) {
    this->experience = experience;
}
int PlayerStats::getExpToNext() const {
    return this->expToNext;
}
void PlayerStats::setExpToNext(int expToNext) {
    this->expToNext = expToNext;
}
int PlayerStats::getGold() const {
    return this->gold;
}
void PlayerStats::setGold(int gold) {
    this->gold = gold;
}
void PlayerStats::addGold(int gold) {
    PlayerStats::setGold(PlayerStats::getGold() + gold);
}
void PlayerStats::subtractGold(int gold) {
    PlayerStats::setGold(PlayerStats::getGold() - gold);
}
int PlayerStats::getEquippedWeaponBonus() const {
    return this->equippedWeaponBonus; 
}
void PlayerStats::setEquippedWeaponBonus(int bonus) {
    this->equippedWeaponBonus = bonus;
}
int PlayerStats::getEquippedArmorBonus() const {
    return this->equippedArmorBonus; 
}
void PlayerStats::setEquippedArmorBonus(int bonus) {
    this->equippedArmorBonus = bonus;
}
void PlayerStats::clearWeaponBonus() {
    PlayerStats::setEquippedWeaponBonus(0);
}
void PlayerStats::clearArmorBonus() {
    PlayerStats::setEquippedArmorBonus(0);
}

void PlayerStats::applyRaceBonuses(const std::string& race) {
    if (race == "human") {
        // Balanced
        setMaxHealth(100);
        setHealth(100);
        setDefense(5);
        setMana(50);
        setMaxMana(50);
    }
    else if (race == "elf") {
        // High mana, low health
        setMaxHealth(80);
        setHealth(80);
        setDefense(3);
        setMana(80);
        setMaxMana(80);
    }
    else if (race == "dwarf") {
        // Tanky race
        setMaxHealth(120);
        setHealth(120);
        setDefense(8);
        setMana(30);
        setMaxMana(30);
    }
}

json PlayerStats::toJson() const {
    return {
        // Base stats
        {"health", getHealth()},
        {"maxHealth", getMaxHealth()},
        {"defense", getDefense()},
        {"tempDefense", getTempDefense()},
        {"level", getLevel()},
        {"mana", getMana()},
        {"maxMana", getMaxMana()},

        // Derived stats
        {"experience", experience},
        {"expToNext", expToNext},
        {"gold", gold},
        {"equippedWeaponBonus", equippedWeaponBonus},
        {"equippedArmorBonus", equippedArmorBonus}
    };
}
void PlayerStats::fromJson(const json& j) {
    setHealth(j.at("health"));
    setMaxHealth(j.at("maxHealth"));
    setDefense(j.at("defense"));
    setTempDefense(j.at("tempDefense"));
    setLevel(j.at("level"));
    setMana(j.at("mana"));
    setMaxMana(j.at("maxMana"));

    experience = j.at("experience");
    expToNext = j.at("expToNext");
    gold = j.at("gold");
    equippedWeaponBonus = j.at("equippedWeaponBonus");
    equippedArmorBonus = j.at("equippedArmorBonus");
}