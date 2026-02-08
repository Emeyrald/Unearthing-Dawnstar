#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <string>
#include "stats.hpp"
#include "skillManager.hpp"

class Enemy {
private:
    std::string name;
    int expDropped;
    int goldDropped;
    Stats stats;
public:
    Enemy();
    Enemy(const std::string& name, int exp, int gold, const Stats& stats);
    ~Enemy();
    
    std::string getName();
    Stats& getStats();
    int dropExp();
    int dropGold();
    void displayStats();
};

#endif // ENEMY_HPP