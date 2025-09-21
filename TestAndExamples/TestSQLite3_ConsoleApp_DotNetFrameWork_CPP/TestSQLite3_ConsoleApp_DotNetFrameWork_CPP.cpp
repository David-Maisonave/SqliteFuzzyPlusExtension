using namespace System;
#include <iostream>
#include "../SQL_Classes/SQLiteDLLConnect.h"
#include "../SQL_Classes/sqlite3pp_ez.h"
#include "../SQL_Classes/sql_DB_TestData_Master_Header.hpp"
#include "../SQL_Classes/OtherDBs/sql_DB_chinook_Master_Header.hpp"
#include "../SQL_Classes/OtherDBs/sql_DB_GameNames_Master_Header.hpp"
#include "../SQL_Classes/OtherDBs/sql_DB_KenshoDataset_Master_Header.hpp"
#include "../SQL_Classes/OtherDBs/sql_DB_NorthWind_Master_Header.hpp"
#include "../SQL_Classes/OtherDBs/sql_DB_sakila_Master_Header.hpp"
using namespace sqlite3pp;
using namespace std;

int main(int argc, char* argv[])
{
    if (argc > 1)
        std::cout << "Number of arguments: " << argc << " ; First Arg=" << argv[0] << "\n";
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
    for (auto& row : tbl)											// (C++11) Range-based loop
        std::wcout << row.get_Function() << row.get_Description() << row.get_Arguments() << row.get_Return() << row.get_Details() << row.get_ExtensionAlias() << row.get_WikiAlias() << std::endl;

    for (auto row = tbl.begin(); row != tbl.end(); ++row)							// C++ style iteration
        std::wcout << row->get_Function() << row->get_Description() << row->get_Arguments() << row->get_Return() << row->get_Details() << row->get_ExtensionAlias() << row->get_WikiAlias() << std::endl;

    for (int row = 0; row < tbl.size(); ++row)								// C style iteration
        std::wcout << tbl[row].get_Function() << tbl[row].get_Description() << tbl[row].get_Arguments() << tbl[row].get_Return() << tbl[row].get_Details() << tbl[row].get_ExtensionAlias() << tbl[row].get_WikiAlias() << std::endl;

    sqlite3pp::Table<sql_DB_TestData_table_zTroubleFields> tbl2; // Table with problematic field and table names.
    for (auto& row : tbl2)
        std::cout << row.get_Some__Names() << " | " << row.get_Zip__Code() << " | " << row.get_City__and__State() << " | " << row.get_Area__Code() << " | " << row.get_Bad__Type() << " | " << row.get_Is__US__Born() << " | " << row.get_Is__US__Citizen__() << " | " << row.get_Unsigned__Big__Integer__Support() << " | " << row.get_Unsigned__Big__Integer__Support2() << " | " << row.get_Big__Integer__Support() << " | " << row.get_Big__Integer__Support__2() << " | " << row.get_Big__Integer__Support__3() << " | " << std::endl;

    sqlite3pp::Table<sql_DB_TestData_table_zz__Trouble__Fields> tbl3; // Table with problematic field and table names.
    for (auto& row : tbl3)
        std::cout << row.get_Some__Names() << " | " << row.get_Zip__Code() << " | " << row.get_City__and__State() << " | " << row.get_Area__Code() << " | " << row.get_Bad__Type() << " | " << row.get_Is__US__Born() << " | " << row.get_Is__US__Citizen__() << " | " << row.get_Unsigned__Big__Integer__Support() << " | " << row.get_Unsigned__Big__Integer__Support2() << " | " << row.get_Big__Integer__Support() << " | " << row.get_Big__Integer__Support__2() << " | " << row.get_Big__Integer__Support__3() << " | " << std::endl;

    dbFileName = "..\\TestDatabase\\chinook3.5Krows.db";
    if (sqlite3pp::file_exists(dbFileName))
    {
        sqlite3pp::setGlobalDB(dbFileName, true);
        sqlite3pp::Table<sql_DB_chinook_table_tracks> tbl;
        for (auto row = tbl.begin(); row != tbl.end(); ++row)
            std::cout << row->get_TrackId() << " | " << row->get_Name() << " | " << row->get_AlbumId() << " | " << row->get_MediaTypeId() << " | " << row->get_GenreId() << " | " << row->get_Composer() << " | " << row->get_Milliseconds() << " | " << row->get_Bytes() << " | " << row->get_UnitPrice() << " | " << std::endl;
  
        for (int row = 0; row < tbl.size(); ++row)
            std::cout << tbl[row].get_TrackId() << " | " << tbl[row].get_Name() << " | " << tbl[row].get_AlbumId() << " | " << tbl[row].get_MediaTypeId() << " | " << tbl[row].get_GenreId() << " | " << tbl[row].get_Composer() << " | " << tbl[row].get_Milliseconds() << " | " << tbl[row].get_Bytes() << " | " << tbl[row].get_UnitPrice() << " | " << std::endl;

        for (auto& row : tbl)
            std::cout << row.get_TrackId() << " | " << row.get_Name() << " | " << row.get_AlbumId() << " | " << row.get_MediaTypeId() << " | " << row.get_GenreId() << " | " << row.get_Composer() << " | " << row.get_Milliseconds() << " | " << row.get_Bytes() << " | " << row.get_UnitPrice() << " | " << std::endl;
    }

    dbFileName = "..\\TestDatabase\\NorthWind_small.db";
    if (sqlite3pp::file_exists(dbFileName))
    {
        sqlite3pp::setGlobalDB(dbFileName, true);
        sqlite3pp::Table<sql_DB_NorthWind_table_Customer> tbl;
        for (auto& row : tbl)  // Note: Varchar type needs cout instead of wcout
            std::cout << row.get_Id() << " | " << row.get_CompanyName() << " | " << row.get_ContactName() << " | " << row.get_ContactTitle() << " | " << row.get_Address() << " | " << row.get_City() << " | " << row.get_Region() << " | " << row.get_PostalCode() << " | " << row.get_Country() << " | " << row.get_Phone() << " | " << row.get_Fax() << " | " << std::endl;
    }

    dbFileName = "..\\TestDatabase\\kensho_dataset(1millionRows).db";
    if (sqlite3pp::file_exists(dbFileName))
    {
        sqlite3pp::setGlobalDB(dbFileName, true);
        sqlite3pp::Table<sql_DB_KenshoDataset_table_Items> tbl;
        for (auto& row : tbl)
            std::wcout << row.get_Labels() << L" | " << row.get_Description() << L" | " << row.get_HashDescription() << L" | " << std::endl;
    }

    dbFileName = "..\\TestDatabase\\GameNames53KRows.db";
    if (sqlite3pp::file_exists(dbFileName))
    {
        sqlite3pp::setGlobalDB(dbFileName, true);
        sqlite3pp::Table<sql_DB_GameNames_table_AlternateNames> tbl;
        for (auto& row : tbl)
            std::wcout << row.get_Name() << L" | " << row.get_Alternate() << L" | " << row.get_Title() << L" | " << row.get_HashName() << L" | " << row.get_HashAlternate() << L" | " << row.get_HashTitle() << L" | " << std::endl;
    }

    dbFileName = "..\\TestDatabase\\sakila.db";
    if (sqlite3pp::file_exists(dbFileName))
    {
        sqlite3pp::setGlobalDB(dbFileName, true);
        sqlite3pp::Table<sql_DB_sakila_table_actor> tbl;
        for (auto& row : tbl)
            std::cout << row.get_actor_id() << " | " << row.get_first_name() << " | " << row.get_last_name() << " | " << row.get_last_update() << " | " << std::endl;

        sqlite3pp::Table<sql_DB_sakila_table_film> tbl2;
        for (auto& row : tbl2)
            std::cout << row.get_film_id() << " | " << row.get_title() << " | " << row.get_description() << " | " << row.get_release_year() << " | " << row.get_language_id() << " | " << row.get_original_language_id() << " | " << row.get_rental_duration() << " | " << row.get_rental_rate() << " | " << row.get_length() << " | " << row.get_replacement_cost() << " | " << row.get_rating() << " | " << row.get_special_features() << " | " << row.get_last_update() << " | " << std::endl;

        sqlite3pp::Table<sql_DB_sakila_table_customer> tbl3;
        for (auto& row : tbl3)
            std::cout << row.get_customer_id() << " | " << row.get_store_id() << " | " << row.get_first_name() << " | " << row.get_last_name() << " | " << row.get_email() << " | " << row.get_address_id() << " | " << row.get_active() << " | " << row.get_create_date() << " | " << row.get_last_update() << " | " << std::endl;

        sqlite3pp::Table<sql_DB_sakila_table_language> tbl4;
        for (auto& row : tbl4)
            std::cout << row.get_language_id() << " | " << row.get_name() << " | " << row.get_last_update() << " | " << std::endl;

        sqlite3pp::Table<sql_DB_sakila_table_payment> tbl5;
        for (auto& row : tbl5)
            std::cout << row.get_payment_id() << " | " << row.get_customer_id() << " | " << row.get_staff_id() << " | " << row.get_rental_id() << " | " << row.get_amount() << " | " << row.get_payment_date() << " | " << row.get_last_update() << " | " << std::endl;

        sqlite3pp::Table<sql_DB_sakila_view_staff_list> tbl6;
        for (auto& row : tbl6)
            std::cout << row.get_ID() << " | " << row.get_name() << " | " << row.get_address() << " | " << row.get_zip_code() << " | " << row.get_phone() << " | " << row.get_city() << " | " << row.get_country() << " | " << row.get_SID() << " | " << std::endl;

        sqlite3pp::Table<sql_DB_sakila_table_address> tbl7;
        for (auto& row : tbl7)
            std::cout << row.get_address_id() << " | " << row.get_address() << " | " << row.get_address2() << " | " << row.get_district() << " | " << row.get_city_id() << " | " << row.get_postal_code() << " | " << row.get_phone() << " | " << row.get_last_update() << " | " << std::endl;
    }

    return 0;
}
