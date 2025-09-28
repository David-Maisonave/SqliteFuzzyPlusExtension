/* This file was automatically generated using [Sqlite3pp_EZ].
Sqlite3pp_EZ Copyright (C) 2025 David Maisonave (http::\www.axter.com)
Example Usage:		(Using sqlite3pp::Table container)
	// Example #1
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<SQL_chinook_db_table_invoice_items> my_tbl;
		for (auto& row : my_tbl)
			std::cout << row << std::endl;

	// Example #2
		for (int i = 0; i < my_tbl.size(); ++i)
			std::cout << my_tbl[i].get_InvoiceLineId() << std::endl;

	// Example #3
		for (auto r = my_tbl.begin(); r != my_tbl.end(); ++r)
			std::cout << r->get_Quantity() << std::endl;

	// Example #4
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<SQL_chinook_db_table_invoice_items> my_tbl;
		// Example#4a -- (C++11) Range-based loop
		for(auto& row : my_tbl)
			std::cout << row.get_InvoiceLineId() << " | " << row.get_InvoiceId() << " | " << row.get_TrackId() << " | " << row.get_UnitPrice() << " | " << row.get_Quantity() << " | " << std::endl;

		// Example#4b -- C++ style iteration
		for (auto row = my_tbl.begin(); row != my_tbl.end(); ++row) 
			std::cout << row->get_InvoiceLineId() << " | " << row->get_InvoiceId() << " | " << row->get_TrackId() << " | " << row->get_UnitPrice() << " | " << row->get_Quantity() << " | " << std::endl;

		// Example#4c -- C style iteration
		for (int row = 0; row < my_tbl.size(); ++row) 
			std::cout << my_tbl[row].get_InvoiceLineId() << " | " << my_tbl[row].get_InvoiceId() << " | " << my_tbl[row].get_TrackId() << " | " << my_tbl[row].get_UnitPrice() << " | " << my_tbl[row].get_Quantity() << " | " << std::endl;
For more details see  https://github.com/David-Maisonave/sqlite3pp_EZ
*/
#ifndef SQL_CHINOOK_DB_TABLE_INVOICE_ITEMS_H
#define SQL_CHINOOK_DB_TABLE_INVOICE_ITEMS_H
#include <string>
#include "..\..\sqlite3pp_ez\sqlite3pp_ez.h"

class SQL_chinook_db_table_invoice_items: public sqlite3pp::sql_base
{
	// A member variable for each field in the table
protected:
	Integer InvoiceLineId = 0;
	Integer InvoiceId = 0;
	Integer TrackId = 0;
	Numeric UnitPrice = 0.0f;
	Integer Quantity = 0;

public:
	using StrType = std::string;
	// Constructors
	SQL_chinook_db_table_invoice_items() {} // Default constructor
	template <class T> SQL_chinook_db_table_invoice_items(const T &t) { setData(t); } // Allows data input from different (or same) tables/views having the same data types and column names

	// getTableName, getColumnNames, getSelectColumnNames, and getStreamData are required for sqlite3pp::Table template class
	static StrType getTableName() { return "invoice_items" ; }
	static StrType getColumnNames() { return "\"InvoiceLineId\", \"InvoiceId\", \"TrackId\", \"UnitPrice\", \"Quantity\""; }
	static StrType getSelectColumnNames() { return "\"InvoiceLineId\", \"InvoiceId\", \"TrackId\", \"UnitPrice\", \"Quantity\""; }
	StrType GetValues() const
	{
		StrType strtype;
		strtype +=  "'" + sqlite3pp::to_string( InvoiceLineId) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( InvoiceId) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( TrackId) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( UnitPrice) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Quantity) + "'";
		return strtype;
	}
	template<class T> void getStreamData( T q ) { q.getter()  >> InvoiceLineId >> InvoiceId >> TrackId >> UnitPrice >> Quantity;}
	template <class T> void setData(const T &t) // Used to transfer data from different tables/views having same data types and column names
	{
		InvoiceLineId = t.get_InvoiceLineId();
		InvoiceId = t.get_InvoiceId();
		TrackId = t.get_TrackId();
		UnitPrice = t.get_UnitPrice();
		Quantity = t.get_Quantity();
	}

	// Miscellaneous functions
	static int getColumnCount() { return 5; }

	// A get_ function for each field in the table, which allows read-only access to protected member variables.
	const Integer& get_InvoiceLineId() const {return InvoiceLineId;}
	const Integer& get_InvoiceId() const {return InvoiceId;}
	const Integer& get_TrackId() const {return TrackId;}
	const Numeric& get_UnitPrice() const {return UnitPrice;}
	const Integer& get_Quantity() const {return Quantity;}

	// A set_ function for each field in the table.
	void set_InvoiceLineId(const Integer& data__) {InvoiceLineId = data__;}
	void set_InvoiceId(const Integer& data__) {InvoiceId = data__;}
	void set_TrackId(const Integer& data__) {TrackId = data__;}
	void set_UnitPrice(const Numeric& data__) {UnitPrice = data__;}
	void set_Quantity(const Integer& data__) {Quantity = data__;}

	////////////////////////////////////////////////////////////////////////////////////////////
	/* sqlite3pp::TableOStream container interface.
	Functions OStream(), operator<<(), and Delimiter() are required when using the sqlite3pp::TableOStream container.
	Example Usage:		(Using sqlite3pp::TableOStream container)
			TableOStream<SQL_chinook_db_table_invoice_items> tbl(DbFileNameArg("myDatabase.db"));
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
		t.os << InvoiceLineId << t.d << InvoiceId << t.d << TrackId << t.d << UnitPrice << t.d << Quantity;
		return t;
	}
	friend std::ostream& operator<<(std::ostream& os, const SQL_chinook_db_table_invoice_items& t);
	friend std::wostream& operator<<(std::wostream& os, const SQL_chinook_db_table_invoice_items& t);
	static StrType Delimiter() { return "," ; }
	////////////////////////////////////////////////////////////////////////////////////////////
};
// sqlite3pp::TableOStream container interface.
inline std::ostream& operator<<(std::ostream& os, const SQL_chinook_db_table_invoice_items& t) { sqlite3pp::ostream_a o(os, t.Delimiter()); return t.OStream(o).os; }
inline std::wostream& operator<<(std::wostream& os, const SQL_chinook_db_table_invoice_items& t) { sqlite3pp::ostream_w o(os, t.Delimiter());  return t.OStream(o).os; }

#endif // !SQL_CHINOOK_DB_TABLE_INVOICE_ITEMS_H
