// TestSQLite_ConsoleApp_CppNotManaged.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
#include "../SQL_Classes/sqlite3pp_ez.h"
#include "../SQL_Classes/sql_DB_TestData_Master_Header.h"

	// Function to test populating all tables & views.
static std::map< std::string, std::shared_ptr<sqlite3pp::TableBase> > testPopulatingAllTables()
{
	std::map< std::string, std::shared_ptr < sqlite3pp::TableBase>> Tables;
	Tables["sql_DB_TestData_table_SimilarWords"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_TestData_table_SimilarWords>());
	Tables["sql_DB_TestData_table_SimilarPhrase"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_TestData_table_SimilarPhrase>());
	Tables["sql_DB_TestData_table_SimilarNames"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_TestData_table_SimilarNames>());
	Tables["sql_DB_TestData_table_Help"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_TestData_table_Help>());
	Tables["sql_DB_TestData_table_TextToConvert"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_TestData_table_TextToConvert>());
	Tables["sql_DB_TestData_table_SimilarSoundingWords"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_TestData_table_SimilarSoundingWords>());
	Tables["sql_DB_TestData_table_SimilarSoundingWords1To1_AllMatch"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_TestData_table_SimilarSoundingWords1To1_AllMatch>());
	Tables["sql_DB_TestData_table_SimilarSoundingWords1To1_NoMatch"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_TestData_table_SimilarSoundingWords1To1_NoMatch>());
	Tables["sql_DB_TestData_table_SamePhone_1To1_AllMatch"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_TestData_table_SamePhone_1To1_AllMatch>());
	Tables["sql_DB_TestData_table_SameName_1To1_AllMatch"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_TestData_table_SameName_1To1_AllMatch>());
	Tables["sql_DB_TestData_table_AllProteins"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_TestData_table_AllProteins>());
	Tables["sql_DB_TestData_table_PerformanceResults"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_TestData_table_PerformanceResults>());
	return Tables;
}
static void testAllTables()
{
	std::map< std::string, std::shared_ptr < sqlite3pp::TableBase>> myTables = testPopulatingAllTables();
	for (auto& t : myTables)
		std::cout << t.second;
}

int main()
{
	sqlite3pp::setGlobalDB(L"..\\..\\SqliteFuzzyPlusExtension\\TestData\\TestData.db");
	// Create C++ headers for associated database tables
	sqlite3pp::SQLiteClassBuilder	createMyClasses(
		"..\\..\\SqliteFuzzyPlusExtension\\TestData\\TestData.db"
		, sqlite3pp::SQLiteClassBuilder::strOpt_std_wstring	// This option creates a class with std::wstring as the default string.
	);

	sqlite3pp::HeaderOpt headerOpt = sqlite3pp::SQLiteClassBuilder::HeadersCreatedSqlDir; // Get default header option

	headerOpt.dest_folder = "SQL_Str\\"; // Change default destination folder
	sqlite3pp::SQLiteClassBuilder	createMyClasses_A(
		"..\\..\\SqliteFuzzyPlusExtension\\TestData\\TestData.db"
		, sqlite3pp::SQLiteClassBuilder::strOpt_std_string	// This option creates a class with string as the default string.
		, headerOpt
		, sqlite3pp::SQLiteClassBuilder::MiscOpt_max
	);

	headerOpt.dest_folder = "SQL_WStr\\"; // Change default destination folder
	sqlite3pp::SQLiteClassBuilder	createMyClasses_W(
		"..\\..\\SqliteFuzzyPlusExtension\\TestData\\TestData.db"
		, sqlite3pp::SQLiteClassBuilder::strOpt_std_wstring	// This option creates a class with std::wstring as the default string.
		, headerOpt
		, sqlite3pp::SQLiteClassBuilder::MiscOpt_max
	);

	headerOpt.dest_folder = "SQL_T_\\"; // Change default destination folder
	sqlite3pp::SQLiteClassBuilder	createMyClasses_T_(
		"..\\..\\SqliteFuzzyPlusExtension\\TestData\\TestData.db"
		, sqlite3pp::SQLiteClassBuilder::strOpt_sql_tstring	// This option creates a class with tstring as the default string and setting string with T_() macro in the header sqlite3pp_ez.h.
		, headerOpt
		, sqlite3pp::SQLiteClassBuilder::MiscOpt_max
	);


	headerOpt.dest_folder = "SQL_T\\"; // Change default destination folder
	sqlite3pp::SQLiteClassBuilder	createMyClasses_T(
		"..\\..\\SqliteFuzzyPlusExtension\\TestData\\TestData.db"
		, sqlite3pp::SQLiteClassBuilder::strOpt_sql_tstring_T	// This option creates a class with tstring as the default string and setting string with windows _T() macro.
		, ""							// Set this to a specific table or view, in which one class is created, or set it to empty to create a class for each table and view in the database.
		, sqlite3pp::SQLiteClassBuilder::MiscOpt_max
		, headerOpt
	);


	std::map< std::string, std::shared_ptr < sqlite3pp::TableBase>> Tables;
	//Tables["sql_table_SimilarWords"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_table_SimilarWords>());
    std::cout << "Finish creating headers\n";

	sqlite3pp::setGlobalDB(L"..\\TestDatabase\\chinook3.5Krows.db", true);
}


