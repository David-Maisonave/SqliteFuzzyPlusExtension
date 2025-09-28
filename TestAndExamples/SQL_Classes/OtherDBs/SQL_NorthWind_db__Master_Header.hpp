#ifndef SQL_NORTHWIND_DB__MASTER_HEADER_H
#define SQL_NORTHWIND_DB__MASTER_HEADER_H
#include <string>
#include "..\..\sqlite3pp_ez\sqlite3pp_ez.h"
#include "SQL_NorthWind_db_table_Employee.hpp"
#include "SQL_NorthWind_db_table_Category.hpp"
#include "SQL_NorthWind_db_table_Customer.hpp"
#include "SQL_NorthWind_db_table_Shipper.hpp"
#include "SQL_NorthWind_db_table_Supplier.hpp"
#include "SQL_NorthWind_db_table_Order.hpp"
#include "SQL_NorthWind_db_table_Product.hpp"
#include "SQL_NorthWind_db_table_OrderDetail.hpp"
#include "SQL_NorthWind_db_table_CustomerCustomerDemo.hpp"
#include "SQL_NorthWind_db_table_CustomerDemographic.hpp"
#include "SQL_NorthWind_db_table_Region.hpp"
#include "SQL_NorthWind_db_table_Territory.hpp"
#include "SQL_NorthWind_db_table_EmployeeTerritory.hpp"
#include "SQL_NorthWind_db_view_ProductDetails_V.hpp"


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
		Tables["SQL_NorthWind_db_table_Employee"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_NorthWind_db_table_Employee>());
		Tables["SQL_NorthWind_db_table_Category"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_NorthWind_db_table_Category>());
		Tables["SQL_NorthWind_db_table_Customer"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_NorthWind_db_table_Customer>());
		Tables["SQL_NorthWind_db_table_Shipper"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_NorthWind_db_table_Shipper>());
		Tables["SQL_NorthWind_db_table_Supplier"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_NorthWind_db_table_Supplier>());
		Tables["SQL_NorthWind_db_table_Order"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_NorthWind_db_table_Order>());
		Tables["SQL_NorthWind_db_table_Product"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_NorthWind_db_table_Product>());
		Tables["SQL_NorthWind_db_table_OrderDetail"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_NorthWind_db_table_OrderDetail>());
		Tables["SQL_NorthWind_db_table_CustomerCustomerDemo"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_NorthWind_db_table_CustomerCustomerDemo>());
		Tables["SQL_NorthWind_db_table_CustomerDemographic"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_NorthWind_db_table_CustomerDemographic>());
		Tables["SQL_NorthWind_db_table_Region"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_NorthWind_db_table_Region>());
		Tables["SQL_NorthWind_db_table_Territory"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_NorthWind_db_table_Territory>());
		Tables["SQL_NorthWind_db_table_EmployeeTerritory"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_NorthWind_db_table_EmployeeTerritory>());
		Tables["SQL_NorthWind_db_view_ProductDetails_V"] = std::shared_ptr<sqlite3pp::TableBase>(new sqlite3pp::Table<SQL_NorthWind_db_view_ProductDetails_V>());
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



#endif // !SQL_NORTHWIND_DB__MASTER_HEADER_H
