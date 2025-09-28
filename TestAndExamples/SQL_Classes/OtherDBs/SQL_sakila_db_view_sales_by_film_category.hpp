/* This file was automatically generated using [Sqlite3pp_EZ].
Sqlite3pp_EZ Copyright (C) 2025 David Maisonave (http::\www.axter.com)
Example Usage:		(Using sqlite3pp::Table container)
	// Example #1
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<SQL_sakila_db_view_sales_by_film_category> my_tbl;
		for (auto& row : my_tbl)
			std::cout << row << std::endl;

	// Example #2
		for (int i = 0; i < my_tbl.size(); ++i)
			std::cout << my_tbl[i].get_category() << std::endl;

	// Example #3
		for (auto r = my_tbl.begin(); r != my_tbl.end(); ++r)
			std::cout << r->get_total_sales() << std::endl;

	// Example #4
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<SQL_sakila_db_view_sales_by_film_category> my_tbl;
		// Example#4a -- (C++11) Range-based loop
		for(auto& row : my_tbl)
			std::cout << row.get_category() << " | " << row.get_total_sales() << " | " << std::endl;

		// Example#4b -- C++ style iteration
		for (auto row = my_tbl.begin(); row != my_tbl.end(); ++row) 
			std::cout << row->get_category() << " | " << row->get_total_sales() << " | " << std::endl;

		// Example#4c -- C style iteration
		for (int row = 0; row < my_tbl.size(); ++row) 
			std::cout << my_tbl[row].get_category() << " | " << my_tbl[row].get_total_sales() << " | " << std::endl;
For more details see  https://github.com/David-Maisonave/sqlite3pp_EZ
*/
#ifndef SQL_SAKILA_DB_VIEW_SALES_BY_FILM_CATEGORY_H
#define SQL_SAKILA_DB_VIEW_SALES_BY_FILM_CATEGORY_H
#include <string>
#include "..\..\sqlite3pp_ez\sqlite3pp_ez.h"

class SQL_sakila_db_view_sales_by_film_category: public sqlite3pp::sql_base
{
	// A member variable for each field in the table
protected:
	Varchar category;
	Text total_sales;

public:
	using StrType = std::string;
	// Constructors
	SQL_sakila_db_view_sales_by_film_category() {} // Default constructor
	template <class T> SQL_sakila_db_view_sales_by_film_category(const T &t) { setData(t); } // Allows data input from different (or same) tables/views having the same data types and column names

	// getTableName, getColumnNames, getSelectColumnNames, and getStreamData are required for sqlite3pp::Table template class
	static StrType getTableName() { return "sales_by_film_category" ; }
	static StrType getColumnNames() { return "\"category\", \"total_sales\""; }
	static StrType getSelectColumnNames() { return "\"category\", \"total_sales\""; }
	StrType GetValues() const
	{
		StrType strtype;
		strtype +=  "'" + sqlite3pp::to_string( category) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( total_sales) + "'";
		return strtype;
	}
	template<class T> void getStreamData( T q ) { q.getter()  >> category >> total_sales;}
	template <class T> void setData(const T &t) // Used to transfer data from different tables/views having same data types and column names
	{
		category = t.get_category();
		total_sales = t.get_total_sales();
	}

	// Miscellaneous functions
	static int getColumnCount() { return 2; }

	// A get_ function for each field in the table, which allows read-only access to protected member variables.
	const Varchar& get_category() const {return category;}
	const Text& get_total_sales() const {return total_sales;}

	// A set_ function for each field in the table.
	void set_category(const Varchar& data__) {category = data__;}
	void set_total_sales(const Text& data__) {total_sales = data__;}

	////////////////////////////////////////////////////////////////////////////////////////////
	/* sqlite3pp::TableOStream container interface.
	Functions OStream(), operator<<(), and Delimiter() are required when using the sqlite3pp::TableOStream container.
	Example Usage:		(Using sqlite3pp::TableOStream container)
			TableOStream<SQL_sakila_db_view_sales_by_film_category> tbl(DbFileNameArg("myDatabase.db"));
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
		t.os << t.str(category) << t.d << t.str(total_sales);
		return t;
	}
	friend std::ostream& operator<<(std::ostream& os, const SQL_sakila_db_view_sales_by_film_category& t);
	friend std::wostream& operator<<(std::wostream& os, const SQL_sakila_db_view_sales_by_film_category& t);
	static StrType Delimiter() { return "," ; }
	////////////////////////////////////////////////////////////////////////////////////////////
};
// sqlite3pp::TableOStream container interface.
inline std::ostream& operator<<(std::ostream& os, const SQL_sakila_db_view_sales_by_film_category& t) { sqlite3pp::ostream_a o(os, t.Delimiter()); return t.OStream(o).os; }
inline std::wostream& operator<<(std::wostream& os, const SQL_sakila_db_view_sales_by_film_category& t) { sqlite3pp::ostream_w o(os, t.Delimiter());  return t.OStream(o).os; }

#endif // !SQL_SAKILA_DB_VIEW_SALES_BY_FILM_CATEGORY_H
