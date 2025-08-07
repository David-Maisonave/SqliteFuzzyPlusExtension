// Copyright (c) 2014 Ross Bayer, MIT License
// https://github.com/Rostepher/libstrcmp

#pragma once

// distance metrics
unsigned damerau_levenshtein(const char*, const char*);
int hamming(const char*, const char*);
double jaro_distance(const char*, const char*);
double jaro_winkler(const char*, const char*);
unsigned levenshtein(const char*, const char*);
unsigned optimal_string_alignment(const char*, const char*);
int edit_distance(const char*, const char*, int*);

// phonetics
char* caverphone(const char*);
char* soundex(const char*);
char* refined_soundex(const char*);
unsigned char* phonetic_hash(const unsigned char*, int);

// translit
unsigned char* transliterate(const unsigned char*, int);
int translen_to_charlen(const char*, int, int);
int script_code(const unsigned char*, int);
void fuzzy_damlev(sqlite3_context* context, int argc, sqlite3_value** argv);
void fuzzy_hamming(sqlite3_context* context, int argc, sqlite3_value** argv);
void fuzzy_jarowin(sqlite3_context* context, int argc, sqlite3_value** argv);
void fuzzy_leven(sqlite3_context* context, int argc, sqlite3_value** argv);
void fuzzy_osadist(sqlite3_context* context, int argc, sqlite3_value** argv);
void fuzzy_editdist(sqlite3_context* context, int argc, sqlite3_value** argv);


void fuzzy_soundex(sqlite3_context* context, int argc, sqlite3_value** argv);
void fuzzy_rsoundex(sqlite3_context* context, int argc, sqlite3_value** argv);
void fuzzy_phonetic(sqlite3_context* context, int argc, sqlite3_value** argv);
void fuzzy_translit(sqlite3_context* context, int argc, sqlite3_value** argv);
void fuzzy_script(sqlite3_context* context, int argc, sqlite3_value** argv);
void fuzzy_caver(sqlite3_context* context, int argc, sqlite3_value** argv);



























