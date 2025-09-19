#include "pch.h"
#include <iostream>
#include <stdexcept>
#include <cassert>
#include <atlstr.h>
#include <fstream>
#include <iostream>
#include <filesystem> 
#include <string>
#include <windows.h>
#include "../SQL_Classes/sqlite3pp_ez.h"
#define SQLITEFUZZYPLUSEXTENSION_LIB "SQLITEFUZZYPLUSEXTENSION.LIB"
#include "..\..\SqliteFuzzyPlusExtension\SqliteFuzzyPlusExtension.h"
using namespace std;
using namespace System;

// This program is a unit test creator and a post code modifier for  SqliteFuzzyPlusExtension.
// It should be run before posting a new version of SqliteFuzzyPlusExtension to GitHub.com
// As post code modifier, it will perform the following:
//      1. Update the version details for FuzzyPlusCSharp, SqliteFuzzyPlusExtension, FuzzyPlusCSharp_PhoneticMatching, and SqliteFuzzyPlusExtensionWithMsPhoneticMatching.
//         The new version is based on the last version listed in the history README.md. (SqliteFuzzyPlusExtension\Docs\version_history\README.md)
//      2. It will update the enum's in SqliteFuzzyPlusExtension.h with the enum's in Fuzzy.cs. (SqliteFuzzyPlusExtension\SqliteFuzzyPlusExtension\FuzzyPlusCSharp\Fuzzy.cs)
// Ad a unit test creator, it will do the following:
//      1. Create *.sql files for unit testing all the fuzzy functions in SQLite. The files will be created in SqliteFuzzyPlusExtension\SqliteFuzzyPlusExtension\TestData\AutoCreatedSqlScript
//      2. Create C++ files for UnitTestConsoleCPPRunner.
//      3. Create C# files for UnitTestConsoleCSharpRunner.
//      4. Create C files for UnitTestConsole_C_Runner.

bool b0 = false;
bool b1 = false;
bool b2 = false;
bool b3 = false;
bool b4 = false;
bool b5 = false;
bool b6 = false;
bool b7 = false;
bool b8 = false;
bool b9 = false;
bool b10 = false;

static bool Verify()
{
    assert(b0 == true && b0 == true && b1 == true && b2 == true && b3 == true && b4 == true && b5 == true && b6 == true && b7 == true && b8 == true && b9 == true && b10 == false);
    return (b0 == true && b0 == true && b1 == true && b2 == true && b3 == true && b4 == true && b5 == true && b6 == true && b7 == true && b8 == true && b9 == true && b10 == false);
}

