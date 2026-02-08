#include "../header/stats.hpp"

Stats::Stats() : level(1), health(100), maxHealth(100), defense(10), tempDefense(10), mana(100), maxMana(100) {};
Stats::~Stats() {};

int Stats::getLevel() const {
    return this->level;
}
void Stats::setLevel(int level) {
    this->level = level;
}
int Stats::getHealth() const {
    return this->health;
}
void Stats::setHealth(int health) {
    this->health = health;
}
int Stats::getMaxHealth() const {
    return this->maxHealth;
}
void Stats::setMaxHealth(int maxHealth) {
    this->maxHealth = maxHealth;
}
int Stats::getDefense() const {
    return this->defense;
}
void Stats::setDefense(int defense) {
    this->defense = defense;
}
int Stats::getTempDefense() const {
    return this->tempDefense;
}
void Stats::setTempDefense(int tempDefense) {
    this->tempDefense = tempDefense;
}
int Stats::getMana() const {
    return this->mana;
}
void Stats::setMana(int mana) {
    this->mana = mana;
}
int Stats::getMaxMana() const {
    return this->maxMana;
}
void Stats::setMaxMana(int maxMana) {
    this->maxMana = maxMana;
}
void Stats::takeDamage(int damage) {
    int effectiveDamage = damage - Stats::getDefense();
    if (effectiveDamage < 0) {
        effectiveDamage = 0;
    }
    Stats::setHealth(Stats::getHealth() - effectiveDamage);
    if (Stats::getHealth() < 0) {
        Stats::setHealth(0);
    }
}
void Stats::heal(int amount) {
    Stats::setHealth(Stats::getHealth() + amount);
    if (Stats::getHealth() > Stats::getMaxHealth()) {
        Stats::setHealth(Stats::getMaxHealth());
    }
}
void Stats::reduceMana(int cost) {
    Stats::setMana(Stats::getMana() - cost);
    if (Stats::getMana() < 0) {
        Stats::setMana(0);
    }
}
void Stats::increaseDefenseTemporarily(int amount) {
    Stats:setTempDefense(Stats::getTempDefense() + amount);
}
void Stats::resetTempDefense() {
    this->defense -= this->tempDefense;
    this->tempDefense = 0;
}
void Stats::rest() {
    Stats::setHealth(Stats::getMaxHealth());
    Stats::setMana(Stats::getMaxMana());
}