#include "../header/building.hpp"
#include <iostream>

Building::Building() 
    : name("Unknown Building"), description("No description"), npc() {}

Building::~Building() {}

std::string Building::getName() {
    return name;
}

void Building::setName(std::string name) {
    this->name = name;
}

std::string Building::getDescription() {
    return description;
}

void Building::setDescription(std::string description) {
    this->description = description;
}

NPC Building::getNPC() {
    return npc;
}

void Building::setNPC(NPC npc) {
    this->npc = npc;
}
