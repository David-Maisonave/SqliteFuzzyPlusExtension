#ifndef SQLITEFUZZYPLUSEXTENSION_H
#define SQLITEFUZZYPLUSEXTENSION_H

#ifdef COMPILE_TO_C_LANGUAGE_SQLITEFUZZYPLUSEXTENSION__
#define EXCLUDE_NAMESPACE_SQLITEFUZZYPLUSEXTENSION
#include "stdbool.h"
#define C_ENUM_NAMING_CONVENTION__(name) enum_##name
#ifndef SQLITEFUZZYPLUSEXTENSION_EXCLUDE_FUNCTION_MACROS_FOR_C
#define SQLITEFUZZYPLUSEXTENSION_INCLUDE_FUNCTION_MACROS_FOR_C
#endif // !SQLITEFUZZYPLUSEXTENSION_EXCLUDE_FUNCTION_MACROS_FOR_C
#else
#include <string>
#define C_ENUM_NAMING_CONVENTION__(name) name
#define NAMESPACE_SQLITEFUZZYPLUSEXTENSION  SqliteFuzzyPlusExtension::
#endif // COMPILE_TO_C_LANGUAGE_SQLITEFUZZYPLUSEXTENSION__

#ifdef SQLITEFUZZYPLUSEXTENSION_INCLUDE_FUNCTION_MACROS_FOR_C
#define SAMESOUND(word1, word2) SameSound(word1, word2, 0, 0, 1)
#define SAMESOUND_NM(word1, word2, methodName) SameSound(word1, word2, GetSameSoundMethodID(methodName), GetStringMatchingAlgorithmID("ExactMatch"), 1)
#define SAMESOUND_ID(word1, word2, methodID) SameSound(word1, word2, methodID, GetStringMatchingAlgorithmID("ExactMatch"), 1)
#endif // SQLITEFUZZYPLUSEXTENSION_INCLUDE_FUNCTION_MACROS_FOR_C


#ifdef EXCLUDE_NAMESPACE_SQLITEFUZZYPLUSEXTENSION
#define NAMESPACE_SQLITEFUZZYPLUSEXTENSION
#endif // EXCLUDE_NAMESPACE_SQLITEFUZZYPLUSEXTENSION


// If building in C language, define EXCLUDE_NAMESPACE_SQLITEFUZZYPLUSEXTENSION to exclude the namespace
#ifndef EXCLUDE_NAMESPACE_SQLITEFUZZYPLUSEXTENSION
namespace SqliteFuzzyPlusExtension {
#endif //!EXCLUDE_NAMESPACE_SQLITEFUZZYPLUSEXTENSION
#ifdef COMPILE_TO_C_LANGUAGE_SQLITEFUZZYPLUSEXTENSION__
#define SEQUENCE_ALIGNMENT_METHODS 32
#define TOKEN_METHODS 64
#define PHRASE_METHODS TOKEN_METHODS + 32
#define CPP_ONLY_FUZZY 128
#define CASE_INSENSITIVE 256
#define BAD_METHODS CPP_ONLY_FUZZY + 96
#define METHODS_UP_FOR_DELETION BAD_METHODS + 10
#define PHONETIC_ALGORITHMS 16384
#define MICROSOFT_PHONETIC_METHODS PHONETIC_ALGORITHMS + 64
#define CPP_ONLY_PHONETIC_ALGORITHMS PHONETIC_ALGORITHMS + CPP_ONLY_FUZZY
#else // COMPILE_TO_C_LANGUAGE_SQLITEFUZZYPLUSEXTENSION__
    const int SEQUENCE_ALIGNMENT_METHODS = 32;
    const int TOKEN_METHODS = 64;
    const int PHRASE_METHODS = TOKEN_METHODS + 32;
    const int CPP_ONLY_FUZZY = 128;
    const int CASE_INSENSITIVE = 256;
    const int BAD_METHODS = CPP_ONLY_FUZZY + 96;
    const int METHODS_UP_FOR_DELETION = BAD_METHODS + 10;
    const int PHONETIC_ALGORITHMS = 16384;
    const int MICROSOFT_PHONETIC_METHODS = PHONETIC_ALGORITHMS + 64;
    const int CPP_ONLY_PHONETIC_ALGORITHMS = PHONETIC_ALGORITHMS + CPP_ONLY_FUZZY;
#endif // COMPILE_TO_C_LANGUAGE_SQLITEFUZZYPLUSEXTENSION__
    // Note: In C language, the enums can not use the same name as a function, so macro C_ENUM_NAMING_CONVENTION__ has been added for C-Only code where all the enums with this macro have an "enum_" prefixed to the name.
    //       The C++ code will still reference all the enums by the original name.
    enum StringMatchingAlgorithm_ID
    {
        UseDefaultStringMatchingAlgorithm = 0,
        // Edit Distance Based Methods
        C_ENUM_NAMING_CONVENTION__(Levenshtein),
        C_ENUM_NAMING_CONVENTION__(DamerauLevenshtein),
        C_ENUM_NAMING_CONVENTION__(JaroWinkler),
        C_ENUM_NAMING_CONVENTION__(HammingDistance),
        C_ENUM_NAMING_CONVENTION__(JaroDistance),
        C_ENUM_NAMING_CONVENTION__(NormalizedLevenshteinDistance),
        C_ENUM_NAMING_CONVENTION__(Levenshtein2Distance),
        C_ENUM_NAMING_CONVENTION__(ChapmanLengthDeviation),
        C_ENUM_NAMING_CONVENTION__(EuclideanDistance),

