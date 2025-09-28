/* This file was automatically generated using [Sqlite3pp_EZ].
Sqlite3pp_EZ Copyright (C) 2025 David Maisonave (http::\www.axter.com)
Example Usage:		(Using sqlite3pp::Table container)
	// Example #1
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<SQL_sakila_db_table_address> my_tbl;
		for (auto& row : my_tbl)
			std::cout << row << std::endl;

	// Example #2
		for (int i = 0; i < my_tbl.size(); ++i)
			std::cout << my_tbl[i].get_address_id() << std::endl;

	// Example #3
		for (auto r = my_tbl.begin(); r != my_tbl.end(); ++r)
			std::cout << r->get_last_update() << std::endl;

	// Example #4
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<SQL_sakila_db_table_address> my_tbl;
		// Example#4a -- (C++11) Range-based loop
		for(auto& row : my_tbl)
			std::cout << row.get_address_id() << " | " << row.get_address() << " | " << row.get_address2() << " | " << row.get_district() << " | " << row.get_city_id() << " | " << row.get_postal_code() << " | " << row.get_phone() << " | " << row.get_last_update() << " | " << std::endl;

		// Example#4b -- C++ style iteration
		for (auto row = my_tbl.begin(); row != my_tbl.end(); ++row) 
			std::cout << row->get_address_id() << " | " << row->get_address() << " | " << row->get_address2() << " | " << row->get_district() << " | " << row->get_city_id() << " | " << row->get_postal_code() << " | " << row->get_phone() << " | " << row->get_last_update() << " | " << std::endl;

		// Example#4c -- C style iteration
		for (int row = 0; row < my_tbl.size(); ++row) 
			std::cout << my_tbl[row].get_address_id() << " | " << my_tbl[row].get_address() << " | " << my_tbl[row].get_address2() << " | " << my_tbl[row].get_district() << " | " << my_tbl[row].get_city_id() << " | " << my_tbl[row].get_postal_code() << " | " << my_tbl[row].get_phone() << " | " << my_tbl[row].get_last_update() << " | " << std::endl;
For more details see  https://github.com/David-Maisonave/sqlite3pp_EZ
*/
#ifndef SQL_SAKILA_DB_TABLE_ADDRESS_H
#define SQL_SAKILA_DB_TABLE_ADDRESS_H
#include <string>
#include "..\..\sqlite3pp_ez\sqlite3pp_ez.h"

class SQL_sakila_db_table_address: public sqlite3pp::sql_base
{
	// A member variable for each field in the table
protected:
	Int address_id = 0;
	Varchar address;
	Varchar address2;
	Varchar district;
	Int city_id = 0;
	Varchar postal_code;
	Varchar phone;
	Bigint last_update = 0;

public:
	using StrType = std::string;
	// Constructors
	SQL_sakila_db_table_address() {} // Default constructor
	template <class T> SQL_sakila_db_table_address(const T &t) { setData(t); } // Allows data input from different (or same) tables/views having the same data types and column names

	// getTableName, getColumnNames, getSelectColumnNames, and getStreamData are required for sqlite3pp::Table template class
	static StrType getTableName() { return "address" ; }
	static StrType getColumnNames() { return "\"address_id\", \"address\", \"address2\", \"district\", \"city_id\", \"postal_code\", \"phone\", \"last_update\""; }
	static StrType getSelectColumnNames() { return "\"address_id\", \"address\", \"address2\", \"district\", \"city_id\", \"postal_code\", \"phone\", \"last_update\""; }
	StrType GetValues() const
	{
		StrType strtype;
		strtype +=  "'" + sqlite3pp::to_string( address_id) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( address) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( address2) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( district) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( city_id) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( postal_code) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( phone) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( last_update) + "'";
		return strtype;
	}
	template<class T> void getStreamData( T q ) { q.getter()  >> address_id >> address >> address2 >> district >> city_id >> postal_code >> phone >> last_update;}
	template <class T> void setData(const T &t) // Used to transfer data from different tables/views having same data types and column names
	{
		address_id = t.get_address_id();
		address = t.get_address();
		address2 = t.get_address2();
		district = t.get_district();
		city_id = t.get_city_id();
		postal_code = t.get_postal_code();
		phone = t.get_phone();
		last_update = t.get_last_update();
	}

	// Miscellaneous functions
	static int getColumnCount() { return 8; }

	// A get_ function for each field in the table, which allows read-only access to protected member variables.
	const Int& get_address_id() const {return address_id;}
	const Varchar& get_address() const {return address;}
	const Varchar& get_address2() const {return address2;}
	const Varchar& get_district() const {return district;}
	const Int& get_city_id() const {return city_id;}
	const Varchar& get_postal_code() const {return postal_code;}
	const Varchar& get_phone() const {return phone;}
	const Bigint& get_last_update() const {return last_update;}

	// A set_ function for each field in the table.
	void set_address_id(const Int& data__) {address_id = data__;}
	void set_address(const Varchar& data__) {address = data__;}
	void set_address2(const Varchar& data__) {address2 = data__;}
	void set_district(const Varchar& data__) {district = data__;}
	void set_city_id(const Int& data__) {city_id = data__;}
	void set_postal_code(const Varchar& data__) {postal_code = data__;}
	void set_phone(const Varchar& data__) {phone = data__;}
	void set_last_update(const Bigint& data__) {last_update = data__;}

	////////////////////////////////////////////////////////////////////////////////////////////
	/* sqlite3pp::TableOStream container interface.
	Functions OStream(), operator<<(), and Delimiter() are required when using the sqlite3pp::TableOStream container.
	Example Usage:		(Using sqlite3pp::TableOStream container)
			TableOStream<SQL_sakila_db_table_address> tbl(DbFileNameArg("myDatabase.db"));
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
		t.os << address_id << t.d << t.str(address) << t.d << t.str(address2) << t.d << t.str(district) << t.d << city_id << t.d << t.str(postal_code) << t.d << t.str(phone) << t.d << last_update;
		return t;
	}
	friend std::ostream& operator<<(std::ostream& os, const SQL_sakila_db_table_address& t);
	friend std::wostream& operator<<(std::wostream& os, const SQL_sakila_db_table_address& t);
	static StrType Delimiter() { return "," ; }
	////////////////////////////////////////////////////////////////////////////////////////////
};
// sqlite3pp::TableOStream container interface.
inline std::ostream& operator<<(std::ostream& os, const SQL_sakila_db_table_address& t) { sqlite3pp::ostream_a o(os, t.Delimiter()); return t.OStream(o).os; }
inline std::wostream& operator<<(std::wostream& os, const SQL_sakila_db_table_address& t) { sqlite3pp::ostream_w o(os, t.Delimiter());  return t.OStream(o).os; }

#endif // !SQL_SAKILA_DB_TABLE_ADDRESS_H
