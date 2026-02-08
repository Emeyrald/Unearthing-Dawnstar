#include <gtest/gtest.h>
#include "../header/inventory.hpp"
#include "../header/weapon.hpp"
#include "../header/armor.hpp"

TEST(InventoryTest, AddRemove) {
    Inventory inv;
    inv.addItem(std::make_unique<Weapon>("Sword", 10, 2));

    EXPECT_EQ(inv.getItems().size(), 1);

    Item* ptr = inv.getItems()[0].get();
    inv.removeItem(ptr);
    EXPECT_EQ(inv.getItems().size(), 0);
}

TEST(InventoryTest, JsonRoundTrip) {
    Inventory inv;
    inv.addItem(std::make_unique<Armor>("Shield", 15, 5));

    json j = inv.toJson();

    Inventory restored;
    restored.fromJson(j);

    EXPECT_EQ(restored.getItems().size(), 1);
    EXPECT_EQ(restored.getItems()[0]->getName(), "Shield");
}