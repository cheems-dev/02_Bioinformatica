# Hirschberg Global Alignment (C++)

Este proyecto implementa el algoritmo del substring y el algoritmo de Hirschberg para alineamiento global de secuencias en C++ puro, usando programación dinámica en espacio lineal (O(n)).

## Estructura del proyecto

```
├── src/
│   ├── hirschberg.h
│   ├── hirschberg.cpp
│   ├── main.cpp
│   └── substring.cpp         
├── test/
│   ├── hirschberg_test.cpp
│   └── substring_test.cpp   
├── resultado.txt
└── README.md
```

## ¿Qué hace el código de `src/hirschberg.cpp`?

El archivo `hirschberg.cpp` implementa el **algoritmo de Hirschberg** para el alineamiento global de dos secuencias (por ejemplo, ADN, proteínas o cadenas de texto). Este algoritmo es una optimización del clásico algoritmo Needleman-Wunsch, pero utiliza solo espacio lineal (O(n)) en vez de cuadrático, lo que lo hace eficiente para secuencias largas.

**Características principales:**
- Permite definir puntajes para coincidencia (`MATCH`), desajuste (`MISMATCH`) y huecos (`GAP`).
- Utiliza programación dinámica para calcular el alineamiento óptimo.
- Divide y conquista: parte la secuencia en mitades y resuelve recursivamente.
- Puede calcular la matriz de puntajes completa y el alineamiento óptimo.
- Permite guardar el alineamiento y la matriz en un archivo de salida.

**Funciones clave:**

- `score(char a, char b)`: Devuelve el puntaje entre dos caracteres.

```cpp
int score(char a, char b) {
    if (a == b) return MATCH;
    if (a == '-' || b == '-') return GAP;
    return MISMATCH;
}
```

- `nw_score`: Calcula la última fila de la matriz de alineamiento (espacio lineal).

```cpp
std::vector<int> nw_score(const std::string& A, const std::string& B) {
    int n = A.size(), m = B.size();
    std::vector<int> prev(m+1, 0), curr(m+1, 0);
    for (int j = 0; j <= m; ++j)
        prev[j] = j * GAP;
    for (int i = 1; i <= n; ++i) {
        curr[0] = i * GAP;
        for (int j = 1; j <= m; ++j) {
            int match = prev[j-1] + score(A[i-1], B[j-1]);
            int del = prev[j] + GAP;
            int ins = curr[j-1] + GAP;
            curr[j] = std::max({match, del, ins});
        }
        std::swap(prev, curr);
    }
    return prev;
}
```

- `hirschberg`: Implementa la recursión principal para obtener el alineamiento óptimo.

```cpp
void hirschberg(const std::string& A, const std::string& B, std::string& alignA, std::string& alignB) {
    int n = A.size(), m = B.size();
    if (n == 0) {
        alignA.append(m, '-');
        alignB += B;
        return;
    }
    if (m == 0) {
        alignA += A;
        alignB.append(n, '-');
        return;
    }
    if (n == 1 || m == 1) {
        // ... caso base con backtracking ...
    }
    // Divide
    int mid = n / 2;
    auto scoreL = nw_score(A.substr(0, mid), B);
    // ... lógica para encontrar el punto de corte ...
    hirschberg(A.substr(0, mid), B.substr(0, max_j), alignA, alignB);
    hirschberg(A.substr(mid), B.substr(max_j), alignA, alignB);
}
```

- `full_score_matrix`: Calcula la matriz completa de puntajes.
- `alignment_score`: Suma el puntaje total de un alineamiento.
- `save_alignment`: Guarda el resultado y la matriz en un archivo.

---

## ¿Qué hace el código de `src/substring.cpp`?

El archivo `substring.cpp` implementa una función para verificar si una cadena es substring de otra (o si son iguales), mostrando la posición donde aparece y devolviendo un valor booleano.

**Fragmento principal:**

```cpp
bool isSubstring(const std::string& a, const std::string& b) {
    if (a.empty() || b.empty()) {
        std::cout << "Una de las cadenas es vacía. Consideramos que es substring en la posición 0." << std::endl;
        return true;
    }
    if (a == b) {
        std::cout << "Las cadenas son idénticas. Substring en la posición 0." << std::endl;
        return true;
    }
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
```

---

## Compilación y ejecución

### Compilar y ejecutar el programa principal (Hirschberg)

```
g++ -std=c++11 -o main src/main.cpp src/hirschberg.cpp
./main
```

Esto generará el archivo `resultado.txt` con el alineamiento, puntaje y matriz de puntajes.

### Compilar y ejecutar pruebas unitarias de Hirschberg

```
g++ -std=c++11 -o test test/hirschberg_test.cpp src/hirschberg.cpp -lgtest -lpthread
./test
```

### Compilar y ejecutar la función substring (ejemplo)

```
g++ -std=c++11 -o substring_main src/substring_main.cpp
./substring_main
```

### Compilar y ejecutar las pruebas unitarias de substring

```
g++ -std=c++11 -o substring_test test/substring_test.cpp src/substring.cpp -lgtest -lpthread
./substring_test
```

---

## Personalización

- Puedes cambiar las secuencias a alinear editando `src/main.cpp`.
- Puedes modificar los puntajes de `MATCH`, `MISMATCH` y `GAP` en `src/hirschberg.cpp`.
- Puedes modificar o agregar pruebas de substring en `test/substring_test.cpp`.

---

## Ejemplo de Salida (`resultado.txt`)

```
==============================
ALINEAMIENTO GLOBAL (Hirschberg)
==============================
Secuencia A: ACTGATTCA
Secuencia B: ACGCATCA
------------------------------
Alineamiento 1: ACTGATTCA
Alineamiento 2: AC-GCATCA

Puntaje total: 2

Matriz de puntajes:
0	-2	-4	-6	-8	-10	-12	-14	-16	
demás filas...

Numero total de alineamientos generados: 1
``` 