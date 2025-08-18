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
double GetPercentage(double distance, double length, double full = 1.0f);

#define SQLITE3_CREATE_FUNCTION1(FuncName) sqlite3_create_function(db, #FuncName, 1, flags, 0, FuncName, 0, 0)
#define SQLITE3_CREATE_FUNCTION2(FuncName) sqlite3_create_function(db, #FuncName, 2, flags, 0, FuncName, 0, 0)
#define SQLITE3_CREATE_FUNCTION3(FuncName) sqlite3_create_function(db, #FuncName, 3, flags, 0, FuncName, 0, 0)
#define SQLITE3_CREATE_FUNCTION4(FuncName) sqlite3_create_function(db, #FuncName, 4, flags, 0, FuncName, 0, 0)
#define SQLITE3_CREATE_FUNCTION5(FuncName) sqlite3_create_function(db, #FuncName, 5, flags, 0, FuncName, 0, 0)
#define SQLITE3_CREATE_FUNCTION_ALIAS1(FuncShortName,FuncName) sqlite3_create_function(db, #FuncShortName, 1, flags, 0, FuncName, 0, 0)
#define SQLITE3_CREATE_FUNCTION_ALIAS2(FuncShortName,FuncName) sqlite3_create_function(db, #FuncShortName, 2, flags, 0, FuncName, 0, 0)
#define SQLITE3_CREATE_FUNCTION_ALIAS3(FuncShortName,FuncName) sqlite3_create_function(db, #FuncShortName, 3, flags, 0, FuncName, 0, 0)


