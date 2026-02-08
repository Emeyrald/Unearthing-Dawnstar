#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <nlohmann/json.hpp>
using nlohmann::json;

class Item {
protected:
    std::string name;
    std::string type;      // "weapon", "armor", "potion", "keyItem", "misc"
    int value;             // gold value

public:
    Item();
    Item(const std::string& name, const std::string& type, int value);
    virtual ~Item();

    std::string getName() const;
    std::string getType() const;
    int getValue() const;

    virtual json toJson() const;
    virtual void fromJson(const json& j);
};

#endif // ITEM_HPP
