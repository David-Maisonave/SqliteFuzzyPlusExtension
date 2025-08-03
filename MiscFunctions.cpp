#include <string>
#include <stdexcept>
#include <cassert>
#include <algorithm>
#include "SqliteFuzzyPlusExtension_Internal.h"

sqlite3_int64 convertToInt64(const std::string& input)
{
    // Clean the input string
    std::string cleaned;
    for (char ch : input) 
        if (ch != ',' && ch != '+') 
            cleaned += ch;
    // Determine the suffix and numeric part
    double number = 0;
    char suffix = '\0';
    size_t len = cleaned.length();
    size_t pos = len;
    // Find the suffix (if any)
    if (pos > 0 && (cleaned[pos - 1] == 'M' || cleaned[pos - 1] == 'B' || cleaned[pos - 1] == 'K')) 
    {
        suffix = cleaned[pos - 1];
        cleaned = cleaned.substr(0, pos - 1); // Remove the suffix
    }
    // Convert the numeric part to a double
    try {
        number = std::stod(cleaned);
    }
    catch (const std::invalid_argument&) {
        throw std::invalid_argument("Invalid numeric part in input string.");
    }
    catch (const std::out_of_range&) {
        throw std::out_of_range("Numeric part out of range.");
    }
    // Apply the suffix multiplier
    if (suffix == 'M') 
        number *= 1e6; // Million
    else if (suffix == 'B') 
        number *= 1e9; // Billion
    else if (suffix == 'K')
        number *= 1e3; // Thousand
    // Convert the result to sqlite3_int64
    if (number > std::numeric_limits<sqlite3_int64>::max() || number < std::numeric_limits<sqlite3_int64>::min())
        throw std::out_of_range("Converted number is out of range for sqlite3_int64.");
    return static_cast<sqlite3_int64>(number);
}

void SameName(sqlite3_context* context, int argc, sqlite3_value** argv)
{
    assert(argc == 2);
    // 1) get shortest of two names, this is maxlen
    // 2) init name1 and name2 char index pointers = 0
    // 3) loop over each character, while name1 & name2 pointers < maxlen :
    //   a) if one is a space or a period, increase that name char
    //   index, repeat loop with same other char
    //   b) lowercase each if necessary
    //
    // Lower case strings:
    //   for ( ; *p; ++p) *p = tolower(*p);
    // Convert names to char* and calculate min length
    const char* name1 = (const char*)sqlite3_value_text(argv[0]);
    const char* name2 = (const char*)sqlite3_value_text(argv[1]);
    if (name1 == NULL || name2 == NULL)
    {
        sqlite3_result_int(context, 0);
        return;
    }
    size_t name1len = strlen(name1);
    size_t name2len = strlen(name2);
    if ((name1len == 0) || (name2len == 0))
    {
        sqlite3_result_int(context, 0);
        return;
    }
    int minlen = (name2len < name1len) ? (int)name2len : (int)name1len;
    char* n = (char*)name1;
    char* m = (char*)name2;
    // default to equal
    int equal = 1;
    // flag for if we actually did a compare of valid chars
    // this lets us fix equal if we didn't do any compares
    // due to all chars being invalid/ignored
    int compared = 0;
    // keep track of both positions
    int n_i = 0;
    int m_i = 0;
    while (n_i < name1len && m_i < name2len)
    {
        if (tolower(*n) < 'a' || tolower(*n) > 'z')
        {
            n++; n_i++; 
            continue;
        }
        if (tolower(*m) < 'a' || tolower(*m) > 'z')
        {
            m++; m_i++; 
            continue;
        }
        compared = 1;
        if (tolower(*n) != tolower(*m))
        {
            equal = 0;
            break;
        }
        n++; m++;
        n_i++; m_i++;
    }
    // all-invalid strings are not equal
    if (!compared) 
        equal = 0;
    sqlite3_result_int(context, equal);
}


void NormalizeNum(sqlite3_context* context, int argc, sqlite3_value** argv) {
    assert(argc == 1);
    const char* source = (char*)sqlite3_value_text(argv[0]);
    if (source == 0) {
        return;
    }
    try
    {
        sqlite3_result_int64(context, convertToInt64(source));
    }
    catch (...) {
        sqlite3_result_text(context, "error", -1, NULL);
    }
}


void MaxValue(sqlite3_context* context, int argc, sqlite3_value** argv) {
    assert(argc == 2);
    int i1 = sqlite3_value_int(argv[0]);
    int i2 = sqlite3_value_int(argv[1]);
    int results = FuzzyPlusCSharp::Fuzzy::MaxValue(i1, i2);
    sqlite3_result_int(context, results);
}

void MaxLength(sqlite3_context* context, int argc, sqlite3_value** argv) {
    assert(argc == 2);
    const char* source1 = (char*)sqlite3_value_text(argv[0]);
    const char* source2 = (char*)sqlite3_value_text(argv[1]);
    int results = std::max((int)strlen(source1), (int)strlen(source2));
    sqlite3_result_int(context, results);
}

void MinValue(sqlite3_context* context, int argc, sqlite3_value** argv) {
    assert(argc == 2);
    int i1 = sqlite3_value_int(argv[0]);
    int i2 = sqlite3_value_int(argv[1]);
    int results = FuzzyPlusCSharp::Fuzzy::MinValue(i1, i2);
    sqlite3_result_int(context, results);
}

void MinLength(sqlite3_context* context, int argc, sqlite3_value** argv) {
    assert(argc == 2);
    const char* source1 = (char*)sqlite3_value_text(argv[0]);
    const char* source2 = (char*)sqlite3_value_text(argv[1]);
    int results = std::min((int)strlen(source1), (int)strlen(source2));
    sqlite3_result_int(context, results);
}

double GetPercentage(double distance, double length, double full)
{
    double difference = distance / length;
    return full - difference;
}
