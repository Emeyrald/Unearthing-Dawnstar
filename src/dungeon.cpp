#include "../header/dungeon.hpp"
#include <iostream>

Dungeon::Dungeon()
    : Area(), enemies() {}

std::vector<std::unique_ptr<Enemy>>& Dungeon::getEnemies() {
    return enemies;
}

void Dungeon::addEnemy(std::unique_ptr<Enemy> enemy) {
    enemies.push_back(std::move(enemy));
}

void Dungeon::explore() {
    std::cout << "\n=== Entering Dungeon: " << getName() << " ===\n";
    std::cout << getDescription() << "\n\n";

    if (enemies.empty()) {
        std::cout << "The dungeon is empty.\n";
        return;
    }

    std::cout << "You sense danger... Enemies appear!\n\n";

    for (const auto& e : enemies) {
        std::cout << "Enemy found: " << e->getName() << "\n";
    }
}
