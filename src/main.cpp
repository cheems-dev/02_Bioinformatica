#include "hirschberg.h"
#include <iostream>

int main() {
    std::string A = "TACGCGC";
    std::string B = "TCCGA";
    std::string alignA, alignB;

    hirschberg(A, B, alignA, alignB);

    int score = alignment_score(alignA, alignB);
    auto matrix = full_score_matrix(A, B);

    int num_alignments = 1;

    save_alignment("resultado.txt", alignA, alignB, score, matrix, num_alignments, A, B);

    std::cout << "Alineamiento guardado en resultado.txt\n";
    std::cout << "Alineamiento 1: " << alignA << "\n";
    std::cout << "Alineamiento 2: " << alignB << "\n";
    std::cout << "Puntaje total: " << score << "\n";
    return 0;
} 