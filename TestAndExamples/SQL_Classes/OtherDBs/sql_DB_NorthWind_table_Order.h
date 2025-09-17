/* This file was automatically generated using [Sqlite3pp_EZ].
Sqlite3pp_EZ Copyright (C) 2021 David Maisonave (http::\www.axter.com)
Example Usage:		(Using sqlite3pp::Table container)
	// Example #1
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_NorthWind_table_Order> my_tbl;
		for (auto row : my_tbl)
			std::wcout << row << std::endl;

	// Example #2
		for (int i = 0; i < my_tbl.size(); ++i)
			std::wcout << my_tbl[i].get_Id() << std::endl;

	// Example #3
		for (auto r = my_tbl.begin(); r != my_tbl.end(); ++r)
			std::wcout << r->get_ShipCountry() << std::endl;

For more details see  https://github.com/David-Maisonave/sqlite3pp_EZ
*/
#ifndef SQL_DB_NORTHWIND_TABLE_ORDER_H
#define SQL_DB_NORTHWIND_TABLE_ORDER_H
#include <string>
#include "..\sqlite3pp_ez.h"

class sql_DB_NorthWind_table_Order: public sqlite3pp::sql_base
{
	// A member variable for each field in the table
protected:
	Integer Id = 0;
	Varchar CustomerId;
	Integer EmployeeId = 0;
	Varchar OrderDate;
	Varchar RequiredDate;
	Varchar ShippedDate;
	Integer ShipVia = 0;
	Decimal Freight = 0.0f;
	Varchar ShipName;
	Varchar ShipAddress;
	Varchar ShipCity;
	Varchar ShipRegion;
	Varchar ShipPostalCode;
	Varchar ShipCountry;

public:
	using StrType = std::string;
	// Constructors
	sql_DB_NorthWind_table_Order() {} // Default constructor
	template <class T> sql_DB_NorthWind_table_Order(const T &t) { setData(t); } // Allows data input from different (or same) tables/views having the same data types and column names

