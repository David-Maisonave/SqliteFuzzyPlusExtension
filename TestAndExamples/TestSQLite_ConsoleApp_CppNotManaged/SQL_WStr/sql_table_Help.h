/* This file was automatically generated using [Sqlite3pp_EZ].
Sqlite3pp_EZ Copyright (C) 2025 David Maisonave (http::\www.axter.com)
Example Usage:		(Using sqlite3pp::Table container)
	// Example #1
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_table_Help> my_tbl;
		for (auto row : my_tbl)
			std::wcout << row << std::endl;

	// Example #2
		for (int i = 0; i < my_tbl.size(); ++i)
			std::wcout << my_tbl[i].get_Function() << std::endl;

	// Example #3
		for (auto r = my_tbl.begin(); r != my_tbl.end(); ++r)
			std::wcout << r->get_WikiAlias() << std::endl;

	// Example #4
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_table_Help> my_tbl;
		// Example#4a -- (C++11) Range-based loop
		for(auto row : my_tbl)
			std::wcout << row.get_Function() << row.get_Description() << row.get_Arguments() << row.get_Return() << row.get_Details() << row.get_ExtensionAlias() << row.get_WikiAlias() << std::endl;

		// Example#4b -- C++ style iteration
		for (auto row = my_tbl.begin(); row != my_tbl.end(); ++row) 
			std::wcout << row->get_Function() << row->get_Description() << row->get_Arguments() << row->get_Return() << row->get_Details() << row->get_ExtensionAlias() << row->get_WikiAlias() << std::endl;

		// Example#4c -- C style iteration
		for (int row = 0; row < my_tbl.size(); ++row) 
			std::wcout << my_tbl[row].get_Function() << my_tbl[row].get_Description() << my_tbl[row].get_Arguments() << my_tbl[row].get_Return() << my_tbl[row].get_Details() << my_tbl[row].get_ExtensionAlias() << my_tbl[row].get_WikiAlias() << std::endl;
For more details see  https://github.com/David-Maisonave/sqlite3pp_EZ
*/
#ifndef SQL_TABLE_HELP_H
#define SQL_TABLE_HELP_H
#include <string>
#include "..\sqlite3pp_ez.h"

class sql_table_Help: public sqlite3pp::sql_base
{
	// A member variable for each field in the table
protected:
	Text Function;
	Text Description;
	Text Arguments;
	Text Return;
	Text Details;
	Text ExtensionAlias;
	Text WikiAlias;

public:
	using StrType = std::wstring;
	// Constructors
	sql_table_Help() {} // Default constructor
	template <class T> sql_table_Help(const T &t) { setData(t); } // Allows data input from different (or same) tables/views having the same data types and column names

	// getTableName, getColumnNames, getSelectColumnNames, and getStreamData are required for sqlite3pp::Table template class
	static StrType getTableName() { return L"Help" ; }
	static StrType getColumnNames() { return L"Function, Description, Arguments, Return, Details, ExtensionAlias, WikiAlias"; }
	static StrType getSelectColumnNames() { return L"'Function', 'Description', 'Arguments', 'Return', 'Details', 'ExtensionAlias', 'WikiAlias'"; }
	StrType GetValues() const
	{
		StrType strtype;
		strtype +=  L"'" + sqlite3pp::to_wstring( Function) + L"'";
		strtype +=  L",'" + sqlite3pp::to_wstring( Description) + L"'";
		strtype +=  L",'" + sqlite3pp::to_wstring( Arguments) + L"'";
		strtype +=  L",'" + sqlite3pp::to_wstring( Return) + L"'";
		strtype +=  L",'" + sqlite3pp::to_wstring( Details) + L"'";
		strtype +=  L",'" + sqlite3pp::to_wstring( ExtensionAlias) + L"'";
		strtype +=  L",'" + sqlite3pp::to_wstring( WikiAlias) + L"'";
		return strtype;
	}
	template<class T> void getStreamData( T q ) { q.getter()  >> Function >> Description >> Arguments >> Return >> Details >> ExtensionAlias >> WikiAlias;}
	template <class T> void setData(const T &t) // Used to transfer data from different tables/views having same data types and column names
	{
		Function = t.get_Function();
		Description = t.get_Description();
		Arguments = t.get_Arguments();
		Return = t.get_Return();
		Details = t.get_Details();
		ExtensionAlias = t.get_ExtensionAlias();
		WikiAlias = t.get_WikiAlias();
	}

	// Miscellaneous functions
	static int getColumnCount() { return 7; }

	// A get_ function for each field in the table, which allows read-only access to protected member variables.
	const Text& get_Function() const {return Function;}
	const Text& get_Description() const {return Description;}
	const Text& get_Arguments() const {return Arguments;}
	const Text& get_Return() const {return Return;}
	const Text& get_Details() const {return Details;}
	const Text& get_ExtensionAlias() const {return ExtensionAlias;}
	const Text& get_WikiAlias() const {return WikiAlias;}

	// A set_ function for each field in the table.
	void set_Function(const Text& data__) {Function = data__;}
	void set_Description(const Text& data__) {Description = data__;}
	void set_Arguments(const Text& data__) {Arguments = data__;}
	void set_Return(const Text& data__) {Return = data__;}
	void set_Details(const Text& data__) {Details = data__;}
	void set_ExtensionAlias(const Text& data__) {ExtensionAlias = data__;}
	void set_WikiAlias(const Text& data__) {WikiAlias = data__;}

	////////////////////////////////////////////////////////////////////////////////////////////
	/* sqlite3pp::TableOStream container interface.
	Functions OStream(), operator<<(), and Delimiter() are required when using the sqlite3pp::TableOStream container.
	Example Usage:		(Using sqlite3pp::TableOStream container)
			TableOStream<sql_table_Help> tbl(DbFileNameArg("myDatabase.db"));
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
		t.os << t.str(Function) << t.d << t.str(Description) << t.d << t.str(Arguments) << t.d << t.str(Return) << t.d << t.str(Details) << t.d << t.str(ExtensionAlias) << t.d << t.str(WikiAlias);
		return t;
	}
	friend std::ostream& operator<<(std::ostream& os, const sql_table_Help& t);
	friend std::wostream& operator<<(std::wostream& os, const sql_table_Help& t);
	static StrType Delimiter() { return L"," ; }
	////////////////////////////////////////////////////////////////////////////////////////////
};
// sqlite3pp::TableOStream container interface.
inline std::ostream& operator<<(std::ostream& os, const sql_table_Help& t) { sqlite3pp::ostream_a o(os, t.Delimiter()); return t.OStream(o).os; }
inline std::wostream& operator<<(std::wostream& os, const sql_table_Help& t) { sqlite3pp::ostream_w o(os, t.Delimiter());  return t.OStream(o).os; }

#endif // !SQL_TABLE_HELP_H
