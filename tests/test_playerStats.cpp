#include <gtest/gtest.h>
#include "../header/playerStats.hpp"
#include <nlohmann/json.hpp>

TEST(PlayerStatsTest, Gold) {
    PlayerStats ps;
    ps.setGold(50);
    ps.addGold(25);
    EXPECT_EQ(ps.getGold(), 75);
    ps.subtractGold(40);
    EXPECT_EQ(ps.getGold(), 35);
}

TEST(PlayerStatsTest, Bonuses) {
    PlayerStats ps;
    ps.setEquippedWeaponBonus(10);
    ps.setEquippedArmorBonus(4);

    EXPECT_EQ(ps.getEquippedWeaponBonus(), 10);
    EXPECT_EQ(ps.getEquippedArmorBonus(), 4);
}

TEST(PlayerStatsTest, JsonSaveLoad) {
    PlayerStats ps;
    ps.setHealth(56);
    ps.setGold(12);

    json j = ps.toJson();

    PlayerStats restored;
    restored.fromJson(j);

    EXPECT_EQ(restored.getHealth(), 56);
    EXPECT_EQ(restored.getGold(), 12);
}