#ifndef SQL_TESTDATA_DB__MASTER_HEADER_H
#define SQL_TESTDATA_DB__MASTER_HEADER_H
#include <string>
#include "..\sqlite3pp_EZ\sqlite3pp_ez.h"
#include "SQL_TestData_db_table_SimilarWords.hpp"
#include "SQL_TestData_db_table_SimilarPhrase.hpp"
#include "SQL_TestData_db_table_SimilarNames.hpp"
#include "SQL_TestData_db_table_Help.hpp"
#include "SQL_TestData_db_table_TextToConvert.hpp"
#include "SQL_TestData_db_table_SimilarSoundingWords.hpp"
#include "SQL_TestData_db_table_SimilarSoundingWords1To1_AllMatch.hpp"
#include "SQL_TestData_db_table_SimilarSoundingWords1To1_NoMatch.hpp"
#include "SQL_TestData_db_table_SamePhone_1To1_AllMatch.hpp"
#include "SQL_TestData_db_table_SameName_1To1_AllMatch.hpp"
#include "SQL_TestData_db_table_AllProteins.hpp"
#include "SQL_TestData_db_table_PerformanceResults.hpp"
#include "SQL_TestData_db_table_zTroubleFields.hpp"
#include "SQL_TestData_db_table_zz Trouble Fields.hpp"


/*
// This example code can be used to test and validate all tables.
// Example Usage:
// 		sqlite3pp::setGlobalDB("myDatabase.db")
// 		sqlite3pp::testAllTables();
// Warning: testPopulatingAllTables and testAllTables may take a very long time on a database with a lot of content.
#include <map>
#include <memory>
namespace sqlite3pp
{
	// Function to test populating all tables & views.
	std::map< std::string, std::shared_ptr<sqlite3pp::TableBase> > testPopulatingAllTables()
	{
		std::map< std::string, std::shared_ptr < sqlite3pp::TableBase>> Tables;
		Tables["SQL_TestData_db_table_SimilarWords"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_TestData_db_table_SimilarWords>());
		Tables["SQL_TestData_db_table_SimilarPhrase"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_TestData_db_table_SimilarPhrase>());
		Tables["SQL_TestData_db_table_SimilarNames"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_TestData_db_table_SimilarNames>());
		Tables["SQL_TestData_db_table_Help"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_TestData_db_table_Help>());
		Tables["SQL_TestData_db_table_TextToConvert"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_TestData_db_table_TextToConvert>());
		Tables["SQL_TestData_db_table_SimilarSoundingWords"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_TestData_db_table_SimilarSoundingWords>());
		Tables["SQL_TestData_db_table_SimilarSoundingWords1To1_AllMatch"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_TestData_db_table_SimilarSoundingWords1To1_AllMatch>());
		Tables["SQL_TestData_db_table_SimilarSoundingWords1To1_NoMatch"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_TestData_db_table_SimilarSoundingWords1To1_NoMatch>());
		Tables["SQL_TestData_db_table_SamePhone_1To1_AllMatch"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_TestData_db_table_SamePhone_1To1_AllMatch>());
		Tables["SQL_TestData_db_table_SameName_1To1_AllMatch"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_TestData_db_table_SameName_1To1_AllMatch>());
		Tables["SQL_TestData_db_table_AllProteins"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_TestData_db_table_AllProteins>());
		Tables["SQL_TestData_db_table_PerformanceResults"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_TestData_db_table_PerformanceResults>());
		Tables["SQL_TestData_db_table_zTroubleFields"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_TestData_db_table_zTroubleFields>());
		Tables["SQL_TestData_db_table_zz__Trouble__Fields"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_TestData_db_table_zz__Trouble__Fields>());
		return Tables;
	}

	// Function to test displaying content of all tables & views.
	void testAllTables()
	{
		std::map< std::string, std::shared_ptr < sqlite3pp::TableBase>> myTables = sqlite3pp::testPopulatingAllTables();
		for (auto& t : myTables)
			t.second->out(std::wcout);
	}
}
*/



#endif // !SQL_TESTDATA_DB__MASTER_HEADER_H
