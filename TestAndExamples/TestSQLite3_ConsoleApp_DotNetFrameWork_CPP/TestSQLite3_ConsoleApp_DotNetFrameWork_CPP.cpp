#include "pch.h"

using namespace System;
#include <iostream>
#include "../SQL_Classes/SQLiteDLLConnect.h"
#include "../SQL_Classes/sqlite3pp_ez.h"
#include "../SQL_Classes/sql_DB_TestData_Master_Header.h"
#include "../SQL_Classes/OtherDBs/sql_DB_chinook_Master_Header.h"
#include "../SQL_Classes/OtherDBs/sql_DB_GameNames_Master_Header.h"
#include "../SQL_Classes/OtherDBs/sql_DB_KenshoDataset_Master_Header.h"
#include "../SQL_Classes/OtherDBs/sql_DB_NorthWind_Master_Header.h"
using namespace sqlite3pp;
using namespace std;

int main()
{
    std::string dbFileName = "..\\..\\SqliteFuzzyPlusExtension\\TestData\\TestData.db";
    sqlite3* db = NULL;

    // Test SQLiteDLLConnect API's
    SQLiteDLLConnect::sqlite3_open(dbFileName.c_str(), &db);

    // Test sqlite3pp API's
    sqlite3pp::database dataBase(db);
    dataBase.execute("SELECT SetParam('WordList', \"['westside', 'story', 'movie']\");");

    sqlite3pp::database dataBase2(dbFileName);
    sqlite3pp::query qry(dataBase2, "SELECT Function, Description, Arguments, Return, Details, ExtensionAlias, WikiAlias FROM Help");
    cout << "Header:\t";
    for (int i = 0; i < qry.column_count(); ++i) {
        cout << qry.column_name(i) << "\t";
    }
    for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {
        for (int j = 0; j < qry.column_count(); ++j) {
            cout << (*i).get<char const*>(j) << "\t";
        }
        cout << endl;
    }

    // Test sqlite3pp_ez API's
    sqlite3pp::setGlobalDB(dbFileName);
    sqlite3pp::Table<sql_DB_TestData_table_Help> tbl;
    for (auto row : tbl)											// (C++11) Range-based loop
        std::wcout << row.get_Function() << row.get_Description() << row.get_Arguments() << row.get_Return() << row.get_Details() << row.get_ExtensionAlias() << row.get_WikiAlias() << std::endl;

    for (auto row = tbl.begin(); row != tbl.end(); ++row)							// C++ style iteration
        std::wcout << row->get_Function() << row->get_Description() << row->get_Arguments() << row->get_Return() << row->get_Details() << row->get_ExtensionAlias() << row->get_WikiAlias() << std::endl;

    for (int row = 0; row < tbl.size(); ++row)								// C style iteration
        std::wcout << tbl[row].get_Function() << tbl[row].get_Description() << tbl[row].get_Arguments() << tbl[row].get_Return() << tbl[row].get_Details() << tbl[row].get_ExtensionAlias() << tbl[row].get_WikiAlias() << std::endl;

    dbFileName = "..\\TestDatabase\\chinook3.5Krows.db";
    if (sqlite3pp::file_exists(dbFileName))
    {
        sqlite3pp::setGlobalDB(dbFileName, true);
        sqlite3pp::Table<sql_DB_chinook_table_tracks> tbl;
        for (auto row : tbl)
            std::wcout << row.get_TrackId() << row.get_Name() << row.get_AlbumId() << row.get_MediaTypeId() << row.get_GenreId() << row.get_Composer() << row.get_Milliseconds() << row.get_Bytes() << row.get_UnitPrice() << std::endl;
    }

    dbFileName = "..\\TestDatabase\\NorthWind_small.db";
    if (sqlite3pp::file_exists(dbFileName))
    {
        sqlite3pp::setGlobalDB(dbFileName, true);
        sqlite3pp::Table<sql_DB_NorthWind_table_Customer> tbl;
        for (auto row : tbl)  // Note: Varchar type needs cout instead of wcout
            std::cout << row.get_Id() << row.get_CompanyName() << row.get_ContactName() << row.get_ContactTitle() << row.get_Address() << row.get_City() << row.get_Region() << row.get_PostalCode() << row.get_Country() << row.get_Phone() << row.get_Fax() << std::endl;
    }

    return 0;
}
