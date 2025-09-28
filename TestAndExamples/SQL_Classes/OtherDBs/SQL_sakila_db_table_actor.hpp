/* This file was automatically generated using [Sqlite3pp_EZ].
Sqlite3pp_EZ Copyright (C) 2025 David Maisonave (http::\www.axter.com)
Example Usage:		(Using sqlite3pp::Table container)
	// Example #1
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<SQL_sakila_db_table_actor> my_tbl;
		for (auto& row : my_tbl)
			std::cout << row << std::endl;

	// Example #2
		for (int i = 0; i < my_tbl.size(); ++i)
			std::cout << my_tbl[i].get_actor_id() << std::endl;

	// Example #3
		for (auto r = my_tbl.begin(); r != my_tbl.end(); ++r)
			std::cout << r->get_last_update() << std::endl;

	// Example #4
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<SQL_sakila_db_table_actor> my_tbl;
		// Example#4a -- (C++11) Range-based loop
		for(auto& row : my_tbl)
			std::cout << row.get_actor_id() << " | " << row.get_first_name() << " | " << row.get_last_name() << " | " << row.get_last_update() << " | " << std::endl;

		// Example#4b -- C++ style iteration
		for (auto row = my_tbl.begin(); row != my_tbl.end(); ++row) 
			std::cout << row->get_actor_id() << " | " << row->get_first_name() << " | " << row->get_last_name() << " | " << row->get_last_update() << " | " << std::endl;

		// Example#4c -- C style iteration
		for (int row = 0; row < my_tbl.size(); ++row) 
			std::cout << my_tbl[row].get_actor_id() << " | " << my_tbl[row].get_first_name() << " | " << my_tbl[row].get_last_name() << " | " << my_tbl[row].get_last_update() << " | " << std::endl;
For more details see  https://github.com/David-Maisonave/sqlite3pp_EZ
*/
#ifndef SQL_SAKILA_DB_TABLE_ACTOR_H
#define SQL_SAKILA_DB_TABLE_ACTOR_H
#include <string>
#include "..\..\sqlite3pp_ez\sqlite3pp_ez.h"

class SQL_sakila_db_table_actor: public sqlite3pp::sql_base
{
	// A member variable for each field in the table
protected:
	Numeric actor_id = 0.0f;
	Varchar first_name;
	Varchar last_name;
	Bigint last_update = 0;

public:
	using StrType = std::string;
	// Constructors
	SQL_sakila_db_table_actor() {} // Default constructor
	template <class T> SQL_sakila_db_table_actor(const T &t) { setData(t); } // Allows data input from different (or same) tables/views having the same data types and column names

	// getTableName, getColumnNames, getSelectColumnNames, and getStreamData are required for sqlite3pp::Table template class
	static StrType getTableName() { return "actor" ; }
	static StrType getColumnNames() { return "\"actor_id\", \"first_name\", \"last_name\", \"last_update\""; }
	static StrType getSelectColumnNames() { return "\"actor_id\", \"first_name\", \"last_name\", \"last_update\""; }
	StrType GetValues() const
	{
		StrType strtype;
		strtype +=  "'" + sqlite3pp::to_string( actor_id) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( first_name) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( last_name) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( last_update) + "'";
		return strtype;
	}
	template<class T> void getStreamData( T q ) { q.getter()  >> actor_id >> first_name >> last_name >> last_update;}
	template <class T> void setData(const T &t) // Used to transfer data from different tables/views having same data types and column names
	{
		actor_id = t.get_actor_id();
		first_name = t.get_first_name();
		last_name = t.get_last_name();
		last_update = t.get_last_update();
	}

	// Miscellaneous functions
	static int getColumnCount() { return 4; }

	// A get_ function for each field in the table, which allows read-only access to protected member variables.
	const Numeric& get_actor_id() const {return actor_id;}
	const Varchar& get_first_name() const {return first_name;}
	const Varchar& get_last_name() const {return last_name;}
	const Bigint& get_last_update() const {return last_update;}

	// A set_ function for each field in the table.
	void set_actor_id(const Numeric& data__) {actor_id = data__;}
	void set_first_name(const Varchar& data__) {first_name = data__;}
	void set_last_name(const Varchar& data__) {last_name = data__;}
	void set_last_update(const Bigint& data__) {last_update = data__;}

	////////////////////////////////////////////////////////////////////////////////////////////
	/* sqlite3pp::TableOStream container interface.
	Functions OStream(), operator<<(), and Delimiter() are required when using the sqlite3pp::TableOStream container.
	Example Usage:		(Using sqlite3pp::TableOStream container)
			TableOStream<SQL_sakila_db_table_actor> tbl(DbFileNameArg("myDatabase.db"));
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
		t.os << actor_id << t.d << t.str(first_name) << t.d << t.str(last_name) << t.d << last_update;
		return t;
	}
	friend std::ostream& operator<<(std::ostream& os, const SQL_sakila_db_table_actor& t);
	friend std::wostream& operator<<(std::wostream& os, const SQL_sakila_db_table_actor& t);
	static StrType Delimiter() { return "," ; }
	////////////////////////////////////////////////////////////////////////////////////////////
};
// sqlite3pp::TableOStream container interface.
inline std::ostream& operator<<(std::ostream& os, const SQL_sakila_db_table_actor& t) { sqlite3pp::ostream_a o(os, t.Delimiter()); return t.OStream(o).os; }
inline std::wostream& operator<<(std::wostream& os, const SQL_sakila_db_table_actor& t) { sqlite3pp::ostream_w o(os, t.Delimiter());  return t.OStream(o).os; }

#endif // !SQL_SAKILA_DB_TABLE_ACTOR_H
