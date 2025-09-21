/* This file was automatically generated using [Sqlite3pp_EZ].
Sqlite3pp_EZ Copyright (C) 2025 David Maisonave (http::\www.axter.com)
Example Usage:		(Using sqlite3pp::Table container)
	// Example #1
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_TestData_table_zTroubleFields> my_tbl;
		for (auto& row : my_tbl)
			std::cout << row << std::endl;

	// Example #2
		for (int i = 0; i < my_tbl.size(); ++i)
			std::cout << my_tbl[i].get_Some__Names() << std::endl;

	// Example #3
		for (auto r = my_tbl.begin(); r != my_tbl.end(); ++r)
			std::cout << r->get_Big__Integer__Support__3() << std::endl;

	// Example #4
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_TestData_table_zTroubleFields> my_tbl;
		// Example#4a -- (C++11) Range-based loop
		for(auto& row : my_tbl)
			std::cout << row.get_Some__Names() << " | " << row.get_Zip__Code() << " | " << row.get_City__and__State() << " | " << row.get_Area__Code() << " | " << row.get_Bad__Type() << " | " << row.get_Is__US__Born() << " | " << row.get_Is__US__Citizen__() << " | " << row.get_Unsigned__Big__Integer__Support() << " | " << row.get_Unsigned__Big__Integer__Support2() << " | " << row.get_Big__Integer__Support() << " | " << row.get_Big__Integer__Support__2() << " | " << row.get_Big__Integer__Support__3() << " | " << std::endl;

		// Example#4b -- C++ style iteration
		for (auto row = my_tbl.begin(); row != my_tbl.end(); ++row) 
			std::cout << row->get_Some__Names() << " | " << row->get_Zip__Code() << " | " << row->get_City__and__State() << " | " << row->get_Area__Code() << " | " << row->get_Bad__Type() << " | " << row->get_Is__US__Born() << " | " << row->get_Is__US__Citizen__() << " | " << row->get_Unsigned__Big__Integer__Support() << " | " << row->get_Unsigned__Big__Integer__Support2() << " | " << row->get_Big__Integer__Support() << " | " << row->get_Big__Integer__Support__2() << " | " << row->get_Big__Integer__Support__3() << " | " << std::endl;

		// Example#4c -- C style iteration
		for (int row = 0; row < my_tbl.size(); ++row) 
			std::cout << my_tbl[row].get_Some__Names() << " | " << my_tbl[row].get_Zip__Code() << " | " << my_tbl[row].get_City__and__State() << " | " << my_tbl[row].get_Area__Code() << " | " << my_tbl[row].get_Bad__Type() << " | " << my_tbl[row].get_Is__US__Born() << " | " << my_tbl[row].get_Is__US__Citizen__() << " | " << my_tbl[row].get_Unsigned__Big__Integer__Support() << " | " << my_tbl[row].get_Unsigned__Big__Integer__Support2() << " | " << my_tbl[row].get_Big__Integer__Support() << " | " << my_tbl[row].get_Big__Integer__Support__2() << " | " << my_tbl[row].get_Big__Integer__Support__3() << " | " << std::endl;
For more details see  https://github.com/David-Maisonave/sqlite3pp_EZ
*/
#ifndef SQL_DB_TESTDATA_TABLE_ZTROUBLEFIELDS_HPP
#define SQL_DB_TESTDATA_TABLE_ZTROUBLEFIELDS_HPP
#include <string>
#include "sqlite3pp_ez.h"

class sql_DB_TestData_table_zTroubleFields: public sqlite3pp::sql_base
{
	// A member variable for each field in the table
protected:
	Text Some__Names;
	Integer Zip__Code = 0;
	Text City__and__State;
	Numeric Area__Code = 0.0f;
	Numeric Bad__Type = 0.0f;
	Boolean Is__US__Born = false;
	Boolean Is__US__Citizen__ = false;
	UBigint Unsigned__Big__Integer__Support = 0;
	UBigint Unsigned__Big__Integer__Support2 = 0;
	Bigint Big__Integer__Support = 0;
	Bigint Big__Integer__Support__2 = 0;
	Bigint Big__Integer__Support__3 = 0;

public:
	using StrType = std::string;
	// Constructors
	sql_DB_TestData_table_zTroubleFields() {} // Default constructor
	template <class T> sql_DB_TestData_table_zTroubleFields(const T &t) { setData(t); } // Allows data input from different (or same) tables/views having the same data types and column names

