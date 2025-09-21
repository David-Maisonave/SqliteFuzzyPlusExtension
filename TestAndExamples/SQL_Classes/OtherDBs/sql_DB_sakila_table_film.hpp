/* This file was automatically generated using [Sqlite3pp_EZ].
Sqlite3pp_EZ Copyright (C) 2025 David Maisonave (http::\www.axter.com)
Example Usage:		(Using sqlite3pp::Table container)
	// Example #1
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_sakila_table_film> my_tbl;
		for (auto& row : my_tbl)
			std::cout << row << std::endl;

	// Example #2
		for (int i = 0; i < my_tbl.size(); ++i)
			std::cout << my_tbl[i].get_film_id() << std::endl;

	// Example #3
		for (auto r = my_tbl.begin(); r != my_tbl.end(); ++r)
			std::cout << r->get_last_update() << std::endl;

	// Example #4
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_sakila_table_film> my_tbl;
		// Example#4a -- (C++11) Range-based loop
		for(auto& row : my_tbl)
			std::cout << row.get_film_id() << " | " << row.get_title() << " | " << row.get_description() << " | " << row.get_release_year() << " | " << row.get_language_id() << " | " << row.get_original_language_id() << " | " << row.get_rental_duration() << " | " << row.get_rental_rate() << " | " << row.get_length() << " | " << row.get_replacement_cost() << " | " << row.get_rating() << " | " << row.get_special_features() << " | " << row.get_last_update() << " | " << std::endl;

		// Example#4b -- C++ style iteration
		for (auto row = my_tbl.begin(); row != my_tbl.end(); ++row) 
			std::cout << row->get_film_id() << " | " << row->get_title() << " | " << row->get_description() << " | " << row->get_release_year() << " | " << row->get_language_id() << " | " << row->get_original_language_id() << " | " << row->get_rental_duration() << " | " << row->get_rental_rate() << " | " << row->get_length() << " | " << row->get_replacement_cost() << " | " << row->get_rating() << " | " << row->get_special_features() << " | " << row->get_last_update() << " | " << std::endl;

		// Example#4c -- C style iteration
		for (int row = 0; row < my_tbl.size(); ++row) 
			std::cout << my_tbl[row].get_film_id() << " | " << my_tbl[row].get_title() << " | " << my_tbl[row].get_description() << " | " << my_tbl[row].get_release_year() << " | " << my_tbl[row].get_language_id() << " | " << my_tbl[row].get_original_language_id() << " | " << my_tbl[row].get_rental_duration() << " | " << my_tbl[row].get_rental_rate() << " | " << my_tbl[row].get_length() << " | " << my_tbl[row].get_replacement_cost() << " | " << my_tbl[row].get_rating() << " | " << my_tbl[row].get_special_features() << " | " << my_tbl[row].get_last_update() << " | " << std::endl;
For more details see  https://github.com/David-Maisonave/sqlite3pp_EZ
*/
#ifndef SQL_DB_SAKILA_TABLE_FILM_HPP
#define SQL_DB_SAKILA_TABLE_FILM_HPP
#include <string>
#include "..\sqlite3pp_ez.h"

class sql_DB_sakila_table_film: public sqlite3pp::sql_base
{
	// A member variable for each field in the table
protected:
	Int film_id = 0;
	Varchar title;
	Text description;
	Varchar release_year;
	Smallint language_id = 0;
	Smallint original_language_id = 0;
	Smallint rental_duration = 0;
	Decimal rental_rate = 0.0f;
	Smallint length = 0;
	Decimal replacement_cost = 0.0f;
	Varchar rating;
	Varchar special_features;
	Bigint last_update = 0;

public:
	using StrType = std::string;
	// Constructors
	sql_DB_sakila_table_film() {} // Default constructor
	template <class T> sql_DB_sakila_table_film(const T &t) { setData(t); } // Allows data input from different (or same) tables/views having the same data types and column names

