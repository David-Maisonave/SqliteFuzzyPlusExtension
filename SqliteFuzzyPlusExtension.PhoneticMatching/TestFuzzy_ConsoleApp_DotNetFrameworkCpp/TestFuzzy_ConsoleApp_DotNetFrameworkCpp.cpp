#include "pch.h"
#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <atlstr.h>
using namespace std;
using namespace System;
#define SQLITEFUZZYPLUSEXTENSION_LIB "SqliteFuzzyPlusExtensionWithMsPhoneticMatching.lib"
#include "..\..\SqliteFuzzyPlusExtension\SqliteFuzzyPlusExtension.h"


static void CreateScript(string rootDir, string fieldName, string table, string FunctionName, string text, bool byName) 
{
    string fileName = byName ? "_ByName_" : "_ByNumber_";
    ofstream f(rootDir + FunctionName + fileName + table + ".sql");
    f << "select " << fieldName << endl;
    for (int i = 0; i < (int)FuzzyPlusCSharp::Fuzzy::DistanceMethod::iEdlibDistance; ++i)
    {
        CString d = FuzzyPlusCSharp::Fuzzy::GetDistanceMethodName(i);
        string distanceName = CW2A(d);
        if (std::isdigit(distanceName[0]))
            continue;
        f << ", " << FunctionName << "(" << fieldName << ", '" << text << "', ";
        if (byName)
            f << "'" << distanceName << "'";
        else
            f << i;
        f << ") as a" << i << " -- " << distanceName << " (ID# " << i << ")" << endl;
    }
    f << "FROM " << table << ";" << endl;
    f << "-- Note: Case insensitive functions have an ID number greater than " << FuzzyPlusCSharp::Fuzzy::CASE_INSENSITIVE << endl;
    f << "--       C++ functions have an ID number equal to or greater than  " << FuzzyPlusCSharp::Fuzzy::CPP_ONLY_FUZZY << " and less than " << FuzzyPlusCSharp::Fuzzy::CASE_INSENSITIVE << endl;
    f << "--       Tokenize functions have an ID number equal to or greater than  " << FuzzyPlusCSharp::Fuzzy::TOKEN_METHODS << " and less than " << FuzzyPlusCSharp::Fuzzy::PHRASE_METHODS << endl;
    f << "--       Phrase functions have an ID number equal to or greater than  " << FuzzyPlusCSharp::Fuzzy::PHRASE_METHODS << " and less than " << FuzzyPlusCSharp::Fuzzy::METHODS_UP_FOR_DELETION << endl;
    f << "--       Functions that are being considered for deletion have an ID number equal to or greater than  " << FuzzyPlusCSharp::Fuzzy::METHODS_UP_FOR_DELETION << " and less than " << FuzzyPlusCSharp::Fuzzy::CPP_ONLY_FUZZY << endl;
    f.close();
}
static void CreateScript(string rootDir, string fieldName, string table, string FunctionName, string text) 
{
    CreateScript(rootDir, fieldName, table, FunctionName, text, false);
    CreateScript(rootDir, fieldName, table, FunctionName, text, true);
}

static void CreateUnitTestSqlFile()
{
    string rootDir = "..\\TestData\\AutoCreatedSqlScript\\";
    CreateScript(rootDir, "Name", "SimilarNames", "Distance", "David Jorge");
    CreateScript(rootDir, "Phrases", "SimilarPhrase", "Distance", "This is a similar phrase test");
    CreateScript(rootDir, "Words", "SimilarWords", "Distance", "David");
    CreateScript(rootDir, "Name", "SimilarNames", "HowSimilar", "David Jorge");
    CreateScript(rootDir, "Phrases", "SimilarPhrase", "HowSimilar", "This is a similar phrase test");
    CreateScript(rootDir, "Words", "SimilarWords", "HowSimilar", "David");
    CreateScript(rootDir, "Name", "SimilarNames", "Similar", "David Jorge");
    CreateScript(rootDir, "Phrases", "SimilarPhrase", "Similar", "This is a similar phrase test");
    CreateScript(rootDir, "Words", "SimilarWords", "Similar", "David");

    CreateScript(rootDir, "Name", "SimilarNames", "IsVerySimilar", "David Jorge");
    CreateScript(rootDir, "Phrases", "SimilarPhrase", "IsVerySimilar", "This is a similar phrase test");
    CreateScript(rootDir, "Words", "SimilarWords", "IsVerySimilar", "David");

    CreateScript(rootDir, "Phrases", "SimilarPhrase", "IsSimilar", "This is a similar phrase test");
    CreateScript(rootDir, "Phrases", "SimilarPhrase", "IsSomeWhatSimilar", "This is a similar phrase test");
    CreateScript(rootDir, "Phrases", "SimilarPhrase", "IsSlightlySimilar", "This is a similar phrase test");
    CreateScript(rootDir, "Phrases", "SimilarPhrase", "IsHardlySimilar", "This is a similar phrase test");
    CreateScript(rootDir, "Phrases", "SimilarPhrase", "IsNotSimilar", "This is a similar phrase test");
    CreateScript(rootDir, "Phrases", "SimilarPhrase", "HowSimilar", "This is a similar phrase test");

}

