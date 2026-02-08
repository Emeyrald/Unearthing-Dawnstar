#ifndef GAMEDRIVER_HPP
#define GAMEDRIVER_HPP

#include <vector>
#include <memory>
#include "player.hpp"
//#include "questManager.hpp"
#include "area.hpp"
#include "enemy.hpp"
#include "shop.hpp"
#include "npc.hpp"
#include <nlohmann/json.hpp>
using nlohmann::json;

class GameDriver {
private:
    Player player;
    //QuestManager questManager;
    std::vector<std::unique_ptr<Area>> worldAreas;

    void mainMenu();
    void characterCreation();
    void initWorld();
    void gameplayLoop();
    void ExploreArea(Area* area);
    void handleCombat(Enemy* enemy);
    void handleShop(Shop* shop);
    void handleNPC(NPC* npc);
    void validateInputInteger(int& input, std::string prompt);
public:
    GameDriver();
    ~GameDriver();
    
    void run();
    void saveGame();
    void loadGame();
};

#endif // GAMEDRIVER_HPP