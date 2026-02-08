#include <gtest/gtest.h>
#include "../header/stats.hpp"

TEST(StatsTest, HealthOperations) {
    Stats s;
    s.setHealth(100);
    EXPECT_EQ(s.getHealth(), 100);

    s.takeDamage(30);
    EXPECT_EQ(s.getHealth(), 80);

    s.heal(20);
    EXPECT_EQ(s.getHealth(), 100);

    s.heal(500);
    EXPECT_EQ(s.getHealth(), s.getMaxHealth());
}

TEST(StatsTest, DefenseAndTempBuff) {
    Stats s;
    s.setDefense(5);
    EXPECT_EQ(s.getDefense(), 5);

    s.increaseDefenseTemporarily(3);
    EXPECT_EQ(s.getTempDefense(), 13);

    s.resetTempDefense();
    EXPECT_EQ(s.getTempDefense(), 0);
}