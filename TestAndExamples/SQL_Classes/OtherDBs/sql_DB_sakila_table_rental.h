/* This file was automatically generated using [Sqlite3pp_EZ].
Sqlite3pp_EZ Copyright (C) 2025 David Maisonave (http::\www.axter.com)
Example Usage:		(Using sqlite3pp::Table container)
	// Example #1
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_sakila_table_rental> my_tbl;
		for (auto row : my_tbl)
			std::wcout << row << std::endl;

	// Example #2
		for (int i = 0; i < my_tbl.size(); ++i)
			std::wcout << my_tbl[i].get_rental_id() << std::endl;

	// Example #3
		for (auto r = my_tbl.begin(); r != my_tbl.end(); ++r)
			std::wcout << r->get_last_update() << std::endl;

	// Example #4
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_sakila_table_rental> my_tbl;
		// Example#4a -- (C++11) Range-based loop
		for(auto row : my_tbl)
			std::cout << row.get_rental_id() << " | " << row.get_rental_date() << " | " << row.get_inventory_id() << " | " << row.get_customer_id() << " | " << row.get_return_date() << " | " << row.get_staff_id() << " | " << row.get_last_update() << " | " << std::endl;

		// Example#4b -- C++ style iteration
		for (auto row = my_tbl.begin(); row != my_tbl.end(); ++row) 
			std::cout << row->get_rental_id() << " | " << row->get_rental_date() << " | " << row->get_inventory_id() << " | " << row->get_customer_id() << " | " << row->get_return_date() << " | " << row->get_staff_id() << " | " << row->get_last_update() << " | " << std::endl;

		// Example#4c -- C style iteration
		for (int row = 0; row < my_tbl.size(); ++row) 
			std::cout << my_tbl[row].get_rental_id() << " | " << my_tbl[row].get_rental_date() << " | " << my_tbl[row].get_inventory_id() << " | " << my_tbl[row].get_customer_id() << " | " << my_tbl[row].get_return_date() << " | " << my_tbl[row].get_staff_id() << " | " << my_tbl[row].get_last_update() << " | " << std::endl;
For more details see  https://github.com/David-Maisonave/sqlite3pp_EZ
*/
#ifndef SQL_DB_SAKILA_TABLE_RENTAL_H
#define SQL_DB_SAKILA_TABLE_RENTAL_H
#include <string>
#include "..\sqlite3pp_ez.h"

class sql_DB_sakila_table_rental: public sqlite3pp::sql_base
{
	// A member variable for each field in the table
protected:
	Int rental_id = 0;
	Bigint rental_date;
	Int inventory_id = 0;
	Int customer_id = 0;
	Bigint return_date;
	Smallint staff_id;
	Bigint last_update;

public:
	using StrType = std::string;
	// Constructors
	sql_DB_sakila_table_rental() {} // Default constructor
	template <class T> sql_DB_sakila_table_rental(const T &t) { setData(t); } // Allows data input from different (or same) tables/views having the same data types and column names

	// getTableName, getColumnNames, getSelectColumnNames, and getStreamData are required for sqlite3pp::Table template class
	static StrType getTableName() { return "rental" ; }
	static StrType getColumnNames() { return "rental_id, rental_date, inventory_id, customer_id, return_date, staff_id, last_update"; }
	static StrType getSelectColumnNames() { return "\"rental_id\", \"rental_date\", \"inventory_id\", \"customer_id\", \"return_date\", \"staff_id\", \"last_update\""; }
	StrType GetValues() const
	{
		StrType strtype;
		strtype +=  "'" + sqlite3pp::to_string( rental_id) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( rental_date) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( inventory_id) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( customer_id) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( return_date) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( staff_id) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( last_update) + "'";
		return strtype;
	}
	template<class T> void getStreamData( T q ) { q.getter()  >> rental_id >> rental_date >> inventory_id >> customer_id >> return_date >> staff_id >> last_update;}
	template <class T> void setData(const T &t) // Used to transfer data from different tables/views having same data types and column names
	{
		rental_id = t.get_rental_id();
		rental_date = t.get_rental_date();
		inventory_id = t.get_inventory_id();
		customer_id = t.get_customer_id();
		return_date = t.get_return_date();
		staff_id = t.get_staff_id();
		last_update = t.get_last_update();
	}

	// Miscellaneous functions
	static int getColumnCount() { return 7; }

	// A get_ function for each field in the table, which allows read-only access to protected member variables.
	const Int& get_rental_id() const {return rental_id;}
	const Bigint& get_rental_date() const {return rental_date;}
	const Int& get_inventory_id() const {return inventory_id;}
	const Int& get_customer_id() const {return customer_id;}
	const Bigint& get_return_date() const {return return_date;}
	const Smallint& get_staff_id() const {return staff_id;}
	const Bigint& get_last_update() const {return last_update;}

	// A set_ function for each field in the table.
	void set_rental_id(const Int& data__) {rental_id = data__;}
	void set_rental_date(const Bigint& data__) {rental_date = data__;}
	void set_inventory_id(const Int& data__) {inventory_id = data__;}
	void set_customer_id(const Int& data__) {customer_id = data__;}
	void set_return_date(const Bigint& data__) {return_date = data__;}
	void set_staff_id(const Smallint& data__) {staff_id = data__;}
	void set_last_update(const Bigint& data__) {last_update = data__;}

	////////////////////////////////////////////////////////////////////////////////////////////
	/* sqlite3pp::TableOStream container interface.
	Functions OStream(), operator<<(), and Delimiter() are required when using the sqlite3pp::TableOStream container.
	Example Usage:		(Using sqlite3pp::TableOStream container)
			TableOStream<sql_DB_sakila_table_rental> tbl(DbFileNameArg("myDatabase.db"));
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
		t.os << rental_id << t.d << rental_date << t.d << inventory_id << t.d << customer_id << t.d << return_date << t.d << staff_id << t.d << last_update;
		return t;
	}
	friend std::ostream& operator<<(std::ostream& os, const sql_DB_sakila_table_rental& t);
	friend std::wostream& operator<<(std::wostream& os, const sql_DB_sakila_table_rental& t);
	static StrType Delimiter() { return "," ; }
	////////////////////////////////////////////////////////////////////////////////////////////
};
// sqlite3pp::TableOStream container interface.
inline std::ostream& operator<<(std::ostream& os, const sql_DB_sakila_table_rental& t) { sqlite3pp::ostream_a o(os, t.Delimiter()); return t.OStream(o).os; }
inline std::wostream& operator<<(std::wostream& os, const sql_DB_sakila_table_rental& t) { sqlite3pp::ostream_w o(os, t.Delimiter());  return t.OStream(o).os; }

#endif // !SQL_DB_SAKILA_TABLE_RENTAL_H
