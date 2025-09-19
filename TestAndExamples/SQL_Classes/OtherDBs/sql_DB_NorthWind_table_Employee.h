/* This file was automatically generated using [Sqlite3pp_EZ].
Sqlite3pp_EZ Copyright (C) 2025 David Maisonave (http::\www.axter.com)
Example Usage:		(Using sqlite3pp::Table container)
	// Example #1
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_NorthWind_table_Employee> my_tbl;
		for (auto row : my_tbl)
			std::wcout << row << std::endl;

	// Example #2
		for (int i = 0; i < my_tbl.size(); ++i)
			std::wcout << my_tbl[i].get_Id() << std::endl;

	// Example #3
		for (auto r = my_tbl.begin(); r != my_tbl.end(); ++r)
			std::wcout << r->get_PhotoPath() << std::endl;

	// Example #4
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_NorthWind_table_Employee> my_tbl;
		// Example#4a -- (C++11) Range-based loop
		for(auto row : my_tbl)
			std::cout << row.get_Id() << " | " << row.get_LastName() << " | " << row.get_FirstName() << " | " << row.get_Title() << " | " << row.get_TitleOfCourtesy() << " | " << row.get_BirthDate() << " | " << row.get_HireDate() << " | " << row.get_Address() << " | " << row.get_City() << " | " << row.get_Region() << " | " << row.get_PostalCode() << " | " << row.get_Country() << " | " << row.get_HomePhone() << " | " << row.get_Extension() << " | " << row.get_Photo() << " | " << row.get_Notes() << " | " << row.get_ReportsTo() << " | " << row.get_PhotoPath() << " | " << std::endl;

		// Example#4b -- C++ style iteration
		for (auto row = my_tbl.begin(); row != my_tbl.end(); ++row) 
			std::cout << row->get_Id() << " | " << row->get_LastName() << " | " << row->get_FirstName() << " | " << row->get_Title() << " | " << row->get_TitleOfCourtesy() << " | " << row->get_BirthDate() << " | " << row->get_HireDate() << " | " << row->get_Address() << " | " << row->get_City() << " | " << row->get_Region() << " | " << row->get_PostalCode() << " | " << row->get_Country() << " | " << row->get_HomePhone() << " | " << row->get_Extension() << " | " << row->get_Photo() << " | " << row->get_Notes() << " | " << row->get_ReportsTo() << " | " << row->get_PhotoPath() << " | " << std::endl;

		// Example#4c -- C style iteration
		for (int row = 0; row < my_tbl.size(); ++row) 
			std::cout << my_tbl[row].get_Id() << " | " << my_tbl[row].get_LastName() << " | " << my_tbl[row].get_FirstName() << " | " << my_tbl[row].get_Title() << " | " << my_tbl[row].get_TitleOfCourtesy() << " | " << my_tbl[row].get_BirthDate() << " | " << my_tbl[row].get_HireDate() << " | " << my_tbl[row].get_Address() << " | " << my_tbl[row].get_City() << " | " << my_tbl[row].get_Region() << " | " << my_tbl[row].get_PostalCode() << " | " << my_tbl[row].get_Country() << " | " << my_tbl[row].get_HomePhone() << " | " << my_tbl[row].get_Extension() << " | " << my_tbl[row].get_Photo() << " | " << my_tbl[row].get_Notes() << " | " << my_tbl[row].get_ReportsTo() << " | " << my_tbl[row].get_PhotoPath() << " | " << std::endl;
For more details see  https://github.com/David-Maisonave/sqlite3pp_EZ
*/
#ifndef SQL_DB_NORTHWIND_TABLE_EMPLOYEE_H
#define SQL_DB_NORTHWIND_TABLE_EMPLOYEE_H
#include <string>
#include "..\sqlite3pp_ez.h"

class sql_DB_NorthWind_table_Employee: public sqlite3pp::sql_base
{
	// A member variable for each field in the table
protected:
	Integer Id = 0;
	Varchar LastName;
	Varchar FirstName;
	Varchar Title;
	Varchar TitleOfCourtesy;
	Varchar BirthDate;
	Varchar HireDate;
	Varchar Address;
	Varchar City;
	Varchar Region;
	Varchar PostalCode;
	Varchar Country;
	Varchar HomePhone;
	Varchar Extension;
	Blob Photo;
	Varchar Notes;
	Integer ReportsTo = 0;
	Varchar PhotoPath;

public:
	using StrType = std::string;
	// Constructors
	sql_DB_NorthWind_table_Employee() {} // Default constructor
	template <class T> sql_DB_NorthWind_table_Employee(const T &t) { setData(t); } // Allows data input from different (or same) tables/views having the same data types and column names

