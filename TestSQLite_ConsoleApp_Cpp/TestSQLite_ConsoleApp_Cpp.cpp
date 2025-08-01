// TestSQLite_ConsoleApp_Cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "..\sqlite\sqlite3ext.h"
SQLITE_EXTENSION_INIT3
#pragma comment(lib, "SqliteFuzzyPlusExtension.lib")

__declspec(dllimport)
int DamLev_Exp2(const char* str1, const char* str2);

__declspec(dllimport)
double HowSimilar(const char* source1, const char* source2, int iDistanceMethod);

__declspec(dllimport)
double Distance(const char* source1, const char* source2, int iDistanceMethod);

int main()
{
    std::cout << "Hello World!\n";
    const char* str1 = "Hello World";
    const char* str2 = "Hellx sorld";
    int x = DamLev_Exp2(str1, str2);
    std::cout << "x = " << x << std::endl;
    double d1 = HowSimilar("David", "David",     32);    // Fuzzy_Damlev
    double d2 = HowSimilar("David", "Davix",     32);    // Fuzzy_Damlev
    double d3 = HowSimilar("David", "Davxx",     32);    // Fuzzy_Damlev
    double d4 = HowSimilar("David", "Daxxx",     32);    // Fuzzy_Damlev
    double d5 = HowSimilar("David", "Dxxxx",     32);    // Fuzzy_Damlev
    double d6 = HowSimilar("David", "xxxxx",     32);    // Fuzzy_Damlev
    double d7 = HowSimilar("David", "Davdi",     32);    // Fuzzy_Damlev
    double d8 = HowSimilar("David", "Da v id",   32);    // Fuzzy_Damlev

    double h1 = HowSimilar("David", "David", 33);//      Fuzzy_Hamming
    double h2 = HowSimilar("David", "Davix", 33);//      Fuzzy_Hamming
    double h3 = HowSimilar("David", "Davxx", 33);//      Fuzzy_Hamming
    double h4 = HowSimilar("David", "Daxxx", 33);//      Fuzzy_Hamming
    double h5 = HowSimilar("David", "Dxxxx", 33);//      Fuzzy_Hamming
    double h6 = HowSimilar("David", "xxxxx", 33);//      Fuzzy_Hamming
    double h7 = HowSimilar("David", "Davdi", 33);//      Fuzzy_Hamming
    double h8 = HowSimilar("David", "Da v id", 33);//    Fuzzy_Hamming

    double jw1 = HowSimilar("David", "David", 34);//      Fuzzy_Jarowin
    double jw2 = HowSimilar("David", "Davix", 34);//      Fuzzy_Jarowin
    double jw3 = HowSimilar("David", "Davxx", 34);//      Fuzzy_Jarowin
    double jw4 = HowSimilar("David", "Daxxx", 34);//      Fuzzy_Jarowin
    double jw5 = HowSimilar("David", "Dxxxx", 34);//      Fuzzy_Jarowin
    double jw6 = HowSimilar("David", "xxxxx", 34);//      Fuzzy_Jarowin
    double jw7 = HowSimilar("David", "Davdi", 34);//      Fuzzy_Jarowin
    double jw8 = HowSimilar("David", "Da v id", 34);//    Fuzzy_Jarowin

    double L1 = HowSimilar("David", "David", 35);//      Fuzzy_Leven
    double L2 = HowSimilar("David", "Davix", 35);//      Fuzzy_Leven
    double L3 = HowSimilar("David", "Davxx", 35);//      Fuzzy_Leven
    double L4 = HowSimilar("David", "Daxxx", 35);//      Fuzzy_Leven
    double L5 = HowSimilar("David", "Dxxxx", 35);//      Fuzzy_Leven
    double L6 = HowSimilar("David", "xxxxx", 35);//      Fuzzy_Leven
    double L7 = HowSimilar("David", "Davdi", 35);//      Fuzzy_Leven
    double L8 = HowSimilar("David", "Da v id", 35);//    Fuzzy_Leven

    double o1 = HowSimilar("David", "David", 36);//      Fuzzy_Osadist
    double o2 = HowSimilar("David", "Davix", 36);//      Fuzzy_Osadist
    double o3 = HowSimilar("David", "Davxx", 36);//      Fuzzy_Osadist
    double o4 = HowSimilar("David", "Daxxx", 36);//      Fuzzy_Osadist
    double o5 = HowSimilar("David", "Dxxxx", 36);//      Fuzzy_Osadist
    double o6 = HowSimilar("David", "xxxxx", 36);//      Fuzzy_Osadist
    double o7 = HowSimilar("David", "Davdi", 36);//      Fuzzy_Osadist
    double o8 = HowSimilar("David", "Da v id", 36);//    Fuzzy_Osadist

    double e1 = HowSimilar("David", "David", 37);//      Fuzzy_Editdist
    double e2 = HowSimilar("David", "Davix", 37);//      Fuzzy_Editdist
    double e3 = HowSimilar("David", "Davxx", 37);//      Fuzzy_Editdist
    double e4 = HowSimilar("David", "Daxxx", 37);//      Fuzzy_Editdist
    double e5 = HowSimilar("David", "Dxxxx", 37);//      Fuzzy_Editdist
    double e6 = HowSimilar("David", "xxxxx", 37);//      Fuzzy_Editdist
    double e7 = HowSimilar("David", "Davdi", 37);//      Fuzzy_Editdist
    double e8 = HowSimilar("David", "Da v id", 37);//    Fuzzy_Editdist

    double ee1 = HowSimilar("This is a similar phrase test", "This is a similar phrase test", 37);//      Fuzzy_Editdist
    double ee2 = HowSimilar("This is a similar phrase test", "This is a similar phrase", 37);//      Fuzzy_Editdist
    double ee3 = HowSimilar("This is a similar phrase test", "This is a similar phrase xxxx", 37);//      Fuzzy_Editdist
    double ee4 = HowSimilar("This is a similar phrase test", "This is a phrase test", 37);//      Fuzzy_Editdist
    double ee5 = HowSimilar("This is a similar phrase test", "This is a similar phrase test", 37);//      Fuzzy_Editdist
    double ee6 = HowSimilar("This is a similar phrase test", "1234 56 7 890xyz free it", 37);//      Fuzzy_Editdist
    double ee7 = HowSimilar("This is a similar phrase test", "This is a similar xxxxx yyyy", 37);//      Fuzzy_Editdist
    double ee8 = HowSimilar("This is a similar phrase test", "similar phrase test", 37);//      Fuzzy_Editdist

    double j1 = HowSimilar("David", "David", 38);//      Fuzzy_Jaro
    double j2 = HowSimilar("David", "Davix", 38);//      Fuzzy_Jaro
    double j3 = HowSimilar("David", "Davxx", 38);//      Fuzzy_Jaro
    double j4 = HowSimilar("David", "Daxxx", 38);//      Fuzzy_Jaro
    double j5 = HowSimilar("David", "Dxxxx", 38);//      Fuzzy_Jaro
    double j6 = HowSimilar("David", "xxxxx", 38);//      Fuzzy_Jaro
    double j7 = HowSimilar("David", "Davdi", 38);//      Fuzzy_Jaro
    double j8 = HowSimilar("David", "Da v id", 38);//    Fuzzy_Jaro


    double zz = HowSimilar("David", "xxxxx", 32);
}
