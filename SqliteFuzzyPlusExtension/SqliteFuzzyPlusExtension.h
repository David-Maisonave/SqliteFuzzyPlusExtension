#ifndef SQLITEFUZZYPLUSEXTENSION_H
#define SQLITEFUZZYPLUSEXTENSION_H

#ifdef __cplusplus
#include <string>
#define C_ENUM_NAMING_CONVENTION__(name) name
#define NAMESPACE_SQLITEFUZZYPLUSEXTENSION  SqliteFuzzyPlusExtension::
#else
#define SQLITEFUZZYPLUSEXTENSION_COMPILE_TO_C_LANGUAGE__
#endif // __cplusplus

#ifdef SQLITEFUZZYPLUSEXTENSION_COMPILE_TO_C_LANGUAGE__
#define EXCLUDE_NAMESPACE_SQLITEFUZZYPLUSEXTENSION
#include "stdbool.h"
#define C_ENUM_NAMING_CONVENTION__(name) enum_##name
#ifndef SQLITEFUZZYPLUSEXTENSION_EXCLUDE_FUNCTION_MACROS_FOR_C
#define SQLITEFUZZYPLUSEXTENSION_INCLUDE_FUNCTION_MACROS_FOR_C
#endif // !SQLITEFUZZYPLUSEXTENSION_EXCLUDE_FUNCTION_MACROS_FOR_C
#endif // SQLITEFUZZYPLUSEXTENSION_COMPILE_TO_C_LANGUAGE__

#ifdef SQLITEFUZZYPLUSEXTENSION_INCLUDE_FUNCTION_MACROS_FOR_C
#define SAMESOUND(word1, word2) SameSound(word1, word2, 0, 0, 1)
#define SAMESOUND_NM(word1, word2, methodName) SameSound(word1, word2, GetSameSoundMethodID(methodName), GetDistanceMethodID("SameSound_StrCmp"), 1)
#define SAMESOUND_ID(word1, word2, methodID) SameSound(word1, word2, methodID, GetDistanceMethodID("SameSound_StrCmp"), 1)
#endif // SQLITEFUZZYPLUSEXTENSION_INCLUDE_FUNCTION_MACROS_FOR_C


#ifdef EXCLUDE_NAMESPACE_SQLITEFUZZYPLUSEXTENSION
#define NAMESPACE_SQLITEFUZZYPLUSEXTENSION
#endif // EXCLUDE_NAMESPACE_SQLITEFUZZYPLUSEXTENSION


