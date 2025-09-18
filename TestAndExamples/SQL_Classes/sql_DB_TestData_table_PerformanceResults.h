/* This file was automatically generated using [Sqlite3pp_EZ].
Sqlite3pp_EZ Copyright (C) 2025 David Maisonave (http::\www.axter.com)
Example Usage:		(Using sqlite3pp::Table container)
	// Example #1
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_TestData_table_PerformanceResults> my_tbl;
		for (auto row : my_tbl)
			std::wcout << row << std::endl;

	// Example #2
		for (int i = 0; i < my_tbl.size(); ++i)
			std::wcout << my_tbl[i].get_FunctionName() << std::endl;

	// Example #3
		for (auto r = my_tbl.begin(); r != my_tbl.end(); ++r)
			std::wcout << r->get_Performance10MillionRows() << std::endl;

	// Example #4
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_TestData_table_PerformanceResults> my_tbl;
		// Example#4a -- (C++11) Range-based loop
		for(auto row : my_tbl)
			std::wcout << row.get_FunctionName() << row.get_FunctionID() << row.get_QueryText() << row.get_QtyRowsReturned() << row.get_Results() << row.get_Notes() << row.get_Performance10KRows() << row.get_Performance100KRows() << row.get_Performance1MillionRows() << row.get_Performance5MillionRows() << row.get_Performance10MillionRows() << std::endl;

		// Example#4b -- C++ style iteration
		for (auto row = my_tbl.begin(); row != my_tbl.end(); ++row) 
			std::wcout << row->get_FunctionName() << row->get_FunctionID() << row->get_QueryText() << row->get_QtyRowsReturned() << row->get_Results() << row->get_Notes() << row->get_Performance10KRows() << row->get_Performance100KRows() << row->get_Performance1MillionRows() << row->get_Performance5MillionRows() << row->get_Performance10MillionRows() << std::endl;

		// Example#4c -- C style iteration
		for (int row = 0; row < my_tbl.size(); ++row) 
			std::wcout << my_tbl[row].get_FunctionName() << my_tbl[row].get_FunctionID() << my_tbl[row].get_QueryText() << my_tbl[row].get_QtyRowsReturned() << my_tbl[row].get_Results() << my_tbl[row].get_Notes() << my_tbl[row].get_Performance10KRows() << my_tbl[row].get_Performance100KRows() << my_tbl[row].get_Performance1MillionRows() << my_tbl[row].get_Performance5MillionRows() << my_tbl[row].get_Performance10MillionRows() << std::endl;
For more details see  https://github.com/David-Maisonave/sqlite3pp_EZ
*/
#ifndef SQL_DB_TESTDATA_TABLE_PERFORMANCERESULTS_H
#define SQL_DB_TESTDATA_TABLE_PERFORMANCERESULTS_H
#include <string>
#include "sqlite3pp_ez.h"

class sql_DB_TestData_table_PerformanceResults: public sqlite3pp::sql_base
{
	// A member variable for each field in the table
protected:
	Text FunctionName;
	Integer FunctionID = 0;
	Text QueryText;
	Integer QtyRowsReturned = 0;
	Blob Results;
	Text Notes;
	Real Performance10KRows = 0.0f;
	Real Performance100KRows = 0.0f;
	Real Performance1MillionRows = 0.0f;
	Real Performance5MillionRows = 0.0f;
	Real Performance10MillionRows = 0.0f;

public:
	using StrType = std::string;
	// Constructors
	sql_DB_TestData_table_PerformanceResults() {} // Default constructor
	template <class T> sql_DB_TestData_table_PerformanceResults(const T &t) { setData(t); } // Allows data input from different (or same) tables/views having the same data types and column names

