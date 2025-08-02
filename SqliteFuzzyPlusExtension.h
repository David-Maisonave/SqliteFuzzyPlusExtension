#ifndef SQLITEFUZZYPLUSEXTENSION_H
#define SQLITEFUZZYPLUSEXTENSION_H

// If building in C language, define EXCLUDE_NAMESPACE_SQLITEFUZZYPLUSEXTENSION to exclude the namespace
#ifndef EXCLUDE_NAMESPACE_SQLITEFUZZYPLUSEXTENSION
namespace SqliteFuzzyPlusExtension {
#endif //EXCLUDE_NAMESPACE_SQLITEFUZZYPLUSEXTENSION

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
unsigned __int64 NormalizeNum(const char* source);
int MaxValue(int source1, int source2);

int DamLev_Exp2(const char* str1, const char* str2);// Test function
#endif //SQLITEFUZZYPLUSEXTENSION_EXCLUDE_FUNC

#endif //SQLITEFUZZYPLUSEXTENSION_H