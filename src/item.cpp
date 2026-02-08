#include "../header/item.hpp"
#include <nlohmann/json.hpp>
using nlohmann::json;

Item::Item() : name(""), type(""), value(0) {}

Item::Item(const std::string& name, const std::string& type, int value)
    : name(name), type(type), value(value) {}

Item::~Item() {}

std::string Item::getName() const {
    return name;
}

std::string Item::getType() const {
    return type;
}

int Item::getValue() const {
    return value;
}

json Item::toJson() const {
    return {
        {"type", "misc"},
        {"name", name},
        {"value", value}
    };
}

void Item::fromJson(const json& j) {
    name = j.at("name");
    type = j.at("type");
    value = j.at("value");
}
