#ifndef SKILL_HPP
#define SKILL_HPP

#include <iostream>
#include <nlohmann/json.hpp>
using nlohmann::json;

class Skill {
private:
    std::string name;
    std::string description;
    std::string use;
    std::string skillClass;
    int damage;
    int buff;
    int manaCost;

public:
    Skill(const std::string& name,
          const std::string& description,
          const std::string& use,
          int damage,
          int buff,
          int manaCost);
    virtual ~Skill();

    std::string getName() const;
    std::string getDescription() const;
    std::string getUse() const;
    std::string getClass() const;
    int getDamage() const;
    int getBuff() const;
    int getManaCost() const;

    json toJson() const;
    void fromJson(const json& j);
};

#endif // SKILL_HPP