/* This file was automatically generated using [Sqlite3pp_EZ].
Sqlite3pp_EZ Copyright (C) 2025 David Maisonave (http::\www.axter.com)
Example Usage:		(Using sqlite3pp::Table container)
	// Example #1
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_NorthWind_view_ProductDetails_V> my_tbl;
		for (auto& row : my_tbl)
			std::cout << row << std::endl;

	// Example #2
		for (int i = 0; i < my_tbl.size(); ++i)
			std::cout << my_tbl[i].get_Id() << std::endl;

	// Example #3
		for (auto r = my_tbl.begin(); r != my_tbl.end(); ++r)
			std::cout << r->get_SupplierRegion() << std::endl;

	// Example #4
		sqlite3pp::setGlobalDB("myDatabase.db");
		sqlite3pp::Table<sql_DB_NorthWind_view_ProductDetails_V> my_tbl;
		// Example#4a -- (C++11) Range-based loop
		for(auto& row : my_tbl)
			std::cout << row.get_Id() << " | " << row.get_ProductName() << " | " << row.get_SupplierId() << " | " << row.get_CategoryId() << " | " << row.get_QuantityPerUnit() << " | " << row.get_UnitPrice() << " | " << row.get_UnitsInStock() << " | " << row.get_UnitsOnOrder() << " | " << row.get_ReorderLevel() << " | " << row.get_Discontinued() << " | " << row.get_CategoryName() << " | " << row.get_CategoryDescription() << " | " << row.get_SupplierName() << " | " << row.get_SupplierRegion() << " | " << std::endl;

		// Example#4b -- C++ style iteration
		for (auto row = my_tbl.begin(); row != my_tbl.end(); ++row) 
			std::cout << row->get_Id() << " | " << row->get_ProductName() << " | " << row->get_SupplierId() << " | " << row->get_CategoryId() << " | " << row->get_QuantityPerUnit() << " | " << row->get_UnitPrice() << " | " << row->get_UnitsInStock() << " | " << row->get_UnitsOnOrder() << " | " << row->get_ReorderLevel() << " | " << row->get_Discontinued() << " | " << row->get_CategoryName() << " | " << row->get_CategoryDescription() << " | " << row->get_SupplierName() << " | " << row->get_SupplierRegion() << " | " << std::endl;

		// Example#4c -- C style iteration
		for (int row = 0; row < my_tbl.size(); ++row) 
			std::cout << my_tbl[row].get_Id() << " | " << my_tbl[row].get_ProductName() << " | " << my_tbl[row].get_SupplierId() << " | " << my_tbl[row].get_CategoryId() << " | " << my_tbl[row].get_QuantityPerUnit() << " | " << my_tbl[row].get_UnitPrice() << " | " << my_tbl[row].get_UnitsInStock() << " | " << my_tbl[row].get_UnitsOnOrder() << " | " << my_tbl[row].get_ReorderLevel() << " | " << my_tbl[row].get_Discontinued() << " | " << my_tbl[row].get_CategoryName() << " | " << my_tbl[row].get_CategoryDescription() << " | " << my_tbl[row].get_SupplierName() << " | " << my_tbl[row].get_SupplierRegion() << " | " << std::endl;
For more details see  https://github.com/David-Maisonave/sqlite3pp_EZ
*/
#ifndef SQL_DB_NORTHWIND_VIEW_PRODUCTDETAILS_V_H
#define SQL_DB_NORTHWIND_VIEW_PRODUCTDETAILS_V_H
#include <string>
#include "..\sqlite3pp_ez.h"

class sql_DB_NorthWind_view_ProductDetails_V: public sqlite3pp::sql_base
{
	// A member variable for each field in the table
protected:
	Integer Id = 0;
	Varchar ProductName;
	Integer SupplierId = 0;
	Integer CategoryId = 0;
	Varchar QuantityPerUnit;
	Decimal UnitPrice = 0.0f;
	Integer UnitsInStock = 0;
	Integer UnitsOnOrder = 0;
	Integer ReorderLevel = 0;
	Integer Discontinued = 0;
	Varchar CategoryName;
	Varchar CategoryDescription;
	Varchar SupplierName;
	Varchar SupplierRegion;

public:
	using StrType = std::string;
	// Constructors
	sql_DB_NorthWind_view_ProductDetails_V() {} // Default constructor
	template <class T> sql_DB_NorthWind_view_ProductDetails_V(const T &t) { setData(t); } // Allows data input from different (or same) tables/views having the same data types and column names

