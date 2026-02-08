#include "../header/npc.hpp"
#include <iostream>

NPC::NPC() : name("Unknown NPC"), dialogue() {}

NPC::~NPC() {}

std::string NPC::getName() {
    return this->name;
}

void NPC::setName(const std::string& name) {
    this->name = name;
}


std::vector<std::string> NPC::getDialogue() {
    return this->dialogue;
}

void NPC::setDialogue(const std::vector<std::string>& lines) {
    this->dialogue = lines;
}


void NPC::talk() {
    if (dialogue.empty()) {
        std::cout << name << " has nothing to say.\n";
        return;
    }

    for (const auto& line : dialogue) {
        std::cout << name << ": " << line << "\n";
    }
}