        // Sequence Alignment Based Methods
        C_ENUM_NAMING_CONVENTION__(LongestCommonSequence) = SEQUENCE_ALIGNMENT_METHODS,
        C_ENUM_NAMING_CONVENTION__(NeedlemanWunsch),
        C_ENUM_NAMING_CONVENTION__(RatcliffObershelpSimilarityDistance),
        C_ENUM_NAMING_CONVENTION__(LongestCommonSubstringDistance),
        C_ENUM_NAMING_CONVENTION__(LongestCommonSubsequenceDistance),
        C_ENUM_NAMING_CONVENTION__(SmithWaterman),
        C_ENUM_NAMING_CONVENTION__(SmithWatermanGotoh),
        C_ENUM_NAMING_CONVENTION__(SmithWatermanGotohWindowedAffine),

        // Token Based Methods
        C_ENUM_NAMING_CONVENTION__(CosineSimilarity) = TOKEN_METHODS,
        C_ENUM_NAMING_CONVENTION__(JaccardSimilarity), // ToDo: JaccardSimilarity, JaccardIndex, and TanimotoCoefficientDistance are most likely the same logic.  Remove the duplicates
        C_ENUM_NAMING_CONVENTION__(JaccardIndex),
        C_ENUM_NAMING_CONVENTION__(TanimotoCoefficientDistance),
        C_ENUM_NAMING_CONVENTION__(OverlapCoefficient),
        C_ENUM_NAMING_CONVENTION__(SorensenDiceDistance),
        C_ENUM_NAMING_CONVENTION__(DiceSimilarity),       
        C_ENUM_NAMING_CONVENTION__(BlockDistance),
        C_ENUM_NAMING_CONVENTION__(MatchingCoefficient),
        C_ENUM_NAMING_CONVENTION__(QGramsDistance),
        C_ENUM_NAMING_CONVENTION__(NGramsDistance),
        C_ENUM_NAMING_CONVENTION__(TverskyIndex_DO_NOT_USE), //Warning: There is NO implementation for this algorithm.  This is just a placeholder

        // Hybrid Algorithms
        C_ENUM_NAMING_CONVENTION__(MongeElkan),
        C_ENUM_NAMING_CONVENTION__(Sift4),
        C_ENUM_NAMING_CONVENTION__(GeneralizedCompressionDistance_DO_NOT_USE), //Warning: There is NO implementation for this algorithm.  This is just a placeholder

