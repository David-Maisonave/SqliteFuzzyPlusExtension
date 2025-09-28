/* This file was automatically generated using [Sqlite3pp_EZ].
Sqlite3pp_EZ Copyright (C) 2025 David Maisonave (http::\www.axter.com)
Example Usage:		(Using sqlite3pp::Table container)
	// Example #1
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<SQL_sakila_db_view_customer_list> my_tbl;
		for (auto& row : my_tbl)
			std::cout << row << std::endl;

	// Example #2
		for (int i = 0; i < my_tbl.size(); ++i)
			std::cout << my_tbl[i].get_ID() << std::endl;

	// Example #3
		for (auto r = my_tbl.begin(); r != my_tbl.end(); ++r)
			std::cout << r->get_SID() << std::endl;

	// Example #4
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<SQL_sakila_db_view_customer_list> my_tbl;
		// Example#4a -- (C++11) Range-based loop
		for(auto& row : my_tbl)
			std::cout << row.get_ID() << " | " << row.get_name() << " | " << row.get_address() << " | " << row.get_zip_code() << " | " << row.get_phone() << " | " << row.get_city() << " | " << row.get_country() << " | " << row.get_notes() << " | " << row.get_SID() << " | " << std::endl;

		// Example#4b -- C++ style iteration
		for (auto row = my_tbl.begin(); row != my_tbl.end(); ++row) 
			std::cout << row->get_ID() << " | " << row->get_name() << " | " << row->get_address() << " | " << row->get_zip_code() << " | " << row->get_phone() << " | " << row->get_city() << " | " << row->get_country() << " | " << row->get_notes() << " | " << row->get_SID() << " | " << std::endl;

		// Example#4c -- C style iteration
		for (int row = 0; row < my_tbl.size(); ++row) 
			std::cout << my_tbl[row].get_ID() << " | " << my_tbl[row].get_name() << " | " << my_tbl[row].get_address() << " | " << my_tbl[row].get_zip_code() << " | " << my_tbl[row].get_phone() << " | " << my_tbl[row].get_city() << " | " << my_tbl[row].get_country() << " | " << my_tbl[row].get_notes() << " | " << my_tbl[row].get_SID() << " | " << std::endl;
For more details see  https://github.com/David-Maisonave/sqlite3pp_EZ
*/
#ifndef SQL_SAKILA_DB_VIEW_CUSTOMER_LIST_H
#define SQL_SAKILA_DB_VIEW_CUSTOMER_LIST_H
#include <string>
#include "..\..\sqlite3pp_ez\sqlite3pp_ez.h"

class SQL_sakila_db_view_customer_list: public sqlite3pp::sql_base
{
	// A member variable for each field in the table
protected:
	Int ID = 0;
	Text name;
	Varchar address;
	Varchar zip_code;
	Varchar phone;
	Varchar city;
	Varchar country;
	Text notes;
	Int SID = 0;

public:
	using StrType = std::string;
	// Constructors
	SQL_sakila_db_view_customer_list() {} // Default constructor
	template <class T> SQL_sakila_db_view_customer_list(const T &t) { setData(t); } // Allows data input from different (or same) tables/views having the same data types and column names

	// getTableName, getColumnNames, getSelectColumnNames, and getStreamData are required for sqlite3pp::Table template class
	static StrType getTableName() { return "customer_list" ; }
	static StrType getColumnNames() { return "\"ID\", \"name\", \"address\", \"zip_code\", \"phone\", \"city\", \"country\", \"notes\", \"SID\""; }
	static StrType getSelectColumnNames() { return "\"ID\", \"name\", \"address\", \"zip_code\", \"phone\", \"city\", \"country\", \"notes\", \"SID\""; }
	StrType GetValues() const
	{
		StrType strtype;
		strtype +=  "'" + sqlite3pp::to_string( ID) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( name) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( address) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( zip_code) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( phone) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( city) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( country) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( notes) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( SID) + "'";
		return strtype;
	}
	template<class T> void getStreamData( T q ) { q.getter()  >> ID >> name >> address >> zip_code >> phone >> city >> country >> notes >> SID;}
	template <class T> void setData(const T &t) // Used to transfer data from different tables/views having same data types and column names
	{
		ID = t.get_ID();
		name = t.get_name();
		address = t.get_address();
		zip_code = t.get_zip_code();
		phone = t.get_phone();
		city = t.get_city();
		country = t.get_country();
		notes = t.get_notes();
		SID = t.get_SID();
	}

	// Miscellaneous functions
	static int getColumnCount() { return 9; }

	// A get_ function for each field in the table, which allows read-only access to protected member variables.
	const Int& get_ID() const {return ID;}
	const Text& get_name() const {return name;}
	const Varchar& get_address() const {return address;}
	const Varchar& get_zip_code() const {return zip_code;}
	const Varchar& get_phone() const {return phone;}
	const Varchar& get_city() const {return city;}
	const Varchar& get_country() const {return country;}
	const Text& get_notes() const {return notes;}
	const Int& get_SID() const {return SID;}

	// A set_ function for each field in the table.
	void set_ID(const Int& data__) {ID = data__;}
	void set_name(const Text& data__) {name = data__;}
	void set_address(const Varchar& data__) {address = data__;}
	void set_zip_code(const Varchar& data__) {zip_code = data__;}
	void set_phone(const Varchar& data__) {phone = data__;}
	void set_city(const Varchar& data__) {city = data__;}
	void set_country(const Varchar& data__) {country = data__;}
	void set_notes(const Text& data__) {notes = data__;}
	void set_SID(const Int& data__) {SID = data__;}

	////////////////////////////////////////////////////////////////////////////////////////////
	/* sqlite3pp::TableOStream container interface.
	Functions OStream(), operator<<(), and Delimiter() are required when using the sqlite3pp::TableOStream container.
	Example Usage:		(Using sqlite3pp::TableOStream container)
			TableOStream<SQL_sakila_db_view_customer_list> tbl(DbFileNameArg("myDatabase.db"));
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
		t.os << ID << t.d << t.str(name) << t.d << t.str(address) << t.d << t.str(zip_code) << t.d << t.str(phone) << t.d << t.str(city) << t.d << t.str(country) << t.d << t.str(notes) << t.d << SID;
		return t;
	}
	friend std::ostream& operator<<(std::ostream& os, const SQL_sakila_db_view_customer_list& t);
	friend std::wostream& operator<<(std::wostream& os, const SQL_sakila_db_view_customer_list& t);
	static StrType Delimiter() { return "," ; }
	////////////////////////////////////////////////////////////////////////////////////////////
};
// sqlite3pp::TableOStream container interface.
inline std::ostream& operator<<(std::ostream& os, const SQL_sakila_db_view_customer_list& t) { sqlite3pp::ostream_a o(os, t.Delimiter()); return t.OStream(o).os; }
inline std::wostream& operator<<(std::wostream& os, const SQL_sakila_db_view_customer_list& t) { sqlite3pp::ostream_w o(os, t.Delimiter());  return t.OStream(o).os; }

#endif // !SQL_SAKILA_DB_VIEW_CUSTOMER_LIST_H
