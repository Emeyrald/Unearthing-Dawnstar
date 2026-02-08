#include "../header/gameDriver.hpp"
#include "../header/town.hpp"
#include "../header/dungeon.hpp"
#include "../header/shop.hpp"
#include "../header/npc.hpp"
#include "../header/enemy.hpp"
#include "../header/item.hpp"
#include "../header/weapon.hpp"
#include "../header/armor.hpp"
#include "../header/potion.hpp"
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <fstream>
using nlohmann::json;

GameDriver::GameDriver() : player() {}

GameDriver::~GameDriver() {}

void GameDriver::run() {
    mainMenu();
}

void GameDriver::saveGame() {
    json j;
    j["player"] = player.toJson();
    std::ofstream file("save.json");
    file << j.dump(4);
}

void GameDriver::loadGame() {
    std::ifstream file("save.json");
    if (!file) return;

    json j;
    file >> j;

    player.fromJson(j.at("player"));
}

void GameDriver::mainMenu() {
    int choice;
    std::string prompt = "\n=== Main Menu ===\n"
                         "1. New Game\n"
                         "2. Load Game\n"
                         "3. Quit\n"
                         "Enter choice: ";
    while (true) {
        std::cout << prompt;
        validateInputInteger(choice, prompt);
        
        if (choice == 1) {
            characterCreation();
            initWorld();
            gameplayLoop();
        }
        else if (choice == 2) {
            loadGame();
            gameplayLoop();
        }
        else if (choice == 3) {
            return;
        }
    }
}

void GameDriver::characterCreation() {
    std::cout << "\n=== Character Creation ===\n";
    
    std::string race, pclass;
    char confirm;
    do {
        do {
            std::cout << "Choose race (human/elf/dwarf): ";
            std::cin >> race;
        } while (race != "human" && race != "elf" && race != "dwarf");

        if(race == "human")
            std::cout << "Human - A well rounded race with no strengths or weaknesses.\n";
        else if(race == "elf")
            std::cout << "Elf - A race blessed with great mana but lower health and defense.\n";
        else if(race == "dwarf")
            std::cout << "Dwarf - A sturdy race with high health and defense but lower mana.\n";
        std::cout << "Confirm choice? (y/n): ";
        std::cin >> confirm;
    } while (confirm != 'y' && confirm != 'Y');

    player.setRace(race);
    player.getStats().applyRaceBonuses(race);

    do {
        do {
            std::cout << "Choose class (swordsman/ranger/wizard): ";
            std::cin >> pclass;
            player.setClass(pclass);
        } while (pclass != "swordsman" && pclass != "ranger" && pclass != "wizard");

        if(pclass == "swordsman")
            std::cout << "Swordsman - A melee fighter skilled in the sword.\n";
        else if(pclass == "ranger")
            std::cout << "Ranger - A ranged fighter using a bow and arrow.\n";
        else if(pclass == "wizard")
            std::cout << "Wizard - A magical fighter requiring great mana to show their strength.\n";
        std::cout << "Confirm choice? (y/n): ";
        std::cin >> confirm;
    } while (confirm != 'y' && confirm != 'Y');

    player.getSkillManager().unlockSkill(player.getStats(), pclass);
    player.getSkillManager().equipSkill();
    std::cout << "\nCharacter created!\n";
}

void GameDriver::initWorld() {
    // Create Town
    auto town = std::make_unique<Town>();
    town->setName("Riverwood");
    town->setDescription("A peaceful riverside town.");

    // Create NPC
    NPC innkeeper;
    innkeeper.setName("Garen");
    innkeeper.setDialogue({"Welcome traveler!", "Care for a drink?"});

    // Create Inn Building
    auto inn = std::make_unique<Building>();
    inn->setName("Sleeping Giant Inn");
    inn->setDescription("A warm inn with friendly faces.");
    inn->setNPC(innkeeper);

    town->addBuilding(std::move(inn));

    // Create Shop
    auto shop = std::make_unique<Shop>();
    shop->setName("Steel & Silk Armory");

    shop->getInventory().addItem(std::make_unique<Weapon>("Iron Sword", 30, 5));
    shop->getInventory().addItem(std::make_unique<Armor>("Hide Armor", 20, 3));
    shop->getInventory().addItem(std::make_unique<Potion>("Small Potion", 15, 25));

    town->addBuilding(std::move(shop));

    // Create Dungeon
    auto cave = std::make_unique<Dungeon>();
    cave->setName("Shadow Cave");
    cave->setDescription("A dark cave where monsters lurk.");

    Stats goblinStats;
    goblinStats.setHealth(20);
    goblinStats.setDefense(1);
    goblinStats.setLevel(1);

    Stats goblin2Stats;
    goblin2Stats.setHealth(100);
    goblin2Stats.setDefense(1);
    goblin2Stats.setLevel(5);

    cave->addEnemy(std::make_unique<Enemy>("Goblin", 200, 100, goblinStats));
    cave->addEnemy(std::make_unique<Enemy>("Goblin2", 200, 100, goblin2Stats));

    // Add areas to world
    worldAreas.push_back(std::move(town));
    worldAreas.push_back(std::move(cave));

    std::cout << "\nWorld initialized.\n";
}

