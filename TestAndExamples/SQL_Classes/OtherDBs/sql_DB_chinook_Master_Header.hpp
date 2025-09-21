#ifndef SQL_DB_CHINOOK_MASTER_HEADER_HPP
#define SQL_DB_CHINOOK_MASTER_HEADER_HPP
#include <string>
#include "..\sqlite3pp_ez.h"
#include "sql_DB_chinook_table_albums.hpp"
#include "sql_DB_chinook_table_sqlite_sequence.hpp"
#include "sql_DB_chinook_table_artists.hpp"
#include "sql_DB_chinook_table_customers.hpp"
#include "sql_DB_chinook_table_employees.hpp"
#include "sql_DB_chinook_table_genres.hpp"
#include "sql_DB_chinook_table_invoices.hpp"
#include "sql_DB_chinook_table_invoice_items.hpp"
#include "sql_DB_chinook_table_media_types.hpp"
#include "sql_DB_chinook_table_playlists.hpp"
#include "sql_DB_chinook_table_playlist_track.hpp"
#include "sql_DB_chinook_table_tracks.hpp"
#include "sql_DB_chinook_table_sqlite_stat1.hpp"


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
		Tables["sql_DB_chinook_table_albums"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_chinook_table_albums>());
		Tables["sql_DB_chinook_table_sqlite_sequence"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_chinook_table_sqlite_sequence>());
		Tables["sql_DB_chinook_table_artists"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_chinook_table_artists>());
		Tables["sql_DB_chinook_table_customers"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_chinook_table_customers>());
		Tables["sql_DB_chinook_table_employees"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_chinook_table_employees>());
		Tables["sql_DB_chinook_table_genres"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_chinook_table_genres>());
		Tables["sql_DB_chinook_table_invoices"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_chinook_table_invoices>());
		Tables["sql_DB_chinook_table_invoice_items"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_chinook_table_invoice_items>());
		Tables["sql_DB_chinook_table_media_types"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_chinook_table_media_types>());
		Tables["sql_DB_chinook_table_playlists"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_chinook_table_playlists>());
		Tables["sql_DB_chinook_table_playlist_track"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_chinook_table_playlist_track>());
		Tables["sql_DB_chinook_table_tracks"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_chinook_table_tracks>());
		Tables["sql_DB_chinook_table_sqlite_stat1"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_chinook_table_sqlite_stat1>());
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



#endif // !SQL_DB_CHINOOK_MASTER_HEADER_HPP
