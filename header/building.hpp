#ifndef BUILDING_HPP
#define BUILDING_HPP

#include <string>
#include "npc.hpp"

class Building {
private:
    std::string name;
    std::string description;
    NPC npc;
public:
    Building();
    virtual ~Building();
    
    std::string getName();
    void setName(std::string name);
    std::string getDescription();
    void setDescription(std::string description);
    NPC getNPC();
    void setNPC(NPC npc);
};

#endif // BUILDING_HPP