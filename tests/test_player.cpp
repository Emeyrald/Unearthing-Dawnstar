#include <gtest/gtest.h>
#include "../header/player.hpp"
#include "../header/weapon.hpp"
#include "../header/skillManager.hpp"
#include "../header/playerStats.hpp"
#include <nlohmann/json.hpp>

using nlohmann::json;

TEST(PlayerTest, Initialization) {
    Player p;

    // Player should start with initialized subsystems
    EXPECT_NO_THROW(p.getStats());
    EXPECT_NO_THROW(p.getInventory());
    EXPECT_NE(p.getInventoryManager(), nullptr);
    EXPECT_NO_THROW(p.getSkillManager());
}

TEST(PlayerTest, SetRaceAndClass) {
    Player p;

    p.setRace("elf");
    EXPECT_EQ(p.getRace(), "elf");

    p.setClass("wizard");
    EXPECT_EQ(p.getClass(), "wizard");
}

TEST(PlayerTest, InventoryOperations) {
    Player p;

    p.getInventory().addItem(std::make_unique<Weapon>("Iron Sword", 20, 5));
    EXPECT_EQ(p.getInventory().getItems().size(), 1);

    Item* weaponPtr = p.getInventory().getItems()[0].get();
    p.getInventory().removeItem(weaponPtr);

    EXPECT_TRUE(p.getInventory().getItems().empty());
}

TEST(PlayerTest, SkillManagerAccessible) {
    Player p;

    EXPECT_NE(&p.getSkillManager(), nullptr);

    // Attempt unlocking low-level skill
    p.setClass("swordsman");

    p.getStats().setLevel(1);
    p.getSkillManager().unlockSkill(p.getStats(), p.getClass());

    EXPECT_GE(p.getSkillManager().unlockedSkills.size(), 1);
}

TEST(PlayerTest, JsonRoundTrip) {
    Player p;

    p.setRace("elf");
    p.setClass("wizard");

    p.getStats().setHealth(78);
    p.getInventory().addItem(std::make_unique<Weapon>("Staff", 40, 8));

    json saved = p.toJson();

    Player restored;
    restored.fromJson(saved);

    EXPECT_EQ(restored.getRace(), "elf");
    EXPECT_EQ(restored.getClass(), "wizard");
    EXPECT_EQ(restored.getStats().getHealth(), 78);
    EXPECT_EQ(restored.getInventory().getItems().size(), 1);
}

TEST(PlayerTest, LevelUpThroughExperience) {
    Player p;
    p.setClass("swordsman");

    auto& stats = p.getStats();
    int startLevel = stats.getLevel();
    int xpNeeded = stats.getExpToNext();

    p.getLevelManager()->addExperience(xpNeeded);

    EXPECT_EQ(stats.getLevel(), startLevel + 1);
}
