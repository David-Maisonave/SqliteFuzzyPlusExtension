/* This file was automatically generated using [Sqlite3pp_EZ].
Sqlite3pp_EZ Copyright (C) 2025 David Maisonave (http::\www.axter.com)
Example Usage:		(Using sqlite3pp::Table container)
	// Example #1
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_sakila_table_city> my_tbl;
		for (auto row : my_tbl)
			std::wcout << row << std::endl;

	// Example #2
		for (int i = 0; i < my_tbl.size(); ++i)
			std::wcout << my_tbl[i].get_city_id() << std::endl;

	// Example #3
		for (auto r = my_tbl.begin(); r != my_tbl.end(); ++r)
			std::wcout << r->get_last_update() << std::endl;

	// Example #4
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_sakila_table_city> my_tbl;
		// Example#4a -- (C++11) Range-based loop
		for(auto row : my_tbl)
			std::cout << row.get_city_id() << " | " << row.get_city() << " | " << row.get_country_id() << " | " << row.get_last_update() << " | " << std::endl;

		// Example#4b -- C++ style iteration
		for (auto row = my_tbl.begin(); row != my_tbl.end(); ++row) 
			std::cout << row->get_city_id() << " | " << row->get_city() << " | " << row->get_country_id() << " | " << row->get_last_update() << " | " << std::endl;

		// Example#4c -- C style iteration
		for (int row = 0; row < my_tbl.size(); ++row) 
			std::cout << my_tbl[row].get_city_id() << " | " << my_tbl[row].get_city() << " | " << my_tbl[row].get_country_id() << " | " << my_tbl[row].get_last_update() << " | " << std::endl;
For more details see  https://github.com/David-Maisonave/sqlite3pp_EZ
*/
#ifndef SQL_DB_SAKILA_TABLE_CITY_H
#define SQL_DB_SAKILA_TABLE_CITY_H
#include <string>
#include "..\sqlite3pp_ez.h"

class sql_DB_sakila_table_city: public sqlite3pp::sql_base
{
	// A member variable for each field in the table
protected:
	Int city_id = 0;
	Varchar city;
	Smallint country_id;
	Bigint last_update;

public:
	using StrType = std::string;
	// Constructors
	sql_DB_sakila_table_city() {} // Default constructor
	template <class T> sql_DB_sakila_table_city(const T &t) { setData(t); } // Allows data input from different (or same) tables/views having the same data types and column names

	// getTableName, getColumnNames, getSelectColumnNames, and getStreamData are required for sqlite3pp::Table template class
	static StrType getTableName() { return "city" ; }
	static StrType getColumnNames() { return "city_id, city, country_id, last_update"; }
	static StrType getSelectColumnNames() { return "\"city_id\", \"city\", \"country_id\", \"last_update\""; }
	StrType GetValues() const
	{
		StrType strtype;
		strtype +=  "'" + sqlite3pp::to_string( city_id) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( city) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( country_id) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( last_update) + "'";
		return strtype;
	}
	template<class T> void getStreamData( T q ) { q.getter()  >> city_id >> city >> country_id >> last_update;}
	template <class T> void setData(const T &t) // Used to transfer data from different tables/views having same data types and column names
	{
		city_id = t.get_city_id();
		city = t.get_city();
		country_id = t.get_country_id();
		last_update = t.get_last_update();
	}

	// Miscellaneous functions
	static int getColumnCount() { return 4; }

	// A get_ function for each field in the table, which allows read-only access to protected member variables.
	const Int& get_city_id() const {return city_id;}
	const Varchar& get_city() const {return city;}
	const Smallint& get_country_id() const {return country_id;}
	const Bigint& get_last_update() const {return last_update;}

	// A set_ function for each field in the table.
	void set_city_id(const Int& data__) {city_id = data__;}
	void set_city(const Varchar& data__) {city = data__;}
	void set_country_id(const Smallint& data__) {country_id = data__;}
	void set_last_update(const Bigint& data__) {last_update = data__;}

	////////////////////////////////////////////////////////////////////////////////////////////
	/* sqlite3pp::TableOStream container interface.
	Functions OStream(), operator<<(), and Delimiter() are required when using the sqlite3pp::TableOStream container.
	Example Usage:		(Using sqlite3pp::TableOStream container)
			TableOStream<sql_DB_sakila_table_city> tbl(DbFileNameArg("myDatabase.db"));
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
		t.os << city_id << t.d << t.str(city) << t.d << country_id << t.d << last_update;
		return t;
	}
	friend std::ostream& operator<<(std::ostream& os, const sql_DB_sakila_table_city& t);
	friend std::wostream& operator<<(std::wostream& os, const sql_DB_sakila_table_city& t);
	static StrType Delimiter() { return "," ; }
	////////////////////////////////////////////////////////////////////////////////////////////
};
// sqlite3pp::TableOStream container interface.
inline std::ostream& operator<<(std::ostream& os, const sql_DB_sakila_table_city& t) { sqlite3pp::ostream_a o(os, t.Delimiter()); return t.OStream(o).os; }
inline std::wostream& operator<<(std::wostream& os, const sql_DB_sakila_table_city& t) { sqlite3pp::ostream_w o(os, t.Delimiter());  return t.OStream(o).os; }

#endif // !SQL_DB_SAKILA_TABLE_CITY_H
