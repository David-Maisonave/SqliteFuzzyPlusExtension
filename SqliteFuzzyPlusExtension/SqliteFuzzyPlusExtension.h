#ifndef SQLITEFUZZYPLUSEXTENSION_H
#define SQLITEFUZZYPLUSEXTENSION_H

#ifndef SQLITEFUZZYPLUSEXTENSION_EXCLUDE_FUNC
#ifndef SQLITEFUZZYPLUSEXTENSION_LIB
#define SQLITEFUZZYPLUSEXTENSION_LIB "SqliteFuzzyPlusExtension.lib"
#endif //!SQLITEFUZZYPLUSEXTENSION_LIB
#endif //!SQLITEFUZZYPLUSEXTENSION_EXCLUDE_FUNC

#ifdef __cplusplus
#include <string>
#else
#define EXCLUDE_NAMESPACE_SQLITEFUZZYPLUSEXTENSION
#endif //__cplusplus

// If building in C language, define EXCLUDE_NAMESPACE_SQLITEFUZZYPLUSEXTENSION to exclude the namespace
#ifndef EXCLUDE_NAMESPACE_SQLITEFUZZYPLUSEXTENSION
namespace SqliteFuzzyPlusExtension {
#endif //!EXCLUDE_NAMESPACE_SQLITEFUZZYPLUSEXTENSION

    const int CASE_INSENSITIVE = 128;
    const int CPP_ONLY_FUZZY = 64;
    enum DistanceMethod_ID
    {
        UseDefaultDistanceMethod = 0,
        Levenshtein,
        DamerauLevenshtein,
        JaroWinkler,
        LongestCommonSequence,
        JaccardIndex,
        OverlapCoefficient,
        NeedlemanWunsch,
        SorensenDiceDistance,
        RatcliffObershelpSimilarityDistance,
        HammingDistance,
        LongestCommonSubstringDistance,
        LongestCommonSubsequenceDistance,
        JaroDistance,
        NormalizedLevenshteinDistance,
        Levenshtein2Distance,
        TanimotoCoefficientDistance,
        EditDistance,

        //Token methods
        CosineSimilarity,
        JaccardSimilarity,
        // Phrase token methods which are all case insensitive only
        PhraseTokenize,
        SimplePhraseTokenize,

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
        // Other C++ (external) only functions. (NOT part of Sqlean)
        EdlibDistance,
        // ------------------------------------------------------------

        // Case INSENSITIVE versions
        iLevenshtein = CASE_INSENSITIVE + Levenshtein,
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

        // ------------------------------------------------------------
        // These functions are NOT supported by CSharp Fuzzy class code, and are only here for C++ SqliteFuzzyPlusExtension usage.
        iEdlibDistance = CASE_INSENSITIVE + EdlibDistance,
        // ------------------------------------------------------------
    };
#ifndef EXCLUDE_NAMESPACE_SQLITEFUZZYPLUSEXTENSION
}
#endif //EXCLUDE_NAMESPACE_SQLITEFUZZYPLUSEXTENSION

#ifndef SQLITEFUZZYPLUSEXTENSION_EXCLUDE_FUNC
#pragma comment(lib, SQLITEFUZZYPLUSEXTENSION_LIB)
/////////////////////////////////////////////////////////////////////////////////
// Wrapper Distance Functions
double HowSimilar(const char* source1, const char* source2, int DistanceMethod_Id);
double HowSimilar(const char* source1, const char* source2, const char* DistanceMethod_Name);
double Distance(const char* source1, const char* source2, int DistanceMethod_Id);
double Distance(const char* source1, const char* source2, const char* DistanceMethod_Name);
#ifndef EXCLUDE_NAMESPACE_SQLITEFUZZYPLUSEXTENSION
SqliteFuzzyPlusExtension::
#endif //EXCLUDE_NAMESPACE_SQLITEFUZZYPLUSEXTENSION
DistanceMethod_ID SetDefaultDistanceMethod(const char* DistanceMethod_Name);
#ifndef EXCLUDE_NAMESPACE_SQLITEFUZZYPLUSEXTENSION
SqliteFuzzyPlusExtension::
#endif //EXCLUDE_NAMESPACE_SQLITEFUZZYPLUSEXTENSION
DistanceMethod_ID SetDefaultDistanceMethod(int DistanceMethod_Id);
bool SameSound(const char* source1, const char* source2, int SameSoundMethod_Id, int DistanceMethod_Id, bool isVerySimilar);
bool SameSound(const char* source1, const char* source2, const char* SameSoundMethod_Name, const char* DistanceMethod_Name, bool isVerySimilar);
bool SameSound(const char* source1, const char* source2, int SameSoundMethod_Id, int DistanceMethod_Id);
bool SameSound(const char* source1, const char* source2, const char* SameSoundMethod_Name, const char* DistanceMethod_Name);

