#ifndef AREA_HPP
#define AREA_HPP

#include <string>

class Area {
private:
    std::string name;
    std::string description;
public:
    Area();
    virtual ~Area() = default;
    
    std::string getName();
    void setName(std::string name);
    std::string getDescription();
    void setDescription(std::string description);
};

#endif // AREA_HPP