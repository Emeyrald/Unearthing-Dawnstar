#include "../header/shop.hpp"
#include "../header/inventory.hpp"
#include "../header/item.hpp"
#include "../header/player.hpp"

Shop::Shop() : Building(), shopInventory() {}

Shop::~Shop() {}

// Return reference so inventory is not copied
Inventory& Shop::getInventory() {
    return shopInventory;
}

// -------------------------------
// Player buys from the shop
// -------------------------------
void Shop::buy(Player& player) {
    auto& shopItems = shopInventory.getItems(); // vector<unique_ptr<Item>>&

    if (shopItems.empty()) {
        std::cout << "The shop has nothing for sale.\n";
        return;
    }

    std::cout << "\n--- Items for Sale ---\n";
    for (size_t i = 0; i < shopItems.size(); i++) {
        std::cout << i+1 << ". " << shopItems[i]->getName()
                  << " (Cost: " << shopItems[i]->getValue() << " gold)\n";
    }

    int choice;
    std::cin >> choice;

    if (choice < 1 || choice > (int)shopItems.size()) {
        std::cout << "Invalid choice.\n";
        return;
    }

    // unique_ptr<Item>&
    std::unique_ptr<Item>& itemPtr = shopItems[choice - 1];

    int cost = itemPtr->getValue();

    if (player.getStats().getGold() < cost) {
        std::cout << "You cannot afford that.\n";
        return;
    }

    // Transfer ownership: move unique_ptr from shop → player
    player.getInventory().addItem(std::move(itemPtr));

    // Remove empty slot
    shopItems.erase(shopItems.begin() + (choice - 1));

    player.getStats().setGold(player.getStats().getGold() - cost);

    std::cout << "You purchased " << player.getInventory().getItems().back()->getName() << "!\n";
}


// -------------------------------
// Player sells an item to the shop
// -------------------------------
void Shop::sell(Player& player) {
    auto& inv = player.getInventory().getItems(); // vector<unique_ptr<Item>>&

    if (inv.empty()) {
        std::cout << "You have nothing to sell.\n";
        return;
    }

    std::cout << "\n--- Items You Can Sell ---\n";
    for (size_t i = 0; i < inv.size(); i++) {
        std::cout << i+1 << ". " << inv[i]->getName()
                  << " (Value: " << inv[i]->getValue() << " gold)\n";
    }

    int choice;
    std::cin >> choice;

    if (choice < 1 || choice > (int)inv.size()) {
        std::cout << "Invalid choice.\n";
        return;
    }

    // unique_ptr<Item>&
    std::unique_ptr<Item>& itemPtr = inv[choice - 1];
    int value = itemPtr->getValue();

    // Transfer ownership: move from player → shop
    shopInventory.addItem(std::move(itemPtr));

    // Remove empty slot
    inv.erase(inv.begin() + (choice - 1));

    player.getStats().setGold(player.getStats().getGold() + value);

    std::cout << "Sold item for " << value << " gold!\n";
}
