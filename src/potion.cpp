#include "../header/potion.hpp"
#include <nlohmann/json.hpp>
using nlohmann::json;

Potion::Potion() : Item("", "potion", 0), healAmount(0) {}

Potion::Potion(const std::string& name, int value, int healAmount)
    : Item(name, "potion", value), healAmount(healAmount) {}

Potion::~Potion() {}

int Potion::getHealAmount() const {
    return healAmount;
}

json Potion::toJson() const {
    return {
        {"type", "potion"},
        {"name", name},
        {"value", value},
        {"healAmount", healAmount}
    };
}

void Potion::fromJson(const json& j) {
    name = j.at("name");
    type = j.at("type");
    value = j.at("value");
    healAmount = j.at("healAmount");
}