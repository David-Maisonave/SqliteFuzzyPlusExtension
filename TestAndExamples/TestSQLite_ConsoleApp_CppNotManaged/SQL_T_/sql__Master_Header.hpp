#ifndef SQL__MASTER_HEADER_H
#define SQL__MASTER_HEADER_H
#include "..\sqlite3pp_ez.h"
#include "sql_table_SimilarWords.hpp"
#include "sql_table_SimilarPhrase.hpp"
#include "sql_table_SimilarNames.hpp"
#include "sql_table_Help.hpp"
#include "sql_table_TextToConvert.hpp"
#include "sql_table_SimilarSoundingWords.hpp"
#include "sql_table_SimilarSoundingWords1To1_AllMatch.hpp"
#include "sql_table_SimilarSoundingWords1To1_NoMatch.hpp"
#include "sql_table_SamePhone_1To1_AllMatch.hpp"
#include "sql_table_SameName_1To1_AllMatch.hpp"
#include "sql_table_AllProteins.hpp"
#include "sql_table_PerformanceResults.hpp"
#include "sql_table_zTroubleFields.hpp"
#include "sql_table_zz Trouble Fields.hpp"


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
		Tables["sql_table_zTroubleFields"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_table_zTroubleFields>());
		Tables["sql_table_zz__Trouble__Fields"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_table_zz__Trouble__Fields>());
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



#endif // !SQL__MASTER_HEADER_H