static int ValidateSamenessFunctions()
{
    int returnValue = 0;
    b0 = SameFirstLastName("David E. Maisonave", "Maisonave, David E.");
    b1 = SameFirstLastName("David M. Jorge", "Jorge ,David M");
    b2 = SameFirstLastName("John H Doe", "Doe, John Henry");
    b3 = SameFirstLastName("Jane M. Doe", "Doe,Jane M");
    b4 = SameFirstLastName("Bobby E. White", "Bobby White");
    b5 = SameNames("David Maisonave", "Maisonave David");
    b6 = SameFirstLastName("David G. Maisonave", "David G. Maisonave III");
    b7 = SameFirstLastName("David G. Maisonave", "David G. Maisonave 3rd");
    b8 = SameFirstLastName("David G. Maisonave", "David G. Maisonave JR");
    b9 = SameFirstLastName("David G. Maisonave", "David G. Maisonave Sr.");
    b10 = SameFirstLastName("John H Doe", "John (Doedoe)"); // This should fail
    if (!Verify())
    {
        returnValue = +-1;
        cout << "Error: Assert fail for API SameFirstLastName or API SameNames. See following boolean results: ";
        cout << "b0 = " << b0 << " ;b1 = " << b1 << " ;b2 = " << b2 << " ;b3 = " << b3 << " ;b4 = " << b4 << " ;(SameNames)b5 = " << b5 << " ;b6 = " << b6 << " ;b7 = " << b7 << " ;b8 = " << b8 << " ;b9 = " << b9 << " ;b10 (Validate-Is-False) = " << b10 << endl;
    }

    b0 = SamePhone("215-123-45678", "1-215-123-45678");
    b1 = SamePhone("215-123-45678", "(215) 123-45678");
    b2 = SamePhone("215-123-45678", "215.123.45678");
    b3 = SamePhone("215-123-45678", "215 123-45678");
    b4 = SamePhone("215-123-45678", "21512345678");
    b5 = SamePhone("215-123-45678", "215-123-45678-ext 0987");
    b6 = SamePhone("215-123-45678", "121512345678");
    b7 = SamePhone("215-123-45678", "215 123 45678");
    b8 = SamePhone("215-123-45678", "PH:215-123-45678");
    b9 = SamePhone("215-123-45678", "[215] (123-45678)");
    b10 = SamePhone("215-123-45678", "123-215-45678"); // This should fail
    if (!Verify())
    {
        returnValue = +-2;
        cout << "Error: Assert fail for API SamePhone. See following boolean results: ";
        cout << "b0 = " << b0 << " ;b1 = " << b1 << " ;b2 = " << b2 << " ;b3 = " << b3 << " ;b4 = " << b4 << " ;b5 = " << b5 << " ;b6 = " << b6 << " ;b7 = " << b7 << " ;b8 = " << b8 << " ;b9 = " << b9 << " ;b10 (Validate-Is-False) = " << b10 << endl;
    }

    b0 = SameSocial("123-45-6789", "123456789");
    b1 = SameSocial("123-45-6789", "123.45.6789");
    b2 = SameSocial("123-45-6789", "123456789");
    b3 = SameSocial("123-45-6789", "123 45 6789");
    b4 = SameSocial("123-45-6789", "123 45 6789  ");
    b10 = SameSocial("123-45-6789", "123-45-8899"); // This should fail
    if (!Verify())
    {
        returnValue = +-4;
        cout << "Error: Assert fail for API SameSocial. See following boolean results: ";
        cout << "b0 = " << b0 << " ;b1 = " << b1 << " ;b2 = " << b2 << " ;b3 = " << b3 << " ;b4 = " << b4 << " ;b5 = " << b5 << " ;b6 = " << b6 << " ;b7 = " << b7 << " ;b8 = " << b8 << " ;b9 = " << b9 << " ;b10 (Validate-Is-False) = " << b10 << endl;
    }

    b0 = SameZip("08015", "08015-1234");
    b1 = SameZip("08015", "08015 1234");
    b2 = SameZip("08015", "Zip# 08015");
    b3 = SameZip("91234", "Anytown, CA 91234");
    b4 = SameZip("91234", "Smith, PO Box 123, Anytown, CA 91234");
    b5 = SameZip("91234", "Smith, PO Box 123, Anytown, CA 91234-0812");
    b6 = SameZip("08015", "Zip# 08015-1234  ");
    b10 = SameZip("08015", "19133"); // This should fail
    if (!Verify())
    {
        returnValue = +-8;
        cout << "Error: Assert fail for API SameZip. See following boolean results: ";
        cout << "b0 = " << b0 << " ;b1 = " << b1 << " ;b2 = " << b2 << " ;b3 = " << b3 << " ;b4 = " << b4 << " ;b5 = " << b5 << " ;b6 = " << b6 << " ;b7 = " << b7 << " ;b8 = " << b8 << " ;b9 = " << b9 << " ;b10 (Validate-Is-False) = " << b10 << endl;
    }

    b0 = SameAddress("N6W23001 BLUEMOUND ROAD, ROLLING MEADOWS, IL, 12345", "N6W23001 BLUEMOUND RD, ROLLING MEADOWS, IL, 12345-4321");
    b1 = SameAddress("N6W23001 BLUEMOUND ROAD, ROLLING MEADOWS, IL, 12345", "N6W23001 BLUEMOUND RD., ROLLING MEADOWS IL 12345");
    b2 = SameAddress("N6W23001 BLUEMOUND ROAD, ROLLING MEADOWS, IL, 12345", "N6W23001 BLUEMOUND ROAD, ROLLING MEADOWS, IL, 12345-4321");
    b3 = SameAddress("11 W Whitesbogs RD, ROLLING MEADOWS, IL, 12345", "11 W Whitesbogs RD, ROLLING MEADOWS, IL, 12345");
    b4 = SameAddress("11 W Whitesbogs RD, ROLLING MEADOWS, IL, 12345", "11 West Whitesbogs RD, ROLLING MEADOWS, IL, 12345");
    b5 = SameAddress("11 W Whitesbogs RD, ROLLING MEADOWS, IL, 12345", "11 W. Whitesbogs RD, ROLLING MEADOWS, IL, 12345");
    b6 = SameAddress("11 W Whitesbogs RD, ROLLING MEADOWS, IL, 12345", "11 W Whitesbogs Road, ROLLING MEADOWS, IL, 12345");
    b10 = SameAddress("N6W23001 BLUEMOUND ROAD, ROLLING MEADOWS, IL, 12345", "11 W Whitesbogs RD, ROLLING MEADOWS, IL, 12345"); // This should fail
    if (!Verify())
    {
        returnValue = +-16;
        cout << "Error: Assert fail for API SameAddress. See following boolean results: ";
        cout << "b0 = " << b0 << " ;b1 = " << b1 << " ;b2 = " << b2 << " ;b3 = " << b3 << " ;b4 = " << b4 << " ;b5 = " << b5 << " ;b6 = " << b6 << " ;b7 = " << b7 << " ;b8 = " << b8 << " ;b9 = " << b9 << " ;b10 (Validate-Is-False) = " << b10 << endl;
    }

    return returnValue;
}


