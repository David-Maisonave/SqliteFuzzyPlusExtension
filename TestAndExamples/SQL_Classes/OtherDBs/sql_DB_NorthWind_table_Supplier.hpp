/* This file was automatically generated using [Sqlite3pp_EZ].
Sqlite3pp_EZ Copyright (C) 2025 David Maisonave (http::\www.axter.com)
Example Usage:		(Using sqlite3pp::Table container)
	// Example #1
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_NorthWind_table_Supplier> my_tbl;
		for (auto& row : my_tbl)
			std::cout << row << std::endl;

	// Example #2
		for (int i = 0; i < my_tbl.size(); ++i)
			std::cout << my_tbl[i].get_Id() << std::endl;

	// Example #3
		for (auto r = my_tbl.begin(); r != my_tbl.end(); ++r)
			std::cout << r->get_HomePage() << std::endl;

	// Example #4
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_NorthWind_table_Supplier> my_tbl;
		// Example#4a -- (C++11) Range-based loop
		for(auto& row : my_tbl)
			std::cout << row.get_Id() << " | " << row.get_CompanyName() << " | " << row.get_ContactName() << " | " << row.get_ContactTitle() << " | " << row.get_Address() << " | " << row.get_City() << " | " << row.get_Region() << " | " << row.get_PostalCode() << " | " << row.get_Country() << " | " << row.get_Phone() << " | " << row.get_Fax() << " | " << row.get_HomePage() << " | " << std::endl;

		// Example#4b -- C++ style iteration
		for (auto row = my_tbl.begin(); row != my_tbl.end(); ++row) 
			std::cout << row->get_Id() << " | " << row->get_CompanyName() << " | " << row->get_ContactName() << " | " << row->get_ContactTitle() << " | " << row->get_Address() << " | " << row->get_City() << " | " << row->get_Region() << " | " << row->get_PostalCode() << " | " << row->get_Country() << " | " << row->get_Phone() << " | " << row->get_Fax() << " | " << row->get_HomePage() << " | " << std::endl;

		// Example#4c -- C style iteration
		for (int row = 0; row < my_tbl.size(); ++row) 
			std::cout << my_tbl[row].get_Id() << " | " << my_tbl[row].get_CompanyName() << " | " << my_tbl[row].get_ContactName() << " | " << my_tbl[row].get_ContactTitle() << " | " << my_tbl[row].get_Address() << " | " << my_tbl[row].get_City() << " | " << my_tbl[row].get_Region() << " | " << my_tbl[row].get_PostalCode() << " | " << my_tbl[row].get_Country() << " | " << my_tbl[row].get_Phone() << " | " << my_tbl[row].get_Fax() << " | " << my_tbl[row].get_HomePage() << " | " << std::endl;
For more details see  https://github.com/David-Maisonave/sqlite3pp_EZ
*/
#ifndef SQL_DB_NORTHWIND_TABLE_SUPPLIER_H
#define SQL_DB_NORTHWIND_TABLE_SUPPLIER_H
#include <string>
#include "..\sqlite3pp_ez.h"

class sql_DB_NorthWind_table_Supplier: public sqlite3pp::sql_base
{
	// A member variable for each field in the table
protected:
	Integer Id = 0;
	Varchar CompanyName;
	Varchar ContactName;
	Varchar ContactTitle;
	Varchar Address;
	Varchar City;
	Varchar Region;
	Varchar PostalCode;
	Varchar Country;
	Varchar Phone;
	Varchar Fax;
	Varchar HomePage;

public:
	using StrType = std::string;
	// Constructors
	sql_DB_NorthWind_table_Supplier() {} // Default constructor
	template <class T> sql_DB_NorthWind_table_Supplier(const T &t) { setData(t); } // Allows data input from different (or same) tables/views having the same data types and column names