        // String Hash Based
        C_ENUM_NAMING_CONVENTION__(SimHash_DO_NOT_USE), // This algorithm is still in development phase.
        C_ENUM_NAMING_CONVENTION__(MinHash_DO_NOT_USE), //Warning: There is NO implementation for this algorithm.  This is just a placeholder

        // Phrase token methods which are all case insensitive only
        C_ENUM_NAMING_CONVENTION__(PhraseTokenize) = PHRASE_METHODS,
        C_ENUM_NAMING_CONVENTION__(SimplePhraseTokenize),

        // ------------------------------------------------------------
        // These functions are NOT supported by CSharp Fuzzy class code, and are only here for C++ SqliteFuzzyPlusExtension usage.
        // Sqlean Fuzzy external functions. 
        Fuzzy_Damlev = CPP_ONLY_FUZZY, // Edit Distance Based
        Fuzzy_Hamming, // Edit Distance Based
        Fuzzy_Jarowin, // Edit Distance Based
        Fuzzy_Leven, // Edit Distance Based
        Fuzzy_Osadist,
        Fuzzy_Editdist, // Edit Distance Based
        Fuzzy_Jaro, // Edit Distance Based
        // Other C++ (external) only functions. (NOT part of Sqlean)
        C_ENUM_NAMING_CONVENTION__(EdlibDistance),
        // ------------------------------------------------------------

        // Bad distance methods (C# and C++)
        // These method(s) are only here for comparisons and testing purposes
        C_ENUM_NAMING_CONVENTION__(ChapmanMeanLength) = BAD_METHODS, // Distance method from SimMetricsCore

        // EditDistance may get removed, replaced, or logic change 
        C_ENUM_NAMING_CONVENTION__(EditDistance) = METHODS_UP_FOR_DELETION,

        //This is NOT a fuzzy method. It's for functions that accepts a comparison argument.
        ExactMatch = CASE_INSENSITIVE - 1,

        ////////////////////////////////////////////////////////////////////////////
        // ToDo: Sort below case insensitive enums in the same order as above
        // Case INSENSITIVE versions
        iLevenshtein = CASE_INSENSITIVE + C_ENUM_NAMING_CONVENTION__(Levenshtein),
        iDamerauLevenshtein,
        iJaroWinkler,
        iHammingDistance,
        iJaroDistance,
        iNormalizedLevenshteinDistance,
        iLevenshtein2Distance,
        iChapmanLengthDeviation,
        iEuclideanDistance,

        // Sequence Alignment Based Methods
        iLongestCommonSequence = CASE_INSENSITIVE + C_ENUM_NAMING_CONVENTION__(LongestCommonSequence),
        iNeedlemanWunsch,
        iRatcliffObershelpSimilarityDistance,
        iLongestCommonSubstringDistance,
        iLongestCommonSubsequenceDistance,
        iSmithWaterman,
        iSmithWatermanGotoh,
        iSmithWatermanGotohWindowedAffine,

        // Token Based Methods
        iCosineSimilarity = CASE_INSENSITIVE + C_ENUM_NAMING_CONVENTION__(CosineSimilarity),
        iJaccardSimilarity, // ToDo: JaccardSimilarity, JaccardIndex, and TanimotoCoefficientDistance are most likely the same logic.  Remove the duplicates
        iJaccardIndex,
        iTanimotoCoefficientDistance,
        iOverlapCoefficient,
        iSorensenDiceDistance,
        iDiceSimilarity,
        iBlockDistance,
        iMatchingCoefficient,
        iQGramsDistance,
        iNGramsDistance,
        iTverskyIndex_DO_NOT_USE, //Warning: There is NO implementation for this algorithm.  This is just a placeholder

        // Hybrid Algorithms
        iMongeElkan = CASE_INSENSITIVE + C_ENUM_NAMING_CONVENTION__(MongeElkan),
        iSift4,
        iGeneralizedCompressionDistance_DO_NOT_USE, //Warning: There is NO implementation for this algorithm.  This is just a placeholder