static void CreateScriptSimilarWords(string rootDir, string fieldName, string table, string FunctionName, string CompareTo, bool byName)
{
    string fileName = byName ? "_ByName_" : "_ByNumber_";
    string fullFileName = rootDir + FunctionName + fileName + table + ".sql";
    ofstream f(fullFileName);
    f << "select " << fieldName << endl;
    for (int i = 0; i <= (int)FuzzyPlusCSharp::Fuzzy::StringMatchingAlgorithm_ID::iChapmanMeanLength; ++i)
    {
        CString d = FuzzyPlusCSharp::Fuzzy::GetStringMatchingAlgorithmName(i);
        string fuzzyFunctionName = CW2A(d).operator char* ();
        if (std::isdigit(fuzzyFunctionName[0]))
            continue;
        if (fuzzyFunctionName.find("DO_NOT_USE") != string::npos && fuzzyFunctionName.find("SimHash") == string::npos)
            continue;
        f << ", " << FunctionName << "(" << fieldName << ", " << CompareTo << ", ";
        if (byName)
            f << "'" << fuzzyFunctionName << "'";
        else
            f << i;
        string note = "";
        if (fuzzyFunctionName.find("DO_NOT_USE") != string::npos)
            note = "   !!! Warning: This is NOT a working algorithm!!!";
        else if (fuzzyFunctionName.find("ChapmanMeanLength") != string::npos)
            note = "   !!! Warning: The ChapmanMeanLength algorithm does not work. It does NOT produce expected results!!!";
        else if (fuzzyFunctionName.find("Hamming") != string::npos)
            note = "   *** Note: The Hamming algorithm only works with strings having equal length ***";
        f << ") as a" << i << " -- " << fuzzyFunctionName << " (ID# " << i << ")" << note << endl;
    }
    if ((FunctionName == "IsSimilar" || FunctionName == "IsVerySimilar") &&
        (table == "SimilarNames" || table == "SimilarWords"))
    {
        for (int i = (int)FuzzyPlusCSharp::Fuzzy::SameSoundMethod::SoundexPhonix; i < FuzzyPlusCSharp::Fuzzy::MICROSOFT_PHONETIC_ALGORITHMS + 1; ++i)
        {
            CString d = FuzzyPlusCSharp::Fuzzy::GetSameSoundMethodName(i);
            string fuzzyFunctionName = CW2A(d).operator char* ();
            if (std::isdigit(fuzzyFunctionName[0]))
                continue;
            f << ", " << FunctionName << "(" << fieldName << ", " << CompareTo << ", ";
            if (byName)
                f << "'" << fuzzyFunctionName << "'";
            else
                f << i;
            f << ") as a" << i << " -- " << fuzzyFunctionName << " (ID# " << i << ")" << endl;
        }
    }
    f << "FROM " << table << ";" << endl;
    f << "-- Note: Case insensitive functions have an ID number greater than " << FuzzyPlusCSharp::Fuzzy::CASE_INSENSITIVE_STRING_MATCHING_ALGORITHMS << endl;
    f << "--       C++ functions have an ID number equal to or greater than  " << FuzzyPlusCSharp::Fuzzy::CPP_ONLY_FUZZY_ALGORITHM_IMPLEMENTATION << " and less than " << FuzzyPlusCSharp::Fuzzy::BAD_STRING_MATCHING_ALGORITHMS << endl;
    f << "--       Tokenize functions have an ID number equal to or greater than  " << FuzzyPlusCSharp::Fuzzy::TOKEN_STRING_MATCHING_ALGORITHMS << " and less than " << FuzzyPlusCSharp::Fuzzy::PHRASE_STRING_MATCHING_ALGORITHMS << endl;
    f << "--       Phrase functions have an ID number equal to or greater than  " << FuzzyPlusCSharp::Fuzzy::PHRASE_STRING_MATCHING_ALGORITHMS << " and less than " << FuzzyPlusCSharp::Fuzzy::CPP_ONLY_FUZZY_ALGORITHM_IMPLEMENTATION << endl;
    f << "--       Functions that are being considered for deletion have an ID number equal to or greater than  " << FuzzyPlusCSharp::Fuzzy::STRING_MATCHING_ALGORITHMS_UP_FOR_DELETION << " and less than " << FuzzyPlusCSharp::Fuzzy::CASE_INSENSITIVE_STRING_MATCHING_ALGORITHMS << endl;
    f.close();
}