// If building in C language, define EXCLUDE_NAMESPACE_SQLITEFUZZYPLUSEXTENSION to exclude the namespace
#ifndef EXCLUDE_NAMESPACE_SQLITEFUZZYPLUSEXTENSION
namespace SqliteFuzzyPlusExtension {
#endif //!EXCLUDE_NAMESPACE_SQLITEFUZZYPLUSEXTENSION
#ifdef SQLITEFUZZYPLUSEXTENSION_COMPILE_TO_C_LANGUAGE__
#define CASE_INSENSITIVE 256
#define CPP_ONLY_FUZZY 128
#define TOKEN_METHODS 64
#define PHRASE_METHODS TOKEN_METHODS + 32
#define METHODS_UP_FOR_DELETION PHRASE_METHODS + 16
#else // SQLITEFUZZYPLUSEXTENSION_COMPILE_TO_C_LANGUAGE__
    const int CASE_INSENSITIVE = 256;
    const int CPP_ONLY_FUZZY = 128;
    const int TOKEN_METHODS = 64;
    const int PHRASE_METHODS = TOKEN_METHODS + 32;
    const int METHODS_UP_FOR_DELETION = PHRASE_METHODS + 16;
#endif // SQLITEFUZZYPLUSEXTENSION_COMPILE_TO_C_LANGUAGE__
    // Note: In C language, the enums can not use the same name as a function, so macro C_ENUM_NAMING_CONVENTION__ has been added for C-Only code where all the enums with this macro have an "enum_" prefixed to the name.
    //       The C++ code will still reference all the enums by the original name.
    enum DistanceMethod_ID
    {
        UseDefaultDistanceMethod = 0,
        C_ENUM_NAMING_CONVENTION__(Levenshtein),
        C_ENUM_NAMING_CONVENTION__(DamerauLevenshtein),
        C_ENUM_NAMING_CONVENTION__(JaroWinkler),
        C_ENUM_NAMING_CONVENTION__(LongestCommonSequence),
        C_ENUM_NAMING_CONVENTION__(JaccardIndex),
        C_ENUM_NAMING_CONVENTION__(OverlapCoefficient),
        C_ENUM_NAMING_CONVENTION__(NeedlemanWunsch),
        C_ENUM_NAMING_CONVENTION__(SorensenDiceDistance),
        C_ENUM_NAMING_CONVENTION__(RatcliffObershelpSimilarityDistance),
        C_ENUM_NAMING_CONVENTION__(HammingDistance),
        C_ENUM_NAMING_CONVENTION__(LongestCommonSubstringDistance),
        C_ENUM_NAMING_CONVENTION__(LongestCommonSubsequenceDistance),
        C_ENUM_NAMING_CONVENTION__(JaroDistance),
        C_ENUM_NAMING_CONVENTION__(NormalizedLevenshteinDistance),
        C_ENUM_NAMING_CONVENTION__(Levenshtein2Distance),
        C_ENUM_NAMING_CONVENTION__(TanimotoCoefficientDistance),
        // Distance method from SimMetricsCore
        C_ENUM_NAMING_CONVENTION__(BlockDistance),
        C_ENUM_NAMING_CONVENTION__(ChapmanLengthDeviation),
        C_ENUM_NAMING_CONVENTION__(ChapmanMeanLength),
        C_ENUM_NAMING_CONVENTION__(EuclideanDistance),
        C_ENUM_NAMING_CONVENTION__(MatchingCoefficient),
        C_ENUM_NAMING_CONVENTION__(MongeElkan),
        C_ENUM_NAMING_CONVENTION__(QGramsDistance),
        C_ENUM_NAMING_CONVENTION__(SmithWaterman),
        C_ENUM_NAMING_CONVENTION__(SmithWatermanGotoh),
        C_ENUM_NAMING_CONVENTION__(SmithWatermanGotohWindowedAffine),
        C_ENUM_NAMING_CONVENTION__(DiceSimilarity),

        //Token methods
        C_ENUM_NAMING_CONVENTION__(CosineSimilarity) = TOKEN_METHODS,
        C_ENUM_NAMING_CONVENTION__(JaccardSimilarity),

        // Phrase token methods which are all case insensitive only
        C_ENUM_NAMING_CONVENTION__(PhraseTokenize) = PHRASE_METHODS,
        C_ENUM_NAMING_CONVENTION__(SimplePhraseTokenize),

        // EditDistance may get removed, replaced, or logic change 
        C_ENUM_NAMING_CONVENTION__(EditDistance) = METHODS_UP_FOR_DELETION,

        // ------------------------------------------------------------
        // These functions are NOT supported by CSharp Fuzzy class code, and are only here for C++ SqliteFuzzyPlusExtension usage.
        // Sqlean Fuzzy external functions. 
        Fuzzy_Damlev = CPP_ONLY_FUZZY,
        Fuzzy_Hamming,
        Fuzzy_Jarowin,
        Fuzzy_Leven,
        Fuzzy_Osadist,
        Fuzzy_Editdist,
        Fuzzy_Jaro,
        SameSound_StrCmp,
        // Other C++ (external) only functions. (NOT part of Sqlean)
        C_ENUM_NAMING_CONVENTION__(EdlibDistance),
        // ------------------------------------------------------------

        // Case INSENSITIVE versions
        iLevenshtein = CASE_INSENSITIVE + C_ENUM_NAMING_CONVENTION__(Levenshtein),
        iDamerauLevenshtein,
        iJaroWinkler,
        iLongestCommonSequence,
        iJaccardIndex,
        iOverlapCoefficient,
        iNeedlemanWunsch,
        iSorensenDiceDistance,
        iRatcliffObershelpSimilarityDistance,
        iHammingDistance,
        iLongestCommonSubstringDistance,
        iLongestCommonSubsequenceDistance,
        iJaroDistance,
        iNormalizedLevenshteinDistance,
        iLevenshtein2Distance,
        iTanimotoCoefficientDistance,
        iEditDistance,

        //Token methods
        iCosineSimilarity,
        iJaccardSimilarity,

