#pragma once
#include "sqlite\sqlite3ext.h"
SQLITE_EXTENSION_INIT3
#include "sqlean_fuzzy\extension.h"
using namespace System;

// C++ functions to use with SQLite
void SameName(sqlite3_context* context, int argc, sqlite3_value** argv);
sqlite3_int64 convertToInt64(const std::string& input);
void NormalizeNum(sqlite3_context* context, int argc, sqlite3_value** argv);
void MaxValue(sqlite3_context* context, int argc, sqlite3_value** argv);
void MaxLength(sqlite3_context* context, int argc, sqlite3_value** argv);
void MinValue(sqlite3_context* context, int argc, sqlite3_value** argv);
void MinLength(sqlite3_context* context, int argc, sqlite3_value** argv);
void Caverphone2(sqlite3_context* context, int argc, sqlite3_value** argv);
double GetPercentage(double distance, double length, double full = 1.0f);

#define CREATE_FUNCTION_STR_RETURN(FuncName) static void FuncName(sqlite3_context* context, int argc, sqlite3_value** argv) { \
    assert(argc == 1); \
    const char* source = (char*)sqlite3_value_text(argv[0]); \
    if (source == 0) { \
        return; \
    } \
    String^ sourc1 = gcnew String(source); \
    FuzzyPlusCSharp::Fuzzy::FuncName(sourc1); \
    sqlite3_result_text(context, source, -1, free); \
}

#define CREATE_FUNCTION_INT_RETURN(FuncName) static void FuncName(sqlite3_context* context, int argc, sqlite3_value** argv) { \
    assert(argc == 1); \
    const char* source = (char*)sqlite3_value_text(argv[0]); \
    if (source == 0) { \
        return; \
    } \
    String^ sourc1 = gcnew String(source); \
    int results = FuzzyPlusCSharp::Fuzzy::FuncName(sourc1); \
    sqlite3_result_int(context, results); \
}

#define CREATE_FUNCTION(FuncName) static void FuncName(sqlite3_context* context, int argc, sqlite3_value** argv) { \
assert(argc == 2 || argc == 3); \
bool isCaseSensitive = TRUE; \
const char* str1 = (const char*)sqlite3_value_text(argv[0]); \
const char* str2 = (const char*)sqlite3_value_text(argv[1]); \
if (str1 == 0 || str2 == 0) { \
    sqlite3_result_error(context, "arguments should not be NULL", -1); \
    return; \
} \
if (argc == 3) \
{ \
    int nIn = sqlite3_value_bytes(argv[2]); \
    isCaseSensitive = nIn == 0 ? FALSE : TRUE; \
} \
String^ sourc1 = gcnew String(str1); \
String^ sourc2 = gcnew String(str2); \
unsigned distance = FuzzyPlusCSharp::Fuzzy::FuncName(sourc1, sourc2, isCaseSensitive); \
sqlite3_result_int(context, distance); \
}

#define CREATE_FUNCTION_FLOAT(FuncName) static void FuncName(sqlite3_context* context, int argc, sqlite3_value** argv) { \
assert(argc == 2 || argc == 3); \
bool isCaseSensitive = TRUE; \
const char* str1 = (const char*)sqlite3_value_text(argv[0]); \
const char* str2 = (const char*)sqlite3_value_text(argv[1]); \
if (str1 == 0 || str2 == 0) { \
    sqlite3_result_error(context, "arguments should not be NULL", -1); \
    return; \
} \
if (argc == 3) \
{ \
    int nIn = sqlite3_value_bytes(argv[2]); \
    isCaseSensitive = nIn == 0 ? FALSE : TRUE; \
} \
String^ sourc1 = gcnew String(str1); \
String^ sourc2 = gcnew String(str2); \
double distance = FuzzyPlusCSharp::Fuzzy::FuncName(sourc1, sourc2, isCaseSensitive); \
sqlite3_result_double(context, distance); \
}

