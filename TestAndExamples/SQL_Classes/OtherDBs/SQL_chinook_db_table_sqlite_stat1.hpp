/* This file was automatically generated using [Sqlite3pp_EZ].
Sqlite3pp_EZ Copyright (C) 2025 David Maisonave (http::\www.axter.com)
Example Usage:		(Using sqlite3pp::Table container)
	// Example #1
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<SQL_chinook_db_table_sqlite_stat1> my_tbl;
		for (auto& row : my_tbl)
			std::cout << row << std::endl;

	// Example #2
		for (int i = 0; i < my_tbl.size(); ++i)
			std::cout << my_tbl[i].get_tbl() << std::endl;

	// Example #3
		for (auto r = my_tbl.begin(); r != my_tbl.end(); ++r)
			std::cout << r->get_stat() << std::endl;

	// Example #4
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<SQL_chinook_db_table_sqlite_stat1> my_tbl;
		// Example#4a -- (C++11) Range-based loop
		for(auto& row : my_tbl)
			std::cout << row.get_tbl() << " | " << row.get_idx() << " | " << row.get_stat() << " | " << std::endl;

		// Example#4b -- C++ style iteration
		for (auto row = my_tbl.begin(); row != my_tbl.end(); ++row) 
			std::cout << row->get_tbl() << " | " << row->get_idx() << " | " << row->get_stat() << " | " << std::endl;

		// Example#4c -- C style iteration
		for (int row = 0; row < my_tbl.size(); ++row) 
			std::cout << my_tbl[row].get_tbl() << " | " << my_tbl[row].get_idx() << " | " << my_tbl[row].get_stat() << " | " << std::endl;
For more details see  https://github.com/David-Maisonave/sqlite3pp_EZ
*/
#ifndef SQL_CHINOOK_DB_TABLE_SQLITE_STAT1_H
#define SQL_CHINOOK_DB_TABLE_SQLITE_STAT1_H
#include <string>
#include "..\..\sqlite3pp_ez\sqlite3pp_ez.h"

class SQL_chinook_db_table_sqlite_stat1: public sqlite3pp::sql_base
{
	// A member variable for each field in the table
protected:
	Text tbl;
	Text idx;
	Text stat;

public:
	using StrType = std::string;
	// Constructors
	SQL_chinook_db_table_sqlite_stat1() {} // Default constructor
	template <class T> SQL_chinook_db_table_sqlite_stat1(const T &t) { setData(t); } // Allows data input from different (or same) tables/views having the same data types and column names

	// getTableName, getColumnNames, getSelectColumnNames, and getStreamData are required for sqlite3pp::Table template class
	static StrType getTableName() { return "sqlite_stat1" ; }
	static StrType getColumnNames() { return "\"tbl\", \"idx\", \"stat\""; }
	static StrType getSelectColumnNames() { return "\"tbl\", \"idx\", \"stat\""; }
	StrType GetValues() const
	{
		StrType strtype;
		strtype +=  "'" + sqlite3pp::to_string( tbl) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( idx) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( stat) + "'";
		return strtype;
	}
	template<class T> void getStreamData( T q ) { q.getter()  >> tbl >> idx >> stat;}
	template <class T> void setData(const T &t) // Used to transfer data from different tables/views having same data types and column names
	{
		tbl = t.get_tbl();
		idx = t.get_idx();
		stat = t.get_stat();
	}

	// Miscellaneous functions
	static int getColumnCount() { return 3; }

	// A get_ function for each field in the table, which allows read-only access to protected member variables.
	const Text& get_tbl() const {return tbl;}
	const Text& get_idx() const {return idx;}
	const Text& get_stat() const {return stat;}

	// A set_ function for each field in the table.
	void set_tbl(const Text& data__) {tbl = data__;}
	void set_idx(const Text& data__) {idx = data__;}
	void set_stat(const Text& data__) {stat = data__;}

	////////////////////////////////////////////////////////////////////////////////////////////
	/* sqlite3pp::TableOStream container interface.
	Functions OStream(), operator<<(), and Delimiter() are required when using the sqlite3pp::TableOStream container.
	Example Usage:		(Using sqlite3pp::TableOStream container)
			TableOStream<SQL_chinook_db_table_sqlite_stat1> tbl(DbFileNameArg("myDatabase.db"));
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
		t.os << t.str(tbl) << t.d << t.str(idx) << t.d << t.str(stat);
		return t;
	}
	friend std::ostream& operator<<(std::ostream& os, const SQL_chinook_db_table_sqlite_stat1& t);
	friend std::wostream& operator<<(std::wostream& os, const SQL_chinook_db_table_sqlite_stat1& t);
	static StrType Delimiter() { return "," ; }
	////////////////////////////////////////////////////////////////////////////////////////////
};
// sqlite3pp::TableOStream container interface.
inline std::ostream& operator<<(std::ostream& os, const SQL_chinook_db_table_sqlite_stat1& t) { sqlite3pp::ostream_a o(os, t.Delimiter()); return t.OStream(o).os; }
inline std::wostream& operator<<(std::wostream& os, const SQL_chinook_db_table_sqlite_stat1& t) { sqlite3pp::ostream_w o(os, t.Delimiter());  return t.OStream(o).os; }

#endif // !SQL_CHINOOK_DB_TABLE_SQLITE_STAT1_H
