#include <atlstr.h>
#include <fstream>
#include <iostream>
#include <string>
#include <windows.h>
using namespace std;
using namespace System;
#define SQLITEFUZZYPLUSEXTENSION_LIB "SQLITEFUZZYPLUSEXTENSION.LIB"
#include "..\..\SqliteFuzzyPlusExtension\SqliteFuzzyPlusExtension.h"

static void CreateScriptSimilarWords(string rootDir, string fieldName, string table, string FunctionName, string CompareTo, bool byName) 
{
    string fileName = byName ? "_ByName_" : "_ByNumber_";
    string fullFileName = rootDir + FunctionName + fileName + table + ".sql";
    ofstream f(fullFileName);
    f << "select " << fieldName << endl;
    for (int i = 0; i <= (int)FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID::iChapmanMeanLength; ++i)
    {
        CString d = FuzzyPlusCSharp::Fuzzy::GetStringMatchingAlgorithmName(i);
        string fuzzyFunctionName = CW2A(d).operator char *();
        if (std::isdigit(fuzzyFunctionName[0]))
            continue;
        if (fuzzyFunctionName.find("DO_NOT_USE") != string::npos && fuzzyFunctionName.find("SimHash") == string::npos)
            continue;
        f << ", " << FunctionName << "(" << fieldName << ", " << CompareTo << ", ";
        if (byName)
            f << "'" << fuzzyFunctionName << "'";
        else
            f << i;
        string note = "";
        if (fuzzyFunctionName.find("DO_NOT_USE") != string::npos)
            note = "   !!! Warning: This is NOT a working algorithm!!!";
        else if (fuzzyFunctionName.find("ChapmanMeanLength") != string::npos)
            note = "   !!! Warning: The ChapmanMeanLength algorithm does not work. It does NOT produce expected results!!!";
        else if (fuzzyFunctionName.find("Hamming") != string::npos)
            note = "   *** Note: The Hamming algorithm only works with strings having equal length ***";
        f << ") as a" << i << " -- " << fuzzyFunctionName << " (ID# " << i << ")" << note << endl;
    }
    if ((FunctionName == "IsSimilar" || FunctionName == "IsVerySimilar") &&
        (table == "SimilarNames" || table == "SimilarWords"))
    {
        for (int i = (int)FuzzyPlusCSharp::Fuzzy::SameSoundMethod::SoundexPhonix; i < FuzzyPlusCSharp::Fuzzy::MICROSOFT_PHONETIC_ALGORITHMS + 1; ++i)
        {
            CString d = FuzzyPlusCSharp::Fuzzy::GetSameSoundMethodName(i);
            string fuzzyFunctionName = CW2A(d).operator char *();
            if (std::isdigit(fuzzyFunctionName[0]))
                continue;
            f << ", " << FunctionName << "(" << fieldName << ", " << CompareTo << ", ";
            if (byName)
                f << "'" << fuzzyFunctionName << "'";
            else
                f << i;
            f << ") as a" << i << " -- " << fuzzyFunctionName << " (ID# " << i << ")" << endl;
        }
    }
    f << "FROM " << table << ";" << endl;
    f << "-- Note: Case insensitive functions have an ID number greater than " << FuzzyPlusCSharp::Fuzzy::CASE_INSENSITIVE_STRING_MATCHING_ALGORITHMS << endl;
    f << "--       C++ functions have an ID number equal to or greater than  " << FuzzyPlusCSharp::Fuzzy::CPP_ONLY_FUZZY_ALGORITHM_IMPLEMENTATION << " and less than " << FuzzyPlusCSharp::Fuzzy::BAD_STRING_MATCHING_ALGORITHMS << endl;
    f << "--       Tokenize functions have an ID number equal to or greater than  " << FuzzyPlusCSharp::Fuzzy::TOKEN_STRING_MATCHING_ALGORITHMS << " and less than " << FuzzyPlusCSharp::Fuzzy::PHRASE_STRING_MATCHING_ALGORITHMS << endl;
    f << "--       Phrase functions have an ID number equal to or greater than  " << FuzzyPlusCSharp::Fuzzy::PHRASE_STRING_MATCHING_ALGORITHMS << " and less than " << FuzzyPlusCSharp::Fuzzy::CPP_ONLY_FUZZY_ALGORITHM_IMPLEMENTATION << endl;
    f << "--       Functions that are being considered for deletion have an ID number equal to or greater than  " << FuzzyPlusCSharp::Fuzzy::STRING_MATCHING_ALGORITHMS_UP_FOR_DELETION << " and less than " << FuzzyPlusCSharp::Fuzzy::CASE_INSENSITIVE_STRING_MATCHING_ALGORITHMS << endl;
    f.close();
}

