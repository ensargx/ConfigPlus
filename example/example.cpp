#include "../include/configplus.hpp"

#include <iostream>

class Example : CConfigPlus
{
public:
    Example() 
    {
        std::cout << "reading: " << "example.toml" << std::endl;
        std::map<std::string, std::string> config = ReadFromFile(ConfigFormat::Toml, "example.toml");
        if (config.empty())
        {
            std::cout << "failed to read config" << std::endl;
            return;
        }

        std::cout << "config:" << std::endl;
        for (auto& [key, value] : config)
        {
            std::cout << key << " = " << value << std::endl;
        }
    }
    CFG_ADD_BOOL(m_bool, true);
    CFG_ADD_INT(m_int, 30);

};

int main()
{
    Example example;
    if (example.m_bool)
    {
        return 2;
    }
    return 1;
}
