#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "item.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <nlohmann/json.hpp>
using nlohmann::json;

class Inventory {
private:
    std::vector<std::unique_ptr<Item>> items;

public:
    Inventory() = default;
    ~Inventory() = default;

    void addItem(std::unique_ptr<Item> item);
    void removeItem(Item* item);
    std::vector<std::unique_ptr<Item>>& getItems();
    Item* findItem(Item* item);
    bool hasItem(Item* item);
    void displayItems();

    json toJson() const;
    void fromJson(const json& j);
};

#endif