	// getTableName, getColumnNames, getSelectColumnNames, and getStreamData are required for sqlite3pp::Table template class
	static StrType getTableName() { return "Employee" ; }
	static StrType getColumnNames() { return "Id, LastName, FirstName, Title, TitleOfCourtesy, BirthDate, HireDate, Address, City, Region, PostalCode, Country, HomePhone, Extension, Photo, Notes, ReportsTo, PhotoPath"; }
	static StrType getSelectColumnNames() { return "\"Id\", \"LastName\", \"FirstName\", \"Title\", \"TitleOfCourtesy\", \"BirthDate\", \"HireDate\", \"Address\", \"City\", \"Region\", \"PostalCode\", \"Country\", \"HomePhone\", \"Extension\", \"Photo\", \"Notes\", \"ReportsTo\", \"PhotoPath\""; }
	StrType GetValues() const
	{
		StrType strtype;
		strtype +=  "'" + sqlite3pp::to_string( Id) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( LastName) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( FirstName) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Title) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( TitleOfCourtesy) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( BirthDate) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( HireDate) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Address) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( City) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Region) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( PostalCode) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Country) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( HomePhone) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Extension) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Photo) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Notes) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( ReportsTo) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( PhotoPath) + "'";
		return strtype;
	}
	template<class T> void getStreamData( T q ) { q.getter()  >> Id >> LastName >> FirstName >> Title >> TitleOfCourtesy >> BirthDate >> HireDate >> Address >> City >> Region >> PostalCode >> Country >> HomePhone >> Extension >> Photo >> Notes >> ReportsTo >> PhotoPath;}
	template <class T> void setData(const T &t) // Used to transfer data from different tables/views having same data types and column names
	{
		Id = t.get_Id();
		LastName = t.get_LastName();
		FirstName = t.get_FirstName();
		Title = t.get_Title();
		TitleOfCourtesy = t.get_TitleOfCourtesy();
		BirthDate = t.get_BirthDate();
		HireDate = t.get_HireDate();
		Address = t.get_Address();
		City = t.get_City();
		Region = t.get_Region();
		PostalCode = t.get_PostalCode();
		Country = t.get_Country();
		HomePhone = t.get_HomePhone();
		Extension = t.get_Extension();
		Photo = t.get_Photo();
		Notes = t.get_Notes();
		ReportsTo = t.get_ReportsTo();
		PhotoPath = t.get_PhotoPath();
	}

	// Miscellaneous functions
	static int getColumnCount() { return 18; }

	// A get_ function for each field in the table, which allows read-only access to protected member variables.
	const Integer& get_Id() const {return Id;}
	const Varchar& get_LastName() const {return LastName;}
	const Varchar& get_FirstName() const {return FirstName;}
	const Varchar& get_Title() const {return Title;}
	const Varchar& get_TitleOfCourtesy() const {return TitleOfCourtesy;}
	const Varchar& get_BirthDate() const {return BirthDate;}
	const Varchar& get_HireDate() const {return HireDate;}
	const Varchar& get_Address() const {return Address;}
	const Varchar& get_City() const {return City;}
	const Varchar& get_Region() const {return Region;}
	const Varchar& get_PostalCode() const {return PostalCode;}
	const Varchar& get_Country() const {return Country;}
	const Varchar& get_HomePhone() const {return HomePhone;}
	const Varchar& get_Extension() const {return Extension;}
	const Blob& get_Photo() const {return Photo;}
	const Varchar& get_Notes() const {return Notes;}
	const Integer& get_ReportsTo() const {return ReportsTo;}
	const Varchar& get_PhotoPath() const {return PhotoPath;}

	// A set_ function for each field in the table.
	void set_Id(const Integer& data__) {Id = data__;}
	void set_LastName(const Varchar& data__) {LastName = data__;}
	void set_FirstName(const Varchar& data__) {FirstName = data__;}
	void set_Title(const Varchar& data__) {Title = data__;}
	void set_TitleOfCourtesy(const Varchar& data__) {TitleOfCourtesy = data__;}
	void set_BirthDate(const Varchar& data__) {BirthDate = data__;}
	void set_HireDate(const Varchar& data__) {HireDate = data__;}
	void set_Address(const Varchar& data__) {Address = data__;}
	void set_City(const Varchar& data__) {City = data__;}
	void set_Region(const Varchar& data__) {Region = data__;}
	void set_PostalCode(const Varchar& data__) {PostalCode = data__;}
	void set_Country(const Varchar& data__) {Country = data__;}
	void set_HomePhone(const Varchar& data__) {HomePhone = data__;}
	void set_Extension(const Varchar& data__) {Extension = data__;}
	void set_Photo(const Blob& data__) {Photo = data__;}
	void set_Notes(const Varchar& data__) {Notes = data__;}
	void set_ReportsTo(const Integer& data__) {ReportsTo = data__;}
	void set_PhotoPath(const Varchar& data__) {PhotoPath = data__;}

	////////////////////////////////////////////////////////////////////////////////////////////
	/* sqlite3pp::TableOStream container interface.
	Functions OStream(), operator<<(), and Delimiter() are required when using the sqlite3pp::TableOStream container.
	Example Usage:		(Using sqlite3pp::TableOStream container)
			TableOStream<sql_DB_NorthWind_table_Employee> tbl(DbFileNameArg("myDatabase.db"));
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
		t.os << Id << t.d << t.str(LastName) << t.d << t.str(FirstName) << t.d << t.str(Title) << t.d << t.str(TitleOfCourtesy) << t.d << t.str(BirthDate) << t.d << t.str(HireDate) << t.d << t.str(Address) << t.d << t.str(City) << t.d << t.str(Region) << t.d << t.str(PostalCode) << t.d << t.str(Country) << t.d << t.str(HomePhone) << t.d << t.str(Extension) << t.d << Photo << t.d << t.str(Notes) << t.d << ReportsTo << t.d << t.str(PhotoPath);
		return t;
	}
	friend std::ostream& operator<<(std::ostream& os, const sql_DB_NorthWind_table_Employee& t);
	friend std::wostream& operator<<(std::wostream& os, const sql_DB_NorthWind_table_Employee& t);
	static StrType Delimiter() { return "," ; }
	////////////////////////////////////////////////////////////////////////////////////////////
};
// sqlite3pp::TableOStream container interface.
inline std::ostream& operator<<(std::ostream& os, const sql_DB_NorthWind_table_Employee& t) { sqlite3pp::ostream_a o(os, t.Delimiter()); return t.OStream(o).os; }
inline std::wostream& operator<<(std::wostream& os, const sql_DB_NorthWind_table_Employee& t) { sqlite3pp::ostream_w o(os, t.Delimiter());  return t.OStream(o).os; }

#endif // !SQL_DB_NORTHWIND_TABLE_EMPLOYEE_H