int main() //array<System::String ^> ^args)
{
    CreateUnitTestSqlFile();

    const char* str1 = "Hello World";
    const char* str2 = "Hellx sorld";
    int x = DamerauLevenshteinDistance(str1, str2);
    std::cout << "x = " << x << std::endl;

    const char* sound1 = "been";
    const char* sound2 = "being";
    int x1 = EnPhoneticDistance(sound1, sound2);
    int x2 = DamerauLevenshteinDistance(sound1, sound2);
    int x3 = Soundex2(sound1, sound2);
    int x4 = EnPhoneticDistance(sound1, sound1);
    int x5 = EnPhoneticDistance(sound2, sound2);
    int x6 = EnPhoneticDistance(sound1, "seen");
    int x7 = EnPhoneticDistance(sound1, "bean");
    int x8 = EnPhoneticDistance(sound1, "xxxx");
    int x9 = EnPhoneticDistance(sound1, str1);
    int x0 = EnPhoneticDistance("Hello World", "Hello Wood");
    int x10 = EnPhoneticDistance(str1, str2);

    int maxlen = MaxValue(5, 6);
    unsigned __int64 i64_1 = NormalizeNum("123.4K");
    unsigned __int64 i64_2 = NormalizeNum("2K");
    unsigned __int64 i64_3 = NormalizeNum("123.4K");
    unsigned __int64 i64_4 = NormalizeNum("345.9K");

    double example1 = Distance("David", "David", SqliteFuzzyPlusExtension::Levenshtein);
    double example2 = Distance("David", "Davix", SqliteFuzzyPlusExtension::DamerauLevenshtein);
    double example3 = Distance("David", "Davxx", SqliteFuzzyPlusExtension::JaroWinkler);
    double example4 = Distance("David", "Daxxx", SqliteFuzzyPlusExtension::Fuzzy_Leven);
    double example5 = Distance("David", "Dxxxx", SqliteFuzzyPlusExtension::Fuzzy_Damlev);
    double example6 = Distance("David", "xxxxx", SqliteFuzzyPlusExtension::Fuzzy_Jarowin);
    double example7 = Distance("David", "david", SqliteFuzzyPlusExtension::iLevenshtein);
    double example8 = Distance("David", "davdi", SqliteFuzzyPlusExtension::iLevenshtein);

    double similar00 = HowSimilar("David", "David", SqliteFuzzyPlusExtension::UseDefaultDistanceMethod);
    double similar01 = HowSimilar("David", "David", SqliteFuzzyPlusExtension::Levenshtein);
    double similar02 = HowSimilar("David", "Davix", SqliteFuzzyPlusExtension::LongestCommonSequence);
    double similar03 = HowSimilar("David", "Davxx", SqliteFuzzyPlusExtension::JaccardIndex);
    double similar04 = HowSimilar("David", "Daxxx", SqliteFuzzyPlusExtension::OverlapCoefficient);
    double similar05 = HowSimilar("David", "Dxxxx", SqliteFuzzyPlusExtension::NeedlemanWunsch);
    double similar06 = HowSimilar("David", "xxxxx", SqliteFuzzyPlusExtension::SorensenDiceDistance);
    double similar07 = HowSimilar("David", "david", SqliteFuzzyPlusExtension::RatcliffObershelpSimilarityDistance);
    double similar08 = HowSimilar("David", "davdi", SqliteFuzzyPlusExtension::HammingDistance);
    double similar09 = HowSimilar("David", "davdi", SqliteFuzzyPlusExtension::LongestCommonSubstringDistance);
    double similar10 = HowSimilar("David", "davdi", SqliteFuzzyPlusExtension::LongestCommonSubsequenceDistance);
    double similar11 = HowSimilar("David", "davdi", SqliteFuzzyPlusExtension::JaroDistance);
    double similar12 = HowSimilar("David", "davdi", SqliteFuzzyPlusExtension::NormalizedLevenshteinDistance);
    double similar13 = HowSimilar("David", "davdi", SqliteFuzzyPlusExtension::Levenshtein2Distance);
    double similar14 = HowSimilar("David", "davdi", SqliteFuzzyPlusExtension::TanimotoCoefficientDistance);
    double similar15 = HowSimilar("David", "davdi", SqliteFuzzyPlusExtension::EdlibDistance);


    double dd1 = Distance("David", "David", SqliteFuzzyPlusExtension::Levenshtein);
    double dd2 = Distance("David", "Davix", SqliteFuzzyPlusExtension::Levenshtein);
    double dd3 = Distance("David", "Davxx", SqliteFuzzyPlusExtension::Levenshtein);
    double dd4 = Distance("David", "Daxxx", SqliteFuzzyPlusExtension::Levenshtein);
    double dd5 = Distance("David", "Dxxxx", SqliteFuzzyPlusExtension::Levenshtein);
    double dd6 = Distance("David", "xxxxx", SqliteFuzzyPlusExtension::Levenshtein);
    double dd7 = Distance("David", "Davdi", SqliteFuzzyPlusExtension::Levenshtein);
    double dd8 = Distance("David", "David", SqliteFuzzyPlusExtension::Levenshtein);
    double dd9 = Distance("David", "Da v id", SqliteFuzzyPlusExtension::Levenshtein);


    double d1 = HowSimilar("David", "David", SqliteFuzzyPlusExtension::Fuzzy_Damlev);    // Fuzzy_Damlev
    double d2 = HowSimilar("David", "Davix", SqliteFuzzyPlusExtension::Fuzzy_Damlev);    // Fuzzy_Damlev
    double d3 = HowSimilar("David", "Davxx", SqliteFuzzyPlusExtension::Fuzzy_Damlev);    // Fuzzy_Damlev
    double d4 = HowSimilar("David", "Daxxx", SqliteFuzzyPlusExtension::Fuzzy_Damlev);    // Fuzzy_Damlev
    double d5 = HowSimilar("David", "Dxxxx", SqliteFuzzyPlusExtension::Fuzzy_Damlev);    // Fuzzy_Damlev
    double d6 = HowSimilar("David", "xxxxx", SqliteFuzzyPlusExtension::Fuzzy_Damlev);    // Fuzzy_Damlev
    double d7 = HowSimilar("David", "Davdi", SqliteFuzzyPlusExtension::Fuzzy_Damlev);    // Fuzzy_Damlev
    double d8 = HowSimilar("David", "Da v id", SqliteFuzzyPlusExtension::Fuzzy_Damlev);    // Fuzzy_Damlev

    double h1 = HowSimilar("David", "David", SqliteFuzzyPlusExtension::Fuzzy_Hamming);//      Fuzzy_Hamming
    double h2 = HowSimilar("David", "Davix", SqliteFuzzyPlusExtension::Fuzzy_Hamming);//      Fuzzy_Hamming
    double h3 = HowSimilar("David", "Davxx", SqliteFuzzyPlusExtension::Fuzzy_Hamming);//      Fuzzy_Hamming
    double h4 = HowSimilar("David", "Daxxx", SqliteFuzzyPlusExtension::Fuzzy_Hamming);//      Fuzzy_Hamming
    double h5 = HowSimilar("David", "Dxxxx", SqliteFuzzyPlusExtension::Fuzzy_Hamming);//      Fuzzy_Hamming
    double h6 = HowSimilar("David", "xxxxx", SqliteFuzzyPlusExtension::Fuzzy_Hamming);//      Fuzzy_Hamming
    double h7 = HowSimilar("David", "Davdi", SqliteFuzzyPlusExtension::Fuzzy_Hamming);//      Fuzzy_Hamming
    double h8 = HowSimilar("David", "Da v id", SqliteFuzzyPlusExtension::Fuzzy_Hamming);//    Fuzzy_Hamming

    double jw1 = HowSimilar("David", "David", SqliteFuzzyPlusExtension::Fuzzy_Jarowin);//      Fuzzy_Jarowin
    double jw2 = HowSimilar("David", "Davix", SqliteFuzzyPlusExtension::Fuzzy_Jarowin);//      Fuzzy_Jarowin
    double jw3 = HowSimilar("David", "Davxx", SqliteFuzzyPlusExtension::Fuzzy_Jarowin);//      Fuzzy_Jarowin
    double jw4 = HowSimilar("David", "Daxxx", SqliteFuzzyPlusExtension::Fuzzy_Jarowin);//      Fuzzy_Jarowin
    double jw5 = HowSimilar("David", "Dxxxx", SqliteFuzzyPlusExtension::Fuzzy_Jarowin);//      Fuzzy_Jarowin
    double jw6 = HowSimilar("David", "xxxxx", SqliteFuzzyPlusExtension::Fuzzy_Jarowin);//      Fuzzy_Jarowin
    double jw7 = HowSimilar("David", "Davdi", SqliteFuzzyPlusExtension::Fuzzy_Jarowin);//      Fuzzy_Jarowin
    double jw8 = HowSimilar("David", "Da v id", SqliteFuzzyPlusExtension::Fuzzy_Jarowin);//    Fuzzy_Jarowin

    double L1 = HowSimilar("David", "David", SqliteFuzzyPlusExtension::Fuzzy_Leven);//      Fuzzy_Leven
    double L2 = HowSimilar("David", "Davix", SqliteFuzzyPlusExtension::Fuzzy_Leven);//      Fuzzy_Leven
    double L3 = HowSimilar("David", "Davxx", SqliteFuzzyPlusExtension::Fuzzy_Leven);//      Fuzzy_Leven
    double L4 = HowSimilar("David", "Daxxx", SqliteFuzzyPlusExtension::Fuzzy_Leven);//      Fuzzy_Leven
    double L5 = HowSimilar("David", "Dxxxx", SqliteFuzzyPlusExtension::Fuzzy_Leven);//      Fuzzy_Leven
    double L6 = HowSimilar("David", "xxxxx", SqliteFuzzyPlusExtension::Fuzzy_Leven);//      Fuzzy_Leven
    double L7 = HowSimilar("David", "Davdi", SqliteFuzzyPlusExtension::Fuzzy_Leven);//      Fuzzy_Leven
    double L8 = HowSimilar("David", "Da v id", SqliteFuzzyPlusExtension::Fuzzy_Leven);//    Fuzzy_Leven

    double o1 = HowSimilar("David", "David", SqliteFuzzyPlusExtension::Fuzzy_Osadist);//      Fuzzy_Osadist
    double o2 = HowSimilar("David", "Davix", SqliteFuzzyPlusExtension::Fuzzy_Osadist);//      Fuzzy_Osadist
    double o3 = HowSimilar("David", "Davxx", SqliteFuzzyPlusExtension::Fuzzy_Osadist);//      Fuzzy_Osadist
    double o4 = HowSimilar("David", "Daxxx", SqliteFuzzyPlusExtension::Fuzzy_Osadist);//      Fuzzy_Osadist
    double o5 = HowSimilar("David", "Dxxxx", SqliteFuzzyPlusExtension::Fuzzy_Osadist);//      Fuzzy_Osadist
    double o6 = HowSimilar("David", "xxxxx", SqliteFuzzyPlusExtension::Fuzzy_Osadist);//      Fuzzy_Osadist
    double o7 = HowSimilar("David", "Davdi", SqliteFuzzyPlusExtension::Fuzzy_Osadist);//      Fuzzy_Osadist
    double o8 = HowSimilar("David", "Da v id", SqliteFuzzyPlusExtension::Fuzzy_Osadist);//    Fuzzy_Osadist

    double e1 = HowSimilar("David", "David", SqliteFuzzyPlusExtension::Fuzzy_Editdist);//      Fuzzy_Editdist
    double e2 = HowSimilar("David", "Davix", SqliteFuzzyPlusExtension::Fuzzy_Editdist);//      Fuzzy_Editdist
    double e3 = HowSimilar("David", "Davxx", SqliteFuzzyPlusExtension::Fuzzy_Editdist);//      Fuzzy_Editdist
    double e4 = HowSimilar("David", "Daxxx", SqliteFuzzyPlusExtension::Fuzzy_Editdist);//      Fuzzy_Editdist
    double e5 = HowSimilar("David", "Dxxxx", SqliteFuzzyPlusExtension::Fuzzy_Editdist);//      Fuzzy_Editdist
    double e6 = HowSimilar("David", "xxxxx", SqliteFuzzyPlusExtension::Fuzzy_Editdist);//      Fuzzy_Editdist
    double e7 = HowSimilar("David", "Davdi", SqliteFuzzyPlusExtension::Fuzzy_Editdist);//      Fuzzy_Editdist
    double e8 = HowSimilar("David", "Da v id", SqliteFuzzyPlusExtension::Fuzzy_Editdist);//    Fuzzy_Editdist

    double ee1 = HowSimilar("This is a similar phrase test", "This is a similar phrase test", SqliteFuzzyPlusExtension::Fuzzy_Editdist);//      Fuzzy_Editdist
    double ee2 = HowSimilar("This is a similar phrase test", "This is a similar phrase", SqliteFuzzyPlusExtension::Fuzzy_Editdist);//      Fuzzy_Editdist
    double ee3 = HowSimilar("This is a similar phrase test", "This is a similar phrase xxxx", SqliteFuzzyPlusExtension::Fuzzy_Editdist);//      Fuzzy_Editdist
    double ee4 = HowSimilar("This is a similar phrase test", "This is a phrase test", SqliteFuzzyPlusExtension::Fuzzy_Editdist);//      Fuzzy_Editdist
    double ee5 = HowSimilar("This is a similar phrase test", "This is a similar phrase test", SqliteFuzzyPlusExtension::Fuzzy_Editdist);//      Fuzzy_Editdist
    double ee6 = HowSimilar("This is a similar phrase test", "1234 56 7 890xyz free it", SqliteFuzzyPlusExtension::Fuzzy_Editdist);//      Fuzzy_Editdist
    double ee7 = HowSimilar("This is a similar phrase test", "This is a similar xxxxx yyyy", SqliteFuzzyPlusExtension::Fuzzy_Editdist);//      Fuzzy_Editdist
    double ee8 = HowSimilar("This is a similar phrase test", "similar phrase test", SqliteFuzzyPlusExtension::Fuzzy_Editdist);//      Fuzzy_Editdist

    double j1 = HowSimilar("David", "David", SqliteFuzzyPlusExtension::Fuzzy_Jaro);//      Fuzzy_Jaro
    double j2 = HowSimilar("David", "Davix", SqliteFuzzyPlusExtension::Fuzzy_Jaro);//      Fuzzy_Jaro
    double j3 = HowSimilar("David", "Davxx", SqliteFuzzyPlusExtension::Fuzzy_Jaro);//      Fuzzy_Jaro
    double j4 = HowSimilar("David", "Daxxx", SqliteFuzzyPlusExtension::Fuzzy_Jaro);//      Fuzzy_Jaro
    double j5 = HowSimilar("David", "Dxxxx", SqliteFuzzyPlusExtension::Fuzzy_Jaro);//      Fuzzy_Jaro
    double j6 = HowSimilar("David", "xxxxx", SqliteFuzzyPlusExtension::Fuzzy_Jaro);//      Fuzzy_Jaro
    double j7 = HowSimilar("David", "Davdi", SqliteFuzzyPlusExtension::Fuzzy_Jaro);//      Fuzzy_Jaro
    double j8 = HowSimilar("David", "Da v id", SqliteFuzzyPlusExtension::Fuzzy_Jaro);//    Fuzzy_Jaro


    double zz = HowSimilar("David", "xxxxx", SqliteFuzzyPlusExtension::Fuzzy_Damlev);

    return 0;
}
