#include <iostream>
#include "include/woj/string.hpp"

int main() {
    constexpr woj::stack::string str{ "Hello, World!" };
    std::cout << str << std::endl;
    return 0;
}