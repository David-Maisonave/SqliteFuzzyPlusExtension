/* This file was automatically generated using [Sqlite3pp_EZ].
Sqlite3pp_EZ Copyright (C) 2025 David Maisonave (http::\www.axter.com)
Example Usage:		(Using sqlite3pp::Table container)
	// Example #1
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_chinook_table_employees> my_tbl;
		for (auto row : my_tbl)
			std::wcout << row << std::endl;

	// Example #2
		for (int i = 0; i < my_tbl.size(); ++i)
			std::wcout << my_tbl[i].get_EmployeeId() << std::endl;

	// Example #3
		for (auto r = my_tbl.begin(); r != my_tbl.end(); ++r)
			std::wcout << r->get_Email() << std::endl;

	// Example #4
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_chinook_table_employees> my_tbl;
		// Example#4a -- (C++11) Range-based loop
		for(auto row : my_tbl)
			std::cout << row.get_EmployeeId() << " | " << row.get_LastName() << " | " << row.get_FirstName() << " | " << row.get_Title() << " | " << row.get_ReportsTo() << " | " << row.get_BirthDate() << " | " << row.get_HireDate() << " | " << row.get_Address() << " | " << row.get_City() << " | " << row.get_State() << " | " << row.get_Country() << " | " << row.get_PostalCode() << " | " << row.get_Phone() << " | " << row.get_Fax() << " | " << row.get_Email() << " | " << std::endl;

		// Example#4b -- C++ style iteration
		for (auto row = my_tbl.begin(); row != my_tbl.end(); ++row) 
			std::cout << row->get_EmployeeId() << " | " << row->get_LastName() << " | " << row->get_FirstName() << " | " << row->get_Title() << " | " << row->get_ReportsTo() << " | " << row->get_BirthDate() << " | " << row->get_HireDate() << " | " << row->get_Address() << " | " << row->get_City() << " | " << row->get_State() << " | " << row->get_Country() << " | " << row->get_PostalCode() << " | " << row->get_Phone() << " | " << row->get_Fax() << " | " << row->get_Email() << " | " << std::endl;

		// Example#4c -- C style iteration
		for (int row = 0; row < my_tbl.size(); ++row) 
			std::cout << my_tbl[row].get_EmployeeId() << " | " << my_tbl[row].get_LastName() << " | " << my_tbl[row].get_FirstName() << " | " << my_tbl[row].get_Title() << " | " << my_tbl[row].get_ReportsTo() << " | " << my_tbl[row].get_BirthDate() << " | " << my_tbl[row].get_HireDate() << " | " << my_tbl[row].get_Address() << " | " << my_tbl[row].get_City() << " | " << my_tbl[row].get_State() << " | " << my_tbl[row].get_Country() << " | " << my_tbl[row].get_PostalCode() << " | " << my_tbl[row].get_Phone() << " | " << my_tbl[row].get_Fax() << " | " << my_tbl[row].get_Email() << " | " << std::endl;
For more details see  https://github.com/David-Maisonave/sqlite3pp_EZ
*/
#ifndef SQL_DB_CHINOOK_TABLE_EMPLOYEES_H
#define SQL_DB_CHINOOK_TABLE_EMPLOYEES_H
#include <string>
#include "..\sqlite3pp_ez.h"

class sql_DB_chinook_table_employees: public sqlite3pp::sql_base
{
	// A member variable for each field in the table
protected:
	Integer EmployeeId = 0;
	Nvarchar LastName;
	Nvarchar FirstName;
	Nvarchar Title;
	Integer ReportsTo = 0;
	Datetime BirthDate;
	Datetime HireDate;
	Nvarchar Address;
	Nvarchar City;
	Nvarchar State;
	Nvarchar Country;
	Nvarchar PostalCode;
	Nvarchar Phone;
	Nvarchar Fax;
	Nvarchar Email;

public:
	using StrType = std::string;
	// Constructors
	sql_DB_chinook_table_employees() {} // Default constructor
	template <class T> sql_DB_chinook_table_employees(const T &t) { setData(t); } // Allows data input from different (or same) tables/views having the same data types and column names

