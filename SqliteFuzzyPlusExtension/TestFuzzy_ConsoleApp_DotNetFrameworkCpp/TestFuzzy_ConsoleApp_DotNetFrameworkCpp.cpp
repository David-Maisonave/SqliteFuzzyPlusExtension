#include "pch.h"
#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <atlstr.h>
#include <stdio.h>
#include <assert.h>
using namespace std;
using namespace System;
#define SQLITEFUZZYPLUSEXTENSION_INCLUDE_FUNCTION_MACROS_FOR_C
#include "..\SqliteFuzzyPlusExtension.h"

static void CreateScriptSimilarWords(string rootDir, string fieldName, string table, string FunctionName, string CompareTo, bool byName) 
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
        f << ", " << FunctionName << "(" << fieldName << ", " << CompareTo << ", ";
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
    for (int i = 0; i < (int)FuzzyPlusCSharp::Fuzzy::SameSoundMethod::fuzzy_translit; ++i)
    {
        CString d = FuzzyPlusCSharp::Fuzzy::GetSameSoundMethodName(i);
        string soundMethodName = CW2A(d);
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
    string rootDir = "..\\TestData\\AutoCreatedSqlScript\\";
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

static void TestPhonetics(const char* defaultSoundMethod)
{
    if (defaultSoundMethod != NULL) {
        SetDefaultSameSoundMethodByName(defaultSoundMethod);
        printf("Using sound method '%s' as default sound method.\n", defaultSoundMethod);
    }
    else
        printf("Using sound method '%i' as default sound method.\n", GetDefaultSoundMethod());
    bool s1 = SameSound("to", "to", SqliteFuzzyPlusExtension::Soundex2, GetDistanceMethodID("ExactMatch"), 1);
    bool s2 = SameSound("to", "two", SqliteFuzzyPlusExtension::Soundex2, GetDistanceMethodID("ExactMatch"), 1);
    bool s3 = SameSound("to", "too", GetSameSoundMethodID("Soundex2"), GetDistanceMethodID("ExactMatch"), 1);
    bool s4 = SameSound("to", "if", GetSameSoundMethodID("Soundex2"), GetDistanceMethodID("ExactMatch"), 1);
    bool s5 = SameSound("to", "no", SqliteFuzzyPlusExtension::Soundex2, GetDistanceMethodID("ExactMatch"), 1);
    bool s6 = SameSound("to", "to", GetSameSoundMethodID("fuzzy_soundex"), GetDistanceMethodID("ExactMatch"), 1);
    bool s7 = SameSound("to", "two", GetSameSoundMethodID("fuzzy_soundex"), GetDistanceMethodID("ExactMatch"), 1);
    bool s8 = SameSound("to", "too", GetSameSoundMethodID("fuzzy_soundex"), GetDistanceMethodID("ExactMatch"), 1);
    bool s9 = SameSound("to", "if", GetSameSoundMethodID("fuzzy_soundex"), GetDistanceMethodID("ExactMatch"), 1);
    bool s0 = SameSound("to", "no", GetSameSoundMethodID("fuzzy_soundex"), GetDistanceMethodID("ExactMatch"), 1);
    printf("(to) s1=%i, s2=%i, s3=%i, s4=%i, s5=%i, s6=%i, s7=%i, s8=%i, s9=%i, s0=%i\n", s1, s2, s3, s4, s5, s6, s7, s8, s9, s0);
    s1 = SAMESOUND("there", "there");
    s2 = SAMESOUND("there", "their");
    s3 = SAMESOUND("there", "they're");
    s4 = SAMESOUND("there", "bear");
    s5 = SAMESOUND("there", "band");
    s6 = SAMESOUND_NM("there", "there", "fuzzy_soundex");
    s7 = SAMESOUND_NM("there", "their", "fuzzy_soundex");
    s8 = SAMESOUND_NM("there", "they're", "fuzzy_soundex");
    s9 = SAMESOUND_ID("there", "bear", SqliteFuzzyPlusExtension::fuzzy_soundex);
    s0 = SAMESOUND_ID("there", "band", SqliteFuzzyPlusExtension::fuzzy_soundex);
    printf("(there) s1=%i, s2=%i, s3=%i, s4=%i, s5=%i, s6=%i, s7=%i, s8=%i, s9=%i, s0=%i\n", s1, s2, s3, s4, s5, s6, s7, s8, s9, s0);
    // Most phonetic test fail when comparing "been", "being" and "bin", except for EnPhoneticDistance
    printf("Most phonetic test fail when comparing 'been', 'being' and 'bin', except for EnPhoneticDistance, and MatchRatingApproach\n");
    printf("Phonetic methods (1-3=default, 4-6=fuzzy_soundex, 7-9=CaverPhonePhonix, a-c=MatchRatingApproach)\n");
    bool b1 = SAMESOUND("been", "being");  // This should pass, but it fails!!!
    bool b2 = SAMESOUND("been", "bin");  // This should fail, but it passes!!!
    bool b3 = SAMESOUND("been", "bean");
    bool b4 = SAMESOUND_NM("been", "being", "fuzzy_soundex");  // This should pass, but it fails!!!
    bool b5 = SAMESOUND_NM("been", "bin", "fuzzy_soundex");  // This should fail, but it passes!!!
    bool b6 = SAMESOUND_NM("been", "bean", "fuzzy_soundex");
    bool b7 = SAMESOUND_NM("been", "being", "CaverPhonePhonix");  // This should pass, but it fails!!!
    bool b8 = SAMESOUND_NM("been", "bin", "CaverPhonePhonix");  // This should fail, but it passes!!!
    bool b9 = SAMESOUND_NM("been", "bean", "CaverPhonePhonix");
    bool ba = SAMESOUND_NM("been", "being", "MatchRatingApproach");
    bool bb = SAMESOUND_NM("been", "bin", "MatchRatingApproach");
    bool bc = SAMESOUND_NM("been", "bean", "MatchRatingApproach");

    if (EnPhoneticDistance_IsSupported()) {
        bool e1 = SAMESOUND_NM("been", "been", "EnPhoneticDistance");
        bool e2 = SAMESOUND_NM("been", "being", "EnPhoneticDistance");  // This passes correctly using EnPhoneticDistance
        bool e3 = SAMESOUND_NM("been", "flat", "EnPhoneticDistance");
        bool e4 = SAMESOUND_ID("been", "bean", SqliteFuzzyPlusExtension::EnPhoneticDistance);
        bool e5 = SAMESOUND_ID("been", "bin", SqliteFuzzyPlusExtension::EnPhoneticDistance);  // This fails correctly using EnPhoneticDistance
        printf("(been) b1=%i, b2=%i, b3=%i, b4=%i, b5=%i, b6=%i, b7=%i, b8=%i, b9=%i, ba=%i, bb=%i, bc=%i,\ne1=%i, e2=%i, e3=%i, e4=%i, e5=%i\n", b1, b2, b3, b4, b5, b6, b7, b8, b9, ba, bb, bc, e1, e2, e3, e4, e5);
    } // Mibspealled word tesxt hearedd
    else
        printf("(been) b1=%i, b2=%i, b3=%i, b4=%i, b5=%i, b6=%i, b7=%i, b8=%i, b9=%i, ba=%i, bb=%i, bc=%i\n", b1, b2, b3, b4, b5, b6, b7, b8, b9, ba, bb, bc);
    if (defaultSoundMethod == NULL)
    {
        printf("Phonix phonetic (1-4=Metaphone, 5-8=DoubleMetaphone, 9-c=CaverPhonePhonix, d-h=MatchRatingApproach)\n");
        bool f1 = SAMESOUND_NM("been", "being", "Metaphone");
        bool f2 = SAMESOUND_NM("been", "bin", "Metaphone");
        bool f3 = SAMESOUND_NM("been", "bean", "Metaphone");
        bool f4 = SAMESOUND_NM("been", "flat", "Metaphone");
        bool f5 = SAMESOUND_NM("been", "being", "DoubleMetaphone");
        bool f6 = SAMESOUND_NM("been", "bin", "DoubleMetaphone");
        bool f7 = SAMESOUND_NM("been", "bean", "DoubleMetaphone");
        bool f8 = SAMESOUND_NM("been", "flat", "DoubleMetaphone");
        bool f9 = SAMESOUND_NM("been", "being", "CaverPhonePhonix");
        bool fa = SAMESOUND_NM("been", "bin", "CaverPhonePhonix");
        bool fb = SAMESOUND_NM("been", "bean", "CaverPhonePhonix");
        bool fc = SAMESOUND_NM("been", "flat", "CaverPhonePhonix");
        bool fd = SAMESOUND_NM("been", "being", "MatchRatingApproach");
        bool fe = SAMESOUND_NM("been", "bin", "MatchRatingApproach");
        bool ff = SAMESOUND_NM("been", "bean", "MatchRatingApproach");
        bool fg = SAMESOUND_NM("been", "flat", "MatchRatingApproach"); // This should fail, but it passes!!!
        bool fh = SAMESOUND_NM("been", "xxxx", "MatchRatingApproach"); // This should fail, but it passes!!!
        printf("(been) f1=%i, f2=%i, f3=%i, f4=%i, f5=%i, f6=%i, f7=%i, f8=%i, f9=%i, fa=%i, fb=%i, fc=%i, fd=%i, fe=%i, ff=%i, fg=%i, fh=%i\n", f1, f2, f3, f4, f5, f6, f7, f8, f9, fa, fb, fc, fd, fe, ff, fg, fh);
    }
    printf("\n\n");
}

static void TestDistanceIsZeroForMatches()
{
    double d0 = Distance("David Jorge", "David Jorge", SqliteFuzzyPlusExtension::Levenshtein);
    double d1 = Distance("David Jorge", "David Jorge", SqliteFuzzyPlusExtension::LongestCommonSequence);
    double d2 = Distance("David Jorge", "David Jorge", SqliteFuzzyPlusExtension::NeedlemanWunsch);
    double d3 = Distance("David Jorge", "David Jorge", SqliteFuzzyPlusExtension::HammingDistance);
    double d4 = Distance("David Jorge", "David Jorge", SqliteFuzzyPlusExtension::JaroDistance);
    double d5 = Distance("David Jorge", "David Jorge", SqliteFuzzyPlusExtension::NormalizedLevenshteinDistance);
    double d6 = Distance("David Jorge", "David Jorge", SqliteFuzzyPlusExtension::Levenshtein2Distance);
    double d7 = Distance("David Jorge", "David Jorge", SqliteFuzzyPlusExtension::BlockDistance);
    double d8 = Distance("David Jorge", "David Jorge", SqliteFuzzyPlusExtension::ChapmanLengthDeviation);
    double d9 = Distance("David Jorge", "David Jorge", SqliteFuzzyPlusExtension::ChapmanMeanLength); //(0.164720987904));
    double da = Distance("David Jorge", "David Jorge", SqliteFuzzyPlusExtension::EuclideanDistance);
    double db = Distance("David Jorge", "David Jorge", SqliteFuzzyPlusExtension::MatchingCoefficient);
    double dc = Distance("David Jorge", "David Jorge", SqliteFuzzyPlusExtension::MongeElkan);
    double dd = Distance("David Jorge", "David Jorge", SqliteFuzzyPlusExtension::QGramsDistance);
    double de = Distance("David Jorge", "David Jorge", SqliteFuzzyPlusExtension::SmithWaterman);
    double df = Distance("David Jorge", "David Jorge", SqliteFuzzyPlusExtension::SmithWatermanGotoh);
    double dg = Distance("David Jorge", "David Jorge", SqliteFuzzyPlusExtension::SmithWatermanGotohWindowedAffine);
    double dh = Distance("David Jorge", "David Jorge", SqliteFuzzyPlusExtension::CosineSimilarity);
    double dj = Distance("David Jorge", "David Jorge", SqliteFuzzyPlusExtension::JaccardSimilarity);
    double dk = Distance("David Jorge", "David Jorge", SqliteFuzzyPlusExtension::Fuzzy_Jaro);
    double dl = Distance("David Jorge", "David Jorge", SqliteFuzzyPlusExtension::iLongestCommonSequence);
    double dm = Distance("David Jorge", "David Jorge", SqliteFuzzyPlusExtension::iNeedlemanWunsch);
    double dn = Distance("David Jorge", "David Jorge", SqliteFuzzyPlusExtension::iHammingDistance);
    double dO = Distance("David Jorge", "David Jorge", SqliteFuzzyPlusExtension::iNormalizedLevenshteinDistance);
    double dp = Distance("David Jorge", "David Jorge", SqliteFuzzyPlusExtension::iLevenshtein2Distance);
    double dq = Distance("David Jorge", "David Jorge", SqliteFuzzyPlusExtension::iCosineSimilarity);
    double dr = Distance("David Jorge", "David Jorge", SqliteFuzzyPlusExtension::iJaccardSimilarity);
    double ds = Distance("David Jorge", "David Jorge", SqliteFuzzyPlusExtension::iBlockDistance);
    double dt = Distance("David Jorge", "David Jorge", SqliteFuzzyPlusExtension::iChapmanLengthDeviation);
    double du = Distance("David Jorge", "David Jorge", SqliteFuzzyPlusExtension::iEuclideanDistance);
    double dv = Distance("David Jorge", "David Jorge", SqliteFuzzyPlusExtension::iMatchingCoefficient);
    double dw = Distance("David Jorge", "David Jorge", SqliteFuzzyPlusExtension::iMongeElkan);
    dw = Distance("ThisIsATestToSeeIfLengthChangesDistance", "ThatIsNotTheSameWord", SqliteFuzzyPlusExtension::iMongeElkan);
    dw = Distance("This is a test to see if length changes the distance", "It is not the same words", SqliteFuzzyPlusExtension::iMongeElkan);
    dw = Distance("David", "David", SqliteFuzzyPlusExtension::iMongeElkan);
    dw = Distance("David", "Davix", SqliteFuzzyPlusExtension::iMongeElkan);
    dw = Distance("David", "Davxx", SqliteFuzzyPlusExtension::iMongeElkan);
    dw = Distance("David", "Daxxx", SqliteFuzzyPlusExtension::iMongeElkan);
    dw = Distance("David", "Dxxxx", SqliteFuzzyPlusExtension::iMongeElkan);
    dw = Distance("David", "xxxxx", SqliteFuzzyPlusExtension::iMongeElkan);
    dw = Distance("David", "zzzzz", SqliteFuzzyPlusExtension::iMongeElkan);
    dw = Distance("David", "Jorge", SqliteFuzzyPlusExtension::iMongeElkan);
    dw = HowSimilar("David", "David", SqliteFuzzyPlusExtension::iMongeElkan);
    dw = HowSimilar("David", "Daved", SqliteFuzzyPlusExtension::iMongeElkan);
    dw = HowSimilar("David", "Davdi", SqliteFuzzyPlusExtension::iMongeElkan);
    dw = HowSimilar("David", "zzzzz", SqliteFuzzyPlusExtension::iMongeElkan);
    double dx = Distance("David Jorge", "David Jorge", SqliteFuzzyPlusExtension::iQGramsDistance);
    double dy = Distance("David Jorge", "David Jorge", SqliteFuzzyPlusExtension::iSmithWaterman);
    double dz = Distance("David Jorge", "David Jorge", SqliteFuzzyPlusExtension::iSmithWatermanGotoh);
    double d_ = Distance("David Jorge", "David Jorge", SqliteFuzzyPlusExtension::iSmithWatermanGotohWindowedAffine);
    double d__ = Distance("David Jorge", "David Jorge", SqliteFuzzyPlusExtension::iSmithWatermanGotohWindowedAffine);
}

static void DoAssertions() {
    // First make sure C# enums match the C/C++ enums. Since the enums are not the same code, need to make sure that any change made to C# code is made to the C/C++ header.
    assert(SqliteFuzzyPlusExtension::Levenshtein == GetDistanceMethodID("Levenshtein"));
    assert(SqliteFuzzyPlusExtension::TanimotoCoefficientDistance == GetDistanceMethodID("TanimotoCoefficientDistance"));
    assert(SqliteFuzzyPlusExtension::DiceSimilarity == GetDistanceMethodID("DiceSimilarity"));
    assert(SqliteFuzzyPlusExtension::JaccardSimilarity == GetDistanceMethodID("JaccardSimilarity"));
    assert(SqliteFuzzyPlusExtension::SimplePhraseTokenize == GetDistanceMethodID("SimplePhraseTokenize"));
    assert(SqliteFuzzyPlusExtension::EditDistance == GetDistanceMethodID("EditDistance"));
    assert(SqliteFuzzyPlusExtension::Fuzzy_Jaro == GetDistanceMethodID("Fuzzy_Jaro"));
    assert(SqliteFuzzyPlusExtension::EdlibDistance == GetDistanceMethodID("EdlibDistance"));
    assert(SqliteFuzzyPlusExtension::ChapmanMeanLength == GetDistanceMethodID("ChapmanMeanLength"));
    assert(SqliteFuzzyPlusExtension::iEdlibDistance == GetDistanceMethodID("iEdlibDistance"));
}

int main() //array<System::String ^> ^args)
{
    DoAssertions();
    TestDistanceIsZeroForMatches();
    CreateUnitTestSqlFiles();
    TestPhonetics(NULL);
    TestPhonetics("MatchRatingApproach");
    TestPhonetics("ColognePhonetics");
    SAMESOUND_NM("been", "been", "MatchRatingApproach");
    SAMESOUND_NM("been", "being", "MatchRatingApproach");
    SAMESOUND_NM("been", "bean", "MatchRatingApproach");
    SAMESOUND_NM("been", "bing", "MatchRatingApproach");
    SAMESOUND_NM("been", "bin", "MatchRatingApproach");
    SAMESOUND_NM("been", "ban", "MatchRatingApproach");
    SAMESOUND_NM("been", "bone", "MatchRatingApproach");
    SAMESOUND_NM("been", "bind", "MatchRatingApproach");
    SAMESOUND_NM("been", "blind", "MatchRatingApproach");
    SAMESOUND_NM("bind", "blind", "MatchRatingApproach");
    SAMESOUND_NM("been", "beeningbond", "MatchRatingApproach");
    SAMESOUND_NM("been", "bingbong", "MatchRatingApproach");

    const char* str1 = "Hello World";
    const char* str2 = "Hellx sorld";
    double x = DamerauLevenshteinDistance(str1, str2);
    std::cout << "x = " << x << std::endl;


    const char* sound1 = "been";
    const char* sound2 = "being";
    int x1 = EnPhoneticDistance(sound1, sound2);
    double x2 = DamerauLevenshteinDistance(sound1, sound2);
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
