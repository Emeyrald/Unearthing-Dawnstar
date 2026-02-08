cmake_minimum_required(VERSION 3.0)
project(UnearthingDawnstar)

set(CMAKE_CXX_STANDARD 17)

# ----------------------------------------------------
# FetchContent for external dependencies
# ----------------------------------------------------
include(FetchContent)

# JSON Library
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(nlohmann_json)

# GoogleTest
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_disable_pthreads ON CACHE BOOL "Disable pthreads for gtest" FORCE)
FetchContent_MakeAvailable(googletest)

# ----------------------------------------------------
# Build Game Library
# ----------------------------------------------------
add_library(gameLib
    src/player.cpp
    src/stats.cpp
    src/playerStats.cpp
    src/levelManager.cpp
    src/skill.cpp
    src/skillManager.cpp
    src/inventory.cpp
    src/item.cpp
    src/inventoryManager.cpp
    src/weapon.cpp
    src/armor.cpp
    src/potion.cpp
    src/building.cpp
    src/shop.cpp
    src/npc.cpp
    src/area.cpp
    src/town.cpp
    src/dungeon.cpp
    src/enemy.cpp
    src/gameDriver.cpp
)

target_include_directories(gameLib PUBLIC header)
target_link_libraries(gameLib PUBLIC nlohmann_json::nlohmann_json)

# ----------------------------------------------------
# Build Game Executable
# ----------------------------------------------------
add_executable(game
    src/main.cpp
)

target_link_libraries(game PRIVATE gameLib)

# ----------------------------------------------------
# Build Tests
# ----------------------------------------------------
add_executable(runTests
    tests/test_stats.cpp
    tests/test_playerStats.cpp
    tests/test_skill.cpp
    tests/test_skillManager.cpp
    tests/test_item.cpp
    tests/test_weaponArmorPotion.cpp
    tests/test_inventory.cpp
    tests/test_enemy.cpp
    tests/test_player.cpp
)

target_link_libraries(runTests PRIVATE
    gameLib
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(runTests)