        // Distance method from SimMetricsCore
        iBlockDistance,
        iChapmanLengthDeviation,
        iChapmanMeanLength,
        iEuclideanDistance,
        iMatchingCoefficient,
        iMongeElkan,
        iQGramsDistance,
        iSmithWaterman,
        iSmithWatermanGotoh,
        iSmithWatermanGotohWindowedAffine,
        iDiceSimilarity,

        // ------------------------------------------------------------
        // These functions are NOT supported by CSharp Fuzzy class code, and are only here for C++ SqliteFuzzyPlusExtension usage.
        C_ENUM_NAMING_CONVENTION__(iEdlibDistance) = CASE_INSENSITIVE + C_ENUM_NAMING_CONVENTION__(EdlibDistance)
        // ------------------------------------------------------------
    };
    enum SameSoundMethod
    {
        UseDefaultSameSoundMethod = 0,
        C_ENUM_NAMING_CONVENTION__(Soundex2),    // Default SameSound method
        C_ENUM_NAMING_CONVENTION__(Caverphone2),
        C_ENUM_NAMING_CONVENTION__(EnPhoneticDistance),
        // ------------------------------------------------------------
        // These functions are NOT supported by CSharp Fuzzy class code, and are only here for C++ SqliteFuzzyPlusExtension usage.
        // SQLean phonetic external functions. 
        C_ENUM_NAMING_CONVENTION__(fuzzy_caver),
        C_ENUM_NAMING_CONVENTION__(fuzzy_phonetic),
        C_ENUM_NAMING_CONVENTION__(fuzzy_soundex),
        C_ENUM_NAMING_CONVENTION__(fuzzy_rsoundex),  //Refined Soundex
        C_ENUM_NAMING_CONVENTION__(fuzzy_translit) //Transliteration
    };
#ifndef EXCLUDE_NAMESPACE_SQLITEFUZZYPLUSEXTENSION
}
#endif //EXCLUDE_NAMESPACE_SQLITEFUZZYPLUSEXTENSION

