#include <windows.h>
#include <cassert>
#include <string>
#include <map>
#include <deque>
#include <algorithm>
#include <functional>
#include <ctype.h>
#include <atlstr.h>
#include "SqliteFuzzyPlusExtension_Internal.h"
#define SQLITEFUZZYPLUSEXTENSION_EXCLUDE_FUNC
#include "SqliteFuzzyPlusExtension.h"
#include "edlib\include\edlib.h"
using namespace System;
// ToDo: Add the following functions:
//      SameFileName -> Will use * and ? as wildcard characters which will get converted to SQL wildcard characters (% and _)
//      Add fuzzy logic to compare blobs that have image or video files.
//      Add fuzzy logic to compare files via file names listed in DB.
//      Add sqlean Define function (E:\_\sqlite-extension\sqlean\src\define)
const sqlite3_api_routines* sqlite3_api = NULL;
static int cacheSize = 32;
static const char* defaultStr = "";
const char* GetSqliteValueStr(sqlite3_value** argv, int pos = 0)
{
    const char* str = (const char*)sqlite3_value_text(argv[pos]);
    return (str == NULL || str[0] == 0) ? defaultStr : str;
}

const unsigned char* GetSqliteValueUnsignedStr(sqlite3_value** argv, int pos = 0)
{
    const unsigned char* str = sqlite3_value_text(argv[pos]);
    return (str == NULL) ? (const unsigned char*)defaultStr : str;
}

static double Edlib_Distance(std::string source1, std::string source2, bool isCaseSensitive = true)
{
    if (isCaseSensitive == false)
    {
        std::transform(source1.begin(), source1.end(), source1.begin(), [](unsigned char c) { return std::tolower(c); });
        std::transform(source2.begin(), source2.end(), source2.begin(), [](unsigned char c) { return std::tolower(c); });
    }
    EdlibAlignResult result = edlibAlign(source1.c_str(), (int)source1.length(), source2.c_str(), (int)source2.length(), edlibDefaultAlignConfig());
    return FuzzyPlusCSharp::Fuzzy::GetPercentWithFixedDecimalDigits(result.editDistance);
}

static void EdlibDistance(sqlite3_context* context, int argc, sqlite3_value** argv)
{
    assert(argc == 2);
    const char* source1 = GetSqliteValueStr(argv);
    const char* source2 = GetSqliteValueStr(argv, 1);
    double distance = Edlib_Distance(source1, source2, true);
    distance = FuzzyPlusCSharp::Fuzzy::GetPercentWithFixedDecimalDigits(distance);
    sqlite3_result_double(context, distance);
}

template<typename T1, typename T2, typename T3, typename T4>
void AddToCache(T1& cacheSizeControl, T2& cache, const T3& key, const T4& result)
{
    if (cacheSize > 0)
    {
        cache[key] = result;
        cacheSizeControl.push_back(key);
        if (cacheSizeControl.size() > cacheSize)
        {
            cache.erase(cacheSizeControl.front());
            cacheSizeControl.pop_front();
        }
    }
}

static void HasCharInSameOrder(sqlite3_context* context, int argc, sqlite3_value** argv) {
    assert(argc == 1 || argc == 2);
    static std::map<std::string, CString > cache;
    static std::deque<std::string> cacheSizeControl;
    bool rapWithQuotes = false;
    char rapChar = '\'';
    const char* str = GetSqliteValueStr(argv);
    CString result = (cacheSize > 0) ? cache[str] : "";
    if (result.IsEmpty())
    {
        String^ source = gcnew String(str);
        result = FuzzyPlusCSharp::Fuzzy::HasCharInSameOrder(source);
        AddToCache(cacheSizeControl, cache, str, result);
    }
    if (argc == 2) 
    {
        int arg2 = sqlite3_value_int(argv[1]);
        if (arg2 == 1)
            rapChar = '\'';
        else if (arg2 == 2)
            rapChar = '"';
        rapWithQuotes = arg2 != 0;
    }
    if (rapWithQuotes)
        result = rapChar + result + rapChar;
    sqlite3_result_text16(context, result, -1, NULL);
}

static void HasWordFrom(sqlite3_context* context, int argc, sqlite3_value** argv) {
    assert(argc == 2 || argc == 3);
    static std::map<std::pair<std::string, std::string>, CString > cache;
    static std::deque<std::pair<std::string, std::string> > cacheSizeControl;
    const char* str1 = GetSqliteValueStr(argv);
    const char* str2 = GetSqliteValueStr(argv, 1);
    CString result = (cacheSize > 0 && argc != 3 && cache.find(std::make_pair(str1, str2)) != cache.end()) ? cache[std::make_pair(str1, str2)] : "";
    if (result.IsEmpty() || argc == 3) // Only supporting 2 argument call for cache for now. 
    {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        int minimumWordLenForWordInWordMatch = 3;
        if (argc == 3)
            minimumWordLenForWordInWordMatch = sqlite3_value_int(argv[2]);
        result = FuzzyPlusCSharp::Fuzzy::HasWordFrom(source1, source2, minimumWordLenForWordInWordMatch);
        AddToCache(cacheSizeControl, cache, std::make_pair(str1, str2), result);
    }
    sqlite3_result_text16(context, result, -1, NULL);
}

static void ValuesList(sqlite3_context* context, int argc, sqlite3_value** argv) {
    assert(argc == 1 || argc == 2);
    static std::map<std::pair<std::string, int>, CString > cache;
    static std::deque<std::pair<std::string, int> > cacheSizeControl;
    const char* str = GetSqliteValueStr(argv);
    int minimumWordLenForWordInWordMatch = 3;
    if (argc == 2)
        minimumWordLenForWordInWordMatch = sqlite3_value_int(argv[1]);
    CString result = (cacheSize > 0 && argc != 3 && cache.find(std::make_pair(str, minimumWordLenForWordInWordMatch)) != cache.end()) ? cache[std::make_pair(str, minimumWordLenForWordInWordMatch)] : "";
    if (result.IsEmpty()) 
    {
        String^ source1 = gcnew String(str);
        result = FuzzyPlusCSharp::Fuzzy::ValuesList(source1, minimumWordLenForWordInWordMatch);
        AddToCache(cacheSizeControl, cache, std::make_pair(str, minimumWordLenForWordInWordMatch), result);
    }
    sqlite3_result_text16(context, result, -1, NULL);
}

static void ToHash(sqlite3_context* context, int argc, sqlite3_value** argv) {
    assert(argc == 1 || argc == 2);
    const char* str = GetSqliteValueStr(argv);
    int hashType = 0;
    if (argc == 2)
    {
        const unsigned char* ustr2 = GetSqliteValueUnsignedStr(argv,1);
        if (isascii(ustr2[0]))
        {
            const char* str2 = GetSqliteValueStr(argv, 1);
            String^ source2 = gcnew String(str2);
            hashType = (int)FuzzyPlusCSharp::Fuzzy::GetHashType(source2);
        }
        else
            hashType = sqlite3_value_int(argv[1]);
    }
    static std::map<std::pair<std::string, int>, CString > cache;
    static std::deque<std::pair<std::string, int> > cacheSizeControl;
    CString result = (cacheSize > 0) ? cache[std::make_pair(str, hashType)] : "";
    if (result.IsEmpty())
    {
        String^ source = gcnew String(str);
        result = FuzzyPlusCSharp::Fuzzy::ToHash(source, (FuzzyPlusCSharp::Fuzzy::HashType)hashType);
        AddToCache(cacheSizeControl, cache, std::make_pair(str, hashType), result);
    }
    sqlite3_result_text16(context, result, -1, NULL);
}