	// getTableName, getColumnNames, getSelectColumnNames, and getStreamData are required for sqlite3pp::Table template class
	static StrType getTableName() { return "ProductDetails_V" ; }
	static StrType getColumnNames() { return "\"Id\", \"ProductName\", \"SupplierId\", \"CategoryId\", \"QuantityPerUnit\", \"UnitPrice\", \"UnitsInStock\", \"UnitsOnOrder\", \"ReorderLevel\", \"Discontinued\", \"CategoryName\", \"CategoryDescription\", \"SupplierName\", \"SupplierRegion\""; }
	static StrType getSelectColumnNames() { return "\"Id\", \"ProductName\", \"SupplierId\", \"CategoryId\", \"QuantityPerUnit\", \"UnitPrice\", \"UnitsInStock\", \"UnitsOnOrder\", \"ReorderLevel\", \"Discontinued\", \"CategoryName\", \"CategoryDescription\", \"SupplierName\", \"SupplierRegion\""; }
	StrType GetValues() const
	{
		StrType strtype;
		strtype +=  "'" + sqlite3pp::to_string( Id) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( ProductName) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( SupplierId) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( CategoryId) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( QuantityPerUnit) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( UnitPrice) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( UnitsInStock) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( UnitsOnOrder) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( ReorderLevel) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( Discontinued) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( CategoryName) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( CategoryDescription) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( SupplierName) + "'";
		strtype +=  ",'" + sqlite3pp::to_string( SupplierRegion) + "'";
		return strtype;
	}
	template<class T> void getStreamData( T q ) { q.getter()  >> Id >> ProductName >> SupplierId >> CategoryId >> QuantityPerUnit >> UnitPrice >> UnitsInStock >> UnitsOnOrder >> ReorderLevel >> Discontinued >> CategoryName >> CategoryDescription >> SupplierName >> SupplierRegion;}
	template <class T> void setData(const T &t) // Used to transfer data from different tables/views having same data types and column names
	{
		Id = t.get_Id();
		ProductName = t.get_ProductName();
		SupplierId = t.get_SupplierId();
		CategoryId = t.get_CategoryId();
		QuantityPerUnit = t.get_QuantityPerUnit();
		UnitPrice = t.get_UnitPrice();
		UnitsInStock = t.get_UnitsInStock();
		UnitsOnOrder = t.get_UnitsOnOrder();
		ReorderLevel = t.get_ReorderLevel();
		Discontinued = t.get_Discontinued();
		CategoryName = t.get_CategoryName();
		CategoryDescription = t.get_CategoryDescription();
		SupplierName = t.get_SupplierName();
		SupplierRegion = t.get_SupplierRegion();
	}

	// Miscellaneous functions
	static int getColumnCount() { return 14; }

	// A get_ function for each field in the table, which allows read-only access to protected member variables.
	const Integer& get_Id() const {return Id;}
	const Varchar& get_ProductName() const {return ProductName;}
	const Integer& get_SupplierId() const {return SupplierId;}
	const Integer& get_CategoryId() const {return CategoryId;}
	const Varchar& get_QuantityPerUnit() const {return QuantityPerUnit;}
	const Decimal& get_UnitPrice() const {return UnitPrice;}
	const Integer& get_UnitsInStock() const {return UnitsInStock;}
	const Integer& get_UnitsOnOrder() const {return UnitsOnOrder;}
	const Integer& get_ReorderLevel() const {return ReorderLevel;}
	const Integer& get_Discontinued() const {return Discontinued;}
	const Varchar& get_CategoryName() const {return CategoryName;}
	const Varchar& get_CategoryDescription() const {return CategoryDescription;}
	const Varchar& get_SupplierName() const {return SupplierName;}
	const Varchar& get_SupplierRegion() const {return SupplierRegion;}

	// A set_ function for each field in the table.
	void set_Id(const Integer& data__) {Id = data__;}
	void set_ProductName(const Varchar& data__) {ProductName = data__;}
	void set_SupplierId(const Integer& data__) {SupplierId = data__;}
	void set_CategoryId(const Integer& data__) {CategoryId = data__;}
	void set_QuantityPerUnit(const Varchar& data__) {QuantityPerUnit = data__;}
	void set_UnitPrice(const Decimal& data__) {UnitPrice = data__;}
	void set_UnitsInStock(const Integer& data__) {UnitsInStock = data__;}
	void set_UnitsOnOrder(const Integer& data__) {UnitsOnOrder = data__;}
	void set_ReorderLevel(const Integer& data__) {ReorderLevel = data__;}
	void set_Discontinued(const Integer& data__) {Discontinued = data__;}
	void set_CategoryName(const Varchar& data__) {CategoryName = data__;}
	void set_CategoryDescription(const Varchar& data__) {CategoryDescription = data__;}
	void set_SupplierName(const Varchar& data__) {SupplierName = data__;}
	void set_SupplierRegion(const Varchar& data__) {SupplierRegion = data__;}

	////////////////////////////////////////////////////////////////////////////////////////////
	/* sqlite3pp::TableOStream container interface.
	Functions OStream(), operator<<(), and Delimiter() are required when using the sqlite3pp::TableOStream container.
	Example Usage:		(Using sqlite3pp::TableOStream container)
			TableOStream<sql_DB_NorthWind_view_ProductDetails_V> tbl(DbFileNameArg("myDatabase.db"));
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
		t.os << Id << t.d << t.str(ProductName) << t.d << SupplierId << t.d << CategoryId << t.d << t.str(QuantityPerUnit) << t.d << UnitPrice << t.d << UnitsInStock << t.d << UnitsOnOrder << t.d << ReorderLevel << t.d << Discontinued << t.d << t.str(CategoryName) << t.d << t.str(CategoryDescription) << t.d << t.str(SupplierName) << t.d << t.str(SupplierRegion);
		return t;
	}
	friend std::ostream& operator<<(std::ostream& os, const sql_DB_NorthWind_view_ProductDetails_V& t);
	friend std::wostream& operator<<(std::wostream& os, const sql_DB_NorthWind_view_ProductDetails_V& t);
	static StrType Delimiter() { return "," ; }
	////////////////////////////////////////////////////////////////////////////////////////////
};
// sqlite3pp::TableOStream container interface.
inline std::ostream& operator<<(std::ostream& os, const sql_DB_NorthWind_view_ProductDetails_V& t) { sqlite3pp::ostream_a o(os, t.Delimiter()); return t.OStream(o).os; }
inline std::wostream& operator<<(std::wostream& os, const sql_DB_NorthWind_view_ProductDetails_V& t) { sqlite3pp::ostream_w o(os, t.Delimiter());  return t.OStream(o).os; }

#endif // !SQL_DB_NORTHWIND_VIEW_PRODUCTDETAILS_V_H