	// getTableName, getColumnNames, getSelectColumnNames, and getStreamData are required for sqlite3pp::Table template class
	static StrType getTableName() { return "employees" ; }
	static StrType getColumnNames() { return "\"EmployeeId\", \"LastName\", \"FirstName\", \"Title\", \"ReportsTo\", \"BirthDate\", \"HireDate\", \"Address\", \"City\", \"State\", \"Country\", \"PostalCode\", \"Phone\", \"Fax\", \"Email\""; }
	static StrType getSelectColumnNames() { return "\"EmployeeId\", \"LastName\", \"FirstName\", \"Title\", \"ReportsTo\", \"BirthDate\", \"HireDate\", \"Address\", \"City\", \"State\", \"Country\", \"PostalCode\", \"Phone\", \"Fax\", \"Email\""; }
	StrType GetValues() const
	{
		StrType strtype;
		strtype +=  "'" + sqlite3pp::to_string( EmployeeId) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( LastName) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( FirstName) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Title) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( ReportsTo) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( BirthDate) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( HireDate) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Address) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( City) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( State) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Country) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( PostalCode) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Phone) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Fax) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Email) + "'";
		return strtype;
	}
	template<class T> void getStreamData( T q ) { q.getter()  >> EmployeeId >> LastName >> FirstName >> Title >> ReportsTo >> BirthDate >> HireDate >> Address >> City >> State >> Country >> PostalCode >> Phone >> Fax >> Email;}
	template <class T> void setData(const T &t) // Used to transfer data from different tables/views having same data types and column names
	{
		EmployeeId = t.get_EmployeeId();
		LastName = t.get_LastName();
		FirstName = t.get_FirstName();
		Title = t.get_Title();
		ReportsTo = t.get_ReportsTo();
		BirthDate = t.get_BirthDate();
		HireDate = t.get_HireDate();
		Address = t.get_Address();
		City = t.get_City();
		State = t.get_State();
		Country = t.get_Country();
		PostalCode = t.get_PostalCode();
		Phone = t.get_Phone();
		Fax = t.get_Fax();
		Email = t.get_Email();
	}

	// Miscellaneous functions
	static int getColumnCount() { return 15; }

	// A get_ function for each field in the table, which allows read-only access to protected member variables.
	const Integer& get_EmployeeId() const {return EmployeeId;}
	const Nvarchar& get_LastName() const {return LastName;}
	const Nvarchar& get_FirstName() const {return FirstName;}
	const Nvarchar& get_Title() const {return Title;}
	const Integer& get_ReportsTo() const {return ReportsTo;}
	const Datetime& get_BirthDate() const {return BirthDate;}
	const Datetime& get_HireDate() const {return HireDate;}
	const Nvarchar& get_Address() const {return Address;}
	const Nvarchar& get_City() const {return City;}
	const Nvarchar& get_State() const {return State;}
	const Nvarchar& get_Country() const {return Country;}
	const Nvarchar& get_PostalCode() const {return PostalCode;}
	const Nvarchar& get_Phone() const {return Phone;}
	const Nvarchar& get_Fax() const {return Fax;}
	const Nvarchar& get_Email() const {return Email;}

	// A set_ function for each field in the table.
	void set_EmployeeId(const Integer& data__) {EmployeeId = data__;}
	void set_LastName(const Nvarchar& data__) {LastName = data__;}
	void set_FirstName(const Nvarchar& data__) {FirstName = data__;}
	void set_Title(const Nvarchar& data__) {Title = data__;}
	void set_ReportsTo(const Integer& data__) {ReportsTo = data__;}
	void set_BirthDate(const Datetime& data__) {BirthDate = data__;}
	void set_HireDate(const Datetime& data__) {HireDate = data__;}
	void set_Address(const Nvarchar& data__) {Address = data__;}
	void set_City(const Nvarchar& data__) {City = data__;}
	void set_State(const Nvarchar& data__) {State = data__;}
	void set_Country(const Nvarchar& data__) {Country = data__;}
	void set_PostalCode(const Nvarchar& data__) {PostalCode = data__;}
	void set_Phone(const Nvarchar& data__) {Phone = data__;}
	void set_Fax(const Nvarchar& data__) {Fax = data__;}
	void set_Email(const Nvarchar& data__) {Email = data__;}

	////////////////////////////////////////////////////////////////////////////////////////////
	/* sqlite3pp::TableOStream container interface.
	Functions OStream(), operator<<(), and Delimiter() are required when using the sqlite3pp::TableOStream container.
	Example Usage:		(Using sqlite3pp::TableOStream container)
			TableOStream<sql_DB_chinook_table_employees> tbl(DbFileNameArg("myDatabase.db"));
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
		t.os << EmployeeId << t.d << t.str(LastName) << t.d << t.str(FirstName) << t.d << t.str(Title) << t.d << ReportsTo << t.d << BirthDate << t.d << HireDate << t.d << t.str(Address) << t.d << t.str(City) << t.d << t.str(State) << t.d << t.str(Country) << t.d << t.str(PostalCode) << t.d << t.str(Phone) << t.d << t.str(Fax) << t.d << t.str(Email);
		return t;
	}
	friend std::ostream& operator<<(std::ostream& os, const sql_DB_chinook_table_employees& t);
	friend std::wostream& operator<<(std::wostream& os, const sql_DB_chinook_table_employees& t);
	static StrType Delimiter() { return "," ; }
	////////////////////////////////////////////////////////////////////////////////////////////
};
// sqlite3pp::TableOStream container interface.
inline std::ostream& operator<<(std::ostream& os, const sql_DB_chinook_table_employees& t) { sqlite3pp::ostream_a o(os, t.Delimiter()); return t.OStream(o).os; }
inline std::wostream& operator<<(std::wostream& os, const sql_DB_chinook_table_employees& t) { sqlite3pp::ostream_w o(os, t.Delimiter());  return t.OStream(o).os; }

#endif // !SQL_DB_CHINOOK_TABLE_EMPLOYEES_H
