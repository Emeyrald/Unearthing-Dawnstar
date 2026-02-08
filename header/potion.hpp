#ifndef POTION_HPP
#define POTION_HPP

#include "item.hpp"
#include <nlohmann/json.hpp>
using nlohmann::json;

class Potion : public Item {
private:
    int healAmount;

public:
    Potion();
    Potion(const std::string& name, int value, int healAmount);
    virtual ~Potion();

    int getHealAmount() const;

    json toJson() const override;
    void fromJson(const json& j) override;
};

#endif // POTION_HPP
