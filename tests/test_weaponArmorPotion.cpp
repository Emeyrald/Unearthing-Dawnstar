#include <gtest/gtest.h>
#include "../header/weapon.hpp"
#include "../header/armor.hpp"
#include "../header/potion.hpp"

TEST(WeaponTest, Json) {
    Weapon w("Sword", 20, 6);
    json j = w.toJson();

    Weapon restored;
    restored.fromJson(j);

    EXPECT_EQ(restored.getDamageBonus(), 6);
}

TEST(ArmorTest, Json) {
    Armor a("Chainmail", 30, 4);
    json j = a.toJson();

    Armor restored;
    restored.fromJson(j);

    EXPECT_EQ(restored.getDefenseBonus(), 4);
}

TEST(PotionTest, Json) {
    Potion p("Heal", 10, 25);
    json j = p.toJson();

    Potion restored;
    restored.fromJson(j);

    EXPECT_EQ(restored.getHealAmount(), 25);
}