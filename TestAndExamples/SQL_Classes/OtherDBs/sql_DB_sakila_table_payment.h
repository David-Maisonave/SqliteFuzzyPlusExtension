/* This file was automatically generated using [Sqlite3pp_EZ].
Sqlite3pp_EZ Copyright (C) 2025 David Maisonave (http::\www.axter.com)
Example Usage:		(Using sqlite3pp::Table container)
	// Example #1
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_sakila_table_payment> my_tbl;
		for (auto row : my_tbl)
			std::wcout << row << std::endl;

	// Example #2
		for (int i = 0; i < my_tbl.size(); ++i)
			std::wcout << my_tbl[i].get_payment_id() << std::endl;

	// Example #3
		for (auto r = my_tbl.begin(); r != my_tbl.end(); ++r)
			std::wcout << r->get_last_update() << std::endl;

	// Example #4
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_sakila_table_payment> my_tbl;
		// Example#4a -- (C++11) Range-based loop
		for(auto row : my_tbl)
			std::cout << row.get_payment_id() << " | " << row.get_customer_id() << " | " << row.get_staff_id() << " | " << row.get_rental_id() << " | " << row.get_amount() << " | " << row.get_payment_date() << " | " << row.get_last_update() << " | " << std::endl;

		// Example#4b -- C++ style iteration
		for (auto row = my_tbl.begin(); row != my_tbl.end(); ++row) 
			std::cout << row->get_payment_id() << " | " << row->get_customer_id() << " | " << row->get_staff_id() << " | " << row->get_rental_id() << " | " << row->get_amount() << " | " << row->get_payment_date() << " | " << row->get_last_update() << " | " << std::endl;

		// Example#4c -- C style iteration
		for (int row = 0; row < my_tbl.size(); ++row) 
			std::cout << my_tbl[row].get_payment_id() << " | " << my_tbl[row].get_customer_id() << " | " << my_tbl[row].get_staff_id() << " | " << my_tbl[row].get_rental_id() << " | " << my_tbl[row].get_amount() << " | " << my_tbl[row].get_payment_date() << " | " << my_tbl[row].get_last_update() << " | " << std::endl;
For more details see  https://github.com/David-Maisonave/sqlite3pp_EZ
*/
#ifndef SQL_DB_SAKILA_TABLE_PAYMENT_H
#define SQL_DB_SAKILA_TABLE_PAYMENT_H
#include <string>
#include "..\sqlite3pp_ez.h"

class sql_DB_sakila_table_payment: public sqlite3pp::sql_base
{
	// A member variable for each field in the table
protected:
	Int payment_id = 0;
	Int customer_id = 0;
	Smallint staff_id;
	Int rental_id = 0;
	Decimal amount = 0.0f;
	Bigint payment_date;
	Bigint last_update;

public:
	using StrType = std::string;
	// Constructors
	sql_DB_sakila_table_payment() {} // Default constructor
	template <class T> sql_DB_sakila_table_payment(const T &t) { setData(t); } // Allows data input from different (or same) tables/views having the same data types and column names

	// getTableName, getColumnNames, getSelectColumnNames, and getStreamData are required for sqlite3pp::Table template class
	static StrType getTableName() { return "payment" ; }
	static StrType getColumnNames() { return "payment_id, customer_id, staff_id, rental_id, amount, payment_date, last_update"; }
	static StrType getSelectColumnNames() { return "\"payment_id\", \"customer_id\", \"staff_id\", \"rental_id\", \"amount\", \"payment_date\", \"last_update\""; }
	StrType GetValues() const
	{
		StrType strtype;
		strtype +=  "'" + sqlite3pp::to_string( payment_id) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( customer_id) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( staff_id) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( rental_id) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( amount) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( payment_date) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( last_update) + "'";
		return strtype;
	}
	template<class T> void getStreamData( T q ) { q.getter()  >> payment_id >> customer_id >> staff_id >> rental_id >> amount >> payment_date >> last_update;}
	template <class T> void setData(const T &t) // Used to transfer data from different tables/views having same data types and column names
	{
		payment_id = t.get_payment_id();
		customer_id = t.get_customer_id();
		staff_id = t.get_staff_id();
		rental_id = t.get_rental_id();
		amount = t.get_amount();
		payment_date = t.get_payment_date();
		last_update = t.get_last_update();
	}

	// Miscellaneous functions
	static int getColumnCount() { return 7; }

	// A get_ function for each field in the table, which allows read-only access to protected member variables.
	const Int& get_payment_id() const {return payment_id;}
	const Int& get_customer_id() const {return customer_id;}
	const Smallint& get_staff_id() const {return staff_id;}
	const Int& get_rental_id() const {return rental_id;}
	const Decimal& get_amount() const {return amount;}
	const Bigint& get_payment_date() const {return payment_date;}
	const Bigint& get_last_update() const {return last_update;}

	// A set_ function for each field in the table.
	void set_payment_id(const Int& data__) {payment_id = data__;}
	void set_customer_id(const Int& data__) {customer_id = data__;}
	void set_staff_id(const Smallint& data__) {staff_id = data__;}
	void set_rental_id(const Int& data__) {rental_id = data__;}
	void set_amount(const Decimal& data__) {amount = data__;}
	void set_payment_date(const Bigint& data__) {payment_date = data__;}
	void set_last_update(const Bigint& data__) {last_update = data__;}

	////////////////////////////////////////////////////////////////////////////////////////////
	/* sqlite3pp::TableOStream container interface.
	Functions OStream(), operator<<(), and Delimiter() are required when using the sqlite3pp::TableOStream container.
	Example Usage:		(Using sqlite3pp::TableOStream container)
			TableOStream<sql_DB_sakila_table_payment> tbl(DbFileNameArg("myDatabase.db"));
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
		t.os << payment_id << t.d << customer_id << t.d << staff_id << t.d << rental_id << t.d << amount << t.d << payment_date << t.d << last_update;
		return t;
	}
	friend std::ostream& operator<<(std::ostream& os, const sql_DB_sakila_table_payment& t);
	friend std::wostream& operator<<(std::wostream& os, const sql_DB_sakila_table_payment& t);
	static StrType Delimiter() { return "," ; }
	////////////////////////////////////////////////////////////////////////////////////////////
};
// sqlite3pp::TableOStream container interface.
inline std::ostream& operator<<(std::ostream& os, const sql_DB_sakila_table_payment& t) { sqlite3pp::ostream_a o(os, t.Delimiter()); return t.OStream(o).os; }
inline std::wostream& operator<<(std::wostream& os, const sql_DB_sakila_table_payment& t) { sqlite3pp::ostream_w o(os, t.Delimiter());  return t.OStream(o).os; }

#endif // !SQL_DB_SAKILA_TABLE_PAYMENT_H
