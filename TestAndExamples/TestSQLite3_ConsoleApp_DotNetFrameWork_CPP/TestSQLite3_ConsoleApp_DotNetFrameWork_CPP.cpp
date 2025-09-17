#include "pch.h"

using namespace System;
#include <iostream>
#include "../SQL_Classes/SQLiteDLLConnect.h"
#include "../SQL_Classes/sqlite3pp_ez.h"
#include "../SQL_Classes/sql_DB_TestData_Master_Header.h"
using namespace sqlite3pp;
using namespace std;

int main()
{
    const std::string dbFileName = "..\\..\\SqliteFuzzyPlusExtension\\TestData\\TestData.db";
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

    return 0;
}
