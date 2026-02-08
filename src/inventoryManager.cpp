#include "../header/inventoryManager.hpp"
#include "../header/player.hpp"
#include "../header/inventory.hpp"
#include "../header/item.hpp"
#include "../header/weapon.hpp"
#include "../header/armor.hpp"
#include "../header/potion.hpp"
#include <memory>
#include <iostream>
using std::cout;
using std::cin;

InventoryManager::InventoryManager(Player* player)
    : player(player) {}

InventoryManager::~InventoryManager() {}

void InventoryManager::equipItem() {
    auto& inv = player->getInventory().getItems(); // vector<unique_ptr<Item>>&

    if (inv.empty()) {
        std::cout << "Your inventory is empty.\n";
        return;
    }

    std::cout << "\n--- Choose an item to equip ---\n";
    for (size_t i = 0; i < inv.size(); i++) {
        std::cout << i + 1 << ". " << inv[i]->getName()
                  << " (" << inv[i]->getType() << ")\n";
    }

    int choice;
    std::cin >> choice;

    if (choice < 1 || choice > (int)inv.size()) {
        std::cout << "Invalid choice.\n";
        return;
    }

    // Take ownership of selected item
    std::unique_ptr<Item> selected = std::move(inv[choice - 1]);
    inv.erase(inv.begin() + (choice - 1));

    // Handle weapon
    if (Weapon* w = dynamic_cast<Weapon*>(selected.get())) {

        // Put old weapon back into inventory
        if (equippedWeapon) {
            inv.push_back(std::move(equippedWeapon));
        }

        // Equip new weapon
        equippedWeapon = std::unique_ptr<Weapon>(static_cast<Weapon*>(selected.release()));
        player->getStats().setEquippedWeaponBonus(equippedWeapon->getDamageBonus());

        std::cout << "Equipped weapon: " << equippedWeapon->getName() << "\n";
        return;
    }

    // Handle armor
    if (Armor* a = dynamic_cast<Armor*>(selected.get())) {

        if (equippedArmor) {
            inv.push_back(std::move(equippedArmor));
        }

        equippedArmor = std::unique_ptr<Armor>(static_cast<Armor*>(selected.release()));
        player->getStats().setEquippedArmorBonus(equippedArmor->getDefenseBonus());

        std::cout << "Equipped armor: " << equippedArmor->getName() << "\n";
        return;
    }

    // Not equipable so it returns to inventory
    std::cout << "You cannot equip this item.\n";
    inv.push_back(std::move(selected));
}

void InventoryManager::unequipItem() {
    int choice;

    std::cout << "\nWhat do you want to unequip?\n1. Weapon\n2. Armor\n";
    std::cin >> choice;

    auto& inv = player->getInventory().getItems(); // vector<unique_ptr<Item>>

    if (choice == 1) {
        if (!equippedWeapon) {
            std::cout << "No weapon equipped.\n";
            return;
        }

        // Move weapon back into the inventory
        inv.push_back(std::move(equippedWeapon));
        std::cout << "Unequipped weapon.\n";

        player->getStats().setEquippedWeaponBonus(0);
        return;
    }

    else if (choice == 2) {
        if (!equippedArmor) {
            std::cout << "No armor equipped.\n";
            return;
        }

        // Move armor back into the inventory
        inv.push_back(std::move(equippedArmor));
        std::cout << "Unequipped armor.\n";

        player->getStats().setEquippedArmorBonus(0);
        return;
    }

    else {
        std::cout << "Invalid choice.\n";
    }
}

void InventoryManager::useItem() {
    auto& inv = player->getInventory().getItems();

    if (inv.empty()) {
        cout << "Inventory is empty.\n";
        return;
    }

    cout << "\nSelect a potion to USE:\n";

    // collect potion indices
    std::vector<int> indices;
    for (size_t i = 0; i < inv.size(); i++) {
        if (inv[i]->getType() == "potion") {
            indices.push_back(i);
            cout << indices.size() << ". " << inv[i]->getName() << "\n";
        }
    }

    if (indices.empty()) {
        cout << "You have no potions.\n";
        return;
    }

    int choice;
    cin >> choice;

    if (choice < 1 || choice > (int)indices.size()) {
        cout << "Invalid choice.\n";
        return;
    }

    Item* selected = inv[indices[choice - 1]].get();
    Potion* p = dynamic_cast<Potion*>(selected);

    if (!p) return;

    int heal = p->getHealAmount();

    player->getStats().setHealth(
        std::min(player->getStats().getMaxHealth(),
            player->getStats().getHealth() + heal)
    );

    cout << "Used " << p->getName() << " and restored "
         << heal << " HP.\n";

    inv.erase(inv.begin() + indices[choice - 1]);
}