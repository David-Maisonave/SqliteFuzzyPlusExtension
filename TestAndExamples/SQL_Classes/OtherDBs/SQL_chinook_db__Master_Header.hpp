#ifndef SQL_CHINOOK_DB__MASTER_HEADER_H
#define SQL_CHINOOK_DB__MASTER_HEADER_H
#include <string>
#include "..\..\sqlite3pp_ez\sqlite3pp_ez.h"
#include "SQL_chinook_db_table_albums.hpp"
#include "SQL_chinook_db_table_sqlite_sequence.hpp"
#include "SQL_chinook_db_table_artists.hpp"
#include "SQL_chinook_db_table_customers.hpp"
#include "SQL_chinook_db_table_employees.hpp"
#include "SQL_chinook_db_table_genres.hpp"
#include "SQL_chinook_db_table_invoices.hpp"
#include "SQL_chinook_db_table_invoice_items.hpp"
#include "SQL_chinook_db_table_media_types.hpp"
#include "SQL_chinook_db_table_playlists.hpp"
#include "SQL_chinook_db_table_playlist_track.hpp"
#include "SQL_chinook_db_table_tracks.hpp"
#include "SQL_chinook_db_table_sqlite_stat1.hpp"


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
		Tables["SQL_chinook_db_table_albums"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_chinook_db_table_albums>());
		Tables["SQL_chinook_db_table_sqlite_sequence"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_chinook_db_table_sqlite_sequence>());
		Tables["SQL_chinook_db_table_artists"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_chinook_db_table_artists>());
		Tables["SQL_chinook_db_table_customers"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_chinook_db_table_customers>());
		Tables["SQL_chinook_db_table_employees"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_chinook_db_table_employees>());
		Tables["SQL_chinook_db_table_genres"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_chinook_db_table_genres>());
		Tables["SQL_chinook_db_table_invoices"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_chinook_db_table_invoices>());
		Tables["SQL_chinook_db_table_invoice_items"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_chinook_db_table_invoice_items>());
		Tables["SQL_chinook_db_table_media_types"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_chinook_db_table_media_types>());
		Tables["SQL_chinook_db_table_playlists"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_chinook_db_table_playlists>());
		Tables["SQL_chinook_db_table_playlist_track"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_chinook_db_table_playlist_track>());
		Tables["SQL_chinook_db_table_tracks"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_chinook_db_table_tracks>());
		Tables["SQL_chinook_db_table_sqlite_stat1"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_chinook_db_table_sqlite_stat1>());
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



#endif // !SQL_CHINOOK_DB__MASTER_HEADER_H
