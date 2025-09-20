/* This file was automatically generated using [Sqlite3pp_EZ].
Sqlite3pp_EZ Copyright (C) 2025 David Maisonave (http::\www.axter.com)
Example Usage:		(Using sqlite3pp::Table container)
	// Example #1
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_chinook_table_tracks> my_tbl;
		for (auto row : my_tbl)
			std::wcout << row << std::endl;

	// Example #2
		for (int i = 0; i < my_tbl.size(); ++i)
			std::wcout << my_tbl[i].get_TrackId() << std::endl;

	// Example #3
		for (auto r = my_tbl.begin(); r != my_tbl.end(); ++r)
			std::wcout << r->get_UnitPrice() << std::endl;

	// Example #4
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_chinook_table_tracks> my_tbl;
		// Example#4a -- (C++11) Range-based loop
		for(auto row : my_tbl)
			std::cout << row.get_TrackId() << " | " << row.get_Name() << " | " << row.get_AlbumId() << " | " << row.get_MediaTypeId() << " | " << row.get_GenreId() << " | " << row.get_Composer() << " | " << row.get_Milliseconds() << " | " << row.get_Bytes() << " | " << row.get_UnitPrice() << " | " << std::endl;

		// Example#4b -- C++ style iteration
		for (auto row = my_tbl.begin(); row != my_tbl.end(); ++row) 
			std::cout << row->get_TrackId() << " | " << row->get_Name() << " | " << row->get_AlbumId() << " | " << row->get_MediaTypeId() << " | " << row->get_GenreId() << " | " << row->get_Composer() << " | " << row->get_Milliseconds() << " | " << row->get_Bytes() << " | " << row->get_UnitPrice() << " | " << std::endl;

		// Example#4c -- C style iteration
		for (int row = 0; row < my_tbl.size(); ++row) 
			std::cout << my_tbl[row].get_TrackId() << " | " << my_tbl[row].get_Name() << " | " << my_tbl[row].get_AlbumId() << " | " << my_tbl[row].get_MediaTypeId() << " | " << my_tbl[row].get_GenreId() << " | " << my_tbl[row].get_Composer() << " | " << my_tbl[row].get_Milliseconds() << " | " << my_tbl[row].get_Bytes() << " | " << my_tbl[row].get_UnitPrice() << " | " << std::endl;
For more details see  https://github.com/David-Maisonave/sqlite3pp_EZ
*/
#ifndef SQL_DB_CHINOOK_TABLE_TRACKS_H
#define SQL_DB_CHINOOK_TABLE_TRACKS_H
#include <string>
#include "..\sqlite3pp_ez.h"

class sql_DB_chinook_table_tracks: public sqlite3pp::sql_base
{
	// A member variable for each field in the table
protected:
	Integer TrackId = 0;
	Nvarchar Name;
	Integer AlbumId = 0;
	Integer MediaTypeId = 0;
	Integer GenreId = 0;
	Nvarchar Composer;
	Integer Milliseconds = 0;
	Integer Bytes = 0;
	Numeric UnitPrice = 0.0f;

public:
	using StrType = std::string;
	// Constructors
	sql_DB_chinook_table_tracks() {} // Default constructor
	template <class T> sql_DB_chinook_table_tracks(const T &t) { setData(t); } // Allows data input from different (or same) tables/views having the same data types and column names

