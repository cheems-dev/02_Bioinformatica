#include <iostream>
#include <string>

// Función que verifica si una cadena es substring de la otra
// Devuelve true si la cadena más corta es substring de la más larga o si son iguales
// Imprime en consola si hay substring y la posición donde aparece
bool isSubstring(const std::string& a, const std::string& b) {
    // Caso especial: si alguna cadena es vacía, consideramos que es substring de la otra
    if (a.empty() || b.empty()) {
        std::cout << "Una de las cadenas es vacía. Consideramos que es substring en la posición 0." << std::endl;
        return true;
    }
    // Si son iguales
    if (a == b) {
        std::cout << "Las cadenas son idénticas. Substring en la posición 0." << std::endl;
        return true;
    }
    // Determinar cuál es la más corta y buscarla en la más larga
    const std::string& shorter = (a.length() < b.length()) ? a : b;
    const std::string& longer  = (a.length() < b.length()) ? b : a;
    size_t pos = longer.find(shorter);
    if (pos != std::string::npos) {
        std::cout << "'" << shorter << "' es substring de '" << longer << "' en la posición " << pos << std::endl;
        return true;
    }
    std::cout << "Ninguna cadena es substring de la otra." << std::endl;
    return false;
} 