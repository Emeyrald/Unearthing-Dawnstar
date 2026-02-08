#ifndef TOWN_HPP
#define TOWN_HPP

#include <vector>
#include <memory>
#include "area.hpp"
#include "building.hpp"

class Town : public Area {
private:
    std::vector<std::unique_ptr<Building>> buildings;
public:
    Town();
    ~Town() override = default;
    
    std::vector<std::unique_ptr<Building>>& getBuildings();
    void addBuilding(std::unique_ptr<Building> b);
};

#endif // TOWN_HPP