static void FastHash(sqlite3_context* context, int argc, sqlite3_value** argv) {
    assert(argc == 1);
    static std::map<std::string, CString > cache;
    static std::deque<std::string> cacheSizeControl;
    const char* str = GetSqliteValueStr(argv);
    CString result;
    if (cacheSize == 0 || cache.find(str) == cache.end())
    {
        String^ source = gcnew String(GetSqliteValueStr(argv));
        unsigned long long ull_result =FuzzyPlusCSharp::Fuzzy::FastHash(source);
        result.Format(_T("%llu"), ull_result);
        AddToCache(cacheSizeControl, cache, str, result);
    }
    else
        result = cache[str];
    sqlite3_result_text16(context, result, -1, NULL); // Have to return as a string because SQLite does not support returning UNSIGNED BigInt. It only does BigInt return.
    //sqlite3_result_int64(context, result);
}

static void TestFoo(sqlite3_context* context, int argc, sqlite3_value** argv) {
    assert(argc == 1);
    const char* str = GetSqliteValueStr(argv);
    std::string result;
    for(int i = 0; i < 20; ++i)
        result += std::string(str) + "_data_record\n";
    sqlite3_result_text(context, result.c_str(), -1, NULL);
    //sqlite3_result_value(context, (sqlite3_value*)result.c_str());
}

static void SetDefaultStringMatchingAlgorithmByName(sqlite3_context* context, int argc, sqlite3_value** argv) {
	assert(argc == 1);
    const char* source = GetSqliteValueStr(argv);
    if (source == 0) {
        return;
    }
    String^ source1 = gcnew String(source);
    FuzzyPlusCSharp::Fuzzy::SetDefaultStringMatchingAlgorithm(source1);
    CString result = FuzzyPlusCSharp::Fuzzy::GetStringMatchingAlgorithmName((int)FuzzyPlusCSharp::Fuzzy::DefaultStringMatchingAlgorithm);
    sqlite3_result_text16(context, result, -1, NULL);
}

static void SetDefaultStringMatchingAlgorithm(sqlite3_context* context, int argc, sqlite3_value** argv) {
    assert(argc == 1);
    const unsigned char* ustr = GetSqliteValueUnsignedStr(argv);
    CString result;
    if (isascii(ustr[0]))
    {
        const char* source = GetSqliteValueStr(argv);
        if (source == 0) {
            return;
        }
        String^ source1 = gcnew String(source);
        FuzzyPlusCSharp::Fuzzy::SetDefaultStringMatchingAlgorithm(source1);
        result = source1;
    }
    else 
    {
        int nIn = sqlite3_value_int(argv[0]);
        FuzzyPlusCSharp::Fuzzy::SetDefaultStringMatchingAlgorithm(nIn);
        result = FuzzyPlusCSharp::Fuzzy::GetStringMatchingAlgorithmName(nIn);
    }
    sqlite3_result_text16(context, result, -1, NULL);
}

static void SetDefaultStringMatchingAlgorithmByID(sqlite3_context* context, int argc, sqlite3_value** argv) {
    assert(argc == 1);
    int nIn = sqlite3_value_int(argv[0]);
    FuzzyPlusCSharp::Fuzzy::SetDefaultStringMatchingAlgorithm(nIn);
    CString result = FuzzyPlusCSharp::Fuzzy::GetStringMatchingAlgorithmName(nIn);
    sqlite3_result_text16(context, result, -1, NULL);
}

static FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID GetStringMatchingAlgorithm(std::string str_StringMatchingAlgorithm)
{
    String^ strStringMatchingAlgorithm = gcnew String(str_StringMatchingAlgorithm.c_str());
    FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID stringMatchingAlgorithm = FuzzyPlusCSharp::Fuzzy::GetStringMatchingAlgorithm(strStringMatchingAlgorithm);
    return stringMatchingAlgorithm;
}

static FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID GetStringMatchingAlgorithm(int iStringMatchingAlgorithm)
{
    FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID stringMatchingAlgorithm = FuzzyPlusCSharp::Fuzzy::GetStringMatchingAlgorithm(iStringMatchingAlgorithm);
    return stringMatchingAlgorithm;
}

static double HowSimilar(std::string source1, std::string source2, FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID stringMatchingAlgorithm = FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID::UseDefaultStringMatchingAlgorithm)
{
    String^ s1;
    String^ s2;
    double length = (double)max(source1.length(), source2.length());
    double d = 0;
    switch (stringMatchingAlgorithm) 
    {
    case FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID::Fuzzy_Damlev:
        return GetPercentage((double)damerau_levenshtein(source1.c_str(), source2.c_str()), length);
    case FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID::Fuzzy_Hamming:
        return GetPercentage((double)hamming(source1.c_str(), source2.c_str()), length);
    case FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID::Fuzzy_Jarowin:
        return jaro_winkler(source1.c_str(), source2.c_str());
    case FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID::Fuzzy_Leven:
        return GetPercentage((double)levenshtein(source1.c_str(), source2.c_str()), length);
    case FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID::Fuzzy_Osadist:
        return GetPercentage((double)optimal_string_alignment(source1.c_str(), source2.c_str()), length);
    case FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID::Fuzzy_Editdist:
        d = edit_distance(source1.c_str(), source2.c_str(), 0);
        if (d > 200)
            return 0.0f;
        return (200 - d) / 200;
    case FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID::Fuzzy_Jaro:
        return jaro_distance(source1.c_str(), source2.c_str());
    case FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID::EdlibDistance:
        return GetPercentage(Edlib_Distance(source1.c_str(), source2.c_str(), true), length);
    default:
        s1 = gcnew String(source1.c_str());
        s2 = gcnew String(source2.c_str());
        return FuzzyPlusCSharp::Fuzzy::HowSimilar(s1, s1, (int)stringMatchingAlgorithm);
    }
    return 1.0f;
}

static double HowSimilar(std::string source1, std::string source2, std::string str_StringMatchingAlgorithm){
    return HowSimilar(source1, source2, GetStringMatchingAlgorithm(str_StringMatchingAlgorithm));
}

static double HowSimilar(std::string source1, std::string source2, int iStringMatchingAlgorithm){
    return HowSimilar(source1, source2, GetStringMatchingAlgorithm(iStringMatchingAlgorithm));
}

static bool GetIsCSharpFuzzy(FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID stringMatchingAlgorithm) {
    return ((int)stringMatchingAlgorithm < FuzzyPlusCSharp::Fuzzy::CPP_ONLY_FUZZY_ALGORITHM_IMPLEMENTATION || (int)stringMatchingAlgorithm > FuzzyPlusCSharp::Fuzzy::CASE_INSENSITIVE_STRING_MATCHING_ALGORITHMS);
}

static bool GetIsCSharpFuzzy(std::string str_StringMatchingAlgorithm) {
    return GetIsCSharpFuzzy(GetStringMatchingAlgorithm(str_StringMatchingAlgorithm));
}

static bool GetIsCSharpFuzzy(int iStringMatchingAlgorithm) {
    return GetIsCSharpFuzzy(GetStringMatchingAlgorithm(iStringMatchingAlgorithm));
}