	// getTableName, getColumnNames, getSelectColumnNames, and getStreamData are required for sqlite3pp::Table template class
	static StrType getTableName() { return "Supplier" ; }
	static StrType getColumnNames() { return "\"Id\", \"CompanyName\", \"ContactName\", \"ContactTitle\", \"Address\", \"City\", \"Region\", \"PostalCode\", \"Country\", \"Phone\", \"Fax\", \"HomePage\""; }
	static StrType getSelectColumnNames() { return "\"Id\", \"CompanyName\", \"ContactName\", \"ContactTitle\", \"Address\", \"City\", \"Region\", \"PostalCode\", \"Country\", \"Phone\", \"Fax\", \"HomePage\""; }
	StrType GetValues() const
	{
		StrType strtype;
		strtype +=  "'" + sqlite3pp::to_string( Id) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( CompanyName) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( ContactName) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( ContactTitle) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Address) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( City) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Region) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( PostalCode) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Country) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Phone) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Fax) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( HomePage) + "'";
		return strtype;
	}
	template<class T> void getStreamData( T q ) { q.getter()  >> Id >> CompanyName >> ContactName >> ContactTitle >> Address >> City >> Region >> PostalCode >> Country >> Phone >> Fax >> HomePage;}
	template <class T> void setData(const T &t) // Used to transfer data from different tables/views having same data types and column names
	{
		Id = t.get_Id();
		CompanyName = t.get_CompanyName();
		ContactName = t.get_ContactName();
		ContactTitle = t.get_ContactTitle();
		Address = t.get_Address();
		City = t.get_City();
		Region = t.get_Region();
		PostalCode = t.get_PostalCode();
		Country = t.get_Country();
		Phone = t.get_Phone();
		Fax = t.get_Fax();
		HomePage = t.get_HomePage();
	}

	// Miscellaneous functions
	static int getColumnCount() { return 12; }

	// A get_ function for each field in the table, which allows read-only access to protected member variables.
	const Integer& get_Id() const {return Id;}
	const Varchar& get_CompanyName() const {return CompanyName;}
	const Varchar& get_ContactName() const {return ContactName;}
	const Varchar& get_ContactTitle() const {return ContactTitle;}
	const Varchar& get_Address() const {return Address;}
	const Varchar& get_City() const {return City;}
	const Varchar& get_Region() const {return Region;}
	const Varchar& get_PostalCode() const {return PostalCode;}
	const Varchar& get_Country() const {return Country;}
	const Varchar& get_Phone() const {return Phone;}
	const Varchar& get_Fax() const {return Fax;}
	const Varchar& get_HomePage() const {return HomePage;}

	// A set_ function for each field in the table.
	void set_Id(const Integer& data__) {Id = data__;}
	void set_CompanyName(const Varchar& data__) {CompanyName = data__;}
	void set_ContactName(const Varchar& data__) {ContactName = data__;}
	void set_ContactTitle(const Varchar& data__) {ContactTitle = data__;}
	void set_Address(const Varchar& data__) {Address = data__;}
	void set_City(const Varchar& data__) {City = data__;}
	void set_Region(const Varchar& data__) {Region = data__;}
	void set_PostalCode(const Varchar& data__) {PostalCode = data__;}
	void set_Country(const Varchar& data__) {Country = data__;}
	void set_Phone(const Varchar& data__) {Phone = data__;}
	void set_Fax(const Varchar& data__) {Fax = data__;}
	void set_HomePage(const Varchar& data__) {HomePage = data__;}

	////////////////////////////////////////////////////////////////////////////////////////////
	/* sqlite3pp::TableOStream container interface.
	Functions OStream(), operator<<(), and Delimiter() are required when using the sqlite3pp::TableOStream container.
	Example Usage:		(Using sqlite3pp::TableOStream container)
			TableOStream<sql_DB_NorthWind_table_Supplier> tbl(DbFileNameArg("myDatabase.db"));
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
		t.os << Id << t.d << t.str(CompanyName) << t.d << t.str(ContactName) << t.d << t.str(ContactTitle) << t.d << t.str(Address) << t.d << t.str(City) << t.d << t.str(Region) << t.d << t.str(PostalCode) << t.d << t.str(Country) << t.d << t.str(Phone) << t.d << t.str(Fax) << t.d << t.str(HomePage);
		return t;
	}
	friend std::ostream& operator<<(std::ostream& os, const sql_DB_NorthWind_table_Supplier& t);
	friend std::wostream& operator<<(std::wostream& os, const sql_DB_NorthWind_table_Supplier& t);
	static StrType Delimiter() { return "," ; }
	////////////////////////////////////////////////////////////////////////////////////////////
};
// sqlite3pp::TableOStream container interface.
inline std::ostream& operator<<(std::ostream& os, const sql_DB_NorthWind_table_Supplier& t) { sqlite3pp::ostream_a o(os, t.Delimiter()); return t.OStream(o).os; }
inline std::wostream& operator<<(std::wostream& os, const sql_DB_NorthWind_table_Supplier& t) { sqlite3pp::ostream_w o(os, t.Delimiter());  return t.OStream(o).os; }

#endif // !SQL_DB_NORTHWIND_TABLE_SUPPLIER_H
