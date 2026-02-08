#include "../header/area.hpp"

Area::Area()
    : name("Unknown Area"), description("No description.") {}


std::string Area::getName() {
    return name;
}

void Area::setName(std::string name) {
    this->name = name;
}

std::string Area::getDescription() {
    return description;
}

void Area::setDescription(std::string description) {
    this->description = description;
}
