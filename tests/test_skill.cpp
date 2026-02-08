#include <gtest/gtest.h>
#include "../header/skill.hpp"

TEST(SkillTest, BasicData) {
    Skill s("Slash", "A basic attack", "Damage", 12, 0, 3);
    EXPECT_EQ(s.getName(), "Slash");
    EXPECT_EQ(s.getDamage(), 12);
    EXPECT_EQ(s.getBuff(), 0);
    EXPECT_EQ(s.getManaCost(), 3);
}