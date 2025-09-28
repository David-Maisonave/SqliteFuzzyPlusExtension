#ifndef SQL_KENSHO_DATASET_DB__MASTER_HEADER_H
#define SQL_KENSHO_DATASET_DB__MASTER_HEADER_H
#include <string>
#include "..\..\sqlite3pp_ez\sqlite3pp_ez.h"
#include "SQL_Kensho_Dataset_db_table_Items.hpp"


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
		Tables["SQL_Kensho_Dataset_db_table_Items"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_Kensho_Dataset_db_table_Items>());
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



#endif // !SQL_KENSHO_DATASET_DB__MASTER_HEADER_H