static void CreateScriptSimilarWords(string rootDir, string fieldName, string table, string FunctionName, string CompareTo)
{
    CreateScriptSimilarWords(rootDir, fieldName, table, FunctionName, CompareTo, false);
    CreateScriptSimilarWords(rootDir, fieldName, table, FunctionName, CompareTo, true);
}

// Function to trim leading whitespace
static std::string ltrim(const std::string& s, string whatToTrim = " \t\n\r\f\v") {
    size_t start = s.find_first_not_of(whatToTrim);
    return (start == std::string::npos) ? "" : s.substr(start);
}

// Function to trim trailing whitespace
static std::string rtrim(const std::string& s, string whatToTrim = " \t\n\r\f\v") {
    size_t end = s.find_last_not_of(whatToTrim);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

static void CreateScriptSimilarSound(string rootDir, string fieldName, string table, string FunctionName, string CompareTo, bool byName)
{
    string fileName = byName ? "_ByName_" : "_ByNumber_";
    string Src2 = ltrim(rtrim(CompareTo, "'"), "'");
    ofstream f(rootDir + FunctionName + fileName + table + "_Src2_" + Src2 + ".sql");
    f << "select " << fieldName << " as src1, " << CompareTo << " as src2 " << endl;
    for (int i = 0; i < (int)FuzzyPlusCSharp::Fuzzy::SameSoundMethod::Fuzzy_Translit; ++i)
    {
        CString d = FuzzyPlusCSharp::Fuzzy::GetSameSoundMethodName(i);
        string soundMethodName = CW2A(d).operator char *();
        if (std::isdigit(soundMethodName[0]))
            continue;
        f << ", " << FunctionName << "(" << fieldName << ", " << CompareTo << ", ";
        if (byName)
            f << "'" << soundMethodName << "'";
        else
            f << i;
        f << ") as a" << i << " -- " << soundMethodName << " (ID# " << i << ")" << endl;
    }
    f << "FROM " << table << ";" << endl;
    f << "-- Note: EnPhoneticDistance only works with SqliteFuzzyPlusExtensionWithMsPhoneticMatching.dll" << endl;
    f.close();
}
static void CreateScriptSimilarSound(string rootDir, string fieldName, string table, string FunctionName, string CompareTo)
{
    CreateScriptSimilarSound(rootDir, fieldName, table, FunctionName, CompareTo, false);
    CreateScriptSimilarSound(rootDir, fieldName, table, FunctionName, CompareTo, true);
}

static void CreateUnitTestSqlFiles()
{
    string rootDir = "..\\..\\SqliteFuzzyPlusExtension\\TestData\\AutoCreatedSqlScript\\";
    CreateScriptSimilarWords(rootDir, "Name", "SimilarNames", "Distance", "'David Jorge'");
    CreateScriptSimilarWords(rootDir, "Phrases", "SimilarPhrase", "Distance", "'This is a similar phrase test'");
    CreateScriptSimilarWords(rootDir, "Words", "SimilarWords", "Distance", "'David'");
    CreateScriptSimilarWords(rootDir, "Name", "SimilarNames", "HowSimilar", "'David Jorge'");
    CreateScriptSimilarWords(rootDir, "Phrases", "SimilarPhrase", "HowSimilar", "'This is a similar phrase test'");
    CreateScriptSimilarWords(rootDir, "Words", "SimilarWords", "HowSimilar", "'David'");
    CreateScriptSimilarWords(rootDir, "Name", "SimilarNames", "Similar", "'David Jorge'");
    CreateScriptSimilarWords(rootDir, "Phrases", "SimilarPhrase", "Similar", "'This is a similar phrase test'");
    CreateScriptSimilarWords(rootDir, "Words", "SimilarWords", "Similar", "'David'");

    CreateScriptSimilarWords(rootDir, "Name", "SimilarNames", "IsVerySimilar", "'David Jorge'");
    CreateScriptSimilarWords(rootDir, "Phrases", "SimilarPhrase", "IsVerySimilar", "'This is a similar phrase test'");
    CreateScriptSimilarWords(rootDir, "Words", "SimilarWords", "IsVerySimilar", "'David'");
    CreateScriptSimilarWords(rootDir, "Name", "SimilarNames", "IsSimilar", "'David Jorge'");
    CreateScriptSimilarWords(rootDir, "Words", "SimilarWords", "IsSimilar", "'David'");

    CreateScriptSimilarWords(rootDir, "Phrases", "SimilarPhrase", "IsSimilar", "'This is a similar phrase test'");
    CreateScriptSimilarWords(rootDir, "Phrases", "SimilarPhrase", "IsSomeWhatSimilar", "'This is a similar phrase test'");
    CreateScriptSimilarWords(rootDir, "Phrases", "SimilarPhrase", "IsSlightlySimilar", "'This is a similar phrase test'");
    CreateScriptSimilarWords(rootDir, "Phrases", "SimilarPhrase", "IsHardlySimilar", "'This is a similar phrase test'");
    CreateScriptSimilarWords(rootDir, "Phrases", "SimilarPhrase", "IsNotSimilar", "'This is a similar phrase test'");
    CreateScriptSimilarWords(rootDir, "Phrases", "SimilarPhrase", "HowSimilar", "'This is a similar phrase test'");

    CreateScriptSimilarSound(rootDir, "Source1", "SimilarSoundingWords1To1_NoMatch", "SameSound", "Source2");
    CreateScriptSimilarSound(rootDir, "Source1", "SimilarSoundingWords1To1_AllMatch", "SameSound", "Source2");
    CreateScriptSimilarSound(rootDir, "Words", "SimilarSoundingWords", "SameSound", "'been'");
    CreateScriptSimilarSound(rootDir, "Words", "SimilarSoundingWords", "SameSound", "'being'");
    CreateScriptSimilarSound(rootDir, "Words", "SimilarSoundingWords", "SameSound", "'bean'");
    CreateScriptSimilarSound(rootDir, "Words", "SimilarSoundingWords", "SameSound", "'their'");
}

int main() //array<System::String ^> ^args)
{
    CreateUnitTestSqlFiles();
    int t = (int)FuzzyPlusCSharp::Fuzzy::GetStringMatchingAlgorithm("Levenshtein");
    t = (int)FuzzyPlusCSharp::Fuzzy::GetStringMatchingAlgorithm("CaverPhonePhonix");
    t = (int)FuzzyPlusCSharp::Fuzzy::GetStringMatchingAlgorithm("badname");

    FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID s = FuzzyPlusCSharp::Fuzzy::GetStringMatchingAlgorithm("Levenshtein");
    s = FuzzyPlusCSharp::Fuzzy::GetStringMatchingAlgorithm("CaverPhonePhonix");
    s = FuzzyPlusCSharp::Fuzzy::GetStringMatchingAlgorithm("badname");

    const char* str1 = "Hello World";
    const char* str2 = "Hellx sorld";
    double x = DamerauLevenshteinDistance(str1, str2);
    std::cout << "x = " << x << std::endl;

    const char* sound1 = "been";
    const char* sound2 = "being";
    int x1 = EnPhoneticDistance(sound1, sound2);
    double x2 = DamerauLevenshteinDistance(sound1, sound2);
    int x3 = SoundexPhonix(sound1, sound2);
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

    double exampleA = Distance("David", "David", SqliteFuzzyPlusExtension::EdlibDistance);
    double exampleB = HowSimilar("David", "David", SqliteFuzzyPlusExtension::EdlibDistance);
    double exampleC = Distance("David", "xxxxx", SqliteFuzzyPlusExtension::EdlibDistance);
    double exampleD = HowSimilar("David", "xxxxx", SqliteFuzzyPlusExtension::EdlibDistance);
    double example1 = Distance("David", "David", SqliteFuzzyPlusExtension::Levenshtein);
    double example2 = Distance("David", "Davix", SqliteFuzzyPlusExtension::DamerauLevenshtein);
    double example3 = Distance("David", "Davxx", SqliteFuzzyPlusExtension::JaroWinkler);
    double example4 = Distance("David", "Daxxx", SqliteFuzzyPlusExtension::Fuzzy_Leven);
    double example5 = Distance("David", "Dxxxx", SqliteFuzzyPlusExtension::Fuzzy_Damlev);
    double example6 = Distance("David", "xxxxx", SqliteFuzzyPlusExtension::Fuzzy_Jarowin);
    double example7 = Distance("David", "david", SqliteFuzzyPlusExtension::iLevenshtein);
    double example8 = Distance("David", "davdi", SqliteFuzzyPlusExtension::iLevenshtein);

    double similar00 = HowSimilar("David", "David", SqliteFuzzyPlusExtension::UseDefaultStringMatchingAlgorithm);
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
