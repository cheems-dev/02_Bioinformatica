#include "../src/hirschberg.h"
#include <gtest/gtest.h>

TEST(HirschbergTest, Simple1) {
    std::string A = "AGC", B = "AAAC";
    std::string alignA, alignB;
    hirschberg(A, B, alignA, alignB);
    EXPECT_EQ(alignA.size(), alignB.size());
    EXPECT_EQ(alignment_score(alignA, alignB), 0); // Puntaje esperado: 0
}

TEST(HirschbergTest, Simple2) {
    std::string A = "ACTGATTCA", B = "ACGCATCA";
    std::string alignA, alignB;
    hirschberg(A, B, alignA, alignB);
    EXPECT_EQ(alignA.size(), alignB.size());
    EXPECT_EQ(alignment_score(alignA, alignB), 4); // Puntaje esperado: 4
}

TEST(HirschbergTest, Empty) {
    std::string A = "", B = "ACG";
    std::string alignA, alignB;
    hirschberg(A, B, alignA, alignB);
    EXPECT_EQ(alignA, "---");
    EXPECT_EQ(alignB, "ACG");
    EXPECT_EQ(alignment_score(alignA, alignB), 3 * GAP);
} 