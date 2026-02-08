#ifndef INVENTORYMANAGER_HPP
#define INVENTORYMANAGER_HPP

#include <memory>

// Forward declarations
class Player;
class Item;
class Weapon;
class Armor;
class Potion;

class InventoryManager {
private:
    Player* player; // Allows access to stats, inventory, etc.
    std::unique_ptr<Weapon> equippedWeapon;
    std::unique_ptr<Armor> equippedArmor;
public:
    InventoryManager(Player* player);
    ~InventoryManager();
    
    void equipItem();
    void unequipItem();
    void useItem();
};

#endif // INVENTORYMANAGER_HPP