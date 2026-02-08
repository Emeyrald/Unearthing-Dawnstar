#include "../header/town.hpp"

Town::Town() : Area(), buildings() {}

std::vector<std::unique_ptr<Building>>& Town::getBuildings() {
    return buildings;
}

void Town::addBuilding(std::unique_ptr<Building> b) {
    buildings.push_back(std::move(b));
}
