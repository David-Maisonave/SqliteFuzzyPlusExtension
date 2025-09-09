#include "pch.h"

using namespace System;
#include "SQLiteDLLConnect.h"
#include "sqlite3pp_ez.h"
using namespace sqlite3pp;

int main(array<System::String ^> ^args)
{
    sqlite3* db = NULL;
    SQLiteDLLConnect::sqlite3_open("..\\..\\SqliteFuzzyPlusExtension\\TestData\\TestData.db", &db);
    database dataBase();
    // dataBase.execute("SELECT SetParam('WordList', \"['westside', 'story', 'movie']\");");
    
    return 0;
}