	// getTableName, getColumnNames, getSelectColumnNames, and getStreamData are required for sqlite3pp::Table template class
	static StrType getTableName() { return "film" ; }
	static StrType getColumnNames() { return "\"film_id\", \"title\", \"description\", \"release_year\", \"language_id\", \"original_language_id\", \"rental_duration\", \"rental_rate\", \"length\", \"replacement_cost\", \"rating\", \"special_features\", \"last_update\""; }
	static StrType getSelectColumnNames() { return "\"film_id\", \"title\", \"description\", \"release_year\", \"language_id\", \"original_language_id\", \"rental_duration\", \"rental_rate\", \"length\", \"replacement_cost\", \"rating\", \"special_features\", \"last_update\""; }
	StrType GetValues() const
	{
		StrType strtype;
		strtype +=  "'" + sqlite3pp::to_string( film_id) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( title) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( description) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( release_year) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( language_id) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( original_language_id) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( rental_duration) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( rental_rate) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( length) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( replacement_cost) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( rating) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( special_features) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( last_update) + "'";
		return strtype;
	}
	template<class T> void getStreamData( T q ) { q.getter()  >> film_id >> title >> description >> release_year >> language_id >> original_language_id >> rental_duration >> rental_rate >> length >> replacement_cost >> rating >> special_features >> last_update;}
	template <class T> void setData(const T &t) // Used to transfer data from different tables/views having same data types and column names
	{
		film_id = t.get_film_id();
		title = t.get_title();
		description = t.get_description();
		release_year = t.get_release_year();
		language_id = t.get_language_id();
		original_language_id = t.get_original_language_id();
		rental_duration = t.get_rental_duration();
		rental_rate = t.get_rental_rate();
		length = t.get_length();
		replacement_cost = t.get_replacement_cost();
		rating = t.get_rating();
		special_features = t.get_special_features();
		last_update = t.get_last_update();
	}

	// Miscellaneous functions
	static int getColumnCount() { return 13; }

	// A get_ function for each field in the table, which allows read-only access to protected member variables.
	const Int& get_film_id() const {return film_id;}
	const Varchar& get_title() const {return title;}
	const Text& get_description() const {return description;}
	const Varchar& get_release_year() const {return release_year;}
	const Smallint& get_language_id() const {return language_id;}
	const Smallint& get_original_language_id() const {return original_language_id;}
	const Smallint& get_rental_duration() const {return rental_duration;}
	const Decimal& get_rental_rate() const {return rental_rate;}
	const Smallint& get_length() const {return length;}
	const Decimal& get_replacement_cost() const {return replacement_cost;}
	const Varchar& get_rating() const {return rating;}
	const Varchar& get_special_features() const {return special_features;}
	const Bigint& get_last_update() const {return last_update;}

	// A set_ function for each field in the table.
	void set_film_id(const Int& data__) {film_id = data__;}
	void set_title(const Varchar& data__) {title = data__;}
	void set_description(const Text& data__) {description = data__;}
	void set_release_year(const Varchar& data__) {release_year = data__;}
	void set_language_id(const Smallint& data__) {language_id = data__;}
	void set_original_language_id(const Smallint& data__) {original_language_id = data__;}
	void set_rental_duration(const Smallint& data__) {rental_duration = data__;}
	void set_rental_rate(const Decimal& data__) {rental_rate = data__;}
	void set_length(const Smallint& data__) {length = data__;}
	void set_replacement_cost(const Decimal& data__) {replacement_cost = data__;}
	void set_rating(const Varchar& data__) {rating = data__;}
	void set_special_features(const Varchar& data__) {special_features = data__;}
	void set_last_update(const Bigint& data__) {last_update = data__;}

	////////////////////////////////////////////////////////////////////////////////////////////
	/* sqlite3pp::TableOStream container interface.
	Functions OStream(), operator<<(), and Delimiter() are required when using the sqlite3pp::TableOStream container.
	Example Usage:		(Using sqlite3pp::TableOStream container)
			TableOStream<sql_DB_sakila_table_film> tbl(DbFileNameArg("myDatabase.db"));
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
		t.os << film_id << t.d << t.str(title) << t.d << t.str(description) << t.d << t.str(release_year) << t.d << language_id << t.d << original_language_id << t.d << rental_duration << t.d << rental_rate << t.d << length << t.d << replacement_cost << t.d << t.str(rating) << t.d << t.str(special_features) << t.d << last_update;
		return t;
	}
	friend std::ostream& operator<<(std::ostream& os, const sql_DB_sakila_table_film& t);
	friend std::wostream& operator<<(std::wostream& os, const sql_DB_sakila_table_film& t);
	static StrType Delimiter() { return "," ; }
	////////////////////////////////////////////////////////////////////////////////////////////
};
// sqlite3pp::TableOStream container interface.
inline std::ostream& operator<<(std::ostream& os, const sql_DB_sakila_table_film& t) { sqlite3pp::ostream_a o(os, t.Delimiter()); return t.OStream(o).os; }
inline std::wostream& operator<<(std::wostream& os, const sql_DB_sakila_table_film& t) { sqlite3pp::ostream_w o(os, t.Delimiter());  return t.OStream(o).os; }

#endif // !SQL_DB_SAKILA_TABLE_FILM_HPP
