#include "../include/configplus.hpp"

#include <iostream>

int main()
{
    Config test;
    test.myInt.value = 42;
    test.myFloat.value = 3.14f;
    test.otherClass.value.myInt.value = 24;

    std::cout << "myInt: " << test.myInt<< std::endl;
    std::cout << "myFloat: " << test.myFloat<< std::endl;

    return 0;
}
