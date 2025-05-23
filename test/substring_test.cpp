#include <gtest/gtest.h>
#include <string>
#include "../src/substring.cpp"

// Prueba: "GCA" y "AGCAT" → true
TEST(SubstringTest, GCAinAGCAT) {
    EXPECT_TRUE(isSubstring("GCA", "AGCAT"));
}

// Prueba: "ACT" y "TGA" → false
TEST(SubstringTest, ACTandTGA) {
    EXPECT_FALSE(isSubstring("ACT", "TGA"));
}

// Prueba: cadena vacía vs. cualquier cadena
TEST(SubstringTest, EmptyStringInXYZ) {
    EXPECT_TRUE(isSubstring("", "XYZ"));
}

TEST(SubstringTest, XYZInEmptyString) {
    EXPECT_TRUE(isSubstring("XYZ", ""));
}

// Prueba: ambas vacías
TEST(SubstringTest, BothEmptyStrings) {
    EXPECT_TRUE(isSubstring("", ""));
} 