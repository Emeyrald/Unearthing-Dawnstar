#include <gtest/gtest.h>
#include "../header/item.hpp"
#include <nlohmann/json.hpp>

TEST(ItemTest, JsonSaveLoad) {
    Item i("Rock", "misc", 3);
    json j = i.toJson();

    Item restored;
    restored.fromJson(j);

    EXPECT_EQ(restored.getName(), "Rock");
    EXPECT_EQ(restored.getValue(), 3);
}