void GameDriver::gameplayLoop() {
    int choice;
    std::string prompt;

    while (true) {
        prompt = "\n=== Game Menu ===\n"
                 "1. Explore Area\n"
                 "2. Show Stats\n"
                 "3. Manage Inventory\n"
                 "4. Manage Skills\n"
                 "5. Save\n"
                 "6. Save and Quit\n"
                 "Enter choice: ";
        std::cout << prompt;
        validateInputInteger(choice, prompt);

        if (choice == 1) {
            prompt = "Which area?\n"
                     "Enter choice: ";
            std::cout << "\n";
            for (size_t i = 0; i < worldAreas.size(); i++) {
                std::cout << i+1 << ". " << worldAreas[i]->getName() << "\n";
            }
            std::cout << prompt;
            validateInputInteger(choice, prompt);

            if (choice >= 1 && choice <= worldAreas.size()) {
                ExploreArea(worldAreas[choice - 1].get());
            }
        }
        else if (choice == 2) {
            player.displayStats();
        }
        else if (choice == 3) {
            prompt = "\n=== Inventory Menu ===\n"
                     "1. View Inventory\n"
                     "2. Equip an Item\n"
                     "3. Unequip an Item\n"
                     "4. Use an Item\n"
                     "5. Go Back to Menu\n"
                     "Enter choice: ";
            while (true) {
                std::cout << prompt;
                validateInputInteger(choice, prompt);
                if (choice == 1) {
                    player.getInventory().displayItems();
                }
                else if (choice == 2) {
                    player.getInventoryManager()->equipItem();
                }
                else if (choice == 3) {
                    player.getInventoryManager()->unequipItem();
                }
                else if (choice == 4) {
                    player.getInventoryManager()->useItem();
                }
                else if (choice == 5) {
                    break;
                }
            }
        }
        else if (choice == 4) {
            prompt = "\n=== Skills Menu ===\n"
                     "1. View Skills\n"
                     "2. Equip a Skill\n"
                     "3. Unequip a Skill\n"
                     "4. Go Back to Menu\n"
                     "Enter choice: ";
            while (true) {
                std::cout << prompt;
                validateInputInteger(choice, prompt);

                if (choice == 1) {
                    player.getSkillManager().viewSkills();
                }
                else if (choice == 2) {
                    player.getSkillManager().equipSkill();
                }
                else if (choice == 3) {
                    player.getSkillManager().unequipSkill();
                }
                else if (choice == 4) {
                    break;
                }
            }
        }
        else if (choice == 5) {
            saveGame();
        }
        else if (choice == 6) {
            saveGame();
            return;
        }
    }
}

void GameDriver::ExploreArea(Area* area) {
    std::cout << "\nExploring: " << area->getName() << "\n";

    // Town
    if (Town* t = dynamic_cast<Town*>(area)) {
        std::cout << "This is a town.\n";

        auto& buildings = t->getBuildings();

        for (size_t i = 0; i < buildings.size(); i++) {
            std::cout << i+1 << ". " << buildings[i]->getName() << "\n";
        }

        int choice;
        std::string prompt = "\nChoose a building to enter: ";
        std::cout << prompt;
        validateInputInteger(choice, prompt);

        if (choice > 0 && choice <= buildings.size()) {
            Building* b = buildings[choice - 1].get();

            if (Shop* shop = dynamic_cast<Shop*>(b)) {
                handleShop(shop);
                return;
            }

            if (b->getName() == "Sleeping Giant Inn") {
                player.getStats().rest();
            }

            NPC npc = b->getNPC();
            handleNPC(&npc);
            return;
        }
    }

    // Dungeon
    if (Dungeon* d = dynamic_cast<Dungeon*>(area)) {
        std::cout << "A dungeon filled with enemies!\n";
        auto& enemies = d->getEnemies();

        if (!enemies.empty()) {
            Enemy* enemy = enemies[0].get();   // fight the first enemy
            handleCombat(enemy);

            // If the enemy died, remove it from the dungeon
            if (enemy->getStats().getHealth() <= 0) {
                enemies.erase(enemies.begin());  // removes the first one
                std::cout << "Enemy defeated! " << enemies.size()
                        << " enemies remain.\n";
            }
        } else {
            std::cout << "This dungeon has no enemies left.\n";
        }
        return;
    }
}

