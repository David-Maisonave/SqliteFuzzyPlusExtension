/* This file was automatically generated using [Sqlite3pp_EZ].
Sqlite3pp_EZ Copyright (C) 2025 David Maisonave (http::\www.axter.com)
Example Usage:		(Using sqlite3pp::Table container)
	// Example #1
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_table_SimilarPhrase> my_tbl;
		for (auto& row : my_tbl)
			std::cout << row << std::endl;

	// Example #2
		for (int i = 0; i < my_tbl.size(); ++i)
			std::cout << my_tbl[i].get_Phrases() << std::endl;

	// Example #3
		for (auto r = my_tbl.begin(); r != my_tbl.end(); ++r)
			std::cout << r->get_get_MyColumnFoo()() << std::endl;

	// Example #4
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_table_SimilarPhrase> my_tbl;
		// Example#4a -- (C++11) Range-based loop
		for(auto& row : my_tbl)
			std::cout << row.get_Phrases() << " | " << std::endl;

		// Example#4b -- C++ style iteration
		for (auto row = my_tbl.begin(); row != my_tbl.end(); ++row) 
			std::cout << row->get_Phrases() << " | " << std::endl;

		// Example#4c -- C style iteration
		for (int row = 0; row < my_tbl.size(); ++row) 
			std::cout << my_tbl[row].get_Phrases() << " | " << std::endl;
For more details see  https://github.com/David-Maisonave/sqlite3pp_EZ
*/
#ifndef SQL_TABLE_SIMILARPHRASE_H
#define SQL_TABLE_SIMILARPHRASE_H
#include <string>
#include "..\sqlite3pp_ez.h"

class sql_table_SimilarPhrase: public sqlite3pp::sql_base
{
	// A member variable for each field in the table
protected:
	Text Phrases;

public:
	using StrType = std::wstring;
	// Constructors
	sql_table_SimilarPhrase() {} // Default constructor
	template <class T> sql_table_SimilarPhrase(const T &t) { setData(t); } // Allows data input from different (or same) tables/views having the same data types and column names

	// getTableName, getColumnNames, getSelectColumnNames, and getStreamData are required for sqlite3pp::Table template class
	static StrType getTableName() { return L"SimilarPhrase" ; }
	static StrType getColumnNames() { return L"\"Phrases\""; }
	static StrType getSelectColumnNames() { return L"\"Phrases\""; }
	StrType GetValues() const
	{
		StrType strtype;
		strtype +=  L"'" + sqlite3pp::to_wstring( Phrases) + L"'";
		return strtype;
	}
	template<class T> void getStreamData( T q ) { q.getter()  >> Phrases;}
	template <class T> void setData(const T &t) // Used to transfer data from different tables/views having same data types and column names
	{
		Phrases = t.get_Phrases();
	}

	// Miscellaneous functions
	static int getColumnCount() { return 1; }

	// A get_ function for each field in the table, which allows read-only access to protected member variables.
	const Text& get_Phrases() const {return Phrases;}

	// A set_ function for each field in the table.
	void set_Phrases(const Text& data__) {Phrases = data__;}

	////////////////////////////////////////////////////////////////////////////////////////////
	/* sqlite3pp::TableOStream container interface.
	Functions OStream(), operator<<(), and Delimiter() are required when using the sqlite3pp::TableOStream container.
	Example Usage:		(Using sqlite3pp::TableOStream container)
			TableOStream<sql_table_SimilarPhrase> tbl(DbFileNameArg("myDatabase.db"));
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
		t.os << t.str(Phrases);
		return t;
	}
	friend std::ostream& operator<<(std::ostream& os, const sql_table_SimilarPhrase& t);
	friend std::wostream& operator<<(std::wostream& os, const sql_table_SimilarPhrase& t);
	static StrType Delimiter() { return L"," ; }
	////////////////////////////////////////////////////////////////////////////////////////////
};
// sqlite3pp::TableOStream container interface.
inline std::ostream& operator<<(std::ostream& os, const sql_table_SimilarPhrase& t) { sqlite3pp::ostream_a o(os, t.Delimiter()); return t.OStream(o).os; }
inline std::wostream& operator<<(std::wostream& os, const sql_table_SimilarPhrase& t) { sqlite3pp::ostream_w o(os, t.Delimiter());  return t.OStream(o).os; }

#endif // !SQL_TABLE_SIMILARPHRASE_H
