#ifndef SKILLMANAGER_HPP
#define SKILLMANAGER_HPP
#include <vector>
#include "skill.hpp"
#include "playerStats.hpp"
#include <nlohmann/json.hpp>
using nlohmann::json;
using std::vector;

class SkillManager {
private:
    vector<Skill> swordsmanSkills;
    vector<Skill> rangerSkills;
    vector<Skill> wizardSkills;
public:
    SkillManager();
    virtual ~SkillManager();
    
    vector<Skill> equippedSkills;
    vector<Skill> unlockedSkills;

    void unlockSkill(PlayerStats& stats, const std::string& playerClass);
    void equipSkill();
    void unequipSkill();
    void viewSkills();

    json toJson() const;
    void fromJson(const json& j);

    // Helpers
    std::pair<std::string, int> findSkillIndex(const Skill& skill) const;
    Skill& getSkillFromIndex(const std::string& cls, int index);
};

#endif // SKILLMANAGER_HPP