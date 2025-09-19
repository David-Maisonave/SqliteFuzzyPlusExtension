#ifndef SQL_DB_SAKILA_MASTER_HEADER_H
#define SQL_DB_SAKILA_MASTER_HEADER_H
#include <string>
#include "..\sqlite3pp_ez.h"
#include "sql_DB_sakila_table_actor.h"
#include "sql_DB_sakila_table_country.h"
#include "sql_DB_sakila_table_city.h"
#include "sql_DB_sakila_table_address.h"
#include "sql_DB_sakila_table_language.h"
#include "sql_DB_sakila_table_category.h"
#include "sql_DB_sakila_table_customer.h"
#include "sql_DB_sakila_table_film.h"
#include "sql_DB_sakila_table_film_actor.h"
#include "sql_DB_sakila_table_film_category.h"
#include "sql_DB_sakila_table_film_text.h"
#include "sql_DB_sakila_table_inventory.h"
#include "sql_DB_sakila_table_staff.h"
#include "sql_DB_sakila_table_store.h"
#include "sql_DB_sakila_table_payment.h"
#include "sql_DB_sakila_table_rental.h"
#include "sql_DB_sakila_view_customer_list.h"
#include "sql_DB_sakila_view_film_list.h"
#include "sql_DB_sakila_view_staff_list.h"
#include "sql_DB_sakila_view_sales_by_store.h"
#include "sql_DB_sakila_view_sales_by_film_category.h"


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
		Tables["sql_DB_sakila_table_actor"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_sakila_table_actor>());
		Tables["sql_DB_sakila_table_country"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_sakila_table_country>());
		Tables["sql_DB_sakila_table_city"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_sakila_table_city>());
		Tables["sql_DB_sakila_table_address"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_sakila_table_address>());
		Tables["sql_DB_sakila_table_language"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_sakila_table_language>());
		Tables["sql_DB_sakila_table_category"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_sakila_table_category>());
		Tables["sql_DB_sakila_table_customer"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_sakila_table_customer>());
		Tables["sql_DB_sakila_table_film"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_sakila_table_film>());
		Tables["sql_DB_sakila_table_film_actor"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_sakila_table_film_actor>());
		Tables["sql_DB_sakila_table_film_category"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_sakila_table_film_category>());
		Tables["sql_DB_sakila_table_film_text"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_sakila_table_film_text>());
		Tables["sql_DB_sakila_table_inventory"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_sakila_table_inventory>());
		Tables["sql_DB_sakila_table_staff"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_sakila_table_staff>());
		Tables["sql_DB_sakila_table_store"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_sakila_table_store>());
		Tables["sql_DB_sakila_table_payment"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_sakila_table_payment>());
		Tables["sql_DB_sakila_table_rental"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_sakila_table_rental>());
		Tables["sql_DB_sakila_view_customer_list"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_sakila_view_customer_list>());
		Tables["sql_DB_sakila_view_film_list"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_sakila_view_film_list>());
		Tables["sql_DB_sakila_view_staff_list"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_sakila_view_staff_list>());
		Tables["sql_DB_sakila_view_sales_by_store"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_sakila_view_sales_by_store>());
		Tables["sql_DB_sakila_view_sales_by_film_category"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_sakila_view_sales_by_film_category>());
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



#endif // !SQL_DB_SAKILA_MASTER_HEADER_H
