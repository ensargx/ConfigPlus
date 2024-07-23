#include "../include/configplus.hpp"

#include <iostream>

int main()
{
    Config config;
    config.var1 = 1;
    config.var2 = 2.5f;
    config.var3.value.var1 = 3;

    std::cout << config.var1.value << std::endl;
    std::cout << config.var2.value << std::endl;
    std::cout << config.var3.value.var1.value << std::endl;

    return 0;
}
