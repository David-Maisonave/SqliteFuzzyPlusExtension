/* This file was automatically generated using [Sqlite3pp_EZ].
Sqlite3pp_EZ Copyright (C) 2025 David Maisonave (http::\www.axter.com)
Example Usage:		(Using sqlite3pp::Table container)
	// Example #1
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_sakila_view_film_list> my_tbl;
		for (auto row : my_tbl)
			std::wcout << row << std::endl;

	// Example #2
		for (int i = 0; i < my_tbl.size(); ++i)
			std::wcout << my_tbl[i].get_FID() << std::endl;

	// Example #3
		for (auto r = my_tbl.begin(); r != my_tbl.end(); ++r)
			std::wcout << r->get_actors() << std::endl;

	// Example #4
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_sakila_view_film_list> my_tbl;
		// Example#4a -- (C++11) Range-based loop
		for(auto row : my_tbl)
			std::cout << row.get_FID() << " | " << row.get_title() << " | " << row.get_description() << " | " << row.get_category() << " | " << row.get_price() << " | " << row.get_length() << " | " << row.get_rating() << " | " << row.get_actors() << " | " << std::endl;

		// Example#4b -- C++ style iteration
		for (auto row = my_tbl.begin(); row != my_tbl.end(); ++row) 
			std::cout << row->get_FID() << " | " << row->get_title() << " | " << row->get_description() << " | " << row->get_category() << " | " << row->get_price() << " | " << row->get_length() << " | " << row->get_rating() << " | " << row->get_actors() << " | " << std::endl;

		// Example#4c -- C style iteration
		for (int row = 0; row < my_tbl.size(); ++row) 
			std::cout << my_tbl[row].get_FID() << " | " << my_tbl[row].get_title() << " | " << my_tbl[row].get_description() << " | " << my_tbl[row].get_category() << " | " << my_tbl[row].get_price() << " | " << my_tbl[row].get_length() << " | " << my_tbl[row].get_rating() << " | " << my_tbl[row].get_actors() << " | " << std::endl;
For more details see  https://github.com/David-Maisonave/sqlite3pp_EZ
*/
#ifndef SQL_DB_SAKILA_VIEW_FILM_LIST_H
#define SQL_DB_SAKILA_VIEW_FILM_LIST_H
#include <string>
#include "..\sqlite3pp_ez.h"

class sql_DB_sakila_view_film_list: public sqlite3pp::sql_base
{
	// A member variable for each field in the table
protected:
	Int FID = 0;
	Varchar title;
	Text description;
	Varchar category;
	Decimal price = 0.0f;
	Smallint length;
	Varchar rating;
	Text actors;

public:
	using StrType = std::string;
	// Constructors
	sql_DB_sakila_view_film_list() {} // Default constructor
	template <class T> sql_DB_sakila_view_film_list(const T &t) { setData(t); } // Allows data input from different (or same) tables/views having the same data types and column names

	// getTableName, getColumnNames, getSelectColumnNames, and getStreamData are required for sqlite3pp::Table template class
	static StrType getTableName() { return "film_list" ; }
	static StrType getColumnNames() { return "\"FID\", \"title\", \"description\", \"category\", \"price\", \"length\", \"rating\", \"actors\""; }
	static StrType getSelectColumnNames() { return "\"FID\", \"title\", \"description\", \"category\", \"price\", \"length\", \"rating\", \"actors\""; }
	StrType GetValues() const
	{
		StrType strtype;
		strtype +=  "'" + sqlite3pp::to_string( FID) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( title) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( description) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( category) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( price) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( length) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( rating) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( actors) + "'";
		return strtype;
	}
	template<class T> void getStreamData( T q ) { q.getter()  >> FID >> title >> description >> category >> price >> length >> rating >> actors;}
	template <class T> void setData(const T &t) // Used to transfer data from different tables/views having same data types and column names
	{
		FID = t.get_FID();
		title = t.get_title();
		description = t.get_description();
		category = t.get_category();
		price = t.get_price();
		length = t.get_length();
		rating = t.get_rating();
		actors = t.get_actors();
	}

	// Miscellaneous functions
	static int getColumnCount() { return 8; }

	// A get_ function for each field in the table, which allows read-only access to protected member variables.
	const Int& get_FID() const {return FID;}
	const Varchar& get_title() const {return title;}
	const Text& get_description() const {return description;}
	const Varchar& get_category() const {return category;}
	const Decimal& get_price() const {return price;}
	const Smallint& get_length() const {return length;}
	const Varchar& get_rating() const {return rating;}
	const Text& get_actors() const {return actors;}

	// A set_ function for each field in the table.
	void set_FID(const Int& data__) {FID = data__;}
	void set_title(const Varchar& data__) {title = data__;}
	void set_description(const Text& data__) {description = data__;}
	void set_category(const Varchar& data__) {category = data__;}
	void set_price(const Decimal& data__) {price = data__;}
	void set_length(const Smallint& data__) {length = data__;}
	void set_rating(const Varchar& data__) {rating = data__;}
	void set_actors(const Text& data__) {actors = data__;}

	////////////////////////////////////////////////////////////////////////////////////////////
	/* sqlite3pp::TableOStream container interface.
	Functions OStream(), operator<<(), and Delimiter() are required when using the sqlite3pp::TableOStream container.
	Example Usage:		(Using sqlite3pp::TableOStream container)
			TableOStream<sql_DB_sakila_view_film_list> tbl(DbFileNameArg("myDatabase.db"));
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
		t.os << FID << t.d << t.str(title) << t.d << t.str(description) << t.d << t.str(category) << t.d << price << t.d << length << t.d << t.str(rating) << t.d << t.str(actors);
		return t;
	}
	friend std::ostream& operator<<(std::ostream& os, const sql_DB_sakila_view_film_list& t);
	friend std::wostream& operator<<(std::wostream& os, const sql_DB_sakila_view_film_list& t);
	static StrType Delimiter() { return "," ; }
	////////////////////////////////////////////////////////////////////////////////////////////
};
// sqlite3pp::TableOStream container interface.
inline std::ostream& operator<<(std::ostream& os, const sql_DB_sakila_view_film_list& t) { sqlite3pp::ostream_a o(os, t.Delimiter()); return t.OStream(o).os; }
inline std::wostream& operator<<(std::wostream& os, const sql_DB_sakila_view_film_list& t) { sqlite3pp::ostream_w o(os, t.Delimiter());  return t.OStream(o).os; }

#endif // !SQL_DB_SAKILA_VIEW_FILM_LIST_H
