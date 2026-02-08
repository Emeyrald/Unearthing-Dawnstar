#include "../header/skill.hpp"
#include <nlohmann/json.hpp>
using nlohmann::json;

Skill::Skill(const std::string& name, const std::string& description, const std::string& use, int damage, int buff, int manaCost) :
name(name), description(description), use(use), damage(damage), buff(buff), manaCost(manaCost) {};
Skill::~Skill() {};

std::string Skill::getName() const {
    return name;
}
std::string Skill::getDescription() const {
    return description;
}
std::string Skill::getUse() const {
    return use;
}
std::string Skill::getClass() const {
    return skillClass;
}
int Skill::getDamage() const {
    return damage;
}
int Skill::getBuff() const {
    return buff;
}
int Skill::getManaCost() const {
    return manaCost;
}

json Skill::toJson() const {
    return {
        {"name", name},
        {"description", description},
        {"use", use},
        {"damage", damage},
        {"buff", buff},
        {"manaCost", manaCost}
    };
}

void Skill::fromJson(const json& j) {
    name = j.at("name");
    description = j.at("description");
    use = j.at("use");
    damage = j.at("damage");
    buff = j.at("buff");
    manaCost = j.at("manaCost");
}