static void HowSimilar(sqlite3_context* context, int argc, sqlite3_value** argv)
{
    assert(argc == 2 || argc == 3);
    const char* str1 = GetSqliteValueStr(argv);
    const char* str2 = GetSqliteValueStr(argv, 1);
    String^ source1 = gcnew String(str1);
    String^ source2 = gcnew String(str2);
    double distance = 0.0f;
    if (argc == 3) 
    {
        const unsigned char* ustr3 = GetSqliteValueUnsignedStr(argv, 2);
        if (isascii(ustr3[0]))
        {
            const char* str3 = GetSqliteValueStr(argv, 2);
            String^ sourc3 = gcnew String(str3);
            distance = GetIsCSharpFuzzy(str3) ? FuzzyPlusCSharp::Fuzzy::HowSimilar(source1, source2, sourc3) : HowSimilar(str1, str2, str3);
        }
        else
        {
            int nIn = sqlite3_value_int(argv[2]);
            distance = GetIsCSharpFuzzy(nIn) ? FuzzyPlusCSharp::Fuzzy::HowSimilar(source1, source2, nIn) : HowSimilar(str1, str2, nIn);
        }
    }
    else
    {
        bool isCSharpFuzzy = GetIsCSharpFuzzy(FuzzyPlusCSharp::Fuzzy::DefaultStringMatchingAlgorithm);
        distance = isCSharpFuzzy ? FuzzyPlusCSharp::Fuzzy::HowSimilar(source1, source2, 0) : HowSimilar(str1, str2, FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID::UseDefaultStringMatchingAlgorithm);
    }
    distance = FuzzyPlusCSharp::Fuzzy::GetPercentWithFixedDecimalDigits(distance);
    sqlite3_result_double(context, distance);
}


static void HowSimilarByName(sqlite3_context* context, int argc, sqlite3_value** argv) {
    assert(argc == 3);
    HowSimilar(context, argc, argv);
}

static void SetDefaultSameSoundMethod(sqlite3_context* context, int argc, sqlite3_value** argv) {
    assert(argc == 1);
    const unsigned char* ustr = GetSqliteValueUnsignedStr(argv);
    if (isascii(ustr[0]))
    {
        const char* source = GetSqliteValueStr(argv);
        if (source == 0) {
            return;
        }
        String^ source1 = gcnew String(source);
        FuzzyPlusCSharp::Fuzzy::SetDefaultSameSoundMethod(source1);
    }
    else
    {
        int nIn = sqlite3_value_int(argv[0]);
        FuzzyPlusCSharp::Fuzzy::SetDefaultSameSoundMethod(nIn);
    }
    CString result = FuzzyPlusCSharp::Fuzzy::GetSameSoundMethodName((int)FuzzyPlusCSharp::Fuzzy::DefaultSameSoundMethod);
    sqlite3_result_text16(context, result, -1, NULL);
}

static void SetPercentDecimalDigits(sqlite3_context* context, int argc, sqlite3_value** argv) {
    assert(argc == 1);
    int nIn = sqlite3_value_int(argv[0]);
    FuzzyPlusCSharp::Fuzzy::SetPercentDecimalDigits(nIn);
    nIn = FuzzyPlusCSharp::Fuzzy::PercentDecimalDigits;
    sqlite3_result_int(context, nIn);
}

static FuzzyPlusCSharp::Fuzzy::SameSoundMethod GetSameSoundMethod(std::string str_SameSoundMethod)
{
    String^ strSameSoundMethod = gcnew String(str_SameSoundMethod.c_str());
    FuzzyPlusCSharp::Fuzzy::SameSoundMethod sameSoundMethod = FuzzyPlusCSharp::Fuzzy::GetSameSoundMethod(strSameSoundMethod);
    return sameSoundMethod;
}

static FuzzyPlusCSharp::Fuzzy::SameSoundMethod GetSameSoundMethod(int iSameSoundMethod)
{
    FuzzyPlusCSharp::Fuzzy::SameSoundMethod sameSoundMethod = FuzzyPlusCSharp::Fuzzy::GetSameSoundMethod(iSameSoundMethod);
    return sameSoundMethod;
}

char* caverphone(const char* src);
unsigned char* phonetic_hash(const unsigned char* zIn, int nIn);
char* soundex(const char* str);
char* refined_soundex(const char* str);
unsigned char* transliterate(const unsigned char* zIn, int nIn);
int script_code(const unsigned char* zIn, int nIn);

static bool Compare(const char* source1, const char* source2, FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID CompareMethod, bool isVerySimilar = true)
{
    String^ s1;
    String^ s2;
    switch (CompareMethod)
    {
    case FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID::ExactMatch:
        return strcmp(source1, source2) == 0;
    default:
        s1 = gcnew String(source1);
        s2 = gcnew String(source2);
        return isVerySimilar ? FuzzyPlusCSharp::Fuzzy::IsVerySimilar(s1, s2, CompareMethod) : FuzzyPlusCSharp::Fuzzy::IsSimilar(s1, s2, CompareMethod);
    }
}

static bool SameSound(std::string source1, std::string source2, 
    FuzzyPlusCSharp::Fuzzy::SameSoundMethod sameSoundMethod = FuzzyPlusCSharp::Fuzzy::SameSoundMethod::UseDefaultSameSoundMethod,
    FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID stringMatchingAlgorithm = FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID::ExactMatch, 
    bool isVerySimilar = true)
{
    double length = (double)max(source1.length(), source2.length());
    char* s1 = NULL;
    char* s2 = NULL;
    bool results = false;
    switch (sameSoundMethod)
    {
    case FuzzyPlusCSharp::Fuzzy::SameSoundMethod::Fuzzy_Caver:
        s1 = caverphone((const char*)source1.c_str());
        s2 = caverphone((const char*)source2.c_str());
        results = Compare(s1, s2, stringMatchingAlgorithm, isVerySimilar);
        break;
    case FuzzyPlusCSharp::Fuzzy::SameSoundMethod::Fuzzy_Phonetic:
        s1 = (char*)phonetic_hash((const unsigned char*)source1.c_str(), (int)source1.length());
        s2 = (char*)phonetic_hash((const unsigned char*)source2.c_str(), (int)source2.length());
        results = Compare(s1, s2, stringMatchingAlgorithm, isVerySimilar);
        break;
    case FuzzyPlusCSharp::Fuzzy::SameSoundMethod::Fuzzy_Soundex:
        s1 = soundex((const char*)source1.c_str());
        s2 = soundex((const char*)source2.c_str());
        results = Compare(s1, s2, stringMatchingAlgorithm, isVerySimilar);
        break;
    case FuzzyPlusCSharp::Fuzzy::SameSoundMethod::Fuzzy_Rsoundex:
        s1 = refined_soundex((const char*)source1.c_str());
        s2 = refined_soundex((const char*)source2.c_str());
        results = Compare(s1, s2, stringMatchingAlgorithm, isVerySimilar);
        break;
    case FuzzyPlusCSharp::Fuzzy::SameSoundMethod::Fuzzy_Translit:
        s1 = (char*)transliterate((const unsigned char*)source1.c_str(), (int)source1.length());
        s2 = (char*)transliterate((const unsigned char*)source2.c_str(), (int)source2.length());
        results = Compare(s1, s2, stringMatchingAlgorithm, isVerySimilar);
        break;
    default:
        String^ s1 = gcnew String(source1.c_str());
        String^ s2 = gcnew String(source2.c_str());
        return FuzzyPlusCSharp::Fuzzy::SameSound(s1, s2, sameSoundMethod, stringMatchingAlgorithm, isVerySimilar);
    }
    free(s1);
    free(s2);
    return results;
}

static void SameSound(sqlite3_context* context, int argc, sqlite3_value** argv)
{
    assert(argc > 1 && argc < 6);
    const char* source1 = GetSqliteValueStr(argv);
    const char* source2 = GetSqliteValueStr(argv, 1);
    bool isSameSound = false;
    if (argc > 2)
    {
        FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID stringMatchingAlgorithm = FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID::ExactMatch;
        bool isVerySimilar = true;
        if (argc > 3) 
        {
            const unsigned char* ustr4 = GetSqliteValueUnsignedStr(argv, 3);
            if (isascii(ustr4[0]))
                stringMatchingAlgorithm = GetStringMatchingAlgorithm((const char*)ustr4);
            else
            {
                int nIn = sqlite3_value_int(argv[3]);
                stringMatchingAlgorithm = GetStringMatchingAlgorithm(nIn);
            }
            if (argc > 4)
            {
                int nIn = sqlite3_value_int(argv[4]);
                isVerySimilar = nIn == 1;
            }
        }
        const unsigned char* ustr3 = GetSqliteValueUnsignedStr(argv, 2);
        if (isascii(ustr3[0]))
            isSameSound = SameSound(source1, source2, GetSameSoundMethod((const char*)ustr3), stringMatchingAlgorithm, isVerySimilar);
        else
        {
            int nIn = sqlite3_value_int(argv[2]);
            isSameSound = SameSound(source1, source2, GetSameSoundMethod(nIn), stringMatchingAlgorithm, isVerySimilar);
        }
    }
    else
        isSameSound = SameSound(source1, source2);
    sqlite3_result_int(context, isSameSound);
}

