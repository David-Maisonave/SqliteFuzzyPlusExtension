// UnitTestConsole_C_Runner.c : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#define COMPILE_TO_C_LANGUAGE_SQLITEFUZZYPLUSEXTENSION__
#include "..\..\SqliteFuzzyPlusExtension\SqliteFuzzyPlusExtension.h"

static void TestPhonetics(const char* defaultSoundMethod) 
{
    if (defaultSoundMethod != NULL)
        SetDefaultSameSoundMethodByName(defaultSoundMethod);
    bool s1 = SameSound("to", "to", enum_SoundexPhonix, GetStringMatchingAlgorithmID("SameSound_StrCmp"), 1);
    bool s2 = SameSound("to", "two", enum_SoundexPhonix, GetStringMatchingAlgorithmID("SameSound_StrCmp"), 1);
    bool s3 = SameSound("to", "too", GetSameSoundMethodID("SoundexPhonix"), GetStringMatchingAlgorithmID("SameSound_StrCmp"), 1);
    bool s4 = SameSound("to", "if", GetSameSoundMethodID("SoundexPhonix"), GetStringMatchingAlgorithmID("SameSound_StrCmp"), 1);
    bool s5 = SameSound("to", "no", enum_SoundexPhonix, GetStringMatchingAlgorithmID("SameSound_StrCmp"), 1);
    bool s6 = SameSound("to", "to", GetSameSoundMethodID("fuzzy_soundex"), GetStringMatchingAlgorithmID("SameSound_StrCmp"), 1);
    bool s7 = SameSound("to", "two", GetSameSoundMethodID("fuzzy_soundex"), GetStringMatchingAlgorithmID("SameSound_StrCmp"), 1);
    bool s8 = SameSound("to", "too", GetSameSoundMethodID("fuzzy_soundex"), GetStringMatchingAlgorithmID("SameSound_StrCmp"), 1);
    bool s9 = SameSound("to", "if", GetSameSoundMethodID("fuzzy_soundex"), GetStringMatchingAlgorithmID("SameSound_StrCmp"), 1);
    bool s0 = SameSound("to", "no", GetSameSoundMethodID("fuzzy_soundex"), GetStringMatchingAlgorithmID("SameSound_StrCmp"), 1);
    printf("(to) s1=%i, s2=%i, s3=%i, s4=%i, s5=%i, s6=%i, s7=%i, s8=%i, s9=%i, s0=%i\n", s1, s2, s3, s4, s5, s6, s7, s8, s9, s0);
    s1 = SAMESOUND("there", "there");
    s2 = SAMESOUND("there", "their");
    s3 = SAMESOUND("there", "they're");
    s4 = SAMESOUND("there", "bear");
    s5 = SAMESOUND("there", "band");
    s6 = SAMESOUND_NM("there", "there", "fuzzy_soundex");
    s7 = SAMESOUND_NM("there", "their", "fuzzy_soundex");
    s8 = SAMESOUND_NM("there", "they're", "fuzzy_soundex");
    s9 = SAMESOUND_ID("there", "bear", Fuzzy_Soundex);
    s0 = SAMESOUND_ID("there", "band", Fuzzy_Soundex);
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
        bool e4 = SAMESOUND_ID("been", "bean", enum_EnPhoneticDistance);
        bool e5 = SAMESOUND_ID("been", "bin", enum_EnPhoneticDistance);  // This fails correctly using EnPhoneticDistance
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

static void TestDistanceFunctionsOnWords(const char* str1, const char* str2) 
{
    printf("\nTesting '%s' and '%s'\n", str1, str2);
    double d0 = Levenshtein(str1, str2, false);
    double d1 = DamerauLevenshtein(str1, str2, false);
    double d2 = Hamming(str1, str2, false);
    double d3 = JaccardDistance(str1, str2, false);
    double d4 = JaroDistance(str1, str2, false);
    double d5 = JaroWinklerDistance(str1, str2, false);
    double d6 = Levenshtein2Distance(str1, str2, false);
    double d7 = LongestCommonSubsequenceDistance(str1, str2, false);
    double d8 = LongestCommonSubstringDistance(str1, str2, false);
    double d9 = NormalizedLevenshteinDistance(str1, str2, false);
    double d10 = OverlapCoefficientDistance(str1, str2, false);
    double d11 = RatcliffObershelpSimilarityDistance(str1, str2, false);
    double d12 = SorensenDiceDistance(str1, str2, false);
    double d13 = TanimotoCoefficientDistance(str1, str2, false);
    double d14 = BlockDistance(str1, str2, false);
    double d15 = NeedlemanWunsch(str1, str2, false);
    double d16 = JaccardIndex(str1, str2, false);
    double d17 = ChapmanLengthDeviation(str1, str2, false);
    double d18 = ChapmanMeanLength(str1, str2, false);
    double d19 = EuclideanDistance(str1, str2, false);
    printf("d0=%.2f, d1=%.2f, d2=%.2f, d3=%.2f, d4=%.2f, d5=%.2f, d6=%.2f, d7=%.2f, d8=%.2f, d9=%.2f, \nd10=%.2f, d11=%.2f, d12=%.2f, d13=%.2f, d14=%.2f, d15=%.2f, d16=%.2f, d17=%.2f, d18=%.2f, d19=%.2f\n", d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19);
    d0 = MatchingCoefficient(str1, str2, false);
    d1 = MongeElkan(str1, str2, false);
    d2 = QGramsDistance(str1, str2, false);
    d3 = SmithWaterman(str1, str2, false);
    d4 = SmithWatermanGotoh(str1, str2, false);
    d5 = SmithWatermanGotohWindowedAffine(str1, str2, false);
    d6 = CosineSimilarity(str1, str2, false);
    d7 = JaccardSimilarity(str1, str2, false);
    d8 = LongestCommonSequence(str1, str2, false);
    d9 = DiceSimilarity(str1, str2, false);
    d10 = PhraseTokenize(str1, str2, false);
    d11 = SimplePhraseTokenize(str1, str2, false);
    printf("d0=%.2f, d1=%.2f, d2=%.2f, d3=%.2f, d4=%.2f, d5=%.2f, d6=%.2f, d7=%.2f, d8=%.2f, d9=%.2f, \nd10=%.2f, d11=%.2f\n", d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11);
}


static void TestDistanceFunctions()
{
    TestDistanceFunctionsOnWords("This is a same sentence test", "This is a same sentence test");
    TestDistanceFunctionsOnWords("This is a test for similar sentence", "This is test for similar sentence");
    TestDistanceFunctionsOnWords("This is a test for similar sentence", "Not the same phrase at all");
}

int main()
{
    printf("Running UnitTestConsole_C_Runner\n");
    TestPhonetics(NULL);
    TestPhonetics("ColognePhonetics");
    TestDistanceFunctions();
}