        // String Hash Based
        iSimHash_DO_NOT_USE = CASE_INSENSITIVE + C_ENUM_NAMING_CONVENTION__(SimHash_DO_NOT_USE), // This algorithm is still in development phase.
        iMinHash_DO_NOT_USE, //Warning: There is NO implementation for this algorithm.  This is just a placeholder

        // Bad distance methods (C# and C++)
        // These method(s) are only here for comparisons and testing purposes
        iChapmanMeanLength = CASE_INSENSITIVE + C_ENUM_NAMING_CONVENTION__(ChapmanMeanLength),

        // METHODS UP FOR DELETION
        iEditDistance = CASE_INSENSITIVE + C_ENUM_NAMING_CONVENTION__(EditDistance)
    };
    enum SameSoundMethod
    {
        UseDefaultSameSoundMethod = PHONETIC_ALGORITHMS,
        C_ENUM_NAMING_CONVENTION__(SoundexPhonix),    // Default SameSound method
        C_ENUM_NAMING_CONVENTION__(CaverPhonePhonix),
        C_ENUM_NAMING_CONVENTION__(MatchRatingApproach),
        C_ENUM_NAMING_CONVENTION__(Metaphone),
        C_ENUM_NAMING_CONVENTION__(DoubleMetaphone),
        C_ENUM_NAMING_CONVENTION__(ColognePhonetics),
        C_ENUM_NAMING_CONVENTION__(SoundexVer2),
        C_ENUM_NAMING_CONVENTION__(EnPhoneticDistance) = MICROSOFT_PHONETIC_METHODS,
        // ------------------------------------------------------------
        // These functions are NOT supported by CSharp Fuzzy class code, and are only here for C++ SqliteFuzzyPlusExtension usage.
        // SQLean phonetic external functions. 
        Fuzzy_Soundex = CPP_ONLY_PHONETIC_ALGORITHMS,
        Fuzzy_Caver,
        Fuzzy_Rsoundex,  //Refined Soundex
        Fuzzy_Phonetic,
        Fuzzy_Translit //Transliteration
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
#ifndef COMPILE_TO_C_LANGUAGE_SQLITEFUZZYPLUSEXTENSION__
extern "C" {
#endif // !COMPILE_TO_C_LANGUAGE_SQLITEFUZZYPLUSEXTENSION__
    double HowSimilar(const char* source1, const char* source2, int StringMatchingAlgorithm_Id);
    double HowSimilarById(const char* source1, const char* source2, int StringMatchingAlgorithm_Id);
    double HowSimilarByName(const char* source1, const char* source2, const char* StringMatchingAlgorithm_Name);
    double Distance(const char* source1, const char* source2, int StringMatchingAlgorithm_Id);
    double DistanceByName(const char* source1, const char* source2, const char* StringMatchingAlgorithm_Name);
    bool IsSimilar(const char* str1, const char* str2, int StringMatchingAlgorithmID_Or_SameSoundMethod_ID);
    bool IsVerySimilar(const char* str1, const char* str2, int StringMatchingAlgorithmID_Or_SameSoundMethod_ID);
    int GetStringMatchingAlgorithmID(const char* StringMatchingAlgorithm_Name);
    int GetSameSoundMethodID(const char* SameSoundMethod_Name);
    int SetDefaultStringMatchingAlgorithmByName(const char* StringMatchingAlgorithm_Name);
    int SetDefaultStringMatchingAlgorithmByID(int StringMatchingAlgorithm_Id);
    int GetDefaultStringMatchingAlgorithm();
    int SetDefaultSameSoundMethod(int sameSoundMethod_ID);
    int SetDefaultSameSoundMethodByName(const char* sameSoundMethod_Name);
    int GetDefaultSoundMethod();
    int SetPercentDecimalDigits(int precision);
    // C language code can simulate overloaded SameSound functions by using GetSameSoundMethodID and GetStringMatchingAlgorithmID
    // Example: SameSound("been", "being", GetSameSoundMethodID("SoundexPhonix"), GetStringMatchingAlgorithmID("Levenshtein"), 1);
    bool SameSound(const char* source1, const char* source2, int SameSoundMethod_Id, int StringMatchingAlgorithm_Id, bool isVerySimilar);
    /////////////////////////////////////////////////////////////////////////////////
    // Distance Functions
#ifndef COMPILE_TO_C_LANGUAGE_SQLITEFUZZYPLUSEXTENSION__
    double DamerauLevenshteinDistance(const char* str1, const char* str2, bool isCaseSensitive = true);
    double DamerauLevenshtein(const char* str1, const char* str2, bool isCaseSensitive = true); // This is an alias for DamerauLevenshteinDistance
    double LevenshteinDistance(const char* str1, const char* str2, bool isCaseSensitive = true);
    double Levenshtein(const char* str1, const char* str2, bool isCaseSensitive = true);  // This is an alias for LevenshteinDistance
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
    double Sift4(const char* source1, const char* source2, bool isCaseSensitive = true);
    double SimHash(const char* source1, const char* source2, bool isCaseSensitive = true);
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
#endif // !COMPILE_TO_C_LANGUAGE_SQLITEFUZZYPLUSEXTENSION__
    double PhraseSimplifiedDiff(const char* str1, const char* str2);
    // SQLean fuzzy Distance Functions
    unsigned fuzzy_damlev(const char* source1, const char* source2);
    int fuzzy_editdist(const char* source1, const char* source2);
    int fuzzy_hamming(const char* source1, const char* source2);
    double fuzzy_jarowin(const char* source1, const char* source2);
    unsigned fuzzy_leven(const char* source1, const char* source2);
    unsigned fuzzy_osadist(const char* source1, const char* source2);
    // Edlib fuzzy Distance Functions
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
    bool SoundexPhonix(const char* str1, const char* str2);
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
#ifndef COMPILE_TO_C_LANGUAGE_SQLITEFUZZYPLUSEXTENSION__
}
    double HowSimilar(const char* source1, const char* source2, const char* StringMatchingAlgorithm_Name);
    double Distance(const char* source1, const char* source2, const char* StringMatchingAlgorithm_Name);
    NAMESPACE_SQLITEFUZZYPLUSEXTENSION StringMatchingAlgorithm_ID SetDefaultStringMatchingAlgorithm(const char* StringMatchingAlgorithm_Name);
    NAMESPACE_SQLITEFUZZYPLUSEXTENSION StringMatchingAlgorithm_ID SetDefaultStringMatchingAlgorithm(int StringMatchingAlgorithm_Id);
    bool SameSound(const char* source1, const char* source2, const char* SameSoundMethod_Name = NULL, const char* StringMatchingAlgorithm_Name = NULL, bool isVerySimilar = true);
    bool SameSound(const char* source1, const char* source2, int SameSoundMethod_Id, int StringMatchingAlgorithm_Id);
    bool SameSound(const char* source1, const char* source2, const char* SameSoundMethod_Name, const char* StringMatchingAlgorithm_Name);
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
#else  // !COMPILE_TO_C_LANGUAGE_SQLITEFUZZYPLUSEXTENSION__
    /////////////////////////////////////////////////////////////////////////////////
    // Distance Functions
    double DamerauLevenshteinDistance(const char* str1, const char* str2, bool isCaseSensitive);
    double DamerauLevenshtein(const char* str1, const char* str2, bool isCaseSensitive); // This is an alias for DamerauLevenshteinDistance
    double LevenshteinDistance(const char* str1, const char* str2, bool isCaseSensitive);
    double Levenshtein(const char* str1, const char* str2, bool isCaseSensitive);  // This is an alias for LevenshteinDistance
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
    double Sift4(const char* source1, const char* source2, bool isCaseSensitive);
    double SimHash(const char* source1, const char* source2, bool isCaseSensitive);
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
#endif // !COMPILE_TO_C_LANGUAGE_SQLITEFUZZYPLUSEXTENSION__

#endif //SQLITEFUZZYPLUSEXTENSION_EXCLUDE_FUNC
#endif //SQLITEFUZZYPLUSEXTENSION_H