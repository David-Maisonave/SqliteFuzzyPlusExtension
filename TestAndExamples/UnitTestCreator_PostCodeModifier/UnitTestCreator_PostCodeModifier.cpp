#include "pch.h"
#include "sqlite3pp_ez.h"
// #include "SQL/sql_Master_Header.h"

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
int main(array<System::String ^> ^args)
{
	const std::string dbFileName = "..\\..\\SqliteFuzzyPlusExtension\\TestData\\TestData.db";
	sqlite3pp::HeaderOpt headerOpt = sqlite3pp::SQLiteClassBuilder::HeadersCreatedSqlDir; // Get default header option
	headerOpt.dest_folder = "..\\SQL_TestDataDb\\"; // Change default destination folder
	headerOpt.header_include = "sqlite3pp_ez.h";
	sqlite3pp::setGlobalDB(dbFileName);
	// Create C++ headers for associated database tables
	sqlite3pp::SQLiteClassBuilder	createMyClasses_A(
		dbFileName
		, sqlite3pp::SQLiteClassBuilder::strOpt_std_string	// This option creates a class with string as the default string.
		, headerOpt
		, sqlite3pp::SQLiteClassBuilder::MiscOpt_max
	);

    return 0;
}
