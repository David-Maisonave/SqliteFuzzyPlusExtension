/* This file was automatically generated using [Sqlite3pp_EZ].
Sqlite3pp_EZ Copyright (C) 2021 David Maisonave (http::\www.axter.com)
Example Usage:		(Using sqlite3pp::Table container)
	// Example #1
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_table_SimilarSoundingWords> my_tbl;
		for (auto row : my_tbl)
			std::wcout << row << std::endl;

	// Example #2
		for (int i = 0; i < my_tbl.size(); ++i)
			std::wcout << my_tbl[i].get_Words() << std::endl;

	// Example #3
		for (auto r = my_tbl.begin(); r != my_tbl.end(); ++r)
			std::wcout << r->get_get_MyColumnFoo()() << std::endl;

For more details see  https://github.com/David-Maisonave/sqlite3pp_EZ
*/
#ifndef SQL_TABLE_SIMILARSOUNDINGWORDS_H
#define SQL_TABLE_SIMILARSOUNDINGWORDS_H
#define _UNICODE
#include <tchar.h>
#include "..\sqlite3pp_ez.h"

class sql_table_SimilarSoundingWords: public sqlite3pp::sql_base
{
	// A member variable for each field in the table
protected:
	Text Words;

public:
	using StrType = sqlite3pp::tstring;
	// Constructors
	sql_table_SimilarSoundingWords() {} // Default constructor
	template <class T> sql_table_SimilarSoundingWords(const T &t) { setData(t); } // Allows data input from different (or same) tables/views having the same data types and column names

	// getTableName, getColumnNames, getSelectColumnNames, and getStreamData are required for sqlite3pp::Table template class
	static StrType getTableName() { return _T("SimilarSoundingWords" ); }
	static StrType getColumnNames() { return _T("Words"); }
	static StrType getSelectColumnNames() { return _T("'Words'"); }
	StrType GetValues() const
	{
		StrType strtype;
		strtype +=  _T("'") + sqlite3pp::to_tstring( Words) + _T("'");
		return strtype;
	}
	template<class T> void getStreamData( T q ) { q.getter()  >> Words;}
	template <class T> void setData(const T &t) // Used to transfer data from different tables/views having same data types and column names
	{
		Words = t.get_Words();
	}

	// Miscellaneous functions
	static int getColumnCount() { return 1; }

	// A get_ function for each field in the table, which allows read-only access to protected member variables.
	const Text& get_Words() const {return Words;}

	// A set_ function for each field in the table.
	void set_Words(const Text& data__) {Words = data__;}

	////////////////////////////////////////////////////////////////////////////////////////////
	/* sqlite3pp::TableOStream container interface.
	Functions OStream(), operator<<(), and Delimiter() are required when using the sqlite3pp::TableOStream container.
	Example Usage:		(Using sqlite3pp::TableOStream container)
			TableOStream<sql_table_SimilarSoundingWords> tbl(DbFileNameArg("myDatabase.db"));
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
		t.os << t.str(Words);
		return t;
	}
	friend std::ostream& operator<<(std::ostream& os, const sql_table_SimilarSoundingWords& t);
	friend std::wostream& operator<<(std::wostream& os, const sql_table_SimilarSoundingWords& t);
	static StrType Delimiter() { return _T("," ); }
	////////////////////////////////////////////////////////////////////////////////////////////
};
// sqlite3pp::TableOStream container interface.
inline std::ostream& operator<<(std::ostream& os, const sql_table_SimilarSoundingWords& t) { sqlite3pp::ostream_a o(os, t.Delimiter()); return t.OStream(o).os; }
inline std::wostream& operator<<(std::wostream& os, const sql_table_SimilarSoundingWords& t) { sqlite3pp::ostream_w o(os, t.Delimiter());  return t.OStream(o).os; }

#endif // !SQL_TABLE_SIMILARSOUNDINGWORDS_H