	// getTableName, getColumnNames, getSelectColumnNames, and getStreamData are required for sqlite3pp::Table template class
	static StrType getTableName() { return "PerformanceResults" ; }
	static StrType getColumnNames() { return "FunctionName, FunctionID, QueryText, QtyRowsReturned, Results, Notes, Performance10KRows, Performance100KRows, Performance1MillionRows, Performance5MillionRows, Performance10MillionRows"; }
	static StrType getSelectColumnNames() { return "'FunctionName', 'FunctionID', 'QueryText', 'QtyRowsReturned', 'Results', 'Notes', 'Performance10KRows', 'Performance100KRows', 'Performance1MillionRows', 'Performance5MillionRows', 'Performance10MillionRows'"; }
	StrType GetValues() const
	{
		StrType strtype;
		strtype +=  "'" + sqlite3pp::to_string( FunctionName) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( FunctionID) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( QueryText) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( QtyRowsReturned) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Results) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Notes) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Performance10KRows) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Performance100KRows) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Performance1MillionRows) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Performance5MillionRows) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Performance10MillionRows) + "'";
		return strtype;
	}
	template<class T> void getStreamData( T q ) { q.getter()  >> FunctionName >> FunctionID >> QueryText >> QtyRowsReturned >> Results >> Notes >> Performance10KRows >> Performance100KRows >> Performance1MillionRows >> Performance5MillionRows >> Performance10MillionRows;}
	template <class T> void setData(const T &t) // Used to transfer data from different tables/views having same data types and column names
	{
		FunctionName = t.get_FunctionName();
		FunctionID = t.get_FunctionID();
		QueryText = t.get_QueryText();
		QtyRowsReturned = t.get_QtyRowsReturned();
		Results = t.get_Results();
		Notes = t.get_Notes();
		Performance10KRows = t.get_Performance10KRows();
		Performance100KRows = t.get_Performance100KRows();
		Performance1MillionRows = t.get_Performance1MillionRows();
		Performance5MillionRows = t.get_Performance5MillionRows();
		Performance10MillionRows = t.get_Performance10MillionRows();
	}

	// Miscellaneous functions
	static int getColumnCount() { return 11; }

	// A get_ function for each field in the table, which allows read-only access to protected member variables.
	const Text& get_FunctionName() const {return FunctionName;}
	const Integer& get_FunctionID() const {return FunctionID;}
	const Text& get_QueryText() const {return QueryText;}
	const Integer& get_QtyRowsReturned() const {return QtyRowsReturned;}
	const Blob& get_Results() const {return Results;}
	const Text& get_Notes() const {return Notes;}
	const Real& get_Performance10KRows() const {return Performance10KRows;}
	const Real& get_Performance100KRows() const {return Performance100KRows;}
	const Real& get_Performance1MillionRows() const {return Performance1MillionRows;}
	const Real& get_Performance5MillionRows() const {return Performance5MillionRows;}
	const Real& get_Performance10MillionRows() const {return Performance10MillionRows;}

	// A set_ function for each field in the table.
	void set_FunctionName(const Text& data__) {FunctionName = data__;}
	void set_FunctionID(const Integer& data__) {FunctionID = data__;}
	void set_QueryText(const Text& data__) {QueryText = data__;}
	void set_QtyRowsReturned(const Integer& data__) {QtyRowsReturned = data__;}
	void set_Results(const Blob& data__) {Results = data__;}
	void set_Notes(const Text& data__) {Notes = data__;}
	void set_Performance10KRows(const Real& data__) {Performance10KRows = data__;}
	void set_Performance100KRows(const Real& data__) {Performance100KRows = data__;}
	void set_Performance1MillionRows(const Real& data__) {Performance1MillionRows = data__;}
	void set_Performance5MillionRows(const Real& data__) {Performance5MillionRows = data__;}
	void set_Performance10MillionRows(const Real& data__) {Performance10MillionRows = data__;}

	////////////////////////////////////////////////////////////////////////////////////////////
	/* sqlite3pp::TableOStream container interface.
	Functions OStream(), operator<<(), and Delimiter() are required when using the sqlite3pp::TableOStream container.
	Example Usage:		(Using sqlite3pp::TableOStream container)
			TableOStream<sql_DB_TestData_table_PerformanceResults> tbl(DbFileNameArg("myDatabase.db"));
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
		t.os << t.str(FunctionName) << t.d << FunctionID << t.d << t.str(QueryText) << t.d << QtyRowsReturned << t.d << Results << t.d << t.str(Notes) << t.d << Performance10KRows << t.d << Performance100KRows << t.d << Performance1MillionRows << t.d << Performance5MillionRows << t.d << Performance10MillionRows;
		return t;
	}
	friend std::ostream& operator<<(std::ostream& os, const sql_DB_TestData_table_PerformanceResults& t);
	friend std::wostream& operator<<(std::wostream& os, const sql_DB_TestData_table_PerformanceResults& t);
	static StrType Delimiter() { return "," ; }
	////////////////////////////////////////////////////////////////////////////////////////////
};
// sqlite3pp::TableOStream container interface.
inline std::ostream& operator<<(std::ostream& os, const sql_DB_TestData_table_PerformanceResults& t) { sqlite3pp::ostream_a o(os, t.Delimiter()); return t.OStream(o).os; }
inline std::wostream& operator<<(std::wostream& os, const sql_DB_TestData_table_PerformanceResults& t) { sqlite3pp::ostream_w o(os, t.Delimiter());  return t.OStream(o).os; }

#endif // !SQL_DB_TESTDATA_TABLE_PERFORMANCERESULTS_H