#ifndef SQLITEFUZZYPLUSEXTENSION_EXCLUDE_FUNC
#ifdef SQLITEFUZZYPLUSEXTENSION_LIB
#pragma comment(lib, SQLITEFUZZYPLUSEXTENSION_LIB)
#endif // SQLITEFUZZYPLUSEXTENSION_LIB
/////////////////////////////////////////////////////////////////////////////////
// Function compiled with extern "C"
#ifndef SQLITEFUZZYPLUSEXTENSION_COMPILE_TO_C_LANGUAGE__
extern "C" {
#endif // !SQLITEFUZZYPLUSEXTENSION_COMPILE_TO_C_LANGUAGE__
    double HowSimilar(const char* source1, const char* source2, int DistanceMethod_Id);
    double HowSimilarById(const char* source1, const char* source2, int DistanceMethod_Id);
    double HowSimilarByName(const char* source1, const char* source2, const char* DistanceMethod_Name);
    double Distance(const char* source1, const char* source2, int DistanceMethod_Id);
    double DistanceByName(const char* source1, const char* source2, const char* DistanceMethod_Name);
    int GetDistanceMethodID(const char* DistanceMethod_Name);
    int GetSameSoundMethodID(const char* SameSoundMethod_Name);
    int SetDefaultDistanceMethodByName(const char* DistanceMethod_Name);
    int SetDefaultDistanceMethodByID(int DistanceMethod_Id);
    int GetDefaultDistanceMethod();
    int SetDefaultSameSoundMethod(int sameSoundMethod_ID);
    int SetDefaultSameSoundMethodByName(const char* sameSoundMethod_Name);
    int GetDefaultSoundMethod();
    // C language code can simulate overloaded SameSound functions by using GetSameSoundMethodID and GetDistanceMethodID
    // Example: SameSound("been", "being", GetSameSoundMethodID("Soundex2"), GetDistanceMethodID("Levenshtein"), 1);
    bool SameSound(const char* source1, const char* source2, int SameSoundMethod_Id, int DistanceMethod_Id, bool isVerySimilar);
    /////////////////////////////////////////////////////////////////////////////////
    // Distance Functions
#ifndef SQLITEFUZZYPLUSEXTENSION_COMPILE_TO_C_LANGUAGE__
    int DamerauLevenshteinDistance(const char* str1, const char* str2, bool isCaseSensitive = true);
    int DamerauLevenshtein(const char* str1, const char* str2, bool isCaseSensitive = true); // This is an alias for DamerauLevenshteinDistance
    int LevenshteinDistance(const char* str1, const char* str2, bool isCaseSensitive = true);
    int Levenshtein(const char* str1, const char* str2, bool isCaseSensitive = true);  // This is an alias for LevenshteinDistance
    double HammingDistance(const char* str1, const char* str2, bool isCaseSensitive = true);
    double Hamming(const char* str1, const char* str2, bool isCaseSensitive = true);  // This is an alias for HammingDistance
    double JaccardDistance(const char* str1, const char* str2, bool isCaseSensitive = true);
    double JaroDistance(const char* str1, const char* str2, bool isCaseSensitive = true);
    double JaroWinklerDistance(const char* str1, const char* str2, bool isCaseSensitive = true);
    double Levenshtein2Distance(const char* str1, const char* str2, bool isCaseSensitive = true);
    double LongestCommonSubsequenceDistance(const char* str1, const char* str2, bool isCaseSensitive = true);
    double LongestCommonSubstringDistance(const char* str1, const char* str2, bool isCaseSensitive = true);
    double NormalizedLevenshteinDistance(const char* str1, const char* str2, bool isCaseSensitive = true);
    double OverlapCoefficientDistance(const char* str1, const char* str2, bool isCaseSensitive = true);
    double RatcliffObershelpSimilarityDistance(const char* str1, const char* str2, bool isCaseSensitive = true);
    double SorensenDiceDistance(const char* str1, const char* str2, bool isCaseSensitive = true);
    double TanimotoCoefficientDistance(const char* str1, const char* str2, bool isCaseSensitive = true);
    double BlockDistance(const char* source1, const char* source2, bool isCaseSensitive = true);
    double NeedlemanWunsch(const char* source1, const char* source2, bool isCaseSensitive = true);
    double JaccardIndex(const char* source1, const char* source2, bool isCaseSensitive = true);
    double ChapmanLengthDeviation(const char* source1, const char* source2, bool isCaseSensitive = true);
    double ChapmanMeanLength(const char* source1, const char* source2, bool isCaseSensitive = true);
    double EuclideanDistance(const char* source1, const char* source2, bool isCaseSensitive = true);
    double MatchingCoefficient(const char* source1, const char* source2, bool isCaseSensitive = true);
    double MongeElkan(const char* source1, const char* source2, bool isCaseSensitive = true);
    double QGramsDistance(const char* source1, const char* source2, bool isCaseSensitive = true);
    double SmithWaterman(const char* source1, const char* source2, bool isCaseSensitive = true);
    double SmithWatermanGotoh(const char* source1, const char* source2, bool isCaseSensitive = true);
    double SmithWatermanGotohWindowedAffine(const char* source1, const char* source2, bool isCaseSensitive = true);
    double CosineSimilarity(const char* source1, const char* source2, bool isCaseSensitive = true);
    double JaccardSimilarity(const char* source1, const char* source2, bool isCaseSensitive = true);
    double LongestCommonSequence(const char* source1, const char* source2, bool isCaseSensitive = true);
    double DiceSimilarity(const char* source1, const char* source2, bool isCaseSensitive = true);
    double PhraseTokenize(const char* source1, const char* source2, bool isCaseSensitive = true);
    double SimplePhraseTokenize(const char* source1, const char* source2, bool isCaseSensitive = true);
#endif // !SQLITEFUZZYPLUSEXTENSION_COMPILE_TO_C_LANGUAGE__
    int PhraseSimplifiedDiff(const char* str1, const char* str2);
    // SQLean fuzzy Distance Functions
    unsigned fuzzy_damlev(const char* source1, const char* source2);
    int fuzzy_editdist(const char* source1, const char* source2);
    int fuzzy_hamming(const char* source1, const char* source2);
    double fuzzy_jarowin(const char* source1, const char* source2);
    unsigned fuzzy_leven(const char* source1, const char* source2);
    unsigned fuzzy_osadist(const char* source1, const char* source2);
    // Edlib fuzzy Distance Functions
    double iEdlibDistance(const char* source1, const char* source2);
    double EdlibDistance(const char* source1, const char* source2);
    bool SameName(const char* name1, const char* name2);
    // -------------------------------------------------------------------------------
    // -------------------------------------------------------------------------------
    // The following functions have NOT been implemented, and will always return false
    bool SameFirstLastName(const char* source1, const char* source2);
    bool SamePhone(const char* source1, const char* source2);
    bool SameSocial(const char* source1, const char* source2);
    bool SameZip(const char* source1, const char* source2);
    bool SameAddress(const char* source1, const char* source2);
    bool SameDate(const char* source1, const char* source2);
    bool SameFileName(const char* source1, const char* source2);
    bool SameNumber(const char* source1, const char* source2);
    // -------------------------------------------------------------------------------
    // -------------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////////
// Phonetic Functions
    bool EnPhoneticDistance(const char* str1, const char* str2);
    bool EnPhoneticDistance_IsSupported();
    bool Soundex2(const char* str1, const char* str2);
    bool Caverphone2(const char* str1, const char* str2);
    bool MatchRatingApproach(const char* str1, const char* str2);
    bool Metaphone(const char* str1, const char* str2);
    bool CaverPhonePhonix(const char* str1, const char* str2);
    bool DoubleMetaphone(const char* str1, const char* str2);
    bool ColognePhonetics(const char* str1, const char* str2);
    // SQLean Phonetic Distance Functions
    bool fuzzy_caver(const char* source1, const char* source2);
    bool fuzzy_phonetic(const char* source1, const char* source2);
    bool fuzzy_rsoundex(const char* source1, const char* source2);
    bool fuzzy_soundex(const char* source1, const char* source2);
    bool fuzzy_translit(const char* source1, const char* source2);
    // C version which returns 0 on success, and a positive number showing how big the buffer is needed on failure due to buffer size too small
    int get_fuzzy_caver(const char* source, char* distBuffer, int bufferSize);
    int get_fuzzy_phonetic(const char* source, char* distBuffer, int bufferSize);
    int get_fuzzy_rsoundex(const char* source, char* distBuffer, int bufferSize);
    int get_fuzzy_soundex(const char* source, char* distBuffer, int bufferSize);
    int get_fuzzy_translit(const char* source, char* distBuffer, int bufferSize);
    int get_fuzzy_script(const char* source);
    bool fuzzy_script(const char* source1, const char* source2);
    /////////////////////////////////////////////////////////////////////////////////
    // Regex Functions
    bool RegexMatch(const char* source, const char* pattern);
    char* RegexSearch(const char* source, const char* pattern, char* returnBuffer, int bufferSize); // If bufferSize is too small, a NULL value is returned.
    char* RegexReplace(const char* source, const char* pattern, const char* replacement, char* returnBuffer, int bufferSize); // If bufferSize is too small, a NULL value is returned.
    /////////////////////////////////////////////////////////////////////////////////
    // Miscellaneous Functions
    int MaxValue(int source1, int source2);
    int MinValue(int source1, int source2);
    int MaxLength(const char* str1, const char* str2);
    int MinLength(const char* str1, const char* str2);
    unsigned __int64 NormalizeNum(const char* source);
#ifndef SQLITEFUZZYPLUSEXTENSION_COMPILE_TO_C_LANGUAGE__
}
    double HowSimilar(const char* source1, const char* source2, const char* DistanceMethod_Name);
    double Distance(const char* source1, const char* source2, const char* DistanceMethod_Name);
    NAMESPACE_SQLITEFUZZYPLUSEXTENSION DistanceMethod_ID SetDefaultDistanceMethod(const char* DistanceMethod_Name);
    NAMESPACE_SQLITEFUZZYPLUSEXTENSION DistanceMethod_ID SetDefaultDistanceMethod(int DistanceMethod_Id);
    bool SameSound(const char* source1, const char* source2, const char* SameSoundMethod_Name = NULL, const char* DistanceMethod_Name = NULL, bool isVerySimilar = true);
    bool SameSound(const char* source1, const char* source2, int SameSoundMethod_Id, int DistanceMethod_Id);
    bool SameSound(const char* source1, const char* source2, const char* SameSoundMethod_Name, const char* DistanceMethod_Name);
    /////////////////////////////////////////////////////////////////////////////////
    // Phonetic Functions
    std::string fuzzy_caver(const char* source);
    std::string fuzzy_phonetic(const char* source);
    std::string fuzzy_rsoundex(const char* source);
    std::string fuzzy_soundex(const char* source);
    std::string fuzzy_translit(const char* source);
    /////////////////////////////////////////////////////////////////////////////////
    // Regex Functions
    std::string RegexSearch(const char* source, const char* pattern);
    std::string RegexReplace(const char* source, const char* pattern, const char* replacement);
    /////////////////////////////////////////////////////////////////////////////////
    // Miscellaneous Functions
    std::string HasCharInSameOrder(const char* str);
    std::string NormalizeFirstLastName(const char* name);