static double Distance(std::string source1, std::string source2, FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID stringMatchingAlgorithm = FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID::UseDefaultStringMatchingAlgorithm)
{
    String^ s1 = gcnew String(source1.c_str());
    String^ s2 = gcnew String(source2.c_str());
    switch (stringMatchingAlgorithm)
    {
    case FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID::Fuzzy_Damlev:
        return (double)damerau_levenshtein(source1.c_str(), source2.c_str());
    case FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID::Fuzzy_Hamming:
        return (double)hamming(source1.c_str(), source2.c_str());
    case FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID::Fuzzy_Jarowin:
        return (1.0f - jaro_winkler(source1.c_str(), source2.c_str())) * 100.0f;
    case FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID::Fuzzy_Leven:
        return (double)levenshtein(source1.c_str(), source2.c_str());
    case FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID::Fuzzy_Osadist:
        return (double)optimal_string_alignment(source1.c_str(), source2.c_str());
    case FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID::Fuzzy_Editdist:
        return edit_distance(source1.c_str(), source2.c_str(), 0);
    case FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID::Fuzzy_Jaro:
        return (1.0f - jaro_distance(source1.c_str(), source2.c_str())) * 100.0f;
    case FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID::EdlibDistance:
        return Edlib_Distance(source1.c_str(), source2.c_str(), true);
    default:
        return FuzzyPlusCSharp::Fuzzy::Distance(s1, s2, stringMatchingAlgorithm);
    }
    return 0.0f;
}

static double Distance(std::string source1, std::string source2, std::string str_StringMatchingAlgorithm) {
    return Distance(source1, source2, GetStringMatchingAlgorithm(str_StringMatchingAlgorithm));
}

static double Distance(std::string source1, std::string source2, int iStringMatchingAlgorithm) {
    return Distance(source1, source2, GetStringMatchingAlgorithm(iStringMatchingAlgorithm));
}
static void Distance(sqlite3_context* context, int argc, sqlite3_value** argv)
{
    assert(argc == 2 || argc == 3);
    const char* str1 = GetSqliteValueStr(argv);
    const char* str2 = GetSqliteValueStr(argv, 1);
    String^ source1 = gcnew String(str1);
    String^ source2 = gcnew String(str2);
    double distance = 0.0f;
    if (argc == 3) 
    {
        const unsigned char* ustr3 = GetSqliteValueUnsignedStr(argv, 2);
        if (isascii(ustr3[0]))
        {
            const char* str3 = GetSqliteValueStr(argv, 2);
            String^ sourc3 = gcnew String(str3);
            distance = GetIsCSharpFuzzy(str3) ? FuzzyPlusCSharp::Fuzzy::Distance(source1, source2, sourc3) : Distance(str1, str2, str3);
        }
        else
        {
            int nIn = sqlite3_value_int(argv[2]);
            distance = GetIsCSharpFuzzy(nIn) ? FuzzyPlusCSharp::Fuzzy::Distance(source1, source2, nIn) : Distance(str1, str2, nIn);
        }
    }
    else
    {
        assert(argc == 2);
        bool isCSharpFuzzy = GetIsCSharpFuzzy(FuzzyPlusCSharp::Fuzzy::DefaultStringMatchingAlgorithm);
        distance = isCSharpFuzzy ? FuzzyPlusCSharp::Fuzzy::Distance(source1, source2, 0) : Distance(str1, str2, FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID::UseDefaultStringMatchingAlgorithm);
    }
    distance = FuzzyPlusCSharp::Fuzzy::GetPercentWithFixedDecimalDigits(distance);
    sqlite3_result_double(context, distance);
}

static void RegexReplace(sqlite3_context* context, int argc, sqlite3_value** argv) {
    assert(argc == 3);
    String^ source = gcnew String(GetSqliteValueStr(argv));
    String^ pattern = gcnew String(GetSqliteValueStr(argv, 1));
    const char* str3 = GetSqliteValueStr(argv, 2);
    String^ replacement = gcnew String(str3);
    CString result(FuzzyPlusCSharp::Fuzzy::RegexReplace(source, pattern, replacement));
    sqlite3_result_text16(context, result, -1, NULL);
}

static void RegexSearch(sqlite3_context* context, int argc, sqlite3_value** argv) {
    assert(argc == 2 || argc == 3);
    String^ source = gcnew String(GetSqliteValueStr(argv));
    String^ pattern = gcnew String(GetSqliteValueStr(argv, 1));
    bool returnOriginalStringIfEmpty = false;
    if (argc == 3)
    {
        int nIn = sqlite3_value_int(argv[2]);
        if (nIn != 0)
            returnOriginalStringIfEmpty = true;
    }
    CString result(FuzzyPlusCSharp::Fuzzy::RegexSearch(source, pattern));
    if (result.IsEmpty() && returnOriginalStringIfEmpty)
        result = source;
    sqlite3_result_text16(context, result, -1, NULL);
}

static void fuzzy_soundex2(sqlite3_context* context, int argc, sqlite3_value** argv)
{
    assert(argc == 1 || argc == 2 || argc == 3);
    if (argc == 1)
        return fuzzy_soundex(context, argc, argv);
    const char* str1 = GetSqliteValueStr(argv);
    const char* str2 = GetSqliteValueStr(argv, 1);
    char* s1 = soundex(str1);
    char* s2 = soundex(str2);
    if (argc == 2)
    {
        int isMatch = strcmp(s1, s2) == 0;
        sqlite3_result_int(context, isMatch);
    }
    else
    {
        String^ source1 = gcnew String(s1);
        String^ source2 = gcnew String(s2);
        const unsigned char* ustr3 = GetSqliteValueUnsignedStr(argv, 2);
        double distance = 0.0f;
        if (isascii(ustr3[0]))
        {
            const char* str3 = GetSqliteValueStr(argv, 2);
            String^ sourc3 = gcnew String(str3);
            distance = GetIsCSharpFuzzy(str3) ? FuzzyPlusCSharp::Fuzzy::HowSimilar(source1, source2, sourc3) : HowSimilar(str1, str2, str3);
        }
        else
        {
            int nIn = sqlite3_value_int(argv[2]);
            distance = GetIsCSharpFuzzy(nIn) ? FuzzyPlusCSharp::Fuzzy::HowSimilar(source1, source2, nIn) : HowSimilar(str1, str2, nIn);
        }
        distance = FuzzyPlusCSharp::Fuzzy::GetPercentWithFixedDecimalDigits(distance);
        sqlite3_result_double(context, distance);
    }
    free(s1);
    free(s2);
}

