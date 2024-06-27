#include "../include/configplus.hpp"

#include <iostream>

class Example : CConfigPlus
{
public:
    Example(const char* path = "example.toml")
    {
        std::cout << "reading: " << path << std::endl;
        std::map<std::string, std::string> config = ReadFromFile(ConfigFormat::Toml, path);
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
    Example example = Example("example.toml");
    std::cout << "m_bool: " << example.m_bool << std::endl;
    std::cout << "m_int: " << example.m_int << std::endl;
    return 1;
}