#define CREATE_FUNCTION_DISTANCE(FuncName) static void FuncName(sqlite3_context* context, int argc, sqlite3_value** argv) { \
assert(argc == 2 || argc == 3); \
FuzzyPlusCSharp::Fuzzy::DistanceMethod d = FuzzyPlusCSharp::Fuzzy::DistanceMethod::UseDefaultDistanceMethod; \
const char* str1 = (const char*)sqlite3_value_text(argv[0]); \
const char* str2 = (const char*)sqlite3_value_text(argv[1]); \
if (str1 == 0 || str2 == 0) { \
    sqlite3_result_error(context, "arguments should not be NULL", -1); \
    return; \
} \
if (argc == 3) \
{ \
    int nIn = sqlite3_value_bytes(argv[2]); \
    d = FuzzyPlusCSharp::Fuzzy::GetDistanceMethod(nIn); \
} \
String^ sourc1 = gcnew String(str1); \
String^ sourc2 = gcnew String(str2); \
unsigned distance = FuzzyPlusCSharp::Fuzzy::FuncName(sourc1, sourc2, d); \
sqlite3_result_int(context, distance); \
}

#define CREATE_FUNCTION2(FuncName) static void FuncName(sqlite3_context* context, int argc, sqlite3_value** argv) { \
assert(argc == 2); \
const char* str1 = (const char*)sqlite3_value_text(argv[0]); \
const char* str2 = (const char*)sqlite3_value_text(argv[1]); \
if (str1 == 0 || str2 == 0) { \
    sqlite3_result_error(context, "arguments should not be NULL", -1); \
    return; \
} \
String^ sourc1 = gcnew String(str1); \
String^ sourc2 = gcnew String(str2); \
unsigned distance = FuzzyPlusCSharp::Fuzzy::FuncName(sourc1, sourc2); \
sqlite3_result_int(context, distance); \
}

//#define CREATE_EXPORT_FUNCTION2(FuzzyName) __declspec(dllexport) \
//int FuzzyName(const char* str1, const char* str2) { \
//    String^ source1 = gcnew String(str1); \
//    String^ source2 = gcnew String(str2); \
//    int distance = FuzzyPlusCSharp::Fuzzy::FuzzyName(source1, source2); \
//    return distance; \
//}
//
//#define CREATE_EXPORT_ALIAS_FUNCTION2_TRUE(ExpName, FuzzyName) __declspec(dllexport) \
//int ExpName(const char* str1, const char* str2) { \
//    String^ source1 = gcnew String(str1); \
//    String^ source2 = gcnew String(str2); \
//    int distance = FuzzyPlusCSharp::Fuzzy::FuzzyName(source1, source2, TRUE); \
//    return distance; \
//}
//
//#define CREATE_EXPORT_FUNCTION2_TRUE(FuzzyName) __declspec(dllexport) \
//int FuzzyName(const char* str1, const char* str2) { \
//    String^ source1 = gcnew String(str1); \
//    String^ source2 = gcnew String(str2); \
//    int distance = FuzzyPlusCSharp::Fuzzy::FuzzyName(source1, source2, TRUE); \
//    return distance; \
//}

#define SQLITE3_CREATE_FUNCTION1(FuncName) sqlite3_create_function(db, #FuncName, 1, flags, 0, FuncName, 0, 0)
#define SQLITE3_CREATE_FUNCTION2(FuncName) sqlite3_create_function(db, #FuncName, 2, flags, 0, FuncName, 0, 0)
#define SQLITE3_CREATE_FUNCTION3(FuncName) sqlite3_create_function(db, #FuncName, 3, flags, 0, FuncName, 0, 0)
#define SQLITE3_CREATE_FUNCTION4(FuncName) sqlite3_create_function(db, #FuncName, 4, flags, 0, FuncName, 0, 0)
#define SQLITE3_CREATE_FUNCTION5(FuncName) sqlite3_create_function(db, #FuncName, 5, flags, 0, FuncName, 0, 0)
#define SQLITE3_CREATE_FUNCTION_ALIAS1(FuncShortName,FuncName) sqlite3_create_function(db, #FuncShortName, 1, flags, 0, FuncName, 0, 0)
#define SQLITE3_CREATE_FUNCTION_ALIAS2(FuncShortName,FuncName) sqlite3_create_function(db, #FuncShortName, 2, flags, 0, FuncName, 0, 0)
#define SQLITE3_CREATE_FUNCTION_ALIAS3(FuncShortName,FuncName) sqlite3_create_function(db, #FuncShortName, 3, flags, 0, FuncName, 0, 0)


