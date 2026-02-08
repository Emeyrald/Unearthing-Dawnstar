#include <gtest/gtest.h>
#include "../header/skillManager.hpp"
#include "../header/playerStats.hpp"

TEST(SkillManagerTest, UnlockBasedOnLevel) {
    PlayerStats ps;
    ps.setLevel(5);

    SkillManager sm;
    sm.unlockSkill(ps, "swordsman");

    EXPECT_EQ(sm.unlockedSkills.size(), 2);
}

TEST(SkillManagerTest, JsonRoundTrip) {
    PlayerStats ps;
    ps.setLevel(10);

    SkillManager sm;
    sm.unlockSkill(ps, "wizard");

    json j = sm.toJson();

    SkillManager restored;
    restored.fromJson(j);

    EXPECT_EQ(restored.unlockedSkills.size(), sm.unlockedSkills.size());
}