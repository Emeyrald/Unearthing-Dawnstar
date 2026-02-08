#ifndef PLAYERSTATS_HPP
#define PLAYERSTATS_HPP
#include <string>
#include "stats.hpp"
#include <nlohmann/json.hpp>
using nlohmann::json;

class PlayerStats : public Stats {
private:
    int experience;
    int expToNext;
    int gold;
    int equippedWeaponBonus;
    int equippedArmorBonus;
public:
    PlayerStats();
    virtual ~PlayerStats();
    
    int getExperience() const;
    void setExperience(int amount);
    int getExpToNext() const;
    void setExpToNext(int amount);
    int getGold() const;
    void addGold(int amount);
    void subtractGold(int amount);
    void setGold(int amount);
    int getEquippedWeaponBonus() const;
    void setEquippedWeaponBonus(int bonus);
    int getEquippedArmorBonus() const;
    void setEquippedArmorBonus(int bonus);
    void clearWeaponBonus();
    void clearArmorBonus();
    void applyRaceBonuses(const std::string& race);

    json toJson() const;
    void fromJson(const json& j);
};
#endif // PLAYERSTATS_HPP