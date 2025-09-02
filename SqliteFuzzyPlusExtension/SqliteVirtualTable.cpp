#include <windows.h>
#include <cassert>
#include <string>
#include <vector>
#include <ctype.h>
#include <atlstr.h>
#include "SqliteFuzzyPlusExtension_Internal.h"
#define SQLITEFUZZYPLUSEXTENSION_EXCLUDE_FUNC
#include "SqliteFuzzyPlusExtension.h"
using namespace System;
#include "SqliteVirtualTable.h"

enum IndexType {
    // The default index type is just scanning the entire file
    CURSOR_SCAN,
    CURSOR_ROWID_EQ,
    CURSOR_ROWID_GT,
    CURSOR_ROWID_LE,
    CURSOR_ROWID_LT,
    CURSOR_ROWID_GE
};

struct VirtualCursor : sqlite3_vtab_cursor {
    int line;
    int mode;
    // Represents all lines that match query
    std::vector<int> matches;
    void seek(int) {
        this->line = line;
    }
};

struct VirtualTable : sqlite3_vtab {
    std::string setup(sqlite3* db)
    {
        return "";
    }
    int length = 0;
    int pos = 0;
    std::string getLine(int num)
    {
        return "";
    }
};

static int iVersion = 0;
static int xCreate(sqlite3* db, void* pAux, int argc, const char* const* argv, sqlite3_vtab** vtab, char** pzErr)
{
    std::string database_filename = sqlite3_db_filename(db, NULL);
    String^ dbFilename = gcnew String(database_filename.c_str());
    System::IntPtr intPtr = (System::IntPtr)db;
    FuzzyPlusCSharp::Fuzzy::CreateSQLiteVirtualConnection(intPtr, dbFilename);
    String^ sql = gcnew String(argv[0]);
    String^ arg = gcnew String("");
    System::Data::DataTable^ d = FuzzyPlusCSharp::Fuzzy::ExecuteQuery(intPtr, sql, arg);
    return SQLITE_OK;
}

static int xBestIndex(sqlite3_vtab* vtab, sqlite3_index_info* info)
{
    return SQLITE_OK;
}

static int xDisconnect(sqlite3_vtab* vtab) {
    return SQLITE_OK;
}

static int xOpen(sqlite3_vtab* vtab, sqlite3_vtab_cursor** cursor) {
    *cursor = new VirtualCursor;
    return SQLITE_OK;
}

static int xClose(sqlite3_vtab_cursor* cursor) {
    delete(cursor);
    return SQLITE_OK;
}

static int xDestroy(sqlite3_vtab* vtab) {
    delete((VirtualTable*)vtab);
    return SQLITE_OK;
}

static int xEof(sqlite3_vtab_cursor* cursor) {
    VirtualCursor* c = (VirtualCursor*)cursor;
    VirtualTable* vtab = (VirtualTable*)c->pVtab;
    if (c->line <= vtab->length) {
        return 0;
    }
    else {
        return 1;
    }
}

static int xFilter(sqlite3_vtab_cursor* c, int idxNum, const char* idxStr, int argc, sqlite3_value** argv) {
    VirtualCursor* cursor = (VirtualCursor*)c;
    cursor->mode = idxNum;

    if (idxNum == CURSOR_SCAN) {
        printf("Scanning table...\n");
        cursor->seek(0);
    }

    return SQLITE_OK;
}

static int xNext(sqlite3_vtab_cursor* c) {
    VirtualCursor* cursor = (VirtualCursor*)c;
    if (cursor->mode == CURSOR_SCAN) {
        cursor->seek(cursor->line + 1);
    }
    return SQLITE_OK;
}

static int xColumn(sqlite3_vtab_cursor* cursor, sqlite3_context* ctx, int N)
{
    return SQLITE_OK;
}

sqlite3_module* createVirtualTableModule() 
{
    sqlite3_module* mod = new(sqlite3_module);
    mod->iVersion = iVersion;
    mod->xCreate = &xCreate;
    mod->xBestIndex = &xBestIndex;
    mod->xDisconnect = &xDisconnect;
    mod->xOpen = &xOpen;
    mod->xClose = &xClose;
    mod->xDestroy = &xDestroy;
    mod->xEof = &xEof;
    mod->xFilter = &xFilter;
    mod->xNext = &xNext;
    mod->xColumn = &xColumn;
    return mod;
}

static void VirtualTableQuery(sqlite3_context* context, int argc, sqlite3_value** argv) {
    assert(argc == 1);
    sqlite3_result_text(context, "1.0", -1, SQLITE_STATIC);
}

static void VirtualTableVersion(sqlite3_context* context, int argc, sqlite3_value** argv) {
    sqlite3_result_text(context, "1.0", -1, SQLITE_STATIC);
}

static sqlite3_module funcVirtualTable = {
    /* iVersion    */ iVersion,
    /* xCreate     */ xCreate,
    /* xConnect    */ 0,
    /* xBestIndex  */ xBestIndex,
    /* xDisconnect */ xDisconnect,
    /* xDestroy    */ xDestroy,
    /* xOpen       */ xOpen,
    /* xClose      */ xClose,
    /* xFilter     */ xFilter,
    /* xNext       */ xNext,
    /* xEof        */ xEof,
    /* xColumn     */ xColumn,
    /* xRowid      */ 0,
    /* xUpdate     */ 0,
    /* xBegin      */ 0,
    /* xSync       */ 0,
    /* xCommit     */ 0,
    /* xRollback   */ 0,
    /* xFindMethod */ 0,
    /* xRename     */ 0,
    /* xSavepoint  */ 0,
    /* xRelease    */ 0,
    /* xRollbackTo */ 0,
    /* xShadowName */ 0
};

int InitiateVirtualTableModule(sqlite3* db, char** pzErrMsg)
{
    static const struct {
        char* zFName;
        int nArg;
        void* pAux;
        void (*xFunc)(sqlite3_context*, int, sqlite3_value**);
        int flags;
    } aFunc[] = {
        //{ (char*) "Sql-Name",            qty-arg,  p,    functionName,          SQLITE_UTF8 },
        { (char*)"VirtualTableVer",     0,  NULL, VirtualTableVersion,   SQLITE_UTF8 | SQLITE_DETERMINISTIC | SQLITE_INNOCUOUS },
        { (char*)"VirtualTableQuery",     1,  NULL, VirtualTableQuery,   SQLITE_UTF8 | SQLITE_DETERMINISTIC | SQLITE_INNOCUOUS },
    };
    for (int i = 0; i < sizeof(aFunc) / sizeof(aFunc[0]); i++) 
    {
        int rc = sqlite3_create_function_v2(
            db,
            aFunc[i].zFName, aFunc[i].nArg,
            aFunc[i].flags,
            aFunc[i].pAux,
            aFunc[i].xFunc, 0, 0, 0);
        if (rc != SQLITE_OK) {
            *pzErrMsg = sqlite3_mprintf("%s: %s", aFunc[i].zFName, sqlite3_errmsg(db));
            return rc;
        }
    }
    int rc = sqlite3_create_module(db, "VirtualQuery", &funcVirtualTable, 0);
    if (rc != SQLITE_OK) 
        return rc;
    return SQLITE_OK;
}