static void fuzzy_rsoundex2(sqlite3_context* context, int argc, sqlite3_value** argv)
{
    assert(argc == 1 || argc == 2 || argc == 3);
    if (argc == 1)
        return fuzzy_rsoundex(context, argc, argv);
    const char* str1 = GetSqliteValueStr(argv);
    const char* str2 = GetSqliteValueStr(argv, 1);
    char* s1 = refined_soundex(str1);
    char* s2 = refined_soundex(str2);
    if (argc == 2)
    {
        int isMatch = strcmp(s1, s2) == 0;
        sqlite3_result_int(context, isMatch);
    }
    else
    {
        String^ source1 = gcnew String(s1);
        String^ source2 = gcnew String(s2);
        const unsigned char* ustr3 = GetSqliteValueUnsignedStr(argv, 2);
        double distance = 0.0f;
        if (isascii(ustr3[0]))
        {
            const char* str3 = GetSqliteValueStr(argv, 2);
            String^ sourc3 = gcnew String(str3);
            distance = GetIsCSharpFuzzy(str3) ? FuzzyPlusCSharp::Fuzzy::HowSimilar(source1, source2, sourc3) : HowSimilar(str1, str2, str3);
        }
        else
        {
            int nIn = sqlite3_value_int(argv[2]);
            distance = GetIsCSharpFuzzy(nIn) ? FuzzyPlusCSharp::Fuzzy::HowSimilar(source1, source2, nIn) : HowSimilar(str1, str2, nIn);
        }
        distance = FuzzyPlusCSharp::Fuzzy::GetPercentWithFixedDecimalDigits(distance);
        sqlite3_result_double(context, distance);
    }
    free(s1);
    free(s2);
}

static void CaverPhonePhonix(sqlite3_context* context, int argc, sqlite3_value** argv) {
    assert(argc == 1 || argc == 2);
    const char* str1 = GetSqliteValueStr(argv);
    if (str1 == 0) {

        sqlite3_result_error(context, "arguments should not be NULL", -1);
        return;
    }
    String^ source1 = gcnew String(str1);
    if (argc == 2)
    {
        const char* str2 = GetSqliteValueStr(argv, 1);
        String^ source2 = gcnew String(str2);
        int results = FuzzyPlusCSharp::Fuzzy::CaverPhonePhonix(source1, source2, FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID::ExactMatch, true);
        sqlite3_result_int(context, results);
        return;
    }
    CString result = FuzzyPlusCSharp::Fuzzy::CaverPhonePhonix(source1);
    sqlite3_result_text16(context, result, -1, NULL);
}

static void SoundexPhonix(sqlite3_context* context, int argc, sqlite3_value** argv) {
    assert(argc == 1 || argc == 2);
    const char* str1 = GetSqliteValueStr(argv);
    if (str1 == 0) {

        sqlite3_result_error(context, "arguments should not be NULL", -1);
        return;
    }
    String^ source1 = gcnew String(str1);
    if (argc == 2)
    {
        const char* str2 = GetSqliteValueStr(argv, 1);
        String^ source2 = gcnew String(str2);
        int results = FuzzyPlusCSharp::Fuzzy::SoundexPhonix(source1, source2, FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID::ExactMatch, true);
        sqlite3_result_int(context, results);
        return;
    }
    CString result = FuzzyPlusCSharp::Fuzzy::SoundexPhonix(source1);
    sqlite3_result_text16(context, result, -1, NULL);
}

template <typename Func>
static void WrapperSqliteFunctionDistance(Func func, sqlite3_context* context, int argc, sqlite3_value** argv)
{
    assert(argc == 2 || argc == 3);
    bool isCaseSensitive = TRUE;
    const char* str1 = GetSqliteValueStr(argv);
    const char* str2 = GetSqliteValueStr(argv, 1);
    if (str1 == 0 || str2 == 0) {
        sqlite3_result_error(context, "arguments should not be NULL", -1);
        return;
    }
    if (argc == 3)
    {
        int nIn = sqlite3_value_bytes(argv[2]);
        isCaseSensitive = nIn == 0 ? FALSE : TRUE;
    }
    String^ sourc1 = gcnew String(str1);
    String^ sourc2 = gcnew String(str2);
    double distance = (double)func(sourc1, sourc2, isCaseSensitive);
    sqlite3_result_double(context, distance);
}

template <typename Func>
static void WrapperSqliteFunctionDistance2(Func func, sqlite3_context* context, int argc, sqlite3_value** argv)
{
    assert(argc == 2);
    const char* str1 = GetSqliteValueStr(argv);
    const char* str2 = GetSqliteValueStr(argv, 1);
    if (str1 == 0 || str2 == 0) {
        sqlite3_result_error(context, "arguments should not be NULL", -1);
        return;
    }
    String^ sourc1 = gcnew String(str1);
    String^ sourc2 = gcnew String(str2);
    double distance = (double)func(sourc1, sourc2);
    sqlite3_result_double(context, distance);
}

template <typename Func>
static void WrapperSqliteFunction2(Func func, sqlite3_context* context, int argc, sqlite3_value** argv)
{
    assert(argc == 2);
    const char* str1 = GetSqliteValueStr(argv);
    const char* str2 = GetSqliteValueStr(argv, 1);
    String^ sourc1 = gcnew String(str1);
    String^ sourc2 = gcnew String(str2);
    unsigned distance = func(sourc1, sourc2);
    sqlite3_result_int(context, distance);
}


static void LevenshteinDistance(sqlite3_context* context, int argc, sqlite3_value** argv) {
    WrapperSqliteFunctionDistance(FuzzyPlusCSharp::Fuzzy::LevenshteinDistance, context, argc, argv);
}
static void DamerauLevenshteinDistance(sqlite3_context* context, int argc, sqlite3_value** argv) {
    WrapperSqliteFunctionDistance(FuzzyPlusCSharp::Fuzzy::DamerauLevenshteinDistance, context, argc, argv);
}
static void EditDistance(sqlite3_context* context, int argc, sqlite3_value** argv) {
    WrapperSqliteFunctionDistance(FuzzyPlusCSharp::Fuzzy::EditDistance, context, argc, argv);
}
static void JaroWinklerDistance(sqlite3_context* context, int argc, sqlite3_value** argv) {
    WrapperSqliteFunctionDistance(FuzzyPlusCSharp::Fuzzy::JaroWinklerDistance, context, argc, argv);
}
static void OverlapCoefficientDistance(sqlite3_context* context, int argc, sqlite3_value** argv) {
    WrapperSqliteFunctionDistance(FuzzyPlusCSharp::Fuzzy::OverlapCoefficientDistance, context, argc, argv);
}
static void JaccardDistance(sqlite3_context* context, int argc, sqlite3_value** argv) {
    WrapperSqliteFunctionDistance(FuzzyPlusCSharp::Fuzzy::JaccardDistance, context, argc, argv);
}
static void SorensenDiceDistance(sqlite3_context* context, int argc, sqlite3_value** argv) {
    WrapperSqliteFunctionDistance(FuzzyPlusCSharp::Fuzzy::SorensenDiceDistance, context, argc, argv);
}
static void RatcliffObershelpSimilarityDistance(sqlite3_context* context, int argc, sqlite3_value** argv) {
    WrapperSqliteFunctionDistance(FuzzyPlusCSharp::Fuzzy::RatcliffObershelpSimilarityDistance, context, argc, argv);
}
static void HammingDistance(sqlite3_context* context, int argc, sqlite3_value** argv) {
    WrapperSqliteFunctionDistance(FuzzyPlusCSharp::Fuzzy::HammingDistance, context, argc, argv);
}
static void LongestCommonSubstringDistance(sqlite3_context* context, int argc, sqlite3_value** argv) {
    WrapperSqliteFunctionDistance(FuzzyPlusCSharp::Fuzzy::LongestCommonSubstringDistance, context, argc, argv);
}
static void LongestCommonSubsequenceDistance(sqlite3_context* context, int argc, sqlite3_value** argv) {
    WrapperSqliteFunctionDistance(FuzzyPlusCSharp::Fuzzy::LongestCommonSubsequenceDistance, context, argc, argv);
}
static void JaroDistance(sqlite3_context* context, int argc, sqlite3_value** argv) {
    WrapperSqliteFunctionDistance(FuzzyPlusCSharp::Fuzzy::JaroDistance, context, argc, argv);
}
static void NormalizedLevenshteinDistance(sqlite3_context* context, int argc, sqlite3_value** argv) {
    WrapperSqliteFunctionDistance(FuzzyPlusCSharp::Fuzzy::NormalizedLevenshteinDistance, context, argc, argv);
}
static void Levenshtein2Distance(sqlite3_context* context, int argc, sqlite3_value** argv) {
    WrapperSqliteFunctionDistance(FuzzyPlusCSharp::Fuzzy::Levenshtein2Distance, context, argc, argv);
}
static void TanimotoCoefficientDistance(sqlite3_context* context, int argc, sqlite3_value** argv) {
    WrapperSqliteFunctionDistance(FuzzyPlusCSharp::Fuzzy::TanimotoCoefficientDistance, context, argc, argv);
}
static void PhraseSimplifiedDiff(sqlite3_context* context, int argc, sqlite3_value** argv) {
    WrapperSqliteFunctionDistance2(FuzzyPlusCSharp::Fuzzy::PhraseSimplifiedDiff, context, argc, argv);
}
static void PhraseSimilar(sqlite3_context* context, int argc, sqlite3_value** argv) {
    WrapperSqliteFunction2(FuzzyPlusCSharp::Fuzzy::PhraseSimilar, context, argc, argv);
}
static void PhraseVerySimilar(sqlite3_context* context, int argc, sqlite3_value** argv) {
    WrapperSqliteFunction2(FuzzyPlusCSharp::Fuzzy::PhraseVerySimilar, context, argc, argv);
}
static void PhraseSomeWhatSimilar(sqlite3_context* context, int argc, sqlite3_value** argv) {
    WrapperSqliteFunction2(FuzzyPlusCSharp::Fuzzy::PhraseSomeWhatSimilar, context, argc, argv);
}
static void PhraseSlightlySimilar(sqlite3_context* context, int argc, sqlite3_value** argv) {
    WrapperSqliteFunction2(FuzzyPlusCSharp::Fuzzy::PhraseSlightlySimilar, context, argc, argv);
}
static void PhraseHardlySimilar(sqlite3_context* context, int argc, sqlite3_value** argv) {
    WrapperSqliteFunction2(FuzzyPlusCSharp::Fuzzy::PhraseHardlySimilar, context, argc, argv);
}
static void RegexMatch(sqlite3_context* context, int argc, sqlite3_value** argv) {
    WrapperSqliteFunction2(FuzzyPlusCSharp::Fuzzy::RegexMatch, context, argc, argv);
}

