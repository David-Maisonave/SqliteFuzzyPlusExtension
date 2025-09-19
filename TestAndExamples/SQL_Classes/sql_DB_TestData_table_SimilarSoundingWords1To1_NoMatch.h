/* This file was automatically generated using [Sqlite3pp_EZ].
Sqlite3pp_EZ Copyright (C) 2025 David Maisonave (http::\www.axter.com)
Example Usage:		(Using sqlite3pp::Table container)
	// Example #1
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_TestData_table_SimilarSoundingWords1To1_NoMatch> my_tbl;
		for (auto row : my_tbl)
			std::wcout << row << std::endl;

	// Example #2
		for (int i = 0; i < my_tbl.size(); ++i)
			std::wcout << my_tbl[i].get_Source1() << std::endl;

	// Example #3
		for (auto r = my_tbl.begin(); r != my_tbl.end(); ++r)
			std::wcout << r->get_Source2() << std::endl;

	// Example #4
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_TestData_table_SimilarSoundingWords1To1_NoMatch> my_tbl;
		// Example#4a -- (C++11) Range-based loop
		for(auto row : my_tbl)
			std::cout << row.get_Source1() << " | " << row.get_Source2() << " | " << std::endl;

		// Example#4b -- C++ style iteration
		for (auto row = my_tbl.begin(); row != my_tbl.end(); ++row) 
			std::cout << row->get_Source1() << " | " << row->get_Source2() << " | " << std::endl;

		// Example#4c -- C style iteration
		for (int row = 0; row < my_tbl.size(); ++row) 
			std::cout << my_tbl[row].get_Source1() << " | " << my_tbl[row].get_Source2() << " | " << std::endl;
For more details see  https://github.com/David-Maisonave/sqlite3pp_EZ
*/
#ifndef SQL_DB_TESTDATA_TABLE_SIMILARSOUNDINGWORDS1TO1_NOMATCH_H
#define SQL_DB_TESTDATA_TABLE_SIMILARSOUNDINGWORDS1TO1_NOMATCH_H
#include <string>
#include "sqlite3pp_ez.h"

class sql_DB_TestData_table_SimilarSoundingWords1To1_NoMatch: public sqlite3pp::sql_base
{
	// A member variable for each field in the table
protected:
	Text Source1;
	Text Source2;

public:
	using StrType = std::string;
	// Constructors
	sql_DB_TestData_table_SimilarSoundingWords1To1_NoMatch() {} // Default constructor
	template <class T> sql_DB_TestData_table_SimilarSoundingWords1To1_NoMatch(const T &t) { setData(t); } // Allows data input from different (or same) tables/views having the same data types and column names

	// getTableName, getColumnNames, getSelectColumnNames, and getStreamData are required for sqlite3pp::Table template class
	static StrType getTableName() { return "SimilarSoundingWords1To1_NoMatch" ; }
	static StrType getColumnNames() { return "Source1, Source2"; }
	static StrType getSelectColumnNames() { return "\"Source1\", \"Source2\""; }
	StrType GetValues() const
	{
		StrType strtype;
		strtype +=  "'" + sqlite3pp::to_string( Source1) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Source2) + "'";
		return strtype;
	}
	template<class T> void getStreamData( T q ) { q.getter()  >> Source1 >> Source2;}
	template <class T> void setData(const T &t) // Used to transfer data from different tables/views having same data types and column names
	{
		Source1 = t.get_Source1();
		Source2 = t.get_Source2();
	}

	// Miscellaneous functions
	static int getColumnCount() { return 2; }

	// A get_ function for each field in the table, which allows read-only access to protected member variables.
	const Text& get_Source1() const {return Source1;}
	const Text& get_Source2() const {return Source2;}

	// A set_ function for each field in the table.
	void set_Source1(const Text& data__) {Source1 = data__;}
	void set_Source2(const Text& data__) {Source2 = data__;}

	////////////////////////////////////////////////////////////////////////////////////////////
	/* sqlite3pp::TableOStream container interface.
	Functions OStream(), operator<<(), and Delimiter() are required when using the sqlite3pp::TableOStream container.
	Example Usage:		(Using sqlite3pp::TableOStream container)
			TableOStream<sql_DB_TestData_table_SimilarSoundingWords1To1_NoMatch> tbl(DbFileNameArg("myDatabase.db"));
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
		t.os << t.str(Source1) << t.d << t.str(Source2);
		return t;
	}
	friend std::ostream& operator<<(std::ostream& os, const sql_DB_TestData_table_SimilarSoundingWords1To1_NoMatch& t);
	friend std::wostream& operator<<(std::wostream& os, const sql_DB_TestData_table_SimilarSoundingWords1To1_NoMatch& t);
	static StrType Delimiter() { return "," ; }
	////////////////////////////////////////////////////////////////////////////////////////////
};
// sqlite3pp::TableOStream container interface.
inline std::ostream& operator<<(std::ostream& os, const sql_DB_TestData_table_SimilarSoundingWords1To1_NoMatch& t) { sqlite3pp::ostream_a o(os, t.Delimiter()); return t.OStream(o).os; }
inline std::wostream& operator<<(std::wostream& os, const sql_DB_TestData_table_SimilarSoundingWords1To1_NoMatch& t) { sqlite3pp::ostream_w o(os, t.Delimiter());  return t.OStream(o).os; }

#endif // !SQL_DB_TESTDATA_TABLE_SIMILARSOUNDINGWORDS1TO1_NOMATCH_H
