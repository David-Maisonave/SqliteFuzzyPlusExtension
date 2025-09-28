#ifndef SQL_SAKILA_DB__MASTER_HEADER_H
#define SQL_SAKILA_DB__MASTER_HEADER_H
#include <string>
#include "..\..\sqlite3pp_ez\sqlite3pp_ez.h"
#include "SQL_sakila_db_table_actor.hpp"
#include "SQL_sakila_db_table_country.hpp"
#include "SQL_sakila_db_table_city.hpp"
#include "SQL_sakila_db_table_address.hpp"
#include "SQL_sakila_db_table_language.hpp"
#include "SQL_sakila_db_table_category.hpp"
#include "SQL_sakila_db_table_customer.hpp"
#include "SQL_sakila_db_table_film.hpp"
#include "SQL_sakila_db_table_film_actor.hpp"
#include "SQL_sakila_db_table_film_category.hpp"
#include "SQL_sakila_db_table_film_text.hpp"
#include "SQL_sakila_db_table_inventory.hpp"
#include "SQL_sakila_db_table_staff.hpp"
#include "SQL_sakila_db_table_store.hpp"
#include "SQL_sakila_db_table_payment.hpp"
#include "SQL_sakila_db_table_rental.hpp"
#include "SQL_sakila_db_view_customer_list.hpp"
#include "SQL_sakila_db_view_film_list.hpp"
#include "SQL_sakila_db_view_staff_list.hpp"
#include "SQL_sakila_db_view_sales_by_store.hpp"
#include "SQL_sakila_db_view_sales_by_film_category.hpp"


/*
// This example code can be used to test and validate all tables.
// Example Usage:
// 		sqlite3pp::setGlobalDB("myDatabase.db")
// 		sqlite3pp::testAllTables();
// Warning: testPopulatingAllTables and testAllTables may take a very long time on a database with a lot of content.
#include <map>
#include <memory>
namespace sqlite3pp
{
	// Function to test populating all tables & views.
	std::map< std::string, std::shared_ptr<sqlite3pp::TableBase> > testPopulatingAllTables()
	{
		std::map< std::string, std::shared_ptr < sqlite3pp::TableBase>> Tables;
		Tables["SQL_sakila_db_table_actor"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_sakila_db_table_actor>());
		Tables["SQL_sakila_db_table_country"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_sakila_db_table_country>());
		Tables["SQL_sakila_db_table_city"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_sakila_db_table_city>());
		Tables["SQL_sakila_db_table_address"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_sakila_db_table_address>());
		Tables["SQL_sakila_db_table_language"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_sakila_db_table_language>());
		Tables["SQL_sakila_db_table_category"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_sakila_db_table_category>());
		Tables["SQL_sakila_db_table_customer"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_sakila_db_table_customer>());
		Tables["SQL_sakila_db_table_film"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_sakila_db_table_film>());
		Tables["SQL_sakila_db_table_film_actor"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_sakila_db_table_film_actor>());
		Tables["SQL_sakila_db_table_film_category"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_sakila_db_table_film_category>());
		Tables["SQL_sakila_db_table_film_text"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_sakila_db_table_film_text>());
		Tables["SQL_sakila_db_table_inventory"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_sakila_db_table_inventory>());
		Tables["SQL_sakila_db_table_staff"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_sakila_db_table_staff>());
		Tables["SQL_sakila_db_table_store"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_sakila_db_table_store>());
		Tables["SQL_sakila_db_table_payment"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_sakila_db_table_payment>());
		Tables["SQL_sakila_db_table_rental"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_sakila_db_table_rental>());
		Tables["SQL_sakila_db_view_customer_list"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_sakila_db_view_customer_list>());
		Tables["SQL_sakila_db_view_film_list"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_sakila_db_view_film_list>());
		Tables["SQL_sakila_db_view_staff_list"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_sakila_db_view_staff_list>());
		Tables["SQL_sakila_db_view_sales_by_store"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_sakila_db_view_sales_by_store>());
		Tables["SQL_sakila_db_view_sales_by_film_category"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_sakila_db_view_sales_by_film_category>());
		return Tables;
	}

	// Function to test displaying content of all tables & views.
	void testAllTables()
	{
		std::map< std::string, std::shared_ptr < sqlite3pp::TableBase>> myTables = sqlite3pp::testPopulatingAllTables();
		for (auto& t : myTables)
			t.second->out(std::wcout);
	}
}
*/



#endif // !SQL_SAKILA_DB__MASTER_HEADER_H
