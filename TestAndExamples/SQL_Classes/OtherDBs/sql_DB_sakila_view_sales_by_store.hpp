/* This file was automatically generated using [Sqlite3pp_EZ].
Sqlite3pp_EZ Copyright (C) 2025 David Maisonave (http::\www.axter.com)
Example Usage:		(Using sqlite3pp::Table container)
	// Example #1
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_sakila_view_sales_by_store> my_tbl;
		for (auto& row : my_tbl)
			std::cout << row << std::endl;

	// Example #2
		for (int i = 0; i < my_tbl.size(); ++i)
			std::cout << my_tbl[i].get_store_id() << std::endl;

	// Example #3
		for (auto r = my_tbl.begin(); r != my_tbl.end(); ++r)
			std::cout << r->get_total_sales() << std::endl;

	// Example #4
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_sakila_view_sales_by_store> my_tbl;
		// Example#4a -- (C++11) Range-based loop
		for(auto& row : my_tbl)
			std::cout << row.get_store_id() << " | " << row.get_store() << " | " << row.get_manager() << " | " << row.get_total_sales() << " | " << std::endl;

		// Example#4b -- C++ style iteration
		for (auto row = my_tbl.begin(); row != my_tbl.end(); ++row) 
			std::cout << row->get_store_id() << " | " << row->get_store() << " | " << row->get_manager() << " | " << row->get_total_sales() << " | " << std::endl;

		// Example#4c -- C style iteration
		for (int row = 0; row < my_tbl.size(); ++row) 
			std::cout << my_tbl[row].get_store_id() << " | " << my_tbl[row].get_store() << " | " << my_tbl[row].get_manager() << " | " << my_tbl[row].get_total_sales() << " | " << std::endl;
For more details see  https://github.com/David-Maisonave/sqlite3pp_EZ
*/
#ifndef SQL_DB_SAKILA_VIEW_SALES_BY_STORE_HPP
#define SQL_DB_SAKILA_VIEW_SALES_BY_STORE_HPP
#include <string>
#include "..\sqlite3pp_ez.h"

class sql_DB_sakila_view_sales_by_store: public sqlite3pp::sql_base
{
	// A member variable for each field in the table
protected:
	Int store_id = 0;
	Text store;
	Text manager;
	Text total_sales;

public:
	using StrType = std::string;
	// Constructors
	sql_DB_sakila_view_sales_by_store() {} // Default constructor
	template <class T> sql_DB_sakila_view_sales_by_store(const T &t) { setData(t); } // Allows data input from different (or same) tables/views having the same data types and column names

	// getTableName, getColumnNames, getSelectColumnNames, and getStreamData are required for sqlite3pp::Table template class
	static StrType getTableName() { return "sales_by_store" ; }
	static StrType getColumnNames() { return "\"store_id\", \"store\", \"manager\", \"total_sales\""; }
	static StrType getSelectColumnNames() { return "\"store_id\", \"store\", \"manager\", \"total_sales\""; }
	StrType GetValues() const
	{
		StrType strtype;
		strtype +=  "'" + sqlite3pp::to_string( store_id) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( store) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( manager) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( total_sales) + "'";
		return strtype;
	}
	template<class T> void getStreamData( T q ) { q.getter()  >> store_id >> store >> manager >> total_sales;}
	template <class T> void setData(const T &t) // Used to transfer data from different tables/views having same data types and column names
	{
		store_id = t.get_store_id();
		store = t.get_store();
		manager = t.get_manager();
		total_sales = t.get_total_sales();
	}

	// Miscellaneous functions
	static int getColumnCount() { return 4; }

	// A get_ function for each field in the table, which allows read-only access to protected member variables.
	const Int& get_store_id() const {return store_id;}
	const Text& get_store() const {return store;}
	const Text& get_manager() const {return manager;}
	const Text& get_total_sales() const {return total_sales;}

	// A set_ function for each field in the table.
	void set_store_id(const Int& data__) {store_id = data__;}
	void set_store(const Text& data__) {store = data__;}
	void set_manager(const Text& data__) {manager = data__;}
	void set_total_sales(const Text& data__) {total_sales = data__;}

	////////////////////////////////////////////////////////////////////////////////////////////
	/* sqlite3pp::TableOStream container interface.
	Functions OStream(), operator<<(), and Delimiter() are required when using the sqlite3pp::TableOStream container.
	Example Usage:		(Using sqlite3pp::TableOStream container)
			TableOStream<sql_DB_sakila_view_sales_by_store> tbl(DbFileNameArg("myDatabase.db"));
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
		t.os << store_id << t.d << t.str(store) << t.d << t.str(manager) << t.d << t.str(total_sales);
		return t;
	}
	friend std::ostream& operator<<(std::ostream& os, const sql_DB_sakila_view_sales_by_store& t);
	friend std::wostream& operator<<(std::wostream& os, const sql_DB_sakila_view_sales_by_store& t);
	static StrType Delimiter() { return "," ; }
	////////////////////////////////////////////////////////////////////////////////////////////
};
// sqlite3pp::TableOStream container interface.
inline std::ostream& operator<<(std::ostream& os, const sql_DB_sakila_view_sales_by_store& t) { sqlite3pp::ostream_a o(os, t.Delimiter()); return t.OStream(o).os; }
inline std::wostream& operator<<(std::wostream& os, const sql_DB_sakila_view_sales_by_store& t) { sqlite3pp::ostream_w o(os, t.Delimiter());  return t.OStream(o).os; }

#endif // !SQL_DB_SAKILA_VIEW_SALES_BY_STORE_HPP
