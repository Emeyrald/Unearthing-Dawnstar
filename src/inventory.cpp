#include "../header/inventory.hpp"
#include "../header/item.hpp"
#include "../header/weapon.hpp"
#include "../header/armor.hpp"
#include "../header/potion.hpp"
#include <algorithm>
#include <vector>
#include <nlohmann/json.hpp>
using nlohmann::json;

// Add an item to the inventory
void Inventory::addItem(std::unique_ptr<Item> item) {
    items.push_back(std::move(item));
}

// Remove an item from the inventory
void Inventory::removeItem(Item* item) {
    items.erase(
        std::remove_if(items.begin(), items.end(),
            [&](const std::unique_ptr<Item>& ptr) {
                return ptr.get() == item;
            }),
        items.end()
    );
}

std::vector<std::unique_ptr<Item>>& Inventory::getItems() {
    return items;
}

Item* Inventory::findItem(Item* item) {
    for (auto& up : items) {
        if (up->getName() == item->getName())
            return up.get();
    }
    return nullptr;
}

// Check if the inventory has a specific item
bool Inventory::hasItem(Item* item) {
    return findItem(item) != nullptr;
}

// Display all items in the inventory
void Inventory::displayItems() {
    if (items.empty()) {
        std::cout << "Inventory is empty.\n";
        return;
    }

    std::cout << "\n--- Inventory Items ---\n";
    for (const auto& item : items) {
        std::cout << "- " << item->getName()
                  << " (Type: " << item->getType()
                  << ", Value: " << item->getValue() << ")\n";
    }
}

json Inventory::toJson() const {
    json arr = json::array();

    for (auto& item : items) {
        arr.push_back(item->toJson());
    }

    return arr;
}

void Inventory::fromJson(const json& j) {
    items.clear();

    for (const auto& element : j) {
        std::string type = element.at("type");

        if (type == "weapon") {
            auto w = std::make_unique<Weapon>();
            w->fromJson(element);
            items.push_back(std::move(w));
        }
        else if (type == "armor") {
            auto a = std::make_unique<Armor>();
            a->fromJson(element);
            items.push_back(std::move(a));
        }
        else if (type == "potion") {
            auto p = std::make_unique<Potion>();
            p->fromJson(element);
            items.push_back(std::move(p));
        }
        else {
            auto it = std::make_unique<Item>();
            it->fromJson(element);
            items.push_back(std::move(it));
        }
    }
}
