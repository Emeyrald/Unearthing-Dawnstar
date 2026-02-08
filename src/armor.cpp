#include "../header/armor.hpp"
#include <nlohmann/json.hpp>
using nlohmann::json;

Armor::Armor() : Item("", "armor", 0), defenseBonus(0) {}

Armor::Armor(const std::string& name, int value, int defenseBonus)
    : Item(name, "armor", value), defenseBonus(defenseBonus) {}

Armor::~Armor() {}

int Armor::getDefenseBonus() const {
    return defenseBonus;
}

json Armor::toJson() const {
    return {
        {"type", "armor"},
        {"name", name},
        {"value", value},
        {"defenseBonus", defenseBonus}
    };
}

void Armor::fromJson(const json& j) {
    name = j.at("name");
    type = j.at("type");
    value = j.at("value");
    defenseBonus = j.at("defenseBonus");
}