#include "hirschberg.h"
#include <algorithm>
#include <fstream>
#include <iostream>

int MATCH = 1;
int MISMATCH = -1;
int GAP = -2;

// La función score y la lógica de programación dinámica implementan la misma
// estructura que la distancia de Levenshtein, pero con puntajes configurables.
// Si se usan MATCH=0, MISMATCH=1, GAP=1, el algoritmo calcula la distancia de
// Levenshtein y el alineamiento óptimo.

int score(char a, char b) {
    if (a == b) return MATCH;
    if (a == '-' || b == '-') return GAP;
    return MISMATCH;
}

// En la función nw_score:
//   - Se consideran tres opciones para cada celda:
//       1. Diagonal (match/mismatch)
//       2. Arriba (gap)
//       3. Izquierda (gap)
//   - Se elige el máximo (o mínimo, según el problema) de esas opciones.
//   - Esta lógica es la misma que la del algoritmo de Levenshtein, pero aquí
//     los puntajes son configurables.
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
        // En la matriz dp de los casos base:
        //   - Se consideran las mismas tres opciones que en Levenshtein:
        //       1. Diagonal (match/mismatch)
        //       2. Arriba (gap)
        //       3. Izquierda (gap)
        //   - Se elige el máximo (o mínimo, según el problema) de esas opciones.
        //   - La estructura y llenado de la matriz es la misma que en Levenshtein,
        //     pero con puntajes configurables.
        std::vector<std::vector<int>> dp(n+1, std::vector<int>(m+1, 0));
        for (int i = 0; i <= n; ++i) dp[i][0] = i * GAP;
        for (int j = 0; j <= m; ++j) dp[0][j] = j * GAP;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                dp[i][j] = std::max({
                    dp[i-1][j-1] + score(A[i-1], B[j-1]),
                    dp[i-1][j] + GAP,
                    dp[i][j-1] + GAP
                });
        // Backtrack
        int i = n, j = m;
        std::string a, b;
        while (i > 0 && j > 0) {
            if (dp[i][j] == dp[i-1][j-1] + score(A[i-1], B[j-1])) {
                a = A[i-1] + a;
                b = B[j-1] + b;
                --i; --j;
            } else if (dp[i][j] == dp[i-1][j] + GAP) {
                a = A[i-1] + a;
                b = '-' + b;
                --i;
            } else {
                a = '-' + a;
                b = B[j-1] + b;
                --j;
            }
        }
        while (i > 0) { a = A[i-1] + a; b = '-' + b; --i; }
        while (j > 0) { a = '-' + a; b = B[j-1] + b; --j; }
        alignA += a;
        alignB += b;
        return;
    }
    // Divide
    int mid = n / 2;
    auto scoreL = nw_score(A.substr(0, mid), B);
    std::string revA = A.substr(mid);
    std::reverse(revA.begin(), revA.end());
    std::string revB = B;
    std::reverse(revB.begin(), revB.end());
    auto scoreR = nw_score(revA, revB);
    int max_j = 0, max_score = scoreL[0] + scoreR[m];
    for (int j = 0; j <= m; ++j) {
        int s = scoreL[j] + scoreR[m-j];
        if (s > max_score) {
            max_score = s;
            max_j = j;
        }
    }
    // Conquista
    hirschberg(A.substr(0, mid), B.substr(0, max_j), alignA, alignB);
    hirschberg(A.substr(mid), B.substr(max_j), alignA, alignB);
}

std::vector<std::vector<int>> full_score_matrix(const std::string& A, const std::string& B) {
    int n = A.size(), m = B.size();
    std::vector<std::vector<int>> dp(n+1, std::vector<int>(m+1, 0));
    for (int i = 0; i <= n; ++i) dp[i][0] = i * GAP;
    for (int j = 0; j <= m; ++j) dp[0][j] = j * GAP;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            dp[i][j] = std::max({
                dp[i-1][j-1] + score(A[i-1], B[j-1]),
                dp[i-1][j] + GAP,
                dp[i][j-1] + GAP
            });
    return dp;
}

int alignment_score(const std::string& alignA, const std::string& alignB) {
    int score_total = 0;
    for (size_t i = 0; i < alignA.size(); ++i)
        score_total += score(alignA[i], alignB[i]);
    return score_total;
}

void save_alignment(const std::string& filename,
                    const std::string& alignA,
                    const std::string& alignB,
                    int score,
                    const std::vector<std::vector<int>>& matrix,
                    int num_alignments,
                    const std::string& seqA,
                    const std::string& seqB) {
    std::ofstream out(filename);
    out << "==============================\n";
    out << "ALINEAMIENTO GLOBAL (Hirschberg)\n";
    out << "==============================\n";
    if (!seqA.empty() && !seqB.empty()) {
        out << "Secuencia A: " << seqA << "\n";
        out << "Secuencia B: " << seqB << "\n";
        out << "------------------------------\n";
    }
    out << "Alineamiento 1: " << alignA << "\n";
    out << "Alineamiento 2: " << alignB << "\n";
    out << "\nPuntaje total: " << score << "\n";
    out << "\nMatriz de puntajes:\n";
    for (const auto& row : matrix) {
        for (int v : row) out << v << "\t";
        out << "\n";
    }
    out << "\nNumero total de alineamientos generados: " << num_alignments << "\n";
    out.close();
} 