/* This file was automatically generated using [Sqlite3pp_EZ].
Sqlite3pp_EZ Copyright (C) 2025 David Maisonave (http::\www.axter.com)
Example Usage:		(Using sqlite3pp::Table container)
	// Example #1
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_GameNames_table_AlternateNames> my_tbl;
		for (auto& row : my_tbl)
			std::cout << row << std::endl;

	// Example #2
		for (int i = 0; i < my_tbl.size(); ++i)
			std::cout << my_tbl[i].get_Name() << std::endl;

	// Example #3
		for (auto r = my_tbl.begin(); r != my_tbl.end(); ++r)
			std::cout << r->get_HashTitle() << std::endl;

	// Example #4
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_GameNames_table_AlternateNames> my_tbl;
		// Example#4a -- (C++11) Range-based loop
		for(auto& row : my_tbl)
			std::cout << row.get_Name() << " | " << row.get_Alternate() << " | " << row.get_Title() << " | " << row.get_HashName() << " | " << row.get_HashAlternate() << " | " << row.get_HashTitle() << " | " << std::endl;

		// Example#4b -- C++ style iteration
		for (auto row = my_tbl.begin(); row != my_tbl.end(); ++row) 
			std::cout << row->get_Name() << " | " << row->get_Alternate() << " | " << row->get_Title() << " | " << row->get_HashName() << " | " << row->get_HashAlternate() << " | " << row->get_HashTitle() << " | " << std::endl;

		// Example#4c -- C style iteration
		for (int row = 0; row < my_tbl.size(); ++row) 
			std::cout << my_tbl[row].get_Name() << " | " << my_tbl[row].get_Alternate() << " | " << my_tbl[row].get_Title() << " | " << my_tbl[row].get_HashName() << " | " << my_tbl[row].get_HashAlternate() << " | " << my_tbl[row].get_HashTitle() << " | " << std::endl;
For more details see  https://github.com/David-Maisonave/sqlite3pp_EZ
*/
#ifndef SQL_DB_GAMENAMES_TABLE_ALTERNATENAMES_H
#define SQL_DB_GAMENAMES_TABLE_ALTERNATENAMES_H
#include <string>
#include "..\sqlite3pp_ez.h"

class sql_DB_GameNames_table_AlternateNames: public sqlite3pp::sql_base
{
	// A member variable for each field in the table
protected:
	Text Name;
	Text Alternate;
	Text Title;
	UBigint HashName = 0;
	UBigint HashAlternate = 0;
	UBigint HashTitle = 0;

public:
	using StrType = std::string;
	// Constructors
	sql_DB_GameNames_table_AlternateNames() {} // Default constructor
	template <class T> sql_DB_GameNames_table_AlternateNames(const T &t) { setData(t); } // Allows data input from different (or same) tables/views having the same data types and column names

	// getTableName, getColumnNames, getSelectColumnNames, and getStreamData are required for sqlite3pp::Table template class
	static StrType getTableName() { return "AlternateNames" ; }
	static StrType getColumnNames() { return "\"Name\", \"Alternate\", \"Title\", \"HashName\", \"HashAlternate\", \"HashTitle\""; }
	static StrType getSelectColumnNames() { return "\"Name\", \"Alternate\", \"Title\", \"HashName\", \"HashAlternate\", \"HashTitle\""; }
	StrType GetValues() const
	{
		StrType strtype;
		strtype +=  "'" + sqlite3pp::to_string( Name) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Alternate) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Title) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( HashName) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( HashAlternate) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( HashTitle) + "'";
		return strtype;
	}
	template<class T> void getStreamData( T q ) { q.getter()  >> Name >> Alternate >> Title >> HashName >> HashAlternate >> HashTitle;}
	template <class T> void setData(const T &t) // Used to transfer data from different tables/views having same data types and column names
	{
		Name = t.get_Name();
		Alternate = t.get_Alternate();
		Title = t.get_Title();
		HashName = t.get_HashName();
		HashAlternate = t.get_HashAlternate();
		HashTitle = t.get_HashTitle();
	}

	// Miscellaneous functions
	static int getColumnCount() { return 6; }

	// A get_ function for each field in the table, which allows read-only access to protected member variables.
	const Text& get_Name() const {return Name;}
	const Text& get_Alternate() const {return Alternate;}
	const Text& get_Title() const {return Title;}
	const UBigint& get_HashName() const {return HashName;}
	const UBigint& get_HashAlternate() const {return HashAlternate;}
	const UBigint& get_HashTitle() const {return HashTitle;}

	// A set_ function for each field in the table.
	void set_Name(const Text& data__) {Name = data__;}
	void set_Alternate(const Text& data__) {Alternate = data__;}
	void set_Title(const Text& data__) {Title = data__;}
	void set_HashName(const UBigint& data__) {HashName = data__;}
	void set_HashAlternate(const UBigint& data__) {HashAlternate = data__;}
	void set_HashTitle(const UBigint& data__) {HashTitle = data__;}

	////////////////////////////////////////////////////////////////////////////////////////////
	/* sqlite3pp::TableOStream container interface.
	Functions OStream(), operator<<(), and Delimiter() are required when using the sqlite3pp::TableOStream container.
	Example Usage:		(Using sqlite3pp::TableOStream container)
			TableOStream<sql_DB_GameNames_table_AlternateNames> tbl(DbFileNameArg("myDatabase.db"));
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
		t.os << t.str(Name) << t.d << t.str(Alternate) << t.d << t.str(Title) << t.d << HashName << t.d << HashAlternate << t.d << HashTitle;
		return t;
	}
	friend std::ostream& operator<<(std::ostream& os, const sql_DB_GameNames_table_AlternateNames& t);
	friend std::wostream& operator<<(std::wostream& os, const sql_DB_GameNames_table_AlternateNames& t);
	static StrType Delimiter() { return "," ; }
	////////////////////////////////////////////////////////////////////////////////////////////
};
// sqlite3pp::TableOStream container interface.
inline std::ostream& operator<<(std::ostream& os, const sql_DB_GameNames_table_AlternateNames& t) { sqlite3pp::ostream_a o(os, t.Delimiter()); return t.OStream(o).os; }
inline std::wostream& operator<<(std::wostream& os, const sql_DB_GameNames_table_AlternateNames& t) { sqlite3pp::ostream_w o(os, t.Delimiter());  return t.OStream(o).os; }

#endif // !SQL_DB_GAMENAMES_TABLE_ALTERNATENAMES_H
