#include <windows.h>
#include <cassert>
#include <string>
#include <algorithm>
#include <ctype.h>
#include <atlstr.h>
#include "SqliteFuzzyPlusExtension_Internal.h"
#define SQLITEFUZZYPLUSEXTENSION_EXCLUDE_FUNC
#include "SqliteFuzzyPlusExtension.h"
#include "edlib\include\edlib.h"
using namespace System;

// ToDo: Add the following functions:
//      SameFirstLastName, SamePhone, SameSocial, SameZip, SameAddress, SameDate, SameNumber
//      SameFileName -> Will use * and ? as wildcard characters which will get converted to SQL wildcard characters (% and _)

// ToDo: Add fuzzy_soundex and fuzzy_rsoundex functions that can optionally handle 3 arguments.

// ToDo: Add MD5 support for both blobs and for files via file names listed in DB.
//      MakeMD5 -> Function checks if argv[0] is blob or text file name.

// ToDo: Add fuzzy logic to compare blobs that have image or video files.
// ToDo: Add fuzzy logic to compare files via file names listed in DB.

const sqlite3_api_routines* sqlite3_api = NULL;

static double Edlib_Distance(std::string source1, std::string source2, bool isCaseSensitive = true)
{
    if (isCaseSensitive == false)
    {
        std::transform(source1.begin(), source1.end(), source1.begin(), [](unsigned char c) { return std::tolower(c); });
        std::transform(source2.begin(), source2.end(), source2.begin(), [](unsigned char c) { return std::tolower(c); });
    }
    EdlibAlignResult result = edlibAlign(source1.c_str(), (int)source1.length(), source2.c_str(), (int)source2.length(), edlibDefaultAlignConfig());
    return result.alignmentLength;
}

static double iEdlibDistance(std::string source1, std::string source2)
{
    return Edlib_Distance(source1, source2, false);
}

static void EdlibDistance(sqlite3_context* context, int argc, sqlite3_value** argv)
{
    assert(argc == 2);
    const char* source1 = (const char*)sqlite3_value_text(argv[0]);
    const char* source2 = (const char*)sqlite3_value_text(argv[1]);
    double distance = Edlib_Distance(source1, source2, true);
    sqlite3_result_double(context, distance);
}

static void iEdlibDistance(sqlite3_context* context, int argc, sqlite3_value** argv)
{
    assert(argc == 2);
    const char* source1 = (const char*)sqlite3_value_text(argv[0]);
    const char* source2 = (const char*)sqlite3_value_text(argv[1]);
    double distance = iEdlibDistance(source1, source2);
    sqlite3_result_double(context, distance);
}


static void HasCharInSameOrder(sqlite3_context* context, int argc, sqlite3_value** argv) {
    assert(argc == 1);
    String^ source = gcnew String((const char*)sqlite3_value_text(argv[0]));
    CString result = FuzzyPlusCSharp::Fuzzy::HasCharInSameOrder(source);
    sqlite3_result_text16(context, result, -1, NULL);
}

static void SetDefaultDistanceMethodByName(sqlite3_context* context, int argc, sqlite3_value** argv) {
	assert(argc == 1);
    const char* source = (char*)sqlite3_value_text(argv[0]);
    if (source == 0) {
        return;
    }
    String^ source1 = gcnew String(source);
    FuzzyPlusCSharp::Fuzzy::SetDefaultDistanceMethod(source1);
    sqlite3_result_text(context, source, -1, NULL);
}

static void SetDefaultDistanceMethod(sqlite3_context* context, int argc, sqlite3_value** argv) {
    assert(argc == 1);
    const unsigned char* ustr = sqlite3_value_text(argv[0]);
    CString result;
    if (isascii(ustr[0]))
    {
        const char* source = (char*)sqlite3_value_text(argv[0]);
        if (source == 0) {
            return;
        }
        String^ source1 = gcnew String(source);
        FuzzyPlusCSharp::Fuzzy::SetDefaultDistanceMethod(source1);
        result = source1;
    }
    else 
    {
        int nIn = sqlite3_value_int(argv[0]);
        FuzzyPlusCSharp::Fuzzy::SetDefaultDistanceMethod(nIn);
        result = FuzzyPlusCSharp::Fuzzy::GetDistanceMethodName(nIn);
    }
    sqlite3_result_text16(context, result, -1, NULL);
}

static void SetDefaultDistanceMethodByID(sqlite3_context* context, int argc, sqlite3_value** argv) {
    assert(argc == 1);
    int nIn = sqlite3_value_int(argv[0]);
    FuzzyPlusCSharp::Fuzzy::SetDefaultDistanceMethod(nIn);
    CString result = FuzzyPlusCSharp::Fuzzy::GetDistanceMethodName(nIn);
    sqlite3_result_text16(context, result, -1, NULL);
}

static FuzzyPlusCSharp::Fuzzy::DistanceMethod GetDistanceMethod(std::string str_DistanceMethod)
{
    String^ strDistanceMethod = gcnew String(str_DistanceMethod.c_str());
    FuzzyPlusCSharp::Fuzzy::DistanceMethod distanceMethod = FuzzyPlusCSharp::Fuzzy::GetDistanceMethod(strDistanceMethod);
    return distanceMethod;
}

static FuzzyPlusCSharp::Fuzzy::DistanceMethod GetDistanceMethod(int iDistanceMethod)
{
    FuzzyPlusCSharp::Fuzzy::DistanceMethod distanceMethod = FuzzyPlusCSharp::Fuzzy::GetDistanceMethod(iDistanceMethod);
    return distanceMethod;
}

