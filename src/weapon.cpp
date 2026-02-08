#include "../header/weapon.hpp"
#include <nlohmann/json.hpp>
using nlohmann::json;

Weapon::Weapon() : Item("", "weapon", 0), damageBonus(0) {}

Weapon::Weapon(const std::string& name, int value, int damageBonus)
    : Item(name, "weapon", value), damageBonus(damageBonus) {}

Weapon::~Weapon() {}

int Weapon::getDamageBonus() const {
    return damageBonus;
}

json Weapon::toJson() const {
    return {
        {"type", "weapon"},
        {"name", name},
        {"value", value},
        {"damageBonus", damageBonus}
    };
}

void Weapon::fromJson(const json& j) {
    name = j.at("name");
    type = j.at("type");
    value = j.at("value");
    damageBonus = j.at("damageBonus");
}