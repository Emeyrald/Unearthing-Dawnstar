#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "item.hpp"
#include <nlohmann/json.hpp>
using nlohmann::json;

class Weapon : public Item {
private:
    int damageBonus;
public:
    Weapon();
    Weapon(const std::string& name, int value, int damageBonus);
    virtual ~Weapon();

    int getDamageBonus() const;

    json toJson() const override;
    void fromJson(const json& j) override;
};

#endif // WEAPON_HPP
