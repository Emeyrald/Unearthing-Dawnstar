#ifndef STATS_HPP
#define STATS_HPP
#include <string>

class Stats {
private:
    int level;
    int health;
    int maxHealth;
    int defense;
    int tempDefense;
    int mana;
    int maxMana;

public:
    Stats();
    virtual ~Stats();
    
    int getLevel() const;
    void setLevel(int level); 
    int getHealth() const;
    void setHealth(int health);
    int getMaxHealth() const;
    void setMaxHealth(int maxHealth);
    int getDefense() const;
    void setDefense(int defense);
    int getTempDefense() const;
    void setTempDefense(int tempDefense);
    int getMana() const;
    void setMana(int mana);
    int getMaxMana() const;
    void setMaxMana(int mana);
    void takeDamage(int damage);
    void heal(int amount);
    void reduceMana(int cost);
    void increaseDefenseTemporarily(int amount);
    void resetTempDefense();
    void rest();
};

#endif // STATS_HPP