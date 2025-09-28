/* This file was automatically generated using [Sqlite3pp_EZ].
Sqlite3pp_EZ Copyright (C) 2025 David Maisonave (http::\www.axter.com)
Example Usage:		(Using sqlite3pp::Table container)
	// Example #1
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<SQL_sakila_db_table_customer> my_tbl;
		for (auto& row : my_tbl)
			std::cout << row << std::endl;

	// Example #2
		for (int i = 0; i < my_tbl.size(); ++i)
			std::cout << my_tbl[i].get_customer_id() << std::endl;

	// Example #3
		for (auto r = my_tbl.begin(); r != my_tbl.end(); ++r)
			std::cout << r->get_last_update() << std::endl;

	// Example #4
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<SQL_sakila_db_table_customer> my_tbl;
		// Example#4a -- (C++11) Range-based loop
		for(auto& row : my_tbl)
			std::cout << row.get_customer_id() << " | " << row.get_store_id() << " | " << row.get_first_name() << " | " << row.get_last_name() << " | " << row.get_email() << " | " << row.get_address_id() << " | " << row.get_active() << " | " << row.get_create_date() << " | " << row.get_last_update() << " | " << std::endl;

		// Example#4b -- C++ style iteration
		for (auto row = my_tbl.begin(); row != my_tbl.end(); ++row) 
			std::cout << row->get_customer_id() << " | " << row->get_store_id() << " | " << row->get_first_name() << " | " << row->get_last_name() << " | " << row->get_email() << " | " << row->get_address_id() << " | " << row->get_active() << " | " << row->get_create_date() << " | " << row->get_last_update() << " | " << std::endl;

		// Example#4c -- C style iteration
		for (int row = 0; row < my_tbl.size(); ++row) 
			std::cout << my_tbl[row].get_customer_id() << " | " << my_tbl[row].get_store_id() << " | " << my_tbl[row].get_first_name() << " | " << my_tbl[row].get_last_name() << " | " << my_tbl[row].get_email() << " | " << my_tbl[row].get_address_id() << " | " << my_tbl[row].get_active() << " | " << my_tbl[row].get_create_date() << " | " << my_tbl[row].get_last_update() << " | " << std::endl;
For more details see  https://github.com/David-Maisonave/sqlite3pp_EZ
*/
#ifndef SQL_SAKILA_DB_TABLE_CUSTOMER_H
#define SQL_SAKILA_DB_TABLE_CUSTOMER_H
#include <string>
#include "..\..\sqlite3pp_ez\sqlite3pp_ez.h"

class SQL_sakila_db_table_customer: public sqlite3pp::sql_base
{
	// A member variable for each field in the table
protected:
	Int customer_id = 0;
	Int store_id = 0;
	Varchar first_name;
	Varchar last_name;
	Varchar email;
	Int address_id = 0;
	Character active;
	Bigint create_date = 0;
	Bigint last_update = 0;

public:
	using StrType = std::string;
	// Constructors
	SQL_sakila_db_table_customer() {} // Default constructor
	template <class T> SQL_sakila_db_table_customer(const T &t) { setData(t); } // Allows data input from different (or same) tables/views having the same data types and column names

	// getTableName, getColumnNames, getSelectColumnNames, and getStreamData are required for sqlite3pp::Table template class
	static StrType getTableName() { return "customer" ; }
	static StrType getColumnNames() { return "\"customer_id\", \"store_id\", \"first_name\", \"last_name\", \"email\", \"address_id\", \"active\", \"create_date\", \"last_update\""; }
	static StrType getSelectColumnNames() { return "\"customer_id\", \"store_id\", \"first_name\", \"last_name\", \"email\", \"address_id\", \"active\", \"create_date\", \"last_update\""; }
	StrType GetValues() const
	{
		StrType strtype;
		strtype +=  "'" + sqlite3pp::to_string( customer_id) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( store_id) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( first_name) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( last_name) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( email) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( address_id) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( active) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( create_date) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( last_update) + "'";
		return strtype;
	}
	template<class T> void getStreamData( T q ) { q.getter()  >> customer_id >> store_id >> first_name >> last_name >> email >> address_id >> active >> create_date >> last_update;}
	template <class T> void setData(const T &t) // Used to transfer data from different tables/views having same data types and column names
	{
		customer_id = t.get_customer_id();
		store_id = t.get_store_id();
		first_name = t.get_first_name();
		last_name = t.get_last_name();
		email = t.get_email();
		address_id = t.get_address_id();
		active = t.get_active();
		create_date = t.get_create_date();
		last_update = t.get_last_update();
	}

	// Miscellaneous functions
	static int getColumnCount() { return 9; }

	// A get_ function for each field in the table, which allows read-only access to protected member variables.
	const Int& get_customer_id() const {return customer_id;}
	const Int& get_store_id() const {return store_id;}
	const Varchar& get_first_name() const {return first_name;}
	const Varchar& get_last_name() const {return last_name;}
	const Varchar& get_email() const {return email;}
	const Int& get_address_id() const {return address_id;}
	const Character& get_active() const {return active;}
	const Bigint& get_create_date() const {return create_date;}
	const Bigint& get_last_update() const {return last_update;}

	// A set_ function for each field in the table.
	void set_customer_id(const Int& data__) {customer_id = data__;}
	void set_store_id(const Int& data__) {store_id = data__;}
	void set_first_name(const Varchar& data__) {first_name = data__;}
	void set_last_name(const Varchar& data__) {last_name = data__;}
	void set_email(const Varchar& data__) {email = data__;}
	void set_address_id(const Int& data__) {address_id = data__;}
	void set_active(const Character& data__) {active = data__;}
	void set_create_date(const Bigint& data__) {create_date = data__;}
	void set_last_update(const Bigint& data__) {last_update = data__;}

	////////////////////////////////////////////////////////////////////////////////////////////
	/* sqlite3pp::TableOStream container interface.
	Functions OStream(), operator<<(), and Delimiter() are required when using the sqlite3pp::TableOStream container.
	Example Usage:		(Using sqlite3pp::TableOStream container)
			TableOStream<SQL_sakila_db_table_customer> tbl(DbFileNameArg("myDatabase.db"));
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
		t.os << customer_id << t.d << store_id << t.d << t.str(first_name) << t.d << t.str(last_name) << t.d << t.str(email) << t.d << address_id << t.d << t.str(active) << t.d << create_date << t.d << last_update;
		return t;
	}
	friend std::ostream& operator<<(std::ostream& os, const SQL_sakila_db_table_customer& t);
	friend std::wostream& operator<<(std::wostream& os, const SQL_sakila_db_table_customer& t);
	static StrType Delimiter() { return "," ; }
	////////////////////////////////////////////////////////////////////////////////////////////
};
// sqlite3pp::TableOStream container interface.
inline std::ostream& operator<<(std::ostream& os, const SQL_sakila_db_table_customer& t) { sqlite3pp::ostream_a o(os, t.Delimiter()); return t.OStream(o).os; }
inline std::wostream& operator<<(std::wostream& os, const SQL_sakila_db_table_customer& t) { sqlite3pp::ostream_w o(os, t.Delimiter());  return t.OStream(o).os; }

#endif // !SQL_SAKILA_DB_TABLE_CUSTOMER_H
