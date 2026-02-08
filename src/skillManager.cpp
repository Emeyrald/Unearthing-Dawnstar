#include "../header/skillManager.hpp"
#include "../header/skill.hpp"
#include "../header/playerStats.hpp"
#include <vector>
#include <nlohmann/json.hpp>
#include <utility>
using nlohmann::json;

using std::vector;

SkillManager::SkillManager() {
    // Swordsman Skills
    swordsmanSkills.emplace_back("Slash", "A quick sword strike.", "Damage", 12, 0, 0);
    swordsmanSkills.emplace_back("Power Strike", "A strong overhead attack.", "Damage", 20, 0, 5);
    swordsmanSkills.emplace_back("Shield Block", "Raise shield to block attacks.", "Buff", 0, 5, 3);
    swordsmanSkills.emplace_back("Flaming Slash", "A sword strike imbued with fire.", "Damage", 25, 0, 7);

    // Ranger Skills
    rangerSkills.emplace_back("Arrow Shot", "Shoot an arrow at the enemy.", "Damage", 10, 0, 0);
    rangerSkills.emplace_back("Double Shot", "Shoot two arrows quickly.", "Damage", 18, 0, 4);
    rangerSkills.emplace_back("Dodge", "Evade the next attack.", "Buff", 0, 5, 2);
    rangerSkills.emplace_back("Lightning Shot", "Shoot an electrified arrow.", "Damage", 22, 0, 6);

    // Wizard Skills
    wizardSkills.emplace_back("Ice Shard", "Shoot a shard of ice.", "Damage", 12, 0, 3);
    wizardSkills.emplace_back("Fireball", "Cast a small fireball.", "Damage", 18, 0, 5);
    wizardSkills.emplace_back("Magic Shield", "Raise a protective barrier.", "Buff", 0, 5, 4);
    wizardSkills.emplace_back("Immolation", "Engulf the enemy in flames.", "Damage", 25, 0, 7);

};
SkillManager::~SkillManager() {};

void SkillManager::unlockSkill(PlayerStats& stats, const std::string& playerClass) {
    const int level = stats.getLevel();

    const vector<Skill>* classSkills = nullptr;

    if (playerClass == "swordsman") classSkills = &swordsmanSkills;
    else if (playerClass == "ranger") classSkills = &rangerSkills;
    else if (playerClass == "wizard") classSkills = &wizardSkills;

    int expectedUnlocks = 0;
    if (level >= 1) expectedUnlocks++;
    if (level >= 5) expectedUnlocks++;
    if (level >= 9) expectedUnlocks++;
    if (level >= 13) expectedUnlocks++;

    int currentlyUnlocked = unlockedSkills.size();

    for (int i = currentlyUnlocked; i < expectedUnlocks && i < classSkills->size(); i++) {
        unlockedSkills.push_back((*classSkills)[i]);
        std::cout << "Unlocked skill: " << (*classSkills)[i].getName() << "!\n";
    }
}

void SkillManager::equipSkill() {
    if (unlockedSkills.empty()) {
        std::cout << "You have no unlocked skills." << "\n";
        return;
    }

    std::cout << "\n" << "Choose a skill to equip:" << "\n";
    for (size_t i = 0; i < unlockedSkills.size(); i++) {
        std::cout << i + 1 << ". " << unlockedSkills[i].getName() << " (" << unlockedSkills[i].getUse() << "): " << unlockedSkills[i].getDescription() << "\n";
        if (unlockedSkills[i].getDamage() != 0) {
            std::cout << "- Damage: " << unlockedSkills[i].getDamage();
        } else {
            std::cout << "- Defense Buff: " << unlockedSkills[i].getBuff();
        }
        std::cout << ", Mana Cost: " << unlockedSkills[i].getManaCost() << "\n";
    }

    std::cout << "Select a skill to equip (1-" << unlockedSkills.size() << "): ";
    int choice;
    std::cin >> choice;

    if (choice < 1 || choice > unlockedSkills.size()) {
        std::cout << "Invalid choice." << "\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        equipSkill();
        return;
    }

    Skill selected = unlockedSkills[choice - 1];

    // Check duplicates
    for (auto& skill: equippedSkills) {
        if (skill.getName() == selected.getName()) {
            std::cout << "Skill already equipped." << "\n";
            equipSkill();
            return;
        }
    }

    // Limit to 4 equipped skills
    if (equippedSkills.size() >= 4) {
        std::cout << "You already have 4 equipped skills." << "\n";
        return;
    }

    equippedSkills.push_back(selected);
    std::cout << "Equipped skill: " << selected.getName() << "!" << "\n";
}