template <typename Func>
static void WrapperSqliteFunctionReturnStr(Func func, sqlite3_context* context, int argc, sqlite3_value** argv)
{
    assert(argc == 1);
    const char* source = GetSqliteValueStr(argv);
    if (source == 0)
        return;
    String^ sourc1 = gcnew String(source);
    func(sourc1);
    sqlite3_result_text(context, source, -1, NULL);
}

static void StringReverse(sqlite3_context* context, int argc, sqlite3_value** argv) {
    WrapperSqliteFunctionReturnStr(FuzzyPlusCSharp::Fuzzy::StringReverse, context, argc, argv);
}
static void GetFileName(sqlite3_context* context, int argc, sqlite3_value** argv) {
    WrapperSqliteFunctionReturnStr(FuzzyPlusCSharp::Fuzzy::GetFileName, context, argc, argv);
}
static void GetExtension(sqlite3_context* context, int argc, sqlite3_value** argv) {
    WrapperSqliteFunctionReturnStr(FuzzyPlusCSharp::Fuzzy::GetExtension, context, argc, argv);
}
static void GetDirectoryName(sqlite3_context* context, int argc, sqlite3_value** argv) {
    WrapperSqliteFunctionReturnStr(FuzzyPlusCSharp::Fuzzy::GetDirectoryName, context, argc, argv);
}
static void GetFileNameWithoutExtension(sqlite3_context* context, int argc, sqlite3_value** argv) {
    WrapperSqliteFunctionReturnStr(FuzzyPlusCSharp::Fuzzy::GetFileNameWithoutExtension, context, argc, argv);
}

template <typename Func>
static void WrapperSqliteFunctionReturnInt(Func func, sqlite3_context* context, int argc, sqlite3_value** argv)
{
    assert(argc == 1);
    const char* source = GetSqliteValueStr(argv);
    if (source == 0)
        return;
    String^ sourc1 = gcnew String(source);
    int results = (int)func(sourc1);
    sqlite3_result_int(context, results);
}

static void IsFileExist(sqlite3_context* context, int argc, sqlite3_value** argv) {
    WrapperSqliteFunctionReturnInt(FuzzyPlusCSharp::Fuzzy::IsFileExist, context, argc, argv);
}
static void IsDirExist(sqlite3_context* context, int argc, sqlite3_value** argv) {
    WrapperSqliteFunctionReturnInt(FuzzyPlusCSharp::Fuzzy::IsDirExist, context, argc, argv);
}

template <typename Func, typename LocalFunc>
static void WrapperSqliteFunctionSimilar(Func func, LocalFunc localFunc, sqlite3_context* context, int argc, sqlite3_value** argv)
{
    assert(argc == 2 || argc == 3);
    FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID d = FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID::UseDefaultStringMatchingAlgorithm;
    const char* str1 = GetSqliteValueStr(argv);
    const char* str2 = GetSqliteValueStr(argv, 1);
    if (str1 == 0 || str2 == 0) {
        sqlite3_result_error(context, "arguments should not be NULL", -1);
        return;
    }
    if (argc == 3)
    {
        const unsigned char* ustr3 = GetSqliteValueUnsignedStr(argv, 2);
        if (isascii(ustr3[0]))
        {
            const char* str3 = GetSqliteValueStr(argv, 2);
            String^ sourc3 = gcnew String(str3);
            d = FuzzyPlusCSharp::Fuzzy::GetStringMatchingAlgorithm(sourc3);
        }
        else
        {
            int nIn = sqlite3_value_int(argv[2]);
            d = FuzzyPlusCSharp::Fuzzy::GetStringMatchingAlgorithm(nIn);
        }
    }
    if (d >= FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID::Fuzzy_Damlev && d <= FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID::EdlibDistance)
    {
        unsigned distance = localFunc(str1, str2, d);
        sqlite3_result_int(context, distance);
    }
    else 
    {
        String^ sourc1 = gcnew String(str1);
        String^ sourc2 = gcnew String(str2);
        unsigned distance = func(sourc1, sourc2, (int)d);
        sqlite3_result_int(context, distance);
    }
}

static bool Is_Similar(const char* source1, const char* source2, FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID id)
{
    return HowSimilar(source1, source2, id) >= FuzzyPlusCSharp::Fuzzy::ISSIMILAR;
}
static bool Is_VerySimilar(const char* source1, const char* source2, FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID id)
{
    return HowSimilar(source1, source2, id) >= FuzzyPlusCSharp::Fuzzy::ISVERYSIMILAR;
}
static bool Is_SomeWhatSimilar(const char* source1, const char* source2, FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID id)
{
    return HowSimilar(source1, source2, id) >= FuzzyPlusCSharp::Fuzzy::ISSOMEWHATSIMILAR;
}
static bool Is_SlightlySimilar(const char* source1, const char* source2, FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID id)
{
    return HowSimilar(source1, source2, id) >= FuzzyPlusCSharp::Fuzzy::ISSLIGHTLYSIMILAR;
}
static bool Is_HardlySimilar(const char* source1, const char* source2, FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID id)
{
    return HowSimilar(source1, source2, id) >= FuzzyPlusCSharp::Fuzzy::ISHARDLYSIMILAR;
}
static bool Is_NotSimilar(const char* source1, const char* source2, FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID id)
{
    return HowSimilar(source1, source2, id) < FuzzyPlusCSharp::Fuzzy::ISHARDLYSIMILAR;
}

