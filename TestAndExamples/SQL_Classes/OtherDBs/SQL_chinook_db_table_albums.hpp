/* This file was automatically generated using [Sqlite3pp_EZ].
Sqlite3pp_EZ Copyright (C) 2025 David Maisonave (http::\www.axter.com)
Example Usage:		(Using sqlite3pp::Table container)
	// Example #1
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<SQL_chinook_db_table_albums> my_tbl;
		for (auto& row : my_tbl)
			std::cout << row << std::endl;

	// Example #2
		for (int i = 0; i < my_tbl.size(); ++i)
			std::cout << my_tbl[i].get_AlbumId() << std::endl;

	// Example #3
		for (auto r = my_tbl.begin(); r != my_tbl.end(); ++r)
			std::cout << r->get_ArtistId() << std::endl;

	// Example #4
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<SQL_chinook_db_table_albums> my_tbl;
		// Example#4a -- (C++11) Range-based loop
		for(auto& row : my_tbl)
			std::cout << row.get_AlbumId() << " | " << row.get_Title() << " | " << row.get_ArtistId() << " | " << std::endl;

		// Example#4b -- C++ style iteration
		for (auto row = my_tbl.begin(); row != my_tbl.end(); ++row) 
			std::cout << row->get_AlbumId() << " | " << row->get_Title() << " | " << row->get_ArtistId() << " | " << std::endl;

		// Example#4c -- C style iteration
		for (int row = 0; row < my_tbl.size(); ++row) 
			std::cout << my_tbl[row].get_AlbumId() << " | " << my_tbl[row].get_Title() << " | " << my_tbl[row].get_ArtistId() << " | " << std::endl;
For more details see  https://github.com/David-Maisonave/sqlite3pp_EZ
*/
#ifndef SQL_CHINOOK_DB_TABLE_ALBUMS_H
#define SQL_CHINOOK_DB_TABLE_ALBUMS_H
#include <string>
#include "..\..\sqlite3pp_ez\sqlite3pp_ez.h"

class SQL_chinook_db_table_albums: public sqlite3pp::sql_base
{
	// A member variable for each field in the table
protected:
	Integer AlbumId = 0;
	Nvarchar Title;
	Integer ArtistId = 0;

public:
	using StrType = std::string;
	// Constructors
	SQL_chinook_db_table_albums() {} // Default constructor
	template <class T> SQL_chinook_db_table_albums(const T &t) { setData(t); } // Allows data input from different (or same) tables/views having the same data types and column names

	// getTableName, getColumnNames, getSelectColumnNames, and getStreamData are required for sqlite3pp::Table template class
	static StrType getTableName() { return "albums" ; }
	static StrType getColumnNames() { return "\"AlbumId\", \"Title\", \"ArtistId\""; }
	static StrType getSelectColumnNames() { return "\"AlbumId\", \"Title\", \"ArtistId\""; }
	StrType GetValues() const
	{
		StrType strtype;
		strtype +=  "'" + sqlite3pp::to_string( AlbumId) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Title) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( ArtistId) + "'";
		return strtype;
	}
	template<class T> void getStreamData( T q ) { q.getter()  >> AlbumId >> Title >> ArtistId;}
	template <class T> void setData(const T &t) // Used to transfer data from different tables/views having same data types and column names
	{
		AlbumId = t.get_AlbumId();
		Title = t.get_Title();
		ArtistId = t.get_ArtistId();
	}

	// Miscellaneous functions
	static int getColumnCount() { return 3; }

	// A get_ function for each field in the table, which allows read-only access to protected member variables.
	const Integer& get_AlbumId() const {return AlbumId;}
	const Nvarchar& get_Title() const {return Title;}
	const Integer& get_ArtistId() const {return ArtistId;}

	// A set_ function for each field in the table.
	void set_AlbumId(const Integer& data__) {AlbumId = data__;}
	void set_Title(const Nvarchar& data__) {Title = data__;}
	void set_ArtistId(const Integer& data__) {ArtistId = data__;}

	////////////////////////////////////////////////////////////////////////////////////////////
	/* sqlite3pp::TableOStream container interface.
	Functions OStream(), operator<<(), and Delimiter() are required when using the sqlite3pp::TableOStream container.
	Example Usage:		(Using sqlite3pp::TableOStream container)
			TableOStream<SQL_chinook_db_table_albums> tbl(DbFileNameArg("myDatabase.db"));
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
		t.os << AlbumId << t.d << t.str(Title) << t.d << ArtistId;
		return t;
	}
	friend std::ostream& operator<<(std::ostream& os, const SQL_chinook_db_table_albums& t);
	friend std::wostream& operator<<(std::wostream& os, const SQL_chinook_db_table_albums& t);
	static StrType Delimiter() { return "," ; }
	////////////////////////////////////////////////////////////////////////////////////////////
};
// sqlite3pp::TableOStream container interface.
inline std::ostream& operator<<(std::ostream& os, const SQL_chinook_db_table_albums& t) { sqlite3pp::ostream_a o(os, t.Delimiter()); return t.OStream(o).os; }
inline std::wostream& operator<<(std::wostream& os, const SQL_chinook_db_table_albums& t) { sqlite3pp::ostream_w o(os, t.Delimiter());  return t.OStream(o).os; }

#endif // !SQL_CHINOOK_DB_TABLE_ALBUMS_H