	// getTableName, getColumnNames, getSelectColumnNames, and getStreamData are required for sqlite3pp::Table template class
	static StrType getTableName() { return "tracks" ; }
	static StrType getColumnNames() { return "\"TrackId\", \"Name\", \"AlbumId\", \"MediaTypeId\", \"GenreId\", \"Composer\", \"Milliseconds\", \"Bytes\", \"UnitPrice\""; }
	static StrType getSelectColumnNames() { return "\"TrackId\", \"Name\", \"AlbumId\", \"MediaTypeId\", \"GenreId\", \"Composer\", \"Milliseconds\", \"Bytes\", \"UnitPrice\""; }
	StrType GetValues() const
	{
		StrType strtype;
		strtype +=  "'" + sqlite3pp::to_string( TrackId) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Name) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( AlbumId) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( MediaTypeId) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( GenreId) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Composer) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Milliseconds) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Bytes) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( UnitPrice) + "'";
		return strtype;
	}
	template<class T> void getStreamData( T q ) { q.getter()  >> TrackId >> Name >> AlbumId >> MediaTypeId >> GenreId >> Composer >> Milliseconds >> Bytes >> UnitPrice;}
	template <class T> void setData(const T &t) // Used to transfer data from different tables/views having same data types and column names
	{
		TrackId = t.get_TrackId();
		Name = t.get_Name();
		AlbumId = t.get_AlbumId();
		MediaTypeId = t.get_MediaTypeId();
		GenreId = t.get_GenreId();
		Composer = t.get_Composer();
		Milliseconds = t.get_Milliseconds();
		Bytes = t.get_Bytes();
		UnitPrice = t.get_UnitPrice();
	}

	// Miscellaneous functions
	static int getColumnCount() { return 9; }

	// A get_ function for each field in the table, which allows read-only access to protected member variables.
	const Integer& get_TrackId() const {return TrackId;}
	const Nvarchar& get_Name() const {return Name;}
	const Integer& get_AlbumId() const {return AlbumId;}
	const Integer& get_MediaTypeId() const {return MediaTypeId;}
	const Integer& get_GenreId() const {return GenreId;}
	const Nvarchar& get_Composer() const {return Composer;}
	const Integer& get_Milliseconds() const {return Milliseconds;}
	const Integer& get_Bytes() const {return Bytes;}
	const Numeric& get_UnitPrice() const {return UnitPrice;}

	// A set_ function for each field in the table.
	void set_TrackId(const Integer& data__) {TrackId = data__;}
	void set_Name(const Nvarchar& data__) {Name = data__;}
	void set_AlbumId(const Integer& data__) {AlbumId = data__;}
	void set_MediaTypeId(const Integer& data__) {MediaTypeId = data__;}
	void set_GenreId(const Integer& data__) {GenreId = data__;}
	void set_Composer(const Nvarchar& data__) {Composer = data__;}
	void set_Milliseconds(const Integer& data__) {Milliseconds = data__;}
	void set_Bytes(const Integer& data__) {Bytes = data__;}
	void set_UnitPrice(const Numeric& data__) {UnitPrice = data__;}

	////////////////////////////////////////////////////////////////////////////////////////////
	/* sqlite3pp::TableOStream container interface.
	Functions OStream(), operator<<(), and Delimiter() are required when using the sqlite3pp::TableOStream container.
	Example Usage:		(Using sqlite3pp::TableOStream container)
			TableOStream<sql_DB_chinook_table_tracks> tbl(DbFileNameArg("myDatabase.db"));
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
		t.os << TrackId << t.d << t.str(Name) << t.d << AlbumId << t.d << MediaTypeId << t.d << GenreId << t.d << t.str(Composer) << t.d << Milliseconds << t.d << Bytes << t.d << UnitPrice;
		return t;
	}
	friend std::ostream& operator<<(std::ostream& os, const sql_DB_chinook_table_tracks& t);
	friend std::wostream& operator<<(std::wostream& os, const sql_DB_chinook_table_tracks& t);
	static StrType Delimiter() { return "," ; }
	////////////////////////////////////////////////////////////////////////////////////////////
};
// sqlite3pp::TableOStream container interface.
inline std::ostream& operator<<(std::ostream& os, const sql_DB_chinook_table_tracks& t) { sqlite3pp::ostream_a o(os, t.Delimiter()); return t.OStream(o).os; }
inline std::wostream& operator<<(std::wostream& os, const sql_DB_chinook_table_tracks& t) { sqlite3pp::ostream_w o(os, t.Delimiter());  return t.OStream(o).os; }

#endif // !SQL_DB_CHINOOK_TABLE_TRACKS_H
