#ifndef SQL_DB_NORTHWIND__MASTER_HEADER_H
#define SQL_DB_NORTHWIND__MASTER_HEADER_H
#include <string>
#include "..\sqlite3pp_ez.h"
#include "sql_DB_NorthWind_table_Employee.hpp"
#include "sql_DB_NorthWind_table_Category.hpp"
#include "sql_DB_NorthWind_table_Customer.hpp"
#include "sql_DB_NorthWind_table_Shipper.hpp"
#include "sql_DB_NorthWind_table_Supplier.hpp"
#include "sql_DB_NorthWind_table_Order.hpp"
#include "sql_DB_NorthWind_table_Product.hpp"
#include "sql_DB_NorthWind_table_OrderDetail.hpp"
#include "sql_DB_NorthWind_table_CustomerCustomerDemo.hpp"
#include "sql_DB_NorthWind_table_CustomerDemographic.hpp"
#include "sql_DB_NorthWind_table_Region.hpp"
#include "sql_DB_NorthWind_table_Territory.hpp"
#include "sql_DB_NorthWind_table_EmployeeTerritory.hpp"
#include "sql_DB_NorthWind_view_ProductDetails_V.hpp"


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
		Tables["sql_DB_NorthWind_table_Employee"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_NorthWind_table_Employee>());
		Tables["sql_DB_NorthWind_table_Category"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_NorthWind_table_Category>());
		Tables["sql_DB_NorthWind_table_Customer"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_NorthWind_table_Customer>());
		Tables["sql_DB_NorthWind_table_Shipper"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_NorthWind_table_Shipper>());
		Tables["sql_DB_NorthWind_table_Supplier"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_NorthWind_table_Supplier>());
		Tables["sql_DB_NorthWind_table_Order"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_NorthWind_table_Order>());
		Tables["sql_DB_NorthWind_table_Product"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_NorthWind_table_Product>());
		Tables["sql_DB_NorthWind_table_OrderDetail"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_NorthWind_table_OrderDetail>());
		Tables["sql_DB_NorthWind_table_CustomerCustomerDemo"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_NorthWind_table_CustomerCustomerDemo>());
		Tables["sql_DB_NorthWind_table_CustomerDemographic"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_NorthWind_table_CustomerDemographic>());
		Tables["sql_DB_NorthWind_table_Region"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_NorthWind_table_Region>());
		Tables["sql_DB_NorthWind_table_Territory"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_NorthWind_table_Territory>());
		Tables["sql_DB_NorthWind_table_EmployeeTerritory"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_NorthWind_table_EmployeeTerritory>());
		Tables["sql_DB_NorthWind_view_ProductDetails_V"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<sql_DB_NorthWind_view_ProductDetails_V>());
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



#endif // !SQL_DB_NORTHWIND__MASTER_HEADER_H
