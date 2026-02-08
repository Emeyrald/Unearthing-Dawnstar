#ifndef DUNGEON_HPP
#define DUNGEON_HPP

#include <vector>
#include <memory>
#include "area.hpp"
#include "enemy.hpp"

class Dungeon : public Area {
private:
    std::vector<std::unique_ptr<Enemy>> enemies;
public:
    Dungeon();
    ~Dungeon() override = default;
    
    std::vector<std::unique_ptr<Enemy>>& getEnemies();
    void addEnemy(std::unique_ptr<Enemy> enemy);
    void explore();
};

#endif // DUNGEON_HPP