void GameDriver::handleCombat(Enemy* enemy) {
    std::cout << "\nA wild " << enemy->getName() << " appears!\n\n";

    int playerBuffTurns = 0;
    int enemyBuffTurns = 0;

    while (player.getStats().getHealth() > 0 && enemy->getStats().getHealth() > 0) {

        // ============================================
        // PLAYER TURN
        // ============================================
        std::cout << "\n-- YOUR TURN --\n";
        std::cout << "HP: " << player.getStats().getHealth()
                  << "   Mana: " << player.getStats().getMana() << "\n";

        auto& skills = player.getSkillManager().equippedSkills;

        std::cout << "Choose a skill:\n";
        for (size_t i = 0; i < skills.size(); i++) {
            std::cout << i+1 << ". " << skills[i].getName()
                      << " (Cost: " << skills[i].getManaCost()
                      << ", Type: " << skills[i].getUse()
                      << ")\n";
        }

        int choice;
        std::string prompt = "\nEnter choice: ";
        validateInputInteger(choice, prompt);

        Skill* chosen = nullptr;

        if (choice < 1 || choice > (int)skills.size()) {
            std::cout << "Invalid choice! Turn skipped.\n";
        } else {
            chosen = &skills[choice - 1];

            // Check mana
            if (player.getStats().getMana() < chosen->getManaCost()) {
                std::cout << "Not enough mana! Turn skipped.\n";
            }
            else if (chosen->getUse() == "Damage") {
                int dmg = chosen->getDamage()
                        + player.getStats().getEquippedWeaponBonus()
                        - enemy->getStats().getDefense();

                if (dmg < 0) dmg = 0;

                enemy->getStats().takeDamage(dmg);
                player.getStats().reduceMana(chosen->getManaCost());

                std::cout << "You used " << chosen->getName()
                          << " dealing " << dmg << " damage!\n";
            }
            else if (chosen->getUse() == "Buff") {
                int buff = chosen->getBuff();
                player.getStats().increaseDefenseTemporarily(buff);

                playerBuffTurns = 2; // lasts 2 turns
                player.getStats().reduceMana(chosen->getManaCost());

                std::cout << "You used " << chosen->getName()
                          << " increasing defense by " << buff
                          << " for 2 turns!\n";
            }
        }

        // Check enemy death
        if (enemy->getStats().getHealth() <= 0) {
            std::cout << "\nYou defeated " << enemy->getName() << "!\n";
            player.getLevelManager()->addExperience(enemy->dropExp());
            player.getStats().addGold(enemy->dropGold());
            return;
        }

        // ============================================
        // ENEMY TURN
        // ============================================
        std::cout << "\n-- ENEMY TURN --\n";

        int dmg;
        // Enemy attack
        if (enemy->getName() == "Goblin") {
            dmg = (std::rand() % 8 + 4) - (player.getStats().getDefense()/2);
        } else {
            // NOT A BUG. THIS IS SO GOBLIN2 ONE SHOTS THE PLAYER AND DEMONSTRATES THE GAME OVER SCREEN
            // SO WE CAN DEMO HOW YOU CAN LOAD YOUR LAST SAVE AFTER YOU DIE
            dmg = 500;
        }
        if (dmg < 0) dmg = 0;
        std::cout << enemy->getName()
                  << " attacks!\n";
        player.getStats().takeDamage(dmg);

        // Check player death
        if (player.getStats().getHealth() <= 0) {
            std::cout << "\nYou died...\nGAME OVER\n";
            mainMenu();
            return;
        }

        // =============================
        // BUFF TURN REDUCTION
        // =============================
        if (playerBuffTurns > 0) {
            playerBuffTurns--;
            if (playerBuffTurns == 0) {
                player.getStats().resetTempDefense();
            }
        }
    }
}

void GameDriver::handleShop(Shop* shop) {
    std::cout << "\nWelcome to " << shop->getName() << "!\n";

    int choice;
    std::string prompt = "\n=== Shop Menu ===\n"
                         "1. Buy\n"
                         "2. Sell\n"
                         "3. Leave\n"
                         "Enter choice: ";
    std::cout << prompt;
    validateInputInteger(choice, prompt);

    if (choice == 1)
        shop->buy(player);
    else if (choice == 2)
        shop->sell(player);
}

void GameDriver::handleNPC(NPC* npc) {
    npc->talk();
}

void GameDriver::validateInputInteger(int& input, std::string prompt) {

    while (true) {
        if (std::cin >> input)
            break;
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\n" << prompt;
        }
    }
}