	// getTableName, getColumnNames, getSelectColumnNames, and getStreamData are required for sqlite3pp::Table template class
	static StrType getTableName() { return "zTroubleFields" ; }
	static StrType getColumnNames() { return "\"Some Names\", \"Zip Code\", \"City and State\", \"Area Code\", \"Bad Type\", \"Is US Born\", \"Is US Citizen \", \"Unsigned Big Integer Support\", \"Unsigned Big Integer Support2\", \"Big Integer Support\", \"Big Integer Support 2\", \"Big Integer Support 3\""; }
	static StrType getSelectColumnNames() { return "\"Some Names\", \"Zip Code\", \"City and State\", \"Area Code\", \"Bad Type\", \"Is US Born\", \"Is US Citizen \", \"Unsigned Big Integer Support\", \"Unsigned Big Integer Support2\", \"Big Integer Support\", \"Big Integer Support 2\", \"Big Integer Support 3\""; }
	StrType GetValues() const
	{
		StrType strtype;
		strtype +=  "'" + sqlite3pp::to_string( Some__Names) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Zip__Code) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( City__and__State) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Area__Code) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Bad__Type) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Is__US__Born) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Is__US__Citizen__) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Unsigned__Big__Integer__Support) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Unsigned__Big__Integer__Support2) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Big__Integer__Support) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Big__Integer__Support__2) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Big__Integer__Support__3) + "'";
		return strtype;
	}
	template<class T> void getStreamData( T q ) { q.getter()  >> Some__Names >> Zip__Code >> City__and__State >> Area__Code >> Bad__Type >> Is__US__Born >> Is__US__Citizen__ >> Unsigned__Big__Integer__Support >> Unsigned__Big__Integer__Support2 >> Big__Integer__Support >> Big__Integer__Support__2 >> Big__Integer__Support__3;}
	template <class T> void setData(const T &t) // Used to transfer data from different tables/views having same data types and column names
	{
		Some__Names = t.get_Some__Names();
		Zip__Code = t.get_Zip__Code();
		City__and__State = t.get_City__and__State();
		Area__Code = t.get_Area__Code();
		Bad__Type = t.get_Bad__Type();
		Is__US__Born = t.get_Is__US__Born();
		Is__US__Citizen__ = t.get_Is__US__Citizen__();
		Unsigned__Big__Integer__Support = t.get_Unsigned__Big__Integer__Support();
		Unsigned__Big__Integer__Support2 = t.get_Unsigned__Big__Integer__Support2();
		Big__Integer__Support = t.get_Big__Integer__Support();
		Big__Integer__Support__2 = t.get_Big__Integer__Support__2();
		Big__Integer__Support__3 = t.get_Big__Integer__Support__3();
	}

	// Miscellaneous functions
	static int getColumnCount() { return 12; }

	// A get_ function for each field in the table, which allows read-only access to protected member variables.
	const Text& get_Some__Names() const {return Some__Names;}
	const Integer& get_Zip__Code() const {return Zip__Code;}
	const Text& get_City__and__State() const {return City__and__State;}
	const Numeric& get_Area__Code() const {return Area__Code;}
	const Numeric& get_Bad__Type() const {return Bad__Type;}
	const Boolean& get_Is__US__Born() const {return Is__US__Born;}
	const Boolean& get_Is__US__Citizen__() const {return Is__US__Citizen__;}
	const UBigint& get_Unsigned__Big__Integer__Support() const {return Unsigned__Big__Integer__Support;}
	const UBigint& get_Unsigned__Big__Integer__Support2() const {return Unsigned__Big__Integer__Support2;}
	const Bigint& get_Big__Integer__Support() const {return Big__Integer__Support;}
	const Bigint& get_Big__Integer__Support__2() const {return Big__Integer__Support__2;}
	const Bigint& get_Big__Integer__Support__3() const {return Big__Integer__Support__3;}

	// A set_ function for each field in the table.
	void set_Some__Names(const Text& data__) {Some__Names = data__;}
	void set_Zip__Code(const Integer& data__) {Zip__Code = data__;}
	void set_City__and__State(const Text& data__) {City__and__State = data__;}
	void set_Area__Code(const Numeric& data__) {Area__Code = data__;}
	void set_Bad__Type(const Numeric& data__) {Bad__Type = data__;}
	void set_Is__US__Born(const Boolean& data__) {Is__US__Born = data__;}
	void set_Is__US__Citizen__(const Boolean& data__) {Is__US__Citizen__ = data__;}
	void set_Unsigned__Big__Integer__Support(const UBigint& data__) {Unsigned__Big__Integer__Support = data__;}
	void set_Unsigned__Big__Integer__Support2(const UBigint& data__) {Unsigned__Big__Integer__Support2 = data__;}
	void set_Big__Integer__Support(const Bigint& data__) {Big__Integer__Support = data__;}
	void set_Big__Integer__Support__2(const Bigint& data__) {Big__Integer__Support__2 = data__;}
	void set_Big__Integer__Support__3(const Bigint& data__) {Big__Integer__Support__3 = data__;}

	////////////////////////////////////////////////////////////////////////////////////////////
	/* sqlite3pp::TableOStream container interface.
	Functions OStream(), operator<<(), and Delimiter() are required when using the sqlite3pp::TableOStream container.
	Example Usage:		(Using sqlite3pp::TableOStream container)
			TableOStream<sql_DB_TestData_table_zTroubleFields> tbl(DbFileNameArg("myDatabase.db"));
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
		t.os << t.str(Some__Names) << t.d << Zip__Code << t.d << t.str(City__and__State) << t.d << Area__Code << t.d << Bad__Type << t.d << Is__US__Born << t.d << Is__US__Citizen__ << t.d << Unsigned__Big__Integer__Support << t.d << Unsigned__Big__Integer__Support2 << t.d << Big__Integer__Support << t.d << Big__Integer__Support__2 << t.d << Big__Integer__Support__3;
		return t;
	}
	friend std::ostream& operator<<(std::ostream& os, const sql_DB_TestData_table_zTroubleFields& t);
	friend std::wostream& operator<<(std::wostream& os, const sql_DB_TestData_table_zTroubleFields& t);
	static StrType Delimiter() { return "," ; }
	////////////////////////////////////////////////////////////////////////////////////////////
};
// sqlite3pp::TableOStream container interface.
inline std::ostream& operator<<(std::ostream& os, const sql_DB_TestData_table_zTroubleFields& t) { sqlite3pp::ostream_a o(os, t.Delimiter()); return t.OStream(o).os; }
inline std::wostream& operator<<(std::wostream& os, const sql_DB_TestData_table_zTroubleFields& t) { sqlite3pp::ostream_w o(os, t.Delimiter());  return t.OStream(o).os; }

#endif // !SQL_DB_TESTDATA_TABLE_ZTROUBLEFIELDS_HPP
