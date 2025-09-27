/* This file was automatically generated using [Sqlite3pp_EZ].
Sqlite3pp_EZ Copyright (C) 2025 David Maisonave (http::\www.axter.com)
Example Usage:		(Using sqlite3pp::Table container)
	// Example #1
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_NorthWind_table_Territory> my_tbl;
		for (auto& row : my_tbl)
			std::cout << row << std::endl;

	// Example #2
		for (int i = 0; i < my_tbl.size(); ++i)
			std::cout << my_tbl[i].get_Id() << std::endl;

	// Example #3
		for (auto r = my_tbl.begin(); r != my_tbl.end(); ++r)
			std::cout << r->get_RegionId() << std::endl;

	// Example #4
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_NorthWind_table_Territory> my_tbl;
		// Example#4a -- (C++11) Range-based loop
		for(auto& row : my_tbl)
			std::cout << row.get_Id() << " | " << row.get_TerritoryDescription() << " | " << row.get_RegionId() << " | " << std::endl;

		// Example#4b -- C++ style iteration
		for (auto row = my_tbl.begin(); row != my_tbl.end(); ++row) 
			std::cout << row->get_Id() << " | " << row->get_TerritoryDescription() << " | " << row->get_RegionId() << " | " << std::endl;

		// Example#4c -- C style iteration
		for (int row = 0; row < my_tbl.size(); ++row) 
			std::cout << my_tbl[row].get_Id() << " | " << my_tbl[row].get_TerritoryDescription() << " | " << my_tbl[row].get_RegionId() << " | " << std::endl;
For more details see  https://github.com/David-Maisonave/sqlite3pp_EZ
*/
#ifndef SQL_DB_NORTHWIND_TABLE_TERRITORY_H
#define SQL_DB_NORTHWIND_TABLE_TERRITORY_H
#include <string>
#include "..\sqlite3pp_ez.h"

class sql_DB_NorthWind_table_Territory: public sqlite3pp::sql_base
{
	// A member variable for each field in the table
protected:
	Varchar Id;
	Varchar TerritoryDescription;
	Integer RegionId = 0;

public:
	using StrType = std::string;
	// Constructors
	sql_DB_NorthWind_table_Territory() {} // Default constructor
	template <class T> sql_DB_NorthWind_table_Territory(const T &t) { setData(t); } // Allows data input from different (or same) tables/views having the same data types and column names

	// getTableName, getColumnNames, getSelectColumnNames, and getStreamData are required for sqlite3pp::Table template class
	static StrType getTableName() { return "Territory" ; }
	static StrType getColumnNames() { return "\"Id\", \"TerritoryDescription\", \"RegionId\""; }
	static StrType getSelectColumnNames() { return "\"Id\", \"TerritoryDescription\", \"RegionId\""; }
	StrType GetValues() const
	{
		StrType strtype;
		strtype +=  "'" + sqlite3pp::to_string( Id) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( TerritoryDescription) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( RegionId) + "'";
		return strtype;
	}
	template<class T> void getStreamData( T q ) { q.getter()  >> Id >> TerritoryDescription >> RegionId;}
	template <class T> void setData(const T &t) // Used to transfer data from different tables/views having same data types and column names
	{
		Id = t.get_Id();
		TerritoryDescription = t.get_TerritoryDescription();
		RegionId = t.get_RegionId();
	}

	// Miscellaneous functions
	static int getColumnCount() { return 3; }

	// A get_ function for each field in the table, which allows read-only access to protected member variables.
	const Varchar& get_Id() const {return Id;}
	const Varchar& get_TerritoryDescription() const {return TerritoryDescription;}
	const Integer& get_RegionId() const {return RegionId;}

	// A set_ function for each field in the table.
	void set_Id(const Varchar& data__) {Id = data__;}
	void set_TerritoryDescription(const Varchar& data__) {TerritoryDescription = data__;}
	void set_RegionId(const Integer& data__) {RegionId = data__;}

	////////////////////////////////////////////////////////////////////////////////////////////
	/* sqlite3pp::TableOStream container interface.
	Functions OStream(), operator<<(), and Delimiter() are required when using the sqlite3pp::TableOStream container.
	Example Usage:		(Using sqlite3pp::TableOStream container)
			TableOStream<sql_DB_NorthWind_table_Territory> tbl(DbFileNameArg("myDatabase.db"));
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
		t.os << t.str(Id) << t.d << t.str(TerritoryDescription) << t.d << RegionId;
		return t;
	}
	friend std::ostream& operator<<(std::ostream& os, const sql_DB_NorthWind_table_Territory& t);
	friend std::wostream& operator<<(std::wostream& os, const sql_DB_NorthWind_table_Territory& t);
	static StrType Delimiter() { return "," ; }
	////////////////////////////////////////////////////////////////////////////////////////////
};
// sqlite3pp::TableOStream container interface.
inline std::ostream& operator<<(std::ostream& os, const sql_DB_NorthWind_table_Territory& t) { sqlite3pp::ostream_a o(os, t.Delimiter()); return t.OStream(o).os; }
inline std::wostream& operator<<(std::wostream& os, const sql_DB_NorthWind_table_Territory& t) { sqlite3pp::ostream_w o(os, t.Delimiter());  return t.OStream(o).os; }

#endif // !SQL_DB_NORTHWIND_TABLE_TERRITORY_H
