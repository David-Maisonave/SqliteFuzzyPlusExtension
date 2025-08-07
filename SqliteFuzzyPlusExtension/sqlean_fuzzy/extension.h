// Copyright (c) 2023 Anton Zhiyanov, MIT License
// https://github.com/nalgeon/sqlean

// Fuzzy string matching and phonetics.

#pragma once

#include "..\sqlite\sqlite3ext.h"
SQLITE_EXTENSION_INIT3

extern int sqlite_fuzzy_init(sqlite3* db, const sqlite3_api_routines* sqlite3_api);

int hamming(const char* str1, const char* str2);
double jaro_winkler(const char* str1, const char* str2);
unsigned levenshtein(const char* str1, const char* str2);
unsigned optimal_string_alignment(const char* str1, const char* str2);
unsigned damerau_levenshtein(const char* str1, const char* str2);
int edit_distance(const char* zA, const char* zB, int* pnMatch);
double jaro_distance(const char* str1, const char* str2);
char* soundex(const char* str);
char* refined_soundex(const char* str);
void fuzzy_soundex(sqlite3_context* context, int argc, sqlite3_value** argv);
void fuzzy_rsoundex(sqlite3_context* context, int argc, sqlite3_value** argv);
