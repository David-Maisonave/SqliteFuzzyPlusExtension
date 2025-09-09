#ifndef SQL_MASTER_HEADER_H
#define SQL_MASTER_HEADER_H
#define _UNICODE
#include <tchar.h>
#include "..\sqlite3pp_ez.h"
#include "sql_table_SimilarWords.h"
#include "sql_table_SimilarPhrase.h"
#include "sql_table_SimilarNames.h"
#include "sql_table_Help.h"
#include "sql_table_TextToConvert.h"
#include "sql_table_SimilarSoundingWords.h"
#include "sql_table_SimilarSoundingWords1To1_AllMatch.h"
#include "sql_table_SimilarSoundingWords1To1_NoMatch.h"
#include "sql_table_SamePhone_1To1_AllMatch.h"
#include "sql_table_SameName_1To1_AllMatch.h"
#include "sql_table_AllProteins.h"
#include "sql_table_PerformanceResults.h"


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
		Tables["sql_table_SimilarWords"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_table_SimilarWords>());
		Tables["sql_table_SimilarPhrase"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_table_SimilarPhrase>());
		Tables["sql_table_SimilarNames"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_table_SimilarNames>());
		Tables["sql_table_Help"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_table_Help>());
		Tables["sql_table_TextToConvert"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_table_TextToConvert>());
		Tables["sql_table_SimilarSoundingWords"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_table_SimilarSoundingWords>());
		Tables["sql_table_SimilarSoundingWords1To1_AllMatch"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_table_SimilarSoundingWords1To1_AllMatch>());
		Tables["sql_table_SimilarSoundingWords1To1_NoMatch"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_table_SimilarSoundingWords1To1_NoMatch>());
		Tables["sql_table_SamePhone_1To1_AllMatch"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_table_SamePhone_1To1_AllMatch>());
		Tables["sql_table_SameName_1To1_AllMatch"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_table_SameName_1To1_AllMatch>());
		Tables["sql_table_AllProteins"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_table_AllProteins>());
		Tables["sql_table_PerformanceResults"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_table_PerformanceResults>());
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



#endif // !SQL_MASTER_HEADER_H