#else  // !SQLITEFUZZYPLUSEXTENSION_COMPILE_TO_C_LANGUAGE__
    /////////////////////////////////////////////////////////////////////////////////
    // Distance Functions
    int DamerauLevenshteinDistance(const char* str1, const char* str2, bool isCaseSensitive);
    int DamerauLevenshtein(const char* str1, const char* str2, bool isCaseSensitive); // This is an alias for DamerauLevenshteinDistance
    int LevenshteinDistance(const char* str1, const char* str2, bool isCaseSensitive);
    int Levenshtein(const char* str1, const char* str2, bool isCaseSensitive);  // This is an alias for LevenshteinDistance
    double HammingDistance(const char* str1, const char* str2, bool isCaseSensitive);
    double Hamming(const char* str1, const char* str2, bool isCaseSensitive);  // This is an alias for HammingDistance
    double JaccardDistance(const char* str1, const char* str2, bool isCaseSensitive);
    double JaroDistance(const char* str1, const char* str2, bool isCaseSensitive);
    double JaroWinklerDistance(const char* str1, const char* str2, bool isCaseSensitive);
    double Levenshtein2Distance(const char* str1, const char* str2, bool isCaseSensitive);
    double LongestCommonSubsequenceDistance(const char* str1, const char* str2, bool isCaseSensitive);
    double LongestCommonSubstringDistance(const char* str1, const char* str2, bool isCaseSensitive);
    double NormalizedLevenshteinDistance(const char* str1, const char* str2, bool isCaseSensitive);
    double OverlapCoefficientDistance(const char* str1, const char* str2, bool isCaseSensitive);
    double RatcliffObershelpSimilarityDistance(const char* str1, const char* str2, bool isCaseSensitive);
    double SorensenDiceDistance(const char* str1, const char* str2, bool isCaseSensitive);
    double TanimotoCoefficientDistance(const char* str1, const char* str2, bool isCaseSensitive);
    double BlockDistance(const char* source1, const char* source2, bool isCaseSensitive);
    double NeedlemanWunsch(const char* source1, const char* source2, bool isCaseSensitive);
    double JaccardIndex(const char* source1, const char* source2, bool isCaseSensitive);
    double ChapmanLengthDeviation(const char* source1, const char* source2, bool isCaseSensitive);
    double ChapmanMeanLength(const char* source1, const char* source2, bool isCaseSensitive);
    double EuclideanDistance(const char* source1, const char* source2, bool isCaseSensitive);
    double MatchingCoefficient(const char* source1, const char* source2, bool isCaseSensitive);
    double MongeElkan(const char* source1, const char* source2, bool isCaseSensitive);
    double QGramsDistance(const char* source1, const char* source2, bool isCaseSensitive);
    double SmithWaterman(const char* source1, const char* source2, bool isCaseSensitive);
    double SmithWatermanGotoh(const char* source1, const char* source2, bool isCaseSensitive);
    double SmithWatermanGotohWindowedAffine(const char* source1, const char* source2, bool isCaseSensitive);
    double CosineSimilarity(const char* source1, const char* source2, bool isCaseSensitive);
    double JaccardSimilarity(const char* source1, const char* source2, bool isCaseSensitive);
    double LongestCommonSequence(const char* source1, const char* source2, bool isCaseSensitive);
    double DiceSimilarity(const char* source1, const char* source2, bool isCaseSensitive);
    double PhraseTokenize(const char* source1, const char* source2, bool isCaseSensitive);
    double SimplePhraseTokenize(const char* source1, const char* source2, bool isCaseSensitive);
#endif // !SQLITEFUZZYPLUSEXTENSION_COMPILE_TO_C_LANGUAGE__

#endif //SQLITEFUZZYPLUSEXTENSION_EXCLUDE_FUNC
#endif //SQLITEFUZZYPLUSEXTENSION_H