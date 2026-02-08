#ifndef NPC_HPP
#define NPC_HPP

#include <string>
#include <vector>

class NPC {
private:
    std::string name;
    std::vector<std::string> dialogue;
public:
    NPC();
    ~NPC();
    
    std::string getName();
    void setName(const std::string& name);
    std::vector<std::string> getDialogue();
    void setDialogue(const std::vector<std::string>& lines);
    void talk();
};

#endif // NPC_HPP