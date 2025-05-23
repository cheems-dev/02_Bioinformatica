#include <iostream>
#include <string>
#include "substring.cpp"

int main() {
    std::string a, b;
    std::cout << "Ejemplo 1: \"GCA\" y \"AGCAT\"\n";
    isSubstring("GCA", "AGCAT");
    std::cout << std::endl;

    std::cout << "Ejemplo 2: \"ACT\" y \"TGA\"\n";
    isSubstring("ACT", "TGA");
    std::cout << std::endl;

    std::cout << "Ejemplo 3: \"\" y \"XYZ\"\n";
    isSubstring("", "XYZ");
    std::cout << std::endl;

    std::cout << "Ejemplo 4: \"XYZ\" y \"\"\n";
    isSubstring("XYZ", "");
    std::cout << std::endl;

    std::cout << "Ejemplo 5: \"ABC\" y \"ABC\"\n";
    isSubstring("ABC", "ABC");
    std::cout << std::endl;

    return 0;
} 