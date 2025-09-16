#include "pch.h"

using namespace System;
#include <iostream>
#include "SQLiteDLLConnect.h"
#include "sqlite3pp_ez.h"
#include "../SQL_TestDataDb/sql_Master_Header.h"
using namespace sqlite3pp;
using namespace std;

int main()
{
    const std::string dbFileName = "..\\..\\SqliteFuzzyPlusExtension\\TestData\\TestData.db";
    sqlite3* db = NULL;
    SQLiteDLLConnect::sqlite3_open(dbFileName.c_str(), &db);
    sqlite3pp::database dataBase(db);
    dataBase.execute("SELECT SetParam('WordList', \"['westside', 'story', 'movie']\");");

    sqlite3pp::database dataBase2(dbFileName);
    sqlite3pp::query qry(dataBase2, "SELECT id, name, phone FROM contacts");
    for (int i = 0; i < qry.column_count(); ++i) {
        cout << qry.column_name(i) << "\t";
    }

    return 0;
}