static void IsSimilar(sqlite3_context* context, int argc, sqlite3_value** argv) {
    WrapperSqliteFunctionSimilar(FuzzyPlusCSharp::Fuzzy::IsSimilarByID, Is_Similar, context, argc, argv);
}
static void IsVerySimilar(sqlite3_context* context, int argc, sqlite3_value** argv) {
    WrapperSqliteFunctionSimilar(FuzzyPlusCSharp::Fuzzy::IsVerySimilarByID, Is_VerySimilar, context, argc, argv);
}
static void IsSomeWhatSimilar(sqlite3_context* context, int argc, sqlite3_value** argv) {
    WrapperSqliteFunctionSimilar(FuzzyPlusCSharp::Fuzzy::IsSomeWhatSimilarByID, Is_SomeWhatSimilar, context, argc, argv);
}
static void IsSlightlySimilar(sqlite3_context* context, int argc, sqlite3_value** argv) {
    WrapperSqliteFunctionSimilar(FuzzyPlusCSharp::Fuzzy::IsSlightlySimilarByID, Is_SlightlySimilar, context, argc, argv);
}
static void IsHardlySimilar(sqlite3_context* context, int argc, sqlite3_value** argv) {
    WrapperSqliteFunctionSimilar(FuzzyPlusCSharp::Fuzzy::IsHardlySimilarByID, Is_HardlySimilar, context, argc, argv);
}
static void IsNotSimilar(sqlite3_context* context, int argc, sqlite3_value** argv) {
    WrapperSqliteFunctionSimilar(FuzzyPlusCSharp::Fuzzy::IsNotSimilarByID, Is_NotSimilar, context, argc, argv);
}

namespace SqliteFuzzyPlusExtension {
    public ref class Fuzzy
    {
        static double DamLev(std::string str1, std::string str2, bool isCaseSensitive) {
            String^ source1 = gcnew String(str1.c_str());
            String^ source2 = gcnew String(str2.c_str());
            double distance = FuzzyPlusCSharp::Fuzzy::DamerauLevenshteinDistance(source1, source2, isCaseSensitive);
            return FuzzyPlusCSharp::Fuzzy::GetPercentWithFixedDecimalDigits(distance);
        }
        static double DamLev(std::string source1, std::string source2) {
            return DamLev(source1, source2, TRUE);
        }
        static double HowSimilar(std::string source1, std::string source2, int iStringMatchingAlgorithm) {
            return ::HowSimilar(source1, source2, GetStringMatchingAlgorithm(iStringMatchingAlgorithm));
        }
        static double Distance(std::string source1, std::string source2, int iStringMatchingAlgorithm) {
            return ::Distance(source1, source2, GetStringMatchingAlgorithm(iStringMatchingAlgorithm));
        }
    };
}

