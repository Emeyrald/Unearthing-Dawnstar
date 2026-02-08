#ifndef ARMOR_HPP
#define ARMOR_HPP

#include "item.hpp"
#include <nlohmann/json.hpp>
using nlohmann::json;

class Armor : public Item {
private:
    int defenseBonus;
public:
    Armor();
    Armor(const std::string& name, int value, int defenseBonus);
    virtual ~Armor();

    int getDefenseBonus() const;
    
    json toJson() const override;
    void fromJson(const json& j) override;
};

#endif // ARMOR_HPP
