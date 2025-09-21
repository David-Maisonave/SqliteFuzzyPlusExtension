/* This file was automatically generated using [Sqlite3pp_EZ].
Sqlite3pp_EZ Copyright (C) 2025 David Maisonave (http::\www.axter.com)
Example Usage:		(Using sqlite3pp::Table container)
	// Example #1
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_chinook_table_invoices> my_tbl;
		for (auto& row : my_tbl)
			std::cout << row << std::endl;

	// Example #2
		for (int i = 0; i < my_tbl.size(); ++i)
			std::cout << my_tbl[i].get_InvoiceId() << std::endl;

	// Example #3
		for (auto r = my_tbl.begin(); r != my_tbl.end(); ++r)
			std::cout << r->get_Total() << std::endl;

	// Example #4
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_chinook_table_invoices> my_tbl;
		// Example#4a -- (C++11) Range-based loop
		for(auto& row : my_tbl)
			std::cout << row.get_InvoiceId() << " | " << row.get_CustomerId() << " | " << row.get_InvoiceDate() << " | " << row.get_BillingAddress() << " | " << row.get_BillingCity() << " | " << row.get_BillingState() << " | " << row.get_BillingCountry() << " | " << row.get_BillingPostalCode() << " | " << row.get_Total() << " | " << std::endl;

		// Example#4b -- C++ style iteration
		for (auto row = my_tbl.begin(); row != my_tbl.end(); ++row) 
			std::cout << row->get_InvoiceId() << " | " << row->get_CustomerId() << " | " << row->get_InvoiceDate() << " | " << row->get_BillingAddress() << " | " << row->get_BillingCity() << " | " << row->get_BillingState() << " | " << row->get_BillingCountry() << " | " << row->get_BillingPostalCode() << " | " << row->get_Total() << " | " << std::endl;

		// Example#4c -- C style iteration
		for (int row = 0; row < my_tbl.size(); ++row) 
			std::cout << my_tbl[row].get_InvoiceId() << " | " << my_tbl[row].get_CustomerId() << " | " << my_tbl[row].get_InvoiceDate() << " | " << my_tbl[row].get_BillingAddress() << " | " << my_tbl[row].get_BillingCity() << " | " << my_tbl[row].get_BillingState() << " | " << my_tbl[row].get_BillingCountry() << " | " << my_tbl[row].get_BillingPostalCode() << " | " << my_tbl[row].get_Total() << " | " << std::endl;
For more details see  https://github.com/David-Maisonave/sqlite3pp_EZ
*/
#ifndef SQL_DB_CHINOOK_TABLE_INVOICES_HPP
#define SQL_DB_CHINOOK_TABLE_INVOICES_HPP
#include <string>
#include "..\sqlite3pp_ez.h"

class sql_DB_chinook_table_invoices: public sqlite3pp::sql_base
{
	// A member variable for each field in the table
protected:
	Integer InvoiceId = 0;
	Integer CustomerId = 0;
	Datetime InvoiceDate;
	Nvarchar BillingAddress;
	Nvarchar BillingCity;
	Nvarchar BillingState;
	Nvarchar BillingCountry;
	Nvarchar BillingPostalCode;
	Numeric Total = 0.0f;

public:
	using StrType = std::string;
	// Constructors
	sql_DB_chinook_table_invoices() {} // Default constructor
	template <class T> sql_DB_chinook_table_invoices(const T &t) { setData(t); } // Allows data input from different (or same) tables/views having the same data types and column names

