#ifndef SQL_DB_GAMENAMES_MASTER_HEADER_HPP
#define SQL_DB_GAMENAMES_MASTER_HEADER_HPP
#include <string>
#include "..\sqlite3pp_ez.h"
#include "sql_DB_GameNames_table_AlternateNames.hpp"


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
		Tables["sql_DB_GameNames_table_AlternateNames"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_GameNames_table_AlternateNames>());
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



#endif // !SQL_DB_GAMENAMES_MASTER_HEADER_HPP
