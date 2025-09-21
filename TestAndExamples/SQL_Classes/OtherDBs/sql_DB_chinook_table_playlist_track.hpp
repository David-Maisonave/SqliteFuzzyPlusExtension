/* This file was automatically generated using [Sqlite3pp_EZ].
Sqlite3pp_EZ Copyright (C) 2025 David Maisonave (http::\www.axter.com)
Example Usage:		(Using sqlite3pp::Table container)
	// Example #1
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_chinook_table_playlist_track> my_tbl;
		for (auto& row : my_tbl)
			std::cout << row << std::endl;

	// Example #2
		for (int i = 0; i < my_tbl.size(); ++i)
			std::cout << my_tbl[i].get_PlaylistId() << std::endl;

	// Example #3
		for (auto r = my_tbl.begin(); r != my_tbl.end(); ++r)
			std::cout << r->get_TrackId() << std::endl;

	// Example #4
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_chinook_table_playlist_track> my_tbl;
		// Example#4a -- (C++11) Range-based loop
		for(auto& row : my_tbl)
			std::cout << row.get_PlaylistId() << " | " << row.get_TrackId() << " | " << std::endl;

		// Example#4b -- C++ style iteration
		for (auto row = my_tbl.begin(); row != my_tbl.end(); ++row) 
			std::cout << row->get_PlaylistId() << " | " << row->get_TrackId() << " | " << std::endl;

		// Example#4c -- C style iteration
		for (int row = 0; row < my_tbl.size(); ++row) 
			std::cout << my_tbl[row].get_PlaylistId() << " | " << my_tbl[row].get_TrackId() << " | " << std::endl;
For more details see  https://github.com/David-Maisonave/sqlite3pp_EZ
*/
#ifndef SQL_DB_CHINOOK_TABLE_PLAYLIST_TRACK_HPP
#define SQL_DB_CHINOOK_TABLE_PLAYLIST_TRACK_HPP
#include <string>
#include "..\sqlite3pp_ez.h"

class sql_DB_chinook_table_playlist_track: public sqlite3pp::sql_base
{
	// A member variable for each field in the table
protected:
	Integer PlaylistId = 0;
	Integer TrackId = 0;

public:
	using StrType = std::string;
	// Constructors
	sql_DB_chinook_table_playlist_track() {} // Default constructor
	template <class T> sql_DB_chinook_table_playlist_track(const T &t) { setData(t); } // Allows data input from different (or same) tables/views having the same data types and column names

	// getTableName, getColumnNames, getSelectColumnNames, and getStreamData are required for sqlite3pp::Table template class
	static StrType getTableName() { return "playlist_track" ; }
	static StrType getColumnNames() { return "\"PlaylistId\", \"TrackId\""; }
	static StrType getSelectColumnNames() { return "\"PlaylistId\", \"TrackId\""; }
	StrType GetValues() const
	{
		StrType strtype;
		strtype +=  "'" + sqlite3pp::to_string( PlaylistId) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( TrackId) + "'";
		return strtype;
	}
	template<class T> void getStreamData( T q ) { q.getter()  >> PlaylistId >> TrackId;}
	template <class T> void setData(const T &t) // Used to transfer data from different tables/views having same data types and column names
	{
		PlaylistId = t.get_PlaylistId();
		TrackId = t.get_TrackId();
	}

	// Miscellaneous functions
	static int getColumnCount() { return 2; }

	// A get_ function for each field in the table, which allows read-only access to protected member variables.
	const Integer& get_PlaylistId() const {return PlaylistId;}
	const Integer& get_TrackId() const {return TrackId;}

	// A set_ function for each field in the table.
	void set_PlaylistId(const Integer& data__) {PlaylistId = data__;}
	void set_TrackId(const Integer& data__) {TrackId = data__;}

	////////////////////////////////////////////////////////////////////////////////////////////
	/* sqlite3pp::TableOStream container interface.
	Functions OStream(), operator<<(), and Delimiter() are required when using the sqlite3pp::TableOStream container.
	Example Usage:		(Using sqlite3pp::TableOStream container)
			TableOStream<sql_DB_chinook_table_playlist_track> tbl(DbFileNameArg("myDatabase.db"));
			tbl.setDelimit("|"); // Change delimiter
			std::cout << tbl; // Send data to screen with the changed delimiter

			std::ofstream ofs ("data.csv", std::ofstream::out);
			tbl.setDelimit(","); // Change delimiter
			ofs << tbl; // Write data to a CSV file using the changed "," delimiter.

			tbl.out(std::cout); // Send data to screen using out() member function.
	To exclude TableOStream interface, set exclude_ostream_operator to true when creating this class using SQLiteClassBuilder.
	*/
	template<class T> T& OStream(T& t) const
	{
		t.os << PlaylistId << t.d << TrackId;
		return t;
	}
	friend std::ostream& operator<<(std::ostream& os, const sql_DB_chinook_table_playlist_track& t);
	friend std::wostream& operator<<(std::wostream& os, const sql_DB_chinook_table_playlist_track& t);
	static StrType Delimiter() { return "," ; }
	////////////////////////////////////////////////////////////////////////////////////////////
};
// sqlite3pp::TableOStream container interface.
inline std::ostream& operator<<(std::ostream& os, const sql_DB_chinook_table_playlist_track& t) { sqlite3pp::ostream_a o(os, t.Delimiter()); return t.OStream(o).os; }
inline std::wostream& operator<<(std::wostream& os, const sql_DB_chinook_table_playlist_track& t) { sqlite3pp::ostream_w o(os, t.Delimiter());  return t.OStream(o).os; }

#endif // !SQL_DB_CHINOOK_TABLE_PLAYLIST_TRACK_HPP
