#include <gtest/gtest.h>
#include "../header/enemy.hpp"

TEST(EnemyTest, DropsAndStats) {
    Stats s;
    s.setHealth(40);
    Enemy e("Goblin", 10, 5, s);

    EXPECT_EQ(e.dropExp(), 10);
    EXPECT_EQ(e.dropGold(), 5);
    EXPECT_EQ(e.getStats().getHealth(), 40);
}