void SkillManager::unequipSkill() {
    if (equippedSkills.empty()) {
        std::cout << "You have no equipped skills to unequip." << "\n";
        return;
    }

    std::cout << "\n" << "--- Equipped Skills ---" << "\n";
    for (size_t i = 0; i < equippedSkills.size(); i++) {
        std::cout << i + 1 << ". " << equippedSkills[i].getName() << "\n";
    }


    std::cout << "Select a skill to unequip (1-" << equippedSkills.size() << "): ";
    int choice;
    std::cin >> choice;

    if (choice < 1 || choice > (int)equippedSkills.size()) {
        std::cout << "Invalid choice" << "\n";
        unequipSkill();
        return;
    }

    Skill removeSkill = equippedSkills[choice - 1];

    // Remove from equipped list
    equippedSkills.erase(equippedSkills.begin() + (choice - 1));

    std::cout << removeSkill.getName() << " has been unequipped." << "\n";
}

void SkillManager::viewSkills() {
    std::cout << "\n" << "--- Equipped Skills ---" << "\n";
    if (equippedSkills.empty()) std::cout << "None" << "\n";
    for (auto& skill : equippedSkills) {
        std::cout << "- " << skill.getName() << "\n";
    }
    std::cout << "\n" << "--- Unlocked Skills ---" << "\n";
    if (unlockedSkills.empty()) std::cout << "None" << "\n";
    for (auto& skill : unlockedSkills) {
        std::cout << "- " << skill.getName() << " (" << skill.getUse() << "): " << skill.getDescription() << "\n";
        if (skill.getDamage() != 0) {
            std::cout << "-- Damage: " << skill.getDamage();
        } else {
            std::cout << "-- Defense Buff: " << skill.getBuff();
        }
        std::cout << ", Mana Cost: " << skill.getManaCost() << "\n";
    }
}

json SkillManager::toJson() const {
    json j;

    j["unlockedSkills"] = json::array();
    for (const Skill& s : unlockedSkills) {
        auto [cls, index] = findSkillIndex(s);
        j["unlockedSkills"].push_back({
            {"class", cls},
            {"index", index}
        });
    }

    j["equippedSkills"] = json::array();
    for (const Skill& s : equippedSkills) {
        auto [cls, index] = findSkillIndex(s);
        j["equippedSkills"].push_back({
            {"class", cls},
            {"index", index}
        });
    }

    return j;
}

void SkillManager::fromJson(const json& j) {
    unlockedSkills.clear();
    equippedSkills.clear();

    for (auto& entry : j.at("unlockedSkills")) {
        std::string cls = entry.at("class");
        int index = entry.at("index");
        unlockedSkills.push_back(getSkillFromIndex(cls, index));
    }

    for (auto& entry : j.at("equippedSkills")) {
        std::string cls = entry.at("class");
        int index = entry.at("index");
        equippedSkills.push_back(getSkillFromIndex(cls, index));
    }
}

std::pair<std::string, int> SkillManager::findSkillIndex(const Skill& skill) const {
    // swordsman
    for (int i = 0; i < swordsmanSkills.size(); i++)
        if (swordsmanSkills[i].getName() == skill.getName())
            return {"swordsman", i};

    // ranger
    for (int i = 0; i < rangerSkills.size(); i++)
        if (rangerSkills[i].getName() == skill.getName())
            return {"ranger", i};

    // wizard
    for (int i = 0; i < wizardSkills.size(); i++)
        if (wizardSkills[i].getName() == skill.getName())
            return {"wizard", i};

    return {"none", -1};
}

Skill& SkillManager::getSkillFromIndex(const std::string& cls, int index) {
    if (cls == "swordsman") return swordsmanSkills[index];
    if (cls == "ranger")    return rangerSkills[index];
    if (cls == "wizard")    return wizardSkills[index];

    throw std::runtime_error("Invalid skill class/index");
}