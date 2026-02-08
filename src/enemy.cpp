#include "../header/enemy.hpp"
#include <iostream>

Enemy::Enemy()
    : name("Unknown Enemy"),
      expDropped(0),
      goldDropped(0),
      stats() {}

Enemy::Enemy(const std::string& name, int exp, int gold, const Stats& stats)
    : name(name),
      expDropped(exp),
      goldDropped(gold),
      stats(stats) {}

Enemy::~Enemy() {}

std::string Enemy::getName() {
    return name;
}

Stats& Enemy::getStats() {
    return stats;
}

int Enemy::dropExp() {
    return expDropped;
}

int Enemy::dropGold() {
    return goldDropped;
}

void Enemy::displayStats() {
    std::cout << "\n-- Enemy Stats: " << name << " --\n";
    std::cout << "Health: " << stats.getHealth() << "/" << stats.getMaxHealth() << "\n";
    std::cout << "Mana: " << stats.getMana() << "/" << stats.getMaxMana() << "\n";
    std::cout << "Defense: " << stats.getDefense() << "\n";
    std::cout << "Level: " << stats.getLevel() << "\n";
    std::cout << "Gold Dropped: " << goldDropped << "\n";
}