	// getTableName, getColumnNames, getSelectColumnNames, and getStreamData are required for sqlite3pp::Table template class
	static StrType getTableName() { return "Order" ; }
	static StrType getColumnNames() { return "Id, CustomerId, EmployeeId, OrderDate, RequiredDate, ShippedDate, ShipVia, Freight, ShipName, ShipAddress, ShipCity, ShipRegion, ShipPostalCode, ShipCountry"; }
	static StrType getSelectColumnNames() { return "'Id', 'CustomerId', 'EmployeeId', 'OrderDate', 'RequiredDate', 'ShippedDate', 'ShipVia', 'Freight', 'ShipName', 'ShipAddress', 'ShipCity', 'ShipRegion', 'ShipPostalCode', 'ShipCountry'"; }
	StrType GetValues() const
	{
		StrType strtype;
		strtype +=  "'" + sqlite3pp::to_string( Id) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( CustomerId) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( EmployeeId) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( OrderDate) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( RequiredDate) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( ShippedDate) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( ShipVia) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Freight) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( ShipName) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( ShipAddress) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( ShipCity) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( ShipRegion) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( ShipPostalCode) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( ShipCountry) + "'";
		return strtype;
	}
	template<class T> void getStreamData( T q ) { q.getter()  >> Id >> CustomerId >> EmployeeId >> OrderDate >> RequiredDate >> ShippedDate >> ShipVia >> Freight >> ShipName >> ShipAddress >> ShipCity >> ShipRegion >> ShipPostalCode >> ShipCountry;}
	template <class T> void setData(const T &t) // Used to transfer data from different tables/views having same data types and column names
	{
		Id = t.get_Id();
		CustomerId = t.get_CustomerId();
		EmployeeId = t.get_EmployeeId();
		OrderDate = t.get_OrderDate();
		RequiredDate = t.get_RequiredDate();
		ShippedDate = t.get_ShippedDate();
		ShipVia = t.get_ShipVia();
		Freight = t.get_Freight();
		ShipName = t.get_ShipName();
		ShipAddress = t.get_ShipAddress();
		ShipCity = t.get_ShipCity();
		ShipRegion = t.get_ShipRegion();
		ShipPostalCode = t.get_ShipPostalCode();
		ShipCountry = t.get_ShipCountry();
	}

	// Miscellaneous functions
	static int getColumnCount() { return 14; }

	// A get_ function for each field in the table, which allows read-only access to protected member variables.
	const Integer& get_Id() const {return Id;}
	const Varchar& get_CustomerId() const {return CustomerId;}
	const Integer& get_EmployeeId() const {return EmployeeId;}
	const Varchar& get_OrderDate() const {return OrderDate;}
	const Varchar& get_RequiredDate() const {return RequiredDate;}
	const Varchar& get_ShippedDate() const {return ShippedDate;}
	const Integer& get_ShipVia() const {return ShipVia;}
	const Decimal& get_Freight() const {return Freight;}
	const Varchar& get_ShipName() const {return ShipName;}
	const Varchar& get_ShipAddress() const {return ShipAddress;}
	const Varchar& get_ShipCity() const {return ShipCity;}
	const Varchar& get_ShipRegion() const {return ShipRegion;}
	const Varchar& get_ShipPostalCode() const {return ShipPostalCode;}
	const Varchar& get_ShipCountry() const {return ShipCountry;}

	// A set_ function for each field in the table.
	void set_Id(const Integer& data__) {Id = data__;}
	void set_CustomerId(const Varchar& data__) {CustomerId = data__;}
	void set_EmployeeId(const Integer& data__) {EmployeeId = data__;}
	void set_OrderDate(const Varchar& data__) {OrderDate = data__;}
	void set_RequiredDate(const Varchar& data__) {RequiredDate = data__;}
	void set_ShippedDate(const Varchar& data__) {ShippedDate = data__;}
	void set_ShipVia(const Integer& data__) {ShipVia = data__;}
	void set_Freight(const Decimal& data__) {Freight = data__;}
	void set_ShipName(const Varchar& data__) {ShipName = data__;}
	void set_ShipAddress(const Varchar& data__) {ShipAddress = data__;}
	void set_ShipCity(const Varchar& data__) {ShipCity = data__;}
	void set_ShipRegion(const Varchar& data__) {ShipRegion = data__;}
	void set_ShipPostalCode(const Varchar& data__) {ShipPostalCode = data__;}
	void set_ShipCountry(const Varchar& data__) {ShipCountry = data__;}

	////////////////////////////////////////////////////////////////////////////////////////////
	/* sqlite3pp::TableOStream container interface.
	Functions OStream(), operator<<(), and Delimiter() are required when using the sqlite3pp::TableOStream container.
	Example Usage:		(Using sqlite3pp::TableOStream container)
			TableOStream<sql_DB_NorthWind_table_Order> tbl(DbFileNameArg("myDatabase.db"));
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
		t.os << Id << t.d << t.str(CustomerId) << t.d << EmployeeId << t.d << t.str(OrderDate) << t.d << t.str(RequiredDate) << t.d << t.str(ShippedDate) << t.d << ShipVia << t.d << Freight << t.d << t.str(ShipName) << t.d << t.str(ShipAddress) << t.d << t.str(ShipCity) << t.d << t.str(ShipRegion) << t.d << t.str(ShipPostalCode) << t.d << t.str(ShipCountry);
		return t;
	}
	friend std::ostream& operator<<(std::ostream& os, const sql_DB_NorthWind_table_Order& t);
	friend std::wostream& operator<<(std::wostream& os, const sql_DB_NorthWind_table_Order& t);
	static StrType Delimiter() { return "," ; }
	////////////////////////////////////////////////////////////////////////////////////////////
};
// sqlite3pp::TableOStream container interface.
inline std::ostream& operator<<(std::ostream& os, const sql_DB_NorthWind_table_Order& t) { sqlite3pp::ostream_a o(os, t.Delimiter()); return t.OStream(o).os; }
inline std::wostream& operator<<(std::wostream& os, const sql_DB_NorthWind_table_Order& t) { sqlite3pp::ostream_w o(os, t.Delimiter());  return t.OStream(o).os; }

#endif // !SQL_DB_NORTHWIND_TABLE_ORDER_H