/////////////////////////////////////////////////////////////////////////////////
// Distance Functions
int DamerauLevenshteinDistance(const char* str1, const char* str2);
int LevenshteinDistance(const char* str1, const char* str2);
int LevenshteinDistance(const char* str1, const char* str2);
double HammingDistance(const char* str1, const char* str2);
double JaccardDistance(const char* str1, const char* str2);
double JaroDistance(const char* str1, const char* str2);
double JaroWinklerDistance(const char* str1, const char* str2);
double Levenshtein2Distance(const char* str1, const char* str2);
double LongestCommonSubsequenceDistance(const char* str1, const char* str2);
double LongestCommonSubstringDistance(const char* str1, const char* str2);
double NormalizedLevenshteinDistance(const char* str1, const char* str2);
double OverlapCoefficientDistance(const char* str1, const char* str2);
int PhraseSimplifiedDiff(const char* str1, const char* str2);
double RatcliffObershelpSimilarityDistance(const char* str1, const char* str2);
double SorensenDiceDistance(const char* str1, const char* str2);
double TanimotoCoefficientDistance(const char* str1, const char* str2);
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

/////////////////////////////////////////////////////////////////////////////////
// Phonetic Functions
bool EnPhoneticDistance(const char* str1, const char* str2);
bool Soundex2(const char* str1, const char* str2);
bool Caverphone2(const char* str1, const char* str2);
// SQLean Phonetic Distance Functions
bool fuzzy_caver(const char* source1, const char* source2);
bool fuzzy_phonetic(const char* source1, const char* source2);
bool fuzzy_rsoundex(const char* source1, const char* source2);
bool fuzzy_soundex(const char* source1, const char* source2);
bool fuzzy_translit(const char* source1, const char* source2);
#ifdef __cplusplus
std::string fuzzy_caver(const char* source);
std::string fuzzy_phonetic(const char* source);
std::string fuzzy_rsoundex(const char* source);
std::string fuzzy_soundex(const char* source);
std::string fuzzy_translit(const char* source);
#endif //__cplusplus
// C version which returns 0 on success, and a positive number showing how big the buffer is needed on failure due to buffer size too small
int fuzzy_caver(const char* source, char* distBuffer, int bufferSize);
int fuzzy_phonetic(const char* source, char* distBuffer, int bufferSize);
int fuzzy_rsoundex(const char* source, char* distBuffer, int bufferSize);
int fuzzy_soundex(const char* source, char* distBuffer, int bufferSize);
int fuzzy_translit(const char* source, char* distBuffer, int bufferSize);


/////////////////////////////////////////////////////////////////////////////////
// Regex Functions
bool RegexMatch(const char* source, const char* pattern);
#ifdef __cplusplus
std::string RegexSearch(const char* source, const char* pattern);
std::string RegexReplace(const char* source, const char* pattern, const char* replacement);
#endif //__cplusplus
char* RegexSearch(const char* source, const char* pattern, char* returnBuffer, int bufferSize); // If bufferSize is too small, a NULL value is returned.
char* RegexReplace(const char* source, const char* pattern, const char* replacement, char* returnBuffer, int bufferSize); // If bufferSize is too small, a NULL value is returned.

/////////////////////////////////////////////////////////////////////////////////
// Miscellaneous Functions
int MaxValue(int source1, int source2);
int MinValue(int source1, int source2);
int MaxLength(const char* str1, const char* str2);
int MinLength(const char* str1, const char* str2);
unsigned __int64 NormalizeNum(const char* source);

#endif //SQLITEFUZZYPLUSEXTENSION_EXCLUDE_FUNC

#endif //SQLITEFUZZYPLUSEXTENSION_H