extern "C"
{
    // CLR Class Library .Net Framework C++
    // Works with DB Browser
    // Works with referencing CSharp DLL
    __declspec(dllexport) int sqlite3_extension_init(sqlite3* db,
        char** pzErrMsg,
        const sqlite3_api_routines* sqlite_api) {
        sqlite3_api = sqlite_api;
        static const int flags = SQLITE_UTF8 | SQLITE_INNOCUOUS | SQLITE_DETERMINISTIC;
        //FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID d = FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID::UseDefaultStringMatchingAlgorithm;

        // Original long distance names
        SQLITE3_CREATE_FUNCTION2(LevenshteinDistance);
        SQLITE3_CREATE_FUNCTION2(DamerauLevenshteinDistance);
        SQLITE3_CREATE_FUNCTION2(JaroWinklerDistance);
        SQLITE3_CREATE_FUNCTION2(OverlapCoefficientDistance);
        SQLITE3_CREATE_FUNCTION2(JaccardDistance);
        SQLITE3_CREATE_FUNCTION2(SorensenDiceDistance);
        SQLITE3_CREATE_FUNCTION2(RatcliffObershelpSimilarityDistance);
        SQLITE3_CREATE_FUNCTION2(HammingDistance);
        SQLITE3_CREATE_FUNCTION2(LongestCommonSubstringDistance);
        SQLITE3_CREATE_FUNCTION2(LongestCommonSubsequenceDistance);
        SQLITE3_CREATE_FUNCTION2(JaroDistance);
        SQLITE3_CREATE_FUNCTION2(NormalizedLevenshteinDistance);
        SQLITE3_CREATE_FUNCTION2(Levenshtein2Distance);
        SQLITE3_CREATE_FUNCTION2(TanimotoCoefficientDistance);
        SQLITE3_CREATE_FUNCTION2(EdlibDistance);
        SQLITE3_CREATE_FUNCTION2(EditDistance);
        SQLITE3_CREATE_FUNCTION2(SameName);
        SQLITE3_CREATE_FUNCTION2(CaverPhonePhonix);
        SQLITE3_CREATE_FUNCTION1(CaverPhonePhonix);
        SQLITE3_CREATE_FUNCTION2(SoundexPhonix);
        SQLITE3_CREATE_FUNCTION1(SoundexPhonix);

        // Methods to set default StringMatchingAlgorithm, DefaultSameSoundMethod, and PercentDecimalDigits 
        SQLITE3_CREATE_FUNCTION1(SetDefaultStringMatchingAlgorithm);
        SQLITE3_CREATE_FUNCTION1(SetDefaultStringMatchingAlgorithmByName);
        SQLITE3_CREATE_FUNCTION1(SetDefaultStringMatchingAlgorithmByID);
        SQLITE3_CREATE_FUNCTION1(SetDefaultSameSoundMethod);
        SQLITE3_CREATE_FUNCTION1(SetPercentDecimalDigits);

        // Similarity functions which use default distance function
        SQLITE3_CREATE_FUNCTION2(IsNotSimilar);
        SQLITE3_CREATE_FUNCTION2(IsVerySimilar);
        SQLITE3_CREATE_FUNCTION2(IsSimilar);
        SQLITE3_CREATE_FUNCTION2(IsSomeWhatSimilar);
        SQLITE3_CREATE_FUNCTION2(IsSlightlySimilar);
        SQLITE3_CREATE_FUNCTION2(IsHardlySimilar);

        SQLITE3_CREATE_FUNCTION3(IsNotSimilar);
        SQLITE3_CREATE_FUNCTION3(IsVerySimilar);
        SQLITE3_CREATE_FUNCTION3(IsSimilar);
        SQLITE3_CREATE_FUNCTION3(IsSomeWhatSimilar);
        SQLITE3_CREATE_FUNCTION3(IsSlightlySimilar);
        SQLITE3_CREATE_FUNCTION3(IsHardlySimilar);

        SQLITE3_CREATE_FUNCTION2(PhraseVerySimilar);
        SQLITE3_CREATE_FUNCTION2(PhraseSimilar);
        SQLITE3_CREATE_FUNCTION2(PhraseSomeWhatSimilar);
        SQLITE3_CREATE_FUNCTION2(PhraseSlightlySimilar);
        SQLITE3_CREATE_FUNCTION2(PhraseHardlySimilar);
        SQLITE3_CREATE_FUNCTION2(PhraseSimplifiedDiff);

        SQLITE3_CREATE_FUNCTION2(HowSimilar);
        SQLITE3_CREATE_FUNCTION3(HowSimilar);
        SQLITE3_CREATE_FUNCTION3(HowSimilarByName);
        SQLITE3_CREATE_FUNCTION2(Distance);
        SQLITE3_CREATE_FUNCTION3(Distance);
        SQLITE3_CREATE_FUNCTION2(SameSound);
        SQLITE3_CREATE_FUNCTION3(SameSound);
        SQLITE3_CREATE_FUNCTION4(SameSound);
        SQLITE3_CREATE_FUNCTION5(SameSound);

        // Alias function names
        SQLITE3_CREATE_FUNCTION_ALIAS2(Lev, LevenshteinDistance);
        SQLITE3_CREATE_FUNCTION_ALIAS2(DamLev, DamerauLevenshteinDistance);
        SQLITE3_CREATE_FUNCTION_ALIAS2(JaroWin, JaroWinklerDistance);
        SQLITE3_CREATE_FUNCTION_ALIAS2(OverlapCoef, OverlapCoefficientDistance);
        SQLITE3_CREATE_FUNCTION_ALIAS2(Jaccard, JaccardDistance);
        SQLITE3_CREATE_FUNCTION_ALIAS2(SorensenDice, SorensenDiceDistance);
        SQLITE3_CREATE_FUNCTION_ALIAS2(Ratcliff, RatcliffObershelpSimilarityDistance);
        SQLITE3_CREATE_FUNCTION_ALIAS2(HammDist, HammingDistance);
        SQLITE3_CREATE_FUNCTION_ALIAS2(LCS, LongestCommonSubstringDistance);
        SQLITE3_CREATE_FUNCTION_ALIAS2(LCSq, LongestCommonSubsequenceDistance);
        SQLITE3_CREATE_FUNCTION_ALIAS2(Jaro, JaroDistance);
        SQLITE3_CREATE_FUNCTION_ALIAS2(NormLev, NormalizedLevenshteinDistance);
        SQLITE3_CREATE_FUNCTION_ALIAS2(Lev2, Levenshtein2Distance);
        SQLITE3_CREATE_FUNCTION_ALIAS2(Tanimoto, TanimotoCoefficientDistance);
        SQLITE3_CREATE_FUNCTION_ALIAS2(Edlib, EdlibDistance);
        SQLITE3_CREATE_FUNCTION_ALIAS2(PhraseDiff, PhraseSimplifiedDiff);
        SQLITE3_CREATE_FUNCTION_ALIAS2(Regex, RegexReplace);
        SQLITE3_CREATE_FUNCTION_ALIAS2(XMatch, RegexMatch);
        SQLITE3_CREATE_FUNCTION_ALIAS2(XSearch, RegexSearch);
        SQLITE3_CREATE_FUNCTION_ALIAS1(StrRev, StringReverse);
        SQLITE3_CREATE_FUNCTION_ALIAS2(MaxVal, MaxValue);
        SQLITE3_CREATE_FUNCTION_ALIAS2(MaxLen, MaxLength);
        SQLITE3_CREATE_FUNCTION_ALIAS2(MinVal, MinValue);
        SQLITE3_CREATE_FUNCTION_ALIAS2(MinLen, MinLength);
        SQLITE3_CREATE_FUNCTION_ALIAS1(GetFileNameWithExtension, GetFileName);
        SQLITE3_CREATE_FUNCTION_ALIAS1(HasChr, HasCharInSameOrder);
        SQLITE3_CREATE_FUNCTION_ALIAS2(HasChr, HasCharInSameOrder);
        SQLITE3_CREATE_FUNCTION_ALIAS2(Similar, HowSimilar);
        SQLITE3_CREATE_FUNCTION_ALIAS3(Similar, HowSimilar);
        SQLITE3_CREATE_FUNCTION_ALIAS1(FileExist, IsFileExist);
        SQLITE3_CREATE_FUNCTION_ALIAS1(DirExist, IsDirExist);
        SQLITE3_CREATE_FUNCTION_ALIAS1(GetDirName, GetDirectoryName);

        // soundex and rsoundex have a 1, 2, and 3 argument version
        SQLITE3_CREATE_FUNCTION_ALIAS1(fuzzy_soundex, fuzzy_soundex2);
        SQLITE3_CREATE_FUNCTION_ALIAS1(fuzzy_rsoundex, fuzzy_rsoundex2);
        SQLITE3_CREATE_FUNCTION_ALIAS1(soundex, fuzzy_soundex2);
        SQLITE3_CREATE_FUNCTION_ALIAS1(rsoundex, fuzzy_rsoundex2);
        // 2 argument version comparing 2 strings to see if the (r)soundex results are equal via strcmp
        SQLITE3_CREATE_FUNCTION_ALIAS2(fuzzy_soundex, fuzzy_soundex2);
        SQLITE3_CREATE_FUNCTION_ALIAS2(fuzzy_rsoundex, fuzzy_rsoundex2);
        SQLITE3_CREATE_FUNCTION_ALIAS2(soundex, fuzzy_soundex2);
        SQLITE3_CREATE_FUNCTION_ALIAS2(rsoundex, fuzzy_rsoundex2);
        // 2 argument version comparing 2 strings and returning the distance of the (r)soundex results for each string. The 3rd argument is the distance method to use on the (r)soundex results.
        SQLITE3_CREATE_FUNCTION_ALIAS3(fuzzy_soundex, fuzzy_soundex2);
        SQLITE3_CREATE_FUNCTION_ALIAS3(fuzzy_rsoundex, fuzzy_rsoundex2);
        SQLITE3_CREATE_FUNCTION_ALIAS3(soundex, fuzzy_soundex2);
        SQLITE3_CREATE_FUNCTION_ALIAS3(rsoundex, fuzzy_rsoundex2);
        SQLITE3_CREATE_FUNCTION_ALIAS2(IncludesAWordFrom, HasWordFrom);
        SQLITE3_CREATE_FUNCTION_ALIAS3(IncludesAWordFrom, HasWordFrom);

        // Miscellaneous functions
        SQLITE3_CREATE_FUNCTION2(RegexMatch);
        SQLITE3_CREATE_FUNCTION2(RegexSearch);
        SQLITE3_CREATE_FUNCTION3(RegexReplace);
        SQLITE3_CREATE_FUNCTION1(StringReverse);
        SQLITE3_CREATE_FUNCTION2(MaxValue);
        SQLITE3_CREATE_FUNCTION2(MaxLength);
        SQLITE3_CREATE_FUNCTION2(MinValue);
        SQLITE3_CREATE_FUNCTION2(MinLength);
        SQLITE3_CREATE_FUNCTION1(NormalizeNum);
        SQLITE3_CREATE_FUNCTION1(HasCharInSameOrder);
        SQLITE3_CREATE_FUNCTION2(HasCharInSameOrder);
        SQLITE3_CREATE_FUNCTION2(HasWordFrom);
        SQLITE3_CREATE_FUNCTION3(HasWordFrom);
        SQLITE3_CREATE_FUNCTION1(ValuesList);
        SQLITE3_CREATE_FUNCTION2(ValuesList);
        SQLITE3_CREATE_FUNCTION1(ToHash);
        SQLITE3_CREATE_FUNCTION2(ToHash);
        SQLITE3_CREATE_FUNCTION1(FastHash);
        SQLITE3_CREATE_FUNCTION1(TestFoo);

        // File associated functions
        SQLITE3_CREATE_FUNCTION1(IsFileExist);
        SQLITE3_CREATE_FUNCTION1(IsDirExist);
        SQLITE3_CREATE_FUNCTION1(GetFileName);
        SQLITE3_CREATE_FUNCTION1(GetExtension);
        SQLITE3_CREATE_FUNCTION1(GetDirectoryName);
        SQLITE3_CREATE_FUNCTION1(GetFileNameWithoutExtension);

        return sqlite_fuzzy_init(db, sqlite_api);
    }
}

#include "SqliteFuzzyPlusExtension_ExportFunctions.hpp"