static double HowSimilar(std::string source1, std::string source2, FuzzyPlusCSharp::Fuzzy::DistanceMethod distanceMethod = FuzzyPlusCSharp::Fuzzy::DistanceMethod::UseDefaultDistanceMethod)
{
    double length = (double)max(source1.length(), source2.length());
    switch (distanceMethod) 
    {
    case FuzzyPlusCSharp::Fuzzy::DistanceMethod::Fuzzy_Damlev:
    default:
        return GetPercentage((double)damerau_levenshtein(source1.c_str(), source2.c_str()), length);
    case FuzzyPlusCSharp::Fuzzy::DistanceMethod::Fuzzy_Hamming:
        return GetPercentage((double)hamming(source1.c_str(), source2.c_str()), length);
    case FuzzyPlusCSharp::Fuzzy::DistanceMethod::Fuzzy_Jarowin:
        return jaro_winkler(source1.c_str(), source2.c_str());
    case FuzzyPlusCSharp::Fuzzy::DistanceMethod::Fuzzy_Leven:
        return GetPercentage((double)levenshtein(source1.c_str(), source2.c_str()), length);
    case FuzzyPlusCSharp::Fuzzy::DistanceMethod::Fuzzy_Osadist:
        return GetPercentage((double)optimal_string_alignment(source1.c_str(), source2.c_str()), length);
    case FuzzyPlusCSharp::Fuzzy::DistanceMethod::Fuzzy_Editdist:
        return edit_distance(source1.c_str(), source2.c_str(), 0);
    case FuzzyPlusCSharp::Fuzzy::DistanceMethod::Fuzzy_Jaro:
        return jaro_distance(source1.c_str(), source2.c_str());
    case FuzzyPlusCSharp::Fuzzy::DistanceMethod::EdlibDistance:
        return GetPercentage(Edlib_Distance(source1.c_str(), source2.c_str(), true), length);
    case FuzzyPlusCSharp::Fuzzy::DistanceMethod::iEdlibDistance:
        return GetPercentage(Edlib_Distance(source1.c_str(), source2.c_str(), false), length);
    }
    return 1.0f;
}

static double HowSimilar(std::string source1, std::string source2, std::string str_DistanceMethod){
    return HowSimilar(source1, source2, GetDistanceMethod(str_DistanceMethod));
}

static double HowSimilar(std::string source1, std::string source2, int iDistanceMethod){
    return HowSimilar(source1, source2, GetDistanceMethod(iDistanceMethod));
}

static bool GetIsCSharpFuzzy(FuzzyPlusCSharp::Fuzzy::DistanceMethod distanceMethod) {
    return ((int)distanceMethod < FuzzyPlusCSharp::Fuzzy::CPP_ONLY_FUZZY || (int)distanceMethod > FuzzyPlusCSharp::Fuzzy::CASE_INSENSITIVE);
}

static bool GetIsCSharpFuzzy(std::string str_DistanceMethod) {
    return GetIsCSharpFuzzy(GetDistanceMethod(str_DistanceMethod));
}

static bool GetIsCSharpFuzzy(int iDistanceMethod) {
    return GetIsCSharpFuzzy(GetDistanceMethod(iDistanceMethod));
}