static void CreateScriptSimilarWords(string rootDir, string fieldName, string table, string FunctionName, string CompareTo)
{
    CreateScriptSimilarWords(rootDir, fieldName, table, FunctionName, CompareTo, false);
    CreateScriptSimilarWords(rootDir, fieldName, table, FunctionName, CompareTo, true);
}

// Function to trim leading whitespace
static std::string ltrim(const std::string& s, string whatToTrim = " \t\n\r\f\v") {
    size_t start = s.find_first_not_of(whatToTrim);
    return (start == std::string::npos) ? "" : s.substr(start);
}

// Function to trim trailing whitespace
static std::string rtrim(const std::string& s, string whatToTrim = " \t\n\r\f\v") {
    size_t end = s.find_last_not_of(whatToTrim);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

static void CreateScriptSimilarSound(string rootDir, string fieldName, string table, string FunctionName, string CompareTo, bool byName)
{
    string fileName = byName ? "_ByName_" : "_ByNumber_";
    string Src2 = ltrim(rtrim(CompareTo, "'"), "'");
    ofstream f(rootDir + FunctionName + fileName + table + "_Src2_" + Src2 + ".sql");
    f << "select " << fieldName << " as src1, " << CompareTo << " as src2 " << endl;
    for (int i = 0; i < (int)FuzzyPlusCSharp::Fuzzy::SameSoundMethod::Fuzzy_Translit; ++i)
    {
        CString d = FuzzyPlusCSharp::Fuzzy::GetSameSoundMethodName(i);
        string soundMethodName = CW2A(d).operator char* ();
        if (std::isdigit(soundMethodName[0]))
            continue;
        f << ", " << FunctionName << "(" << fieldName << ", " << CompareTo << ", ";
        if (byName)
            f << "'" << soundMethodName << "'";
        else
            f << i;
        f << ") as a" << i << " -- " << soundMethodName << " (ID# " << i << ")" << endl;
    }
    f << "FROM " << table << ";" << endl;
    f << "-- Note: EnPhoneticDistance only works with SqliteFuzzyPlusExtensionWithMsPhoneticMatching.dll" << endl;
    f.close();
}
static void CreateScriptSimilarSound(string rootDir, string fieldName, string table, string FunctionName, string CompareTo)
{
    CreateScriptSimilarSound(rootDir, fieldName, table, FunctionName, CompareTo, false);
    CreateScriptSimilarSound(rootDir, fieldName, table, FunctionName, CompareTo, true);
}

static void CreateUnitTestSqlFiles()
{
    string rootDir = "..\\..\\SqliteFuzzyPlusExtension\\TestData\\AutoCreatedSqlScript\\";
    CreateScriptSimilarWords(rootDir, "Name", "SimilarNames", "Distance", "'David Jorge'");
    CreateScriptSimilarWords(rootDir, "Phrases", "SimilarPhrase", "Distance", "'This is a similar phrase test'");
    CreateScriptSimilarWords(rootDir, "Words", "SimilarWords", "Distance", "'David'");
    CreateScriptSimilarWords(rootDir, "Name", "SimilarNames", "HowSimilar", "'David Jorge'");
    CreateScriptSimilarWords(rootDir, "Phrases", "SimilarPhrase", "HowSimilar", "'This is a similar phrase test'");
    CreateScriptSimilarWords(rootDir, "Words", "SimilarWords", "HowSimilar", "'David'");
    CreateScriptSimilarWords(rootDir, "Name", "SimilarNames", "Similar", "'David Jorge'");
    CreateScriptSimilarWords(rootDir, "Phrases", "SimilarPhrase", "Similar", "'This is a similar phrase test'");
    CreateScriptSimilarWords(rootDir, "Words", "SimilarWords", "Similar", "'David'");

    CreateScriptSimilarWords(rootDir, "Name", "SimilarNames", "IsVerySimilar", "'David Jorge'");
    CreateScriptSimilarWords(rootDir, "Phrases", "SimilarPhrase", "IsVerySimilar", "'This is a similar phrase test'");
    CreateScriptSimilarWords(rootDir, "Words", "SimilarWords", "IsVerySimilar", "'David'");
    CreateScriptSimilarWords(rootDir, "Name", "SimilarNames", "IsSimilar", "'David Jorge'");
    CreateScriptSimilarWords(rootDir, "Words", "SimilarWords", "IsSimilar", "'David'");

    CreateScriptSimilarWords(rootDir, "Phrases", "SimilarPhrase", "IsSimilar", "'This is a similar phrase test'");
    CreateScriptSimilarWords(rootDir, "Phrases", "SimilarPhrase", "IsSomeWhatSimilar", "'This is a similar phrase test'");
    CreateScriptSimilarWords(rootDir, "Phrases", "SimilarPhrase", "IsSlightlySimilar", "'This is a similar phrase test'");
    CreateScriptSimilarWords(rootDir, "Phrases", "SimilarPhrase", "IsHardlySimilar", "'This is a similar phrase test'");
    CreateScriptSimilarWords(rootDir, "Phrases", "SimilarPhrase", "IsNotSimilar", "'This is a similar phrase test'");
    CreateScriptSimilarWords(rootDir, "Phrases", "SimilarPhrase", "HowSimilar", "'This is a similar phrase test'");

    CreateScriptSimilarSound(rootDir, "Source1", "SimilarSoundingWords1To1_NoMatch", "SameSound", "Source2");
    CreateScriptSimilarSound(rootDir, "Source1", "SimilarSoundingWords1To1_AllMatch", "SameSound", "Source2");
    CreateScriptSimilarSound(rootDir, "Words", "SimilarSoundingWords", "SameSound", "'been'");
    CreateScriptSimilarSound(rootDir, "Words", "SimilarSoundingWords", "SameSound", "'being'");
    CreateScriptSimilarSound(rootDir, "Words", "SimilarSoundingWords", "SameSound", "'bean'");
    CreateScriptSimilarSound(rootDir, "Words", "SimilarSoundingWords", "SameSound", "'their'");
}

static int CreateDbClassInterface(const std::string &dbFileName, const sqlite3pp::HeaderOpt &headerOpt)
{
    if (!std::filesystem::exists(dbFileName.c_str()))
    {
        cout << "Warn: Can not find database file '" << dbFileName << "'. Check if file exist." << endl;
        return -32;
    }
    // Create C++ headers for associated database tables
    sqlite3pp::SQLiteClassBuilder	createMyClasses_A(
        dbFileName
        , sqlite3pp::SQLiteClassBuilder::strOpt_std_string	// This option creates a class with string as the default string.
        , headerOpt
        , sqlite3pp::SQLiteClassBuilder::MiscOpt_max
    );
    return 0;
}

int main()
{
    int returnValue = ValidateSamenessFunctions();
    CreateUnitTestSqlFiles();

    sqlite3pp::sql_base::SetVerbosityLevel(sqlite3pp::VBLV_WARN);
    const std::string dbFileName = "..\\..\\SqliteFuzzyPlusExtension\\TestData\\TestData.db";
	sqlite3pp::HeaderOpt headerOpt = sqlite3pp::SQLiteClassBuilder::HeadersCreatedSqlDir; // Get default header option
	headerOpt.dest_folder = "..\\SQL_Classes\\"; // Change default destination folder
    headerOpt.header_prefix = "sql_DB_TestData_";
	headerOpt.header_include = "sqlite3pp_ez.h";
    if (CreateDbClassInterface(dbFileName, headerOpt) != 0)
    {
        returnValue =+ -32;
        cout << "Error: Failed to create SQL classes for database " << dbFileName << " in path " << headerOpt.dest_folder << "." << endl;
    }

    headerOpt.dest_folder = "..\\SQL_Classes\\OtherDBs\\";
    headerOpt.header_include = "..\\sqlite3pp_ez.h";

    headerOpt.header_prefix = "sql_DB_NorthWind_";
    CreateDbClassInterface("..\\TestDatabase\\NorthWind_small.db", headerOpt);

    headerOpt.header_prefix = "sql_DB_chinook_";
    CreateDbClassInterface("..\\TestDatabase\\chinook3.5Krows.db", headerOpt);

    headerOpt.header_prefix = "sql_DB_GameNames_";
    CreateDbClassInterface("..\\TestDatabase\\GameNames53KRows.db", headerOpt);

    headerOpt.header_prefix = "sql_DB_KenshoDataset_";
    CreateDbClassInterface("..\\TestDatabase\\kensho_dataset(1millionRows).db", headerOpt);

    headerOpt.header_prefix = "sql_DB_sakila_";
    CreateDbClassInterface("..\\TestDatabase\\sakila.db", headerOpt);


    return returnValue;
}
