/* This file was automatically generated using [Sqlite3pp_EZ].
Sqlite3pp_EZ Copyright (C) 2025 David Maisonave (http::\www.axter.com)
Example Usage:		(Using sqlite3pp::Table container)
	// Example #1
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_sakila_table_store> my_tbl;
		for (auto& row : my_tbl)
			std::cout << row << std::endl;

	// Example #2
		for (int i = 0; i < my_tbl.size(); ++i)
			std::cout << my_tbl[i].get_store_id() << std::endl;

	// Example #3
		for (auto r = my_tbl.begin(); r != my_tbl.end(); ++r)
			std::cout << r->get_last_update() << std::endl;

	// Example #4
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_sakila_table_store> my_tbl;
		// Example#4a -- (C++11) Range-based loop
		for(auto& row : my_tbl)
			std::cout << row.get_store_id() << " | " << row.get_manager_staff_id() << " | " << row.get_address_id() << " | " << row.get_last_update() << " | " << std::endl;

		// Example#4b -- C++ style iteration
		for (auto row = my_tbl.begin(); row != my_tbl.end(); ++row) 
			std::cout << row->get_store_id() << " | " << row->get_manager_staff_id() << " | " << row->get_address_id() << " | " << row->get_last_update() << " | " << std::endl;

		// Example#4c -- C style iteration
		for (int row = 0; row < my_tbl.size(); ++row) 
			std::cout << my_tbl[row].get_store_id() << " | " << my_tbl[row].get_manager_staff_id() << " | " << my_tbl[row].get_address_id() << " | " << my_tbl[row].get_last_update() << " | " << std::endl;
For more details see  https://github.com/David-Maisonave/sqlite3pp_EZ
*/
#ifndef SQL_DB_SAKILA_TABLE_STORE_H
#define SQL_DB_SAKILA_TABLE_STORE_H
#include <string>
#include "..\sqlite3pp_ez.h"

class sql_DB_sakila_table_store: public sqlite3pp::sql_base
{
	// A member variable for each field in the table
protected:
	Int store_id = 0;
	Smallint manager_staff_id = 0;
	Int address_id = 0;
	Bigint last_update = 0;

public:
	using StrType = std::string;
	// Constructors
	sql_DB_sakila_table_store() {} // Default constructor
	template <class T> sql_DB_sakila_table_store(const T &t) { setData(t); } // Allows data input from different (or same) tables/views having the same data types and column names

	// getTableName, getColumnNames, getSelectColumnNames, and getStreamData are required for sqlite3pp::Table template class
	static StrType getTableName() { return "store" ; }
	static StrType getColumnNames() { return "\"store_id\", \"manager_staff_id\", \"address_id\", \"last_update\""; }
	static StrType getSelectColumnNames() { return "\"store_id\", \"manager_staff_id\", \"address_id\", \"last_update\""; }
	StrType GetValues() const
	{
		StrType strtype;
		strtype +=  "'" + sqlite3pp::to_string( store_id) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( manager_staff_id) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( address_id) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( last_update) + "'";
		return strtype;
	}
	template<class T> void getStreamData( T q ) { q.getter()  >> store_id >> manager_staff_id >> address_id >> last_update;}
	template <class T> void setData(const T &t) // Used to transfer data from different tables/views having same data types and column names
	{
		store_id = t.get_store_id();
		manager_staff_id = t.get_manager_staff_id();
		address_id = t.get_address_id();
		last_update = t.get_last_update();
	}

	// Miscellaneous functions
	static int getColumnCount() { return 4; }

	// A get_ function for each field in the table, which allows read-only access to protected member variables.
	const Int& get_store_id() const {return store_id;}
	const Smallint& get_manager_staff_id() const {return manager_staff_id;}
	const Int& get_address_id() const {return address_id;}
	const Bigint& get_last_update() const {return last_update;}

	// A set_ function for each field in the table.
	void set_store_id(const Int& data__) {store_id = data__;}
	void set_manager_staff_id(const Smallint& data__) {manager_staff_id = data__;}
	void set_address_id(const Int& data__) {address_id = data__;}
	void set_last_update(const Bigint& data__) {last_update = data__;}

	////////////////////////////////////////////////////////////////////////////////////////////
	/* sqlite3pp::TableOStream container interface.
	Functions OStream(), operator<<(), and Delimiter() are required when using the sqlite3pp::TableOStream container.
	Example Usage:		(Using sqlite3pp::TableOStream container)
			TableOStream<sql_DB_sakila_table_store> tbl(DbFileNameArg("myDatabase.db"));
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
		t.os << store_id << t.d << manager_staff_id << t.d << address_id << t.d << last_update;
		return t;
	}
	friend std::ostream& operator<<(std::ostream& os, const sql_DB_sakila_table_store& t);
	friend std::wostream& operator<<(std::wostream& os, const sql_DB_sakila_table_store& t);
	static StrType Delimiter() { return "," ; }
	////////////////////////////////////////////////////////////////////////////////////////////
};
// sqlite3pp::TableOStream container interface.
inline std::ostream& operator<<(std::ostream& os, const sql_DB_sakila_table_store& t) { sqlite3pp::ostream_a o(os, t.Delimiter()); return t.OStream(o).os; }
inline std::wostream& operator<<(std::wostream& os, const sql_DB_sakila_table_store& t) { sqlite3pp::ostream_w o(os, t.Delimiter());  return t.OStream(o).os; }

#endif // !SQL_DB_SAKILA_TABLE_STORE_H
