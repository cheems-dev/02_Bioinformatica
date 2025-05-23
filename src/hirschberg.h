#ifndef HIRSCHBERG_H
#define HIRSCHBERG_H

#include <string>
#include <vector>

// -----------------------------------------------------------------------------
// Este archivo declara las funciones y variables para el algoritmo de Hirschberg.
// La lógica de programación dinámica implementada en este proyecto es la misma
// que la de la distancia de Levenshtein, pero con puntajes configurables para
// match, mismatch y gap. Si se usan MATCH=0, MISMATCH=1, GAP=1, el algoritmo
// calcula la distancia de Levenshtein y el alineamiento óptimo. 
// -----------------------------------------------------------------------------

// Parámetros de puntaje (modificables)
extern int MATCH;
extern int MISMATCH;
extern int GAP;

// Función de puntaje personalizada
int score(char a, char b);

// Calcula la última fila de la matriz de alineamiento (espacio lineal)
std::vector<int> nw_score(const std::string& A, const std::string& B);

// Algoritmo de Hirschberg (divide y vencerás)
void hirschberg(const std::string& A, const std::string& B, std::string& alignA, std::string& alignB);

// Calcula la matriz completa de puntajes (para imprimir/guardar)
std::vector<std::vector<int>> full_score_matrix(const std::string& A, const std::string& B);

// Calcula el puntaje total de un alineamiento
int alignment_score(const std::string& alignA, const std::string& alignB);

// Guarda resultados en un archivo
void save_alignment(const std::string& filename,
                    const std::string& alignA,
                    const std::string& alignB,
                    int score,
                    const std::vector<std::vector<int>>& matrix,
                    int num_alignments,
                    const std::string& seqA = "",
                    const std::string& seqB = "");

#endif 