static void HowSimilar(sqlite3_context* context, int argc, sqlite3_value** argv)
{
    assert(argc == 2 || argc == 3);
    const char* str1 = (const char*)sqlite3_value_text(argv[0]);
    const char* str2 = (const char*)sqlite3_value_text(argv[1]);
    String^ source1 = gcnew String(str1);
    String^ source2 = gcnew String(str2);
    double distance = 0.0f;
    if (argc == 3) 
    {
        const unsigned char* ustr3 = sqlite3_value_text(argv[2]);
        if (isascii(ustr3[0]))
        {
            const char* str3 = (const char*)sqlite3_value_text(argv[2]);
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
        bool isCSharpFuzzy = GetIsCSharpFuzzy(FuzzyPlusCSharp::Fuzzy::DefaultDistanceMethod);
        distance = isCSharpFuzzy ? FuzzyPlusCSharp::Fuzzy::HowSimilar(source1, source2, 0) : HowSimilar(str1, str2, FuzzyPlusCSharp::Fuzzy::DistanceMethod::UseDefaultDistanceMethod);
    }
    sqlite3_result_double(context, distance);
}


static void HowSimilarByName(sqlite3_context* context, int argc, sqlite3_value** argv) {
    assert(argc == 3);
    HowSimilar(context, argc, argv);
}

static void SetDefaultSameSoundMethod(sqlite3_context* context, int argc, sqlite3_value** argv) {
    assert(argc == 1);
    const unsigned char* ustr = sqlite3_value_text(argv[0]);
    CString result;
    if (isascii(ustr[0]))
    {
        const char* source = (char*)sqlite3_value_text(argv[0]);
        if (source == 0) {
            return;
        }
        String^ source1 = gcnew String(source);
        FuzzyPlusCSharp::Fuzzy::SetDefaultSameSoundMethod(source1);
        result = source1;
    }
    else
    {
        int nIn = sqlite3_value_int(argv[0]);
        FuzzyPlusCSharp::Fuzzy::SetDefaultSameSoundMethod(nIn);
        result = FuzzyPlusCSharp::Fuzzy::GetSameSoundMethodName(nIn);
    }
    sqlite3_result_text16(context, result, -1, NULL);
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

static bool Compare(const char* source1, const char* source2, FuzzyPlusCSharp::Fuzzy::DistanceMethod CompareMethod, bool isVerySimilar = true)
{
    String^ s1;
    String^ s2;
    switch (CompareMethod)
    {
    case FuzzyPlusCSharp::Fuzzy::DistanceMethod::SameSound_StrCmp:
        return strcmp(source1, source2) == 0;
    default:
        s1 = gcnew String(source1);
        s2 = gcnew String(source2);
        return isVerySimilar ? FuzzyPlusCSharp::Fuzzy::IsVerySimilar(s1, s2, CompareMethod) : FuzzyPlusCSharp::Fuzzy::IsSimilar(s1, s2, CompareMethod);
    }
}

static bool SameSound(std::string source1, std::string source2, 
    FuzzyPlusCSharp::Fuzzy::SameSoundMethod sameSoundMethod = FuzzyPlusCSharp::Fuzzy::SameSoundMethod::UseDefaultSameSoundMethod,
    FuzzyPlusCSharp::Fuzzy::DistanceMethod distanceMethod = FuzzyPlusCSharp::Fuzzy::DistanceMethod::SameSound_StrCmp, 
    bool isVerySimilar = true)
{
    double length = (double)max(source1.length(), source2.length());
    char* s1 = NULL;
    char* s2 = NULL;
    bool results = false;
    switch (sameSoundMethod)
    {
    case FuzzyPlusCSharp::Fuzzy::SameSoundMethod::fuzzy_caver:
        s1 = caverphone((const char*)source1.c_str());
        s2 = caverphone((const char*)source2.c_str());
        results = Compare(s1, s2, distanceMethod, isVerySimilar);
        break;
    case FuzzyPlusCSharp::Fuzzy::SameSoundMethod::fuzzy_phonetic:
        s1 = (char*)phonetic_hash((const unsigned char*)source1.c_str(), (int)source1.length());
        s2 = (char*)phonetic_hash((const unsigned char*)source2.c_str(), (int)source2.length());
        results = Compare(s1, s2, distanceMethod, isVerySimilar);
        break;
    case FuzzyPlusCSharp::Fuzzy::SameSoundMethod::fuzzy_soundex:
        s1 = soundex((const char*)source1.c_str());
        s2 = soundex((const char*)source2.c_str());
        results = Compare(s1, s2, distanceMethod, isVerySimilar);
        break;
    case FuzzyPlusCSharp::Fuzzy::SameSoundMethod::fuzzy_rsoundex:
        s1 = refined_soundex((const char*)source1.c_str());
        s2 = refined_soundex((const char*)source2.c_str());
        results = Compare(s1, s2, distanceMethod, isVerySimilar);
        break;
    case FuzzyPlusCSharp::Fuzzy::SameSoundMethod::fuzzy_translit:
        s1 = (char*)transliterate((const unsigned char*)source1.c_str(), (int)source1.length());
        s2 = (char*)transliterate((const unsigned char*)source2.c_str(), (int)source2.length());
        results = Compare(s1, s2, distanceMethod, isVerySimilar);
        break;
    case FuzzyPlusCSharp::Fuzzy::SameSoundMethod::Caverphone2:
    case FuzzyPlusCSharp::Fuzzy::SameSoundMethod::Soundex2:
    case FuzzyPlusCSharp::Fuzzy::SameSoundMethod::EnPhoneticDistance:
        default:
        String^ s1 = gcnew String(source1.c_str());
        String^ s2 = gcnew String(source2.c_str());
        return FuzzyPlusCSharp::Fuzzy::SameSound(s1, s2, sameSoundMethod, distanceMethod, isVerySimilar);
    }
    free(s1);
    free(s2);
    return results;
}

static void SameSound(sqlite3_context* context, int argc, sqlite3_value** argv)
{
    assert(argc > 1 && argc < 6);
    const char* source1 = (const char*)sqlite3_value_text(argv[0]);
    const char* source2 = (const char*)sqlite3_value_text(argv[1]);
    bool isSameSound = false;
    if (argc > 2)
    {
        FuzzyPlusCSharp::Fuzzy::DistanceMethod distanceMethod = FuzzyPlusCSharp::Fuzzy::DistanceMethod::SameSound_StrCmp;
        bool isVerySimilar = true;
        if (argc > 3) 
        {
            const unsigned char* ustr4 = sqlite3_value_text(argv[3]);
            if (isascii(ustr4[0]))
                distanceMethod = GetDistanceMethod((const char*)ustr4);
            else
            {
                int nIn = sqlite3_value_int(argv[3]);
                distanceMethod = GetDistanceMethod(nIn);
            }
            if (argc > 4)
            {
                int nIn = sqlite3_value_int(argv[4]);
                isVerySimilar = nIn == 1;
            }
        }
        const unsigned char* ustr3 = sqlite3_value_text(argv[2]);
        if (isascii(ustr3[0]))
            isSameSound = SameSound(source1, source2, GetSameSoundMethod((const char*)ustr3), distanceMethod, isVerySimilar);
        else
        {
            int nIn = sqlite3_value_int(argv[2]);
            isSameSound = SameSound(source1, source2, GetSameSoundMethod(nIn), distanceMethod, isVerySimilar);
        }
    }
    else
        isSameSound = SameSound(source1, source2);
    sqlite3_result_int(context, isSameSound);
}

static double Distance(std::string source1, std::string source2, FuzzyPlusCSharp::Fuzzy::DistanceMethod distanceMethod = FuzzyPlusCSharp::Fuzzy::DistanceMethod::UseDefaultDistanceMethod)
{
    switch (distanceMethod)
    {
    case FuzzyPlusCSharp::Fuzzy::DistanceMethod::Fuzzy_Damlev:
    default:
        return (double)damerau_levenshtein(source1.c_str(), source2.c_str());
    case FuzzyPlusCSharp::Fuzzy::DistanceMethod::Fuzzy_Hamming:
        return (double)hamming(source1.c_str(), source2.c_str());
    case FuzzyPlusCSharp::Fuzzy::DistanceMethod::Fuzzy_Jarowin:
        return jaro_winkler(source1.c_str(), source2.c_str());
    case FuzzyPlusCSharp::Fuzzy::DistanceMethod::Fuzzy_Leven:
        return (double)levenshtein(source1.c_str(), source2.c_str());
    case FuzzyPlusCSharp::Fuzzy::DistanceMethod::Fuzzy_Osadist:
        return (double)optimal_string_alignment(source1.c_str(), source2.c_str());
    case FuzzyPlusCSharp::Fuzzy::DistanceMethod::Fuzzy_Editdist:
        return edit_distance(source1.c_str(), source2.c_str(), 0);
    case FuzzyPlusCSharp::Fuzzy::DistanceMethod::Fuzzy_Jaro:
        return jaro_distance(source1.c_str(), source2.c_str());
    case FuzzyPlusCSharp::Fuzzy::DistanceMethod::EdlibDistance:
        return Edlib_Distance(source1.c_str(), source2.c_str(), true);
    case FuzzyPlusCSharp::Fuzzy::DistanceMethod::iEdlibDistance:
        return Edlib_Distance(source1.c_str(), source2.c_str(), false);
    }
    return 1.0f;
}

static double Distance(std::string source1, std::string source2, std::string str_DistanceMethod) {
    return Distance(source1, source2, GetDistanceMethod(str_DistanceMethod));
}

static double Distance(std::string source1, std::string source2, int iDistanceMethod) {
    return Distance(source1, source2, GetDistanceMethod(iDistanceMethod));
}
static void Distance(sqlite3_context* context, int argc, sqlite3_value** argv)
{
    assert(argc == 2 || argc == 3);
    const char* str1 = (const char*)sqlite3_value_text(argv[0]);
    const char* str2 = (const char*)sqlite3_value_text(argv[1]);
    String^ source1 = gcnew String(str1);
    String^ source2 = gcnew String(str2);
    double distance = 0.0f;
    if (argc == 3) 
    {
        const unsigned char* ustr3 = sqlite3_value_text(argv[2]);
        if (isascii(ustr3[0]))
        {
            const char* str3 = (const char*)sqlite3_value_text(argv[2]);
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
        bool isCSharpFuzzy = GetIsCSharpFuzzy(FuzzyPlusCSharp::Fuzzy::DefaultDistanceMethod);
        distance = isCSharpFuzzy ? FuzzyPlusCSharp::Fuzzy::Distance(source1, source2, 0) : Distance(str1, str2, FuzzyPlusCSharp::Fuzzy::DistanceMethod::UseDefaultDistanceMethod);
    }
    sqlite3_result_double(context, distance);
}

static void RegexReplace(sqlite3_context* context, int argc, sqlite3_value** argv) {
    assert(argc == 3);
    String^ source = gcnew String((const char*)sqlite3_value_text(argv[0]));
    String^ pattern = gcnew String((const char*)sqlite3_value_text(argv[1]));
    const char* str3 = (const char*)sqlite3_value_text(argv[2]);
    String^ replacement = gcnew String(str3);
    CString result(FuzzyPlusCSharp::Fuzzy::RegexReplace(source, pattern, replacement));
    sqlite3_result_text16(context, result, -1, NULL);
}

static void RegexSearch(sqlite3_context* context, int argc, sqlite3_value** argv) {
    assert(argc == 2 || argc == 3);
    String^ source = gcnew String((const char*)sqlite3_value_text(argv[0]));
    String^ pattern = gcnew String((const char*)sqlite3_value_text(argv[1]));
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
    const char* str1 = (const char*)sqlite3_value_text(argv[0]);
    const char* str2 = (const char*)sqlite3_value_text(argv[1]);
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
        const unsigned char* ustr3 = sqlite3_value_text(argv[2]);
        double distance = 0.0f;
        if (isascii(ustr3[0]))
        {
            const char* str3 = (const char*)sqlite3_value_text(argv[2]);
            String^ sourc3 = gcnew String(str3);
            distance = GetIsCSharpFuzzy(str3) ? FuzzyPlusCSharp::Fuzzy::HowSimilar(source1, source2, sourc3) : HowSimilar(str1, str2, str3);
        }
        else
        {
            int nIn = sqlite3_value_int(argv[2]);
            distance = GetIsCSharpFuzzy(nIn) ? FuzzyPlusCSharp::Fuzzy::HowSimilar(source1, source2, nIn) : HowSimilar(str1, str2, nIn);
        }
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
    const char* str1 = (const char*)sqlite3_value_text(argv[0]);
    const char* str2 = (const char*)sqlite3_value_text(argv[1]);
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
        const unsigned char* ustr3 = sqlite3_value_text(argv[2]);
        double distance = 0.0f;
        if (isascii(ustr3[0]))
        {
            const char* str3 = (const char*)sqlite3_value_text(argv[2]);
            String^ sourc3 = gcnew String(str3);
            distance = GetIsCSharpFuzzy(str3) ? FuzzyPlusCSharp::Fuzzy::HowSimilar(source1, source2, sourc3) : HowSimilar(str1, str2, str3);
        }
        else
        {
            int nIn = sqlite3_value_int(argv[2]);
            distance = GetIsCSharpFuzzy(nIn) ? FuzzyPlusCSharp::Fuzzy::HowSimilar(source1, source2, nIn) : HowSimilar(str1, str2, nIn);
        }
        sqlite3_result_double(context, distance);
    }
    free(s1);
    free(s2);
}

static void Caverphone2(sqlite3_context* context, int argc, sqlite3_value** argv) {
    assert(argc == 1 || argc == 2);
    const char* str1 = (const char*)sqlite3_value_text(argv[0]);
    if (str1 == 0) {

        sqlite3_result_error(context, "arguments should not be NULL", -1);
        return;
    }
    String^ source1 = gcnew String(str1);
    if (argc == 2)
    {
        const char* str2 = (const char*)sqlite3_value_text(argv[1]);
        String^ source2 = gcnew String(str2);
        int results = FuzzyPlusCSharp::Fuzzy::Caverphone2(source1, source2, FuzzyPlusCSharp::Fuzzy::DistanceMethod::SameSound_StrCmp, true);
        sqlite3_result_int(context, results);
        return;
    }
    CString result = FuzzyPlusCSharp::Fuzzy::Caverphone2(source1);
    sqlite3_result_text16(context, result, -1, NULL);
}

static void Soundex2(sqlite3_context* context, int argc, sqlite3_value** argv) {
    assert(argc == 1 || argc == 2);
    const char* str1 = (const char*)sqlite3_value_text(argv[0]);
    if (str1 == 0) {

        sqlite3_result_error(context, "arguments should not be NULL", -1);
        return;
    }
    String^ source1 = gcnew String(str1);
    if (argc == 2)
    {
        const char* str2 = (const char*)sqlite3_value_text(argv[1]);
        String^ source2 = gcnew String(str2);
        int results = FuzzyPlusCSharp::Fuzzy::Soundex2(source1, source2, FuzzyPlusCSharp::Fuzzy::DistanceMethod::SameSound_StrCmp, true);
        sqlite3_result_int(context, results);
        return;
    }
    CString result = FuzzyPlusCSharp::Fuzzy::Soundex2(source1);
    sqlite3_result_text16(context, result, -1, NULL);
}


CREATE_FUNCTION(LevenshteinDistance);
CREATE_FUNCTION(DamerauLevenshteinDistance);
CREATE_FUNCTION(EditDistance);
CREATE_FUNCTION_FLOAT(JaroWinklerDistance);
CREATE_FUNCTION_FLOAT(OverlapCoefficientDistance);
CREATE_FUNCTION_FLOAT(JaccardDistance);
CREATE_FUNCTION_FLOAT(SorensenDiceDistance);
CREATE_FUNCTION_FLOAT(RatcliffObershelpSimilarityDistance);
CREATE_FUNCTION_FLOAT(HammingDistance);
CREATE_FUNCTION_FLOAT(LongestCommonSubstringDistance);
CREATE_FUNCTION_FLOAT(LongestCommonSubsequenceDistance);
CREATE_FUNCTION_FLOAT(JaroDistance);
CREATE_FUNCTION_FLOAT(NormalizedLevenshteinDistance);
CREATE_FUNCTION_FLOAT(Levenshtein2Distance);
CREATE_FUNCTION_FLOAT(TanimotoCoefficientDistance);
CREATE_FUNCTION_DISTANCE(IsNotSimilar);
CREATE_FUNCTION_DISTANCE(IsVerySimilar);
CREATE_FUNCTION_DISTANCE(IsSimilar);
CREATE_FUNCTION_DISTANCE(IsSomeWhatSimilar);
CREATE_FUNCTION_DISTANCE(IsSlightlySimilar);
CREATE_FUNCTION_DISTANCE(IsHardlySimilar);
CREATE_FUNCTION2(PhraseSimplifiedDiff);
CREATE_FUNCTION2(PhraseVerySimilar);
CREATE_FUNCTION2(PhraseSimilar);
CREATE_FUNCTION2(PhraseSomeWhatSimilar);
CREATE_FUNCTION2(PhraseSlightlySimilar);
CREATE_FUNCTION2(PhraseHardlySimilar);

CREATE_FUNCTION_STR_RETURN(StringReverse);
CREATE_FUNCTION_STR_RETURN(GetFileName);
CREATE_FUNCTION_STR_RETURN(GetExtension);
CREATE_FUNCTION_STR_RETURN(GetDirectoryName);
CREATE_FUNCTION_STR_RETURN(GetFileNameWithoutExtension);

CREATE_FUNCTION_INT_RETURN(IsFileExist);
CREATE_FUNCTION_INT_RETURN(IsDirExist);
CREATE_FUNCTION2(RegexMatch);

namespace SqliteFuzzyPlusExtension {
    public ref class Fuzzy
    {
        static int DamLev(std::string str1, std::string str2, bool isCaseSensitive) {
            String^ source1 = gcnew String(str1.c_str());
            String^ source2 = gcnew String(str2.c_str());
            int distance = FuzzyPlusCSharp::Fuzzy::DamerauLevenshteinDistance(source1, source2, isCaseSensitive);
            return distance;
        }
        static int DamLev(std::string source1, std::string source2) {
            return DamLev(source1, source2, TRUE);
        }
        static double HowSimilar(std::string source1, std::string source2, int iDistanceMethod) {
            return ::HowSimilar(source1, source2, GetDistanceMethod(iDistanceMethod));
        }
        static double Distance(std::string source1, std::string source2, int iDistanceMethod) {
            return ::Distance(source1, source2, GetDistanceMethod(iDistanceMethod));
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
        //FuzzyPlusCSharp::Fuzzy::DistanceMethod d = FuzzyPlusCSharp::Fuzzy::DistanceMethod::UseDefaultDistanceMethod;

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
        SQLITE3_CREATE_FUNCTION2(iEdlibDistance);
        SQLITE3_CREATE_FUNCTION2(EditDistance);
        SQLITE3_CREATE_FUNCTION2(SameName);
        SQLITE3_CREATE_FUNCTION2(Caverphone2);
        SQLITE3_CREATE_FUNCTION1(Caverphone2);
        SQLITE3_CREATE_FUNCTION2(Soundex2);
        SQLITE3_CREATE_FUNCTION1(Soundex2);

        // Methods to set default distance functions either by name (string) or by ID (integer)
        SQLITE3_CREATE_FUNCTION1(SetDefaultDistanceMethod);
        SQLITE3_CREATE_FUNCTION1(SetDefaultDistanceMethodByName);
        SQLITE3_CREATE_FUNCTION1(SetDefaultDistanceMethodByID);

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
        SQLITE3_CREATE_FUNCTION_ALIAS2(iEdlib, iEdlibDistance);
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

/////////////////////////////////////////////////////////////////////////////////
// Export Distance Functions
__declspec(dllexport)
int DamerauLevenshteinDistance(const char* str1, const char* str2) {
        String^ source1 = gcnew String(str1);
        String^ source2 = gcnew String(str2);
        int distance = FuzzyPlusCSharp::Fuzzy::DamerauLevenshteinDistance(source1, source2, TRUE);
        return distance;
}

__declspec(dllexport)
int LevenshteinDistance(const char* str1, const char* str2) {
    String^ source1 = gcnew String(str1);
    String^ source2 = gcnew String(str2);
    int distance = FuzzyPlusCSharp::Fuzzy::LevenshteinDistance(source1, source2, TRUE);
    return distance;
}

__declspec(dllexport)
double HammingDistance(const char* str1, const char* str2) {
    String^ source1 = gcnew String(str1);
    String^ source2 = gcnew String(str2);
    double distance = FuzzyPlusCSharp::Fuzzy::HammingDistance(source1, source2, TRUE);
    return distance;
}

__declspec(dllexport)
double JaccardDistance(const char* str1, const char* str2) {
    String^ source1 = gcnew String(str1);
    String^ source2 = gcnew String(str2);
    double distance = FuzzyPlusCSharp::Fuzzy::JaccardDistance(source1, source2, TRUE);
    return distance;
}

__declspec(dllexport)
double JaroDistance(const char* str1, const char* str2) {
    String^ source1 = gcnew String(str1);
    String^ source2 = gcnew String(str2);
    double distance = FuzzyPlusCSharp::Fuzzy::JaroDistance(source1, source2, TRUE);
    return distance;
}

__declspec(dllexport)
double JaroWinklerDistance(const char* str1, const char* str2) {
    String^ source1 = gcnew String(str1);
    String^ source2 = gcnew String(str2);
    double distance = FuzzyPlusCSharp::Fuzzy::JaroWinklerDistance(source1, source2, TRUE);
    return distance;
}

__declspec(dllexport)
double Levenshtein2Distance(const char* str1, const char* str2) {
    String^ source1 = gcnew String(str1);
    String^ source2 = gcnew String(str2);
    double distance = FuzzyPlusCSharp::Fuzzy::Levenshtein2Distance(source1, source2, TRUE);
    return distance;
}

__declspec(dllexport)
double LongestCommonSubsequenceDistance(const char* str1, const char* str2) {
    String^ source1 = gcnew String(str1);
    String^ source2 = gcnew String(str2);
    double distance = FuzzyPlusCSharp::Fuzzy::LongestCommonSubsequenceDistance(source1, source2, TRUE);
    return distance;
}

__declspec(dllexport)
double LongestCommonSubstringDistance(const char* str1, const char* str2) {
    String^ source1 = gcnew String(str1);
    String^ source2 = gcnew String(str2);
    double distance = FuzzyPlusCSharp::Fuzzy::LongestCommonSubstringDistance(source1, source2, TRUE);
    return distance;
}

__declspec(dllexport)
double NormalizedLevenshteinDistance(const char* str1, const char* str2) {
    String^ source1 = gcnew String(str1);
    String^ source2 = gcnew String(str2);
    double distance = FuzzyPlusCSharp::Fuzzy::NormalizedLevenshteinDistance(source1, source2, TRUE);
    return distance;
}

__declspec(dllexport)
double OverlapCoefficientDistance(const char* str1, const char* str2) {
    String^ source1 = gcnew String(str1);
    String^ source2 = gcnew String(str2);
    double distance = FuzzyPlusCSharp::Fuzzy::OverlapCoefficientDistance(source1, source2, TRUE);
    return distance;
}

__declspec(dllexport)
int PhraseSimplifiedDiff(const char* str1, const char* str2) {
    String^ source1 = gcnew String(str1);
    String^ source2 = gcnew String(str2);
    int distance = FuzzyPlusCSharp::Fuzzy::PhraseSimplifiedDiff(source1, source2);
    return distance;
}

__declspec(dllexport)
double RatcliffObershelpSimilarityDistance(const char* str1, const char* str2) {
    String^ source1 = gcnew String(str1);
    String^ source2 = gcnew String(str2);
    double distance = FuzzyPlusCSharp::Fuzzy::RatcliffObershelpSimilarityDistance(source1, source2, TRUE);
    return distance;
}

__declspec(dllexport)
double SorensenDiceDistance(const char* str1, const char* str2) {
    String^ source1 = gcnew String(str1);
    String^ source2 = gcnew String(str2);
    double distance = FuzzyPlusCSharp::Fuzzy::SorensenDiceDistance(source1, source2, TRUE);
    return distance;
}

__declspec(dllexport)
double TanimotoCoefficientDistance(const char* str1, const char* str2) {
    String^ source1 = gcnew String(str1);
    String^ source2 = gcnew String(str2);
    double distance = FuzzyPlusCSharp::Fuzzy::TanimotoCoefficientDistance(source1, source2, TRUE);
    return distance;
}

__declspec(dllexport)
double EdlibDistance(const char* source1, const char* source2) {
    return Edlib_Distance(source1, source2, true);
}

// Export Edlib fuzzy Distance Functions
__declspec(dllexport)
double iEdlibDistance(const char* source1, const char* source2) {
    return Edlib_Distance(source1, source2, false);
}

// Export SQLean fuzzy Distance Functions
__declspec(dllexport)
unsigned fuzzy_damlev(const char* source1, const char* source2) {
    return damerau_levenshtein(source1, source2);
}

__declspec(dllexport)
int fuzzy_editdist(const char* source1, const char* source2) {
    return edit_distance(source1, source2, 0);
}

__declspec(dllexport)
int fuzzy_hamming(const char* source1, const char* source2) {
    return hamming(source1, source2);
}

__declspec(dllexport)
double fuzzy_jarowin(const char* source1, const char* source2) {
    return jaro_winkler(source1, source2);
}

__declspec(dllexport)
unsigned fuzzy_leven(const char* source1, const char* source2) {
    return levenshtein(source1, source2);
}

__declspec(dllexport)
unsigned fuzzy_osadist(const char* source1, const char* source2) {
    return optimal_string_alignment(source1, source2);
}


/////////////////////////////////////////////////////////////////////////////////
// Export Wrapper Distance Functions
__declspec(dllexport)
SqliteFuzzyPlusExtension::DistanceMethod_ID SetDefaultDistanceMethod(const char* DistanceMethod_Name) {
    String^ source1 = gcnew String(DistanceMethod_Name);
    FuzzyPlusCSharp::Fuzzy::SetDefaultDistanceMethod(source1);
    return (SqliteFuzzyPlusExtension::DistanceMethod_ID)FuzzyPlusCSharp::Fuzzy::DefaultDistanceMethod;
}

__declspec(dllexport)
SqliteFuzzyPlusExtension::DistanceMethod_ID SetDefaultDistanceMethod(int DistanceMethod_Id) {
    FuzzyPlusCSharp::Fuzzy::SetDefaultDistanceMethod(DistanceMethod_Id);
    return (SqliteFuzzyPlusExtension::DistanceMethod_ID)FuzzyPlusCSharp::Fuzzy::DefaultDistanceMethod;
}

__declspec(dllexport)
double Distance(const char* source1, const char* source2, int DistanceMethod_Id) {
    return Distance(source1, source2, GetDistanceMethod(DistanceMethod_Id));
}

__declspec(dllexport)
double Distance(const char* source1, const char* source2, const char* DistanceMethod_Name) {
    return Distance(source1, source2, GetDistanceMethod(DistanceMethod_Name));
}

__declspec(dllexport)
double HowSimilar(const char* source1, const char* source2, int DistanceMethod_Id) {
    return HowSimilar(source1, source2, GetDistanceMethod(DistanceMethod_Id));
}

__declspec(dllexport)
double HowSimilar(const char* source1, const char* source2, const char* DistanceMethod_Name) {
    return HowSimilar(source1, source2, GetDistanceMethod(DistanceMethod_Name));
}

/////////////////////////////////////////////////////////////////////////////////
// Export Phonetic Functions
__declspec(dllexport)
bool EnPhoneticDistance(const char* str1, const char* str2) {
    String^ source1 = gcnew String(str1);
    String^ source2 = gcnew String(str2);
    bool distance = FuzzyPlusCSharp::Fuzzy::EnPhoneticDistance(source1, source2, TRUE);
    return distance;
}

__declspec(dllexport)
bool Caverphone2(const char* str1, const char* str2) {
    String^ source1 = gcnew String(str1);
    String^ source2 = gcnew String(str2);
    bool distance = FuzzyPlusCSharp::Fuzzy::Caverphone2(source1, source2);
    return distance;
}

__declspec(dllexport)
bool Soundex2(const char* str1, const char* str2) {
    String^ source1 = gcnew String(str1);
    String^ source2 = gcnew String(str2);
    bool distance = FuzzyPlusCSharp::Fuzzy::Soundex2(source1, source2);
    return distance;
}

__declspec(dllexport)
std::string fuzzy_caver(const char* source) {
    char* value = caverphone(source);
    std::string returnValue = value;
    free(value);
    return returnValue;
}

__declspec(dllexport)
bool fuzzy_caver(const char* source1, const char* source2) {
    std::string s1 = fuzzy_caver(source1);
    std::string s2 = fuzzy_caver(source2);
    return s1 == s2;
}

__declspec(dllexport)
std::string fuzzy_phonetic(const char* source) {
    char* value = (char*)phonetic_hash((const unsigned char*)source, (int)strlen(source));
    std::string returnValue = value;
    free(value);
    return returnValue;
}

__declspec(dllexport)
bool fuzzy_phonetic(const char* source1, const char* source2) {
    std::string s1 = fuzzy_phonetic(source1);
    std::string s2 = fuzzy_phonetic(source2);
    return s1 == s2;
}

__declspec(dllexport)
std::string fuzzy_rsoundex(const char* source) {
    char* value = refined_soundex(source);
    std::string returnValue = value;
    free(value);
    return returnValue;
}
__declspec(dllexport)
bool fuzzy_rsoundex(const char* source1, const char* source2) {
    std::string s1 = fuzzy_rsoundex(source1);
    std::string s2 = fuzzy_rsoundex(source2);
    return s1 == s2;
}

__declspec(dllexport)
std::string fuzzy_soundex(const char* source) {
    char* value = soundex(source);
    std::string returnValue = value;
    free(value);
    return returnValue;
}
__declspec(dllexport)
bool fuzzy_soundex(const char* source1, const char* source2) {
    std::string s1 = fuzzy_soundex(source1);
    std::string s2 = fuzzy_soundex(source2);
    return s1 == s2;
}

__declspec(dllexport)
std::string fuzzy_translit(const char* source) {
    char* value = (char*)transliterate((const unsigned char*)source, (int)strlen(source));
    std::string returnValue = value;
    free(value);
    return returnValue;
}
__declspec(dllexport)
bool fuzzy_translit(const char* source1, const char* source2) {
    std::string s1 = fuzzy_translit(source1);
    std::string s2 = fuzzy_translit(source2);
    return s1 == s2;
}

__declspec(dllexport)
int fuzzy_caver(const char* source, char* distBuffer, int bufferSize)
{
    std::string s = fuzzy_caver(source);
    if (s.length() + 1 > bufferSize)
        return (int)s.length() + 1;
    strcpy_s(distBuffer, bufferSize, s.c_str());
    return 0;
}

__declspec(dllexport)
int fuzzy_phonetic(const char* source, char* distBuffer, int bufferSize)
{
    std::string s = fuzzy_phonetic(source);
    if (s.length() + 1 > bufferSize)
        return (int)s.length() + 1;
    strcpy_s(distBuffer, bufferSize, s.c_str());
    return 0;
}

__declspec(dllexport)
int fuzzy_rsoundex(const char* source, char* distBuffer, int bufferSize)
{
    std::string s = fuzzy_rsoundex(source);
    if (s.length() + 1 > bufferSize)
        return (int)s.length() + 1;
    strcpy_s(distBuffer, bufferSize, s.c_str());
    return 0;
}

__declspec(dllexport)
int fuzzy_soundex(const char* source, char* distBuffer, int bufferSize)
{
    std::string s = fuzzy_soundex(source);
    if (s.length() + 1 > bufferSize)
        return (int)s.length() + 1;
    strcpy_s(distBuffer, bufferSize, s.c_str());
    return 0;
}

__declspec(dllexport)
int fuzzy_translit(const char* source, char* distBuffer, int bufferSize)
{
    std::string s = fuzzy_translit(source);
    if (s.length() + 1 > bufferSize)
        return (int)s.length() + 1;
    strcpy_s(distBuffer, bufferSize, s.c_str());
    return 0;
}

__declspec(dllexport)
bool SameSound(const char* source1, const char* source2, int SameSoundMethod_Id, int DistanceMethod_Id, bool isVerySimilar) {
    return SameSound(source1, source2, GetSameSoundMethod(SameSoundMethod_Id), GetDistanceMethod(DistanceMethod_Id), isVerySimilar);
}

__declspec(dllexport)
bool SameSound(const char* source1, const char* source2, const char* SameSoundMethod_Name, const char* DistanceMethod_Name, bool isVerySimilar) {
    return SameSound(source1, source2, GetSameSoundMethod(SameSoundMethod_Name), GetDistanceMethod(DistanceMethod_Name), isVerySimilar);
}

__declspec(dllexport)
bool SameSound(const char* source1, const char* source2, int SameSoundMethod_Id, int DistanceMethod_Id) {
    return SameSound(source1, source2, GetSameSoundMethod(SameSoundMethod_Id), GetDistanceMethod(DistanceMethod_Id), true);
}

__declspec(dllexport)
bool SameSound(const char* source1, const char* source2, const char* SameSoundMethod_Name, const char* DistanceMethod_Name) {
    return SameSound(source1, source2, GetSameSoundMethod(SameSoundMethod_Name), GetDistanceMethod(DistanceMethod_Name), true);
}

/////////////////////////////////////////////////////////////////////////////////
// Export Regex Functions
__declspec(dllexport)
bool RegexMatch(const char* source, const char* pattern) {
    String^ source1 = gcnew String(source);
    String^ source2 = gcnew String(pattern);
    return FuzzyPlusCSharp::Fuzzy::RegexMatch(source1, source2);
}

__declspec(dllexport)
std::string RegexSearch(const char* source, const char* pattern) {
    String^ source1 = gcnew String(source);
    String^ source2 = gcnew String(pattern);
    CString results = FuzzyPlusCSharp::Fuzzy::RegexSearch(source1, source2);
    CT2CA pszConvertedAnsiString(results);
    std::string returnValue = pszConvertedAnsiString;
    return returnValue;
}

__declspec(dllexport)
std::string RegexReplace(const char* source, const char* pattern, const char* replacement) {
    String^ source1 = gcnew String(source);
    String^ source2 = gcnew String(pattern);
    String^ source3 = gcnew String(replacement);
    CString results = FuzzyPlusCSharp::Fuzzy::RegexReplace(source1, source2, source3);
    CT2CA pszConvertedAnsiString(results);
    std::string returnValue = pszConvertedAnsiString;
    return returnValue;
}

__declspec(dllexport)
char* RegexSearch(const char* source, const char* pattern, char* returnBuffer, int bufferSize)
{
    std::string r = RegexSearch(source, pattern);
    if (r.length() < bufferSize)
    {
        strcpy_s(returnBuffer, bufferSize, r.c_str());
        return returnBuffer;
    }
    return NULL;
}

__declspec(dllexport)
char* RegexReplace(const char* source, const char* pattern, const char* replacement, char* returnBuffer, int bufferSize)
{
    std::string r = RegexReplace(source, pattern, replacement);
    if (r.length() < bufferSize)
    {
        strcpy_s(returnBuffer, bufferSize, r.c_str());
        return returnBuffer;
    }
    return NULL;
}

/////////////////////////////////////////////////////////////////////////////////
// Export Miscellaneous Functions
__declspec(dllexport)
unsigned __int64 NormalizeNum(const char* source) {
    try {
        return convertToInt64(source);
    }
    catch (...) {
        return -1;
    }
}

__declspec(dllexport)
int MaxValue(int source1, int source2) {
    return FuzzyPlusCSharp::Fuzzy::MaxValue(source1, source2);
}

__declspec(dllexport)
int MinValue(int source1, int source2) {
    return FuzzyPlusCSharp::Fuzzy::MinValue(source1, source2);
}

__declspec(dllexport)
int MaxLength(const char* str1, const char* str2) {
    String^ source1 = gcnew String(str1);
    String^ source2 = gcnew String(str2);
    return FuzzyPlusCSharp::Fuzzy::MaxLength(source1, source2);
}

__declspec(dllexport)
int MinLength(const char* str1, const char* str2) {
    String^ source1 = gcnew String(str1);
    String^ source2 = gcnew String(str2);
    return FuzzyPlusCSharp::Fuzzy::MinLength(source1, source2);
}