	// getTableName, getColumnNames, getSelectColumnNames, and getStreamData are required for sqlite3pp::Table template class
	static StrType getTableName() { return "invoices" ; }
	static StrType getColumnNames() { return "\"InvoiceId\", \"CustomerId\", \"InvoiceDate\", \"BillingAddress\", \"BillingCity\", \"BillingState\", \"BillingCountry\", \"BillingPostalCode\", \"Total\""; }
	static StrType getSelectColumnNames() { return "\"InvoiceId\", \"CustomerId\", \"InvoiceDate\", \"BillingAddress\", \"BillingCity\", \"BillingState\", \"BillingCountry\", \"BillingPostalCode\", \"Total\""; }
	StrType GetValues() const
	{
		StrType strtype;
		strtype +=  "'" + sqlite3pp::to_string( InvoiceId) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( CustomerId) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( InvoiceDate) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( BillingAddress) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( BillingCity) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( BillingState) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( BillingCountry) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( BillingPostalCode) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Total) + "'";
		return strtype;
	}
	template<class T> void getStreamData( T q ) { q.getter()  >> InvoiceId >> CustomerId >> InvoiceDate >> BillingAddress >> BillingCity >> BillingState >> BillingCountry >> BillingPostalCode >> Total;}
	template <class T> void setData(const T &t) // Used to transfer data from different tables/views having same data types and column names
	{
		InvoiceId = t.get_InvoiceId();
		CustomerId = t.get_CustomerId();
		InvoiceDate = t.get_InvoiceDate();
		BillingAddress = t.get_BillingAddress();
		BillingCity = t.get_BillingCity();
		BillingState = t.get_BillingState();
		BillingCountry = t.get_BillingCountry();
		BillingPostalCode = t.get_BillingPostalCode();
		Total = t.get_Total();
	}

	// Miscellaneous functions
	static int getColumnCount() { return 9; }

	// A get_ function for each field in the table, which allows read-only access to protected member variables.
	const Integer& get_InvoiceId() const {return InvoiceId;}
	const Integer& get_CustomerId() const {return CustomerId;}
	const Datetime& get_InvoiceDate() const {return InvoiceDate;}
	const Nvarchar& get_BillingAddress() const {return BillingAddress;}
	const Nvarchar& get_BillingCity() const {return BillingCity;}
	const Nvarchar& get_BillingState() const {return BillingState;}
	const Nvarchar& get_BillingCountry() const {return BillingCountry;}
	const Nvarchar& get_BillingPostalCode() const {return BillingPostalCode;}
	const Numeric& get_Total() const {return Total;}

	// A set_ function for each field in the table.
	void set_InvoiceId(const Integer& data__) {InvoiceId = data__;}
	void set_CustomerId(const Integer& data__) {CustomerId = data__;}
	void set_InvoiceDate(const Datetime& data__) {InvoiceDate = data__;}
	void set_BillingAddress(const Nvarchar& data__) {BillingAddress = data__;}
	void set_BillingCity(const Nvarchar& data__) {BillingCity = data__;}
	void set_BillingState(const Nvarchar& data__) {BillingState = data__;}
	void set_BillingCountry(const Nvarchar& data__) {BillingCountry = data__;}
	void set_BillingPostalCode(const Nvarchar& data__) {BillingPostalCode = data__;}
	void set_Total(const Numeric& data__) {Total = data__;}

	////////////////////////////////////////////////////////////////////////////////////////////
	/* sqlite3pp::TableOStream container interface.
	Functions OStream(), operator<<(), and Delimiter() are required when using the sqlite3pp::TableOStream container.
	Example Usage:		(Using sqlite3pp::TableOStream container)
			TableOStream<sql_DB_chinook_table_invoices> tbl(DbFileNameArg("myDatabase.db"));
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
		t.os << InvoiceId << t.d << CustomerId << t.d << InvoiceDate << t.d << t.str(BillingAddress) << t.d << t.str(BillingCity) << t.d << t.str(BillingState) << t.d << t.str(BillingCountry) << t.d << t.str(BillingPostalCode) << t.d << Total;
		return t;
	}
	friend std::ostream& operator<<(std::ostream& os, const sql_DB_chinook_table_invoices& t);
	friend std::wostream& operator<<(std::wostream& os, const sql_DB_chinook_table_invoices& t);
	static StrType Delimiter() { return "," ; }
	////////////////////////////////////////////////////////////////////////////////////////////
};
// sqlite3pp::TableOStream container interface.
inline std::ostream& operator<<(std::ostream& os, const sql_DB_chinook_table_invoices& t) { sqlite3pp::ostream_a o(os, t.Delimiter()); return t.OStream(o).os; }
inline std::wostream& operator<<(std::wostream& os, const sql_DB_chinook_table_invoices& t) { sqlite3pp::ostream_w o(os, t.Delimiter());  return t.OStream(o).os; }

#endif // !SQL_DB_CHINOOK_TABLE_INVOICES_HPP
