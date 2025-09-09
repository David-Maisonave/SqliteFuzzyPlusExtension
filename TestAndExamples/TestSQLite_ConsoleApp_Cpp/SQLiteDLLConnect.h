// Define all the SQLite dll functions
#ifndef __SQLITEDLLCONNECT_H
#define __SQLITEDLLCONNECT_H

#include "sqlite3.h"

#define DllImport __declspec(dllimport)

namespace SQLiteDLLConnect
{	// Sqlite3.dll imports -- See https://www.sqlite.org/c3ref/funclist.html
	using sqlite3_filename = char*;
	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_open")] // 
		static int SQLite3_open(
			const char* filename,   /* Database filename (UTF-8) */
			sqlite3** ppDb          /* OUT: SQLite db handle */
		);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_open16")] // 
		static int SQLite3_open16(
			const void* filename,   /* Database filename (UTF-16) */
			sqlite3** ppDb          /* OUT: SQLite db handle */
		);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_open_v2")] // 
		static int SQLite3_open_v2(
			const char* filename,   /* Database filename (UTF-8) */
			sqlite3** ppDb,         /* OUT: SQLite db handle */
			int flags,              /* Flags */
			const char* zVfs		/* Name of VFS module to use */
		);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_enable_load_extension")] // 
		static int SQLite3_enable_load_extension(sqlite3* db, int onoff);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_close")] // 
		static int SQLite3_close(sqlite3* db);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_close_v2")] // 
		static int SQLite3_close_v2(sqlite3* db);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_config")] // 
		static int SQLite3_config(int, ...); // https://www.sqlite.org/c3ref/config.html

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_win32_set_directory")] // 
		static int SQLite3_win32_set_directory(
			unsigned long type, /* Identifier for directory being set or reset */
			void* zValue        /* New value for directory being set or reset */
		);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_win32_set_directory8")] // 
		static int SQLite3_win32_set_directory8(unsigned long type, const char* zValue);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_win32_set_directory16")] // 
		static int SQLite3_win32_set_directory16(unsigned long type, const void* zValue);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_busy_timeout")] // 
		static int SQLite3_busy_timeout(sqlite3*, int ms);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_changes")] // 
		static int SQLite3_changes(sqlite3*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_changes64")] // 
		static sqlite3_int64 SQLite3_changes64(sqlite3*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_prepare")] // 
		static int SQLite3_prepare(
			sqlite3* db,            /* Database handle */
			const char* zSql,       /* SQL statement, UTF-8 encoded */
			int nByte,              /* Maximum length of zSql in bytes. */
			sqlite3_stmt** ppStmt,  /* OUT: Statement handle */
			const char** pzTail     /* OUT: Pointer to unused portion of zSql */
		);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_prepare_v2")] // 
		static int SQLite3_prepare_v2(
			sqlite3* db,            /* Database handle */
			const char* zSql,       /* SQL statement, UTF-8 encoded */
			int nByte,              /* Maximum length of zSql in bytes. */
			sqlite3_stmt** ppStmt,  /* OUT: Statement handle */
			const char** pzTail     /* OUT: Pointer to unused portion of zSql */
		);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_prepare_v3")] // 
		static int SQLite3_prepare_v3(
			sqlite3* db,            /* Database handle */
			const char* zSql,       /* SQL statement, UTF-8 encoded */
			int nByte,              /* Maximum length of zSql in bytes. */
			unsigned int prepFlags, /* Zero or more SQLITE_PREPARE_ flags */
			sqlite3_stmt** ppStmt,  /* OUT: Statement handle */
			const char** pzTail     /* OUT: Pointer to unused portion of zSql */
		);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_prepare16")] // 
		static int SQLite3_prepare16(
			sqlite3* db,            /* Database handle */
			const void* zSql,       /* SQL statement, UTF-16 encoded */
			int nByte,              /* Maximum length of zSql in bytes. */
			sqlite3_stmt** ppStmt,  /* OUT: Statement handle */
			const void** pzTail     /* OUT: Pointer to unused portion of zSql */
		);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_prepare16_v2")] // 
		static int SQLite3_prepare16_v2(
			sqlite3* db,            /* Database handle */
			const void* zSql,       /* SQL statement, UTF-16 encoded */
			int nByte,              /* Maximum length of zSql in bytes. */
			sqlite3_stmt** ppStmt,  /* OUT: Statement handle */
			const void** pzTail     /* OUT: Pointer to unused portion of zSql */
		);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_prepare16_v3")] // 
		static int SQLite3_prepare16_v3(
			sqlite3* db,            /* Database handle */
			const void* zSql,       /* SQL statement, UTF-16 encoded */
			int nByte,              /* Maximum length of zSql in bytes. */
			unsigned int prepFlags, /* Zero or more SQLITE_PREPARE_ flags */
			sqlite3_stmt** ppStmt,  /* OUT: Statement handle */
			const void** pzTail     /* OUT: Pointer to unused portion of zSql */
		);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_step")] // 
		static int SQLite3_step(sqlite3_stmt*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_reset")] // 
		static int SQLite3_reset(sqlite3_stmt* pStmt);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_finalize")] // Destroy A Prepared Statement Object
		static int SQLite3_finalize(sqlite3_stmt* pStmt);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_last_insert_rowid")] // 
		static sqlite3_int64 SQLite3_last_insert_rowid(sqlite3*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_errmsg16")] // 
		static const void* SQLite3_errmsg16(sqlite3*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_errcode")] // 
		static int SQLite3_errcode(sqlite3* db);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_extended_errcode")] // 
		static int SQLite3_extended_errcode(sqlite3* db);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_errmsg")] // 
		static const char* SQLite3_errmsg(sqlite3*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_errstr")] // 
		static const char* SQLite3_errstr(int);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_error_offset")] // 
		static int SQLite3_error_offset(sqlite3* db);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_bind_parameter_index")] // 
		static int SQLite3_bind_parameter_index(sqlite3_stmt*, const char* zName);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_bind_null")] // 
		static int SQLite3_bind_null(sqlite3_stmt*, int);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_bind_int")] // 
		static int SQLite3_bind_int(sqlite3_stmt*, int, int);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_bind_int64")] // 
		static int SQLite3_bind_int64(sqlite3_stmt*, int, sqlite3_int64);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_bind_double")] // 
		static int SQLite3_bind_double(sqlite3_stmt*, int, double);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_bind_text")] // 
		static int SQLite3_bind_text(sqlite3_stmt*, int, const char*, int, void(*)(void*));

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_bind_text16")] // 
		static int SQLite3_bind_text16(sqlite3_stmt*, int, const void*, int, void(*)(void*));

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_bind_text64")] // 
		static int SQLite3_bind_text64(sqlite3_stmt*, int, const char*, sqlite3_uint64,
			void(*)(void*), unsigned char encoding);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_bind_blob")] // 
		static int SQLite3_bind_blob(sqlite3_stmt*, int, const void*, int n, void(*)(void*));

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_bind_blob64")] // 
		static int SQLite3_bind_blob64(sqlite3_stmt*, int, const void*, sqlite3_uint64,
			void(*)(void*));

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_bind_value")] // 
		static int SQLite3_bind_value(sqlite3_stmt*, int, const sqlite3_value*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_bind_pointer")] // 
		static int SQLite3_bind_pointer(sqlite3_stmt*, int, void*, const char*, void(*)(void*));


	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_bind_zeroblob")] // 
		static int SQLite3_bind_zeroblob(sqlite3_stmt*, int, int n);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_bind_zeroblob64")] // 
		static int SQLite3_bind_zeroblob64(sqlite3_stmt*, int, sqlite3_uint64);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_bind_parameter_count")] // 
		static int SQLite3_bind_parameter_count(sqlite3_stmt*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_bind_parameter_name")] // 
		static const char* SQLite3_bind_parameter_name(sqlite3_stmt*, int);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_column_count")] // 
		static int SQLite3_column_count(sqlite3_stmt* pStmt);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_column_name")] // 
		static const char* SQLite3_column_name(sqlite3_stmt*, int N);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_column_name16")] // 
		static const void* SQLite3_column_name16(sqlite3_stmt*, int N);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_column_type")] // 
		static int SQLite3_column_type(sqlite3_stmt*, int iCol);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_column_int")] // 
		static int SQLite3_column_int(sqlite3_stmt*, int iCol);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_column_int64")] // 
		static sqlite3_int64 SQLite3_column_int64(sqlite3_stmt*, int iCol);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_column_double")] // 
		static double SQLite3_column_double(sqlite3_stmt*, int iCol);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_column_text")] // 
		static const unsigned char* SQLite3_column_text(sqlite3_stmt*, int iCol);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_column_text16")] // 
		static const void* SQLite3_column_text16(sqlite3_stmt*, int iCol);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_column_blob")] // 
		static const void* SQLite3_column_blob(sqlite3_stmt*, int iCol);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_column_bytes")] // 
		static int SQLite3_column_bytes(sqlite3_stmt*, int iCol);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_column_bytes16")] // 
		static int SQLite3_column_bytes16(sqlite3_stmt*, int iCol);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_column_value")] // 
		static sqlite3_value* SQLite3_column_value(sqlite3_stmt*, int iCol);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_column_database_name")] // 
		static const char* SQLite3_column_database_name(sqlite3_stmt*, int);;

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_column_database_name16")] // 
		static const void* SQLite3_column_database_name16(sqlite3_stmt*, int);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_column_table_name")] // 
		static const char* SQLite3_column_table_name(sqlite3_stmt*, int);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_column_table_name16")] // 
		static const void* SQLite3_column_table_name16(sqlite3_stmt*, int);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_column_origin_name")] // 
		static const char* SQLite3_column_origin_name(sqlite3_stmt*, int);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_column_origin_name16")] // 
		static const void* SQLite3_column_origin_name16(sqlite3_stmt*, int);

	[DllImport("sqlite3.dll", EntryPoint="sqlite3_exec")] // 
	static int SQLite3_exec(
		sqlite3*,                                  /* An open database */
		const char* sql,                           /* SQL to be evaluated */
		int (*callback)(void*, int, char**, char**),  /* Callback function */
		void*,                                    /* 1st argument to callback */
		char** errmsg                              /* Error msg written here */
	);

	[DllImport("sqlite3.dll", EntryPoint="sqlite3_get_table")] // 
	static int SQLite3_get_table(
		sqlite3* db,          /* An open database */
		const char* zSql,     /* SQL to be evaluated */
		char*** pazResult,    /* Results of the query */
		int* pnRow,           /* Number of result rows written here */
		int* pnColumn,        /* Number of result columns written here */
		char** pzErrmsg       /* Error msg written here */
	);

	[DllImport("sqlite3.dll", EntryPoint="sqlite3_free_table")] // 
		static void SQLite3_free_table(char** result);

	[DllImport("sqlite3.dll", EntryPoint="sqlite3_malloc")] // 
		static void* SQLite3_malloc(int);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_malloc64")] // 
		static void* SQLite3_malloc64(sqlite3_uint64);

	[DllImport("sqlite3.dll", EntryPoint="sqlite3_realloc")] // 
		static void* SQLite3_realloc(void*, int);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_realloc64")] // 
		static void* SQLite3_realloc64(void*, sqlite3_uint64);

	[DllImport("sqlite3.dll", EntryPoint="sqlite3_free")] // 
		static void SQLite3_free(void*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_msize")] // 
		static sqlite3_uint64 SQLite3_msize(void*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_blob_bytes")] // 
		static int SQLite3_blob_bytes(sqlite3_blob*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_commit_hook")] // 
		static void* SQLite3_commit_hook(sqlite3*, int(*)(void*), void*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_rollback_hook")] // 
		static void* SQLite3_rollback_hook(sqlite3*, void(*)(void*), void*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_value_blob")] // 
		static const void* SQLite3_value_blob(sqlite3_value*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_value_double")] // 
		static double SQLite3_value_double(sqlite3_value*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_value_int")] // 
		static int SQLite3_value_int(sqlite3_value*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_value_int64")] // 
		static sqlite3_int64 SQLite3_value_int64(sqlite3_value*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_value_pointer")] // 
		static void* SQLite3_value_pointer(sqlite3_value*, const char*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_value_text")] // 
		static const unsigned char* SQLite3_value_text(sqlite3_value*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_value_text16")] // 
		static const void* SQLite3_value_text16(sqlite3_value*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_value_text16le")] // 
		static const void* SQLite3_value_text16le(sqlite3_value*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_value_text16be")] // 
		static const void* SQLite3_value_text16be(sqlite3_value*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_value_bytes")] // 
		static int SQLite3_value_bytes(sqlite3_value*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_value_bytes16")] // 
		static int SQLite3_value_bytes16(sqlite3_value*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_value_type")] // 
		static int SQLite3_value_type(sqlite3_value*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_value_numeric_type")] // 
		static int SQLite3_value_numeric_type(sqlite3_value*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_value_nochange")] // 
		static int SQLite3_value_nochange(sqlite3_value*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_value_frombind")] // 
		static int SQLite3_value_frombind(sqlite3_value*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_blob_close")] // 
		static int SQLite3_blob_close(sqlite3_blob*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_blob_open")] // 
		static int SQLite3_blob_open(
			sqlite3*,
			const char* zDb,
			const char* zTable,
			const char* zColumn,
			sqlite3_int64 iRow,
			int flags,
			sqlite3_blob** ppBlob
		);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_blob_read")] // 
		static int SQLite3_blob_read(sqlite3_blob*, void* Z, int N, int iOffset);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_blob_reopen")] // 
		static int SQLite3_blob_reopen(sqlite3_blob*, sqlite3_int64);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_blob_write")] // 
		static int SQLite3_blob_write(sqlite3_blob*, const void* z, int n, int iOffset);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_busy_handler")] // 
		static int SQLite3_busy_handler(sqlite3*, int(*)(void*, int), void*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_column_decltype")] // 
		static const char* SQLite3_column_decltype(sqlite3_stmt*, int);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_column_decltype16")] // 
		static const void* SQLite3_column_decltype16(sqlite3_stmt*, int);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_db_filename")] // 
		static sqlite3_filename SQLite3_db_filename(sqlite3* db, const char* zDbName);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_db_name")] // 
		static const char* SQLite3_db_name(sqlite3* db, int N);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_db_config")] // 
		static int SQLite3_db_config(sqlite3*, int op, ...);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_db_handle")] // 
		static sqlite3* SQLite3_db_handle(sqlite3_stmt*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_db_mutex")] // 
		static sqlite3_mutex* SQLite3_db_mutex(sqlite3*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_db_readonly")] // 
		static int SQLite3_db_readonly(sqlite3* db, const char* zDbName);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_db_release_memory")] // 
		static int SQLite3_db_release_memory(sqlite3*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_db_status")] // 
		static int SQLite3_db_status(sqlite3*, int op, int* pCur, int* pHiwtr, int resetFlg);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_next_stmt")] // 
		static sqlite3_stmt* SQLite3_next_stmt(sqlite3* pDb, sqlite3_stmt* pStmt);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_sql")] // 
		static const char* SQLite3_sql(sqlite3_stmt* pStmt);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_expanded_sql")] // 
		static char* SQLite3_expanded_sql(sqlite3_stmt* pStmt);

#ifdef SQLITE_ENABLE_NORMALIZE
	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_normalized_sql")] // 
		static const char* SQLite3_normalized_sql(sqlite3_stmt* pStmt);
#endif //SQLITE_ENABLE_NORMALIZE

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_log")] // 
		static void SQLite3_log(int iErrCode, const char* zFormat, ...);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_limit")] // 
		static int SQLite3_limit(sqlite3*, int id, int newVal);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_clear_bindings")] // 
		static int SQLite3_clear_bindings(sqlite3_stmt*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_complete")] // 
		static int SQLite3_complete(const char* sql);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_complete16")] // 
		static int SQLite3_complete16(const void* sql);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_context_db_handle")] // 
		static sqlite3* SQLite3_context_db_handle(sqlite3_context*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_extended_result_codes")] // 
		static int SQLite3_extended_result_codes(sqlite3*, int onoff);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_create_module")] // 
		static int SQLite3_create_module(
			sqlite3* db,               /* SQLite connection to register module with */
			const char* zName,         /* Name of the module */
			const sqlite3_module* p,   /* Methods for the module */
			void* pClientData          /* Client data for xCreate/xConnect */
		);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_create_module_v2")] // 
		static int SQLite3_create_module_v2(
			sqlite3* db,               /* SQLite connection to register module with */
			const char* zName,         /* Name of the module */
			const sqlite3_module* p,   /* Methods for the module */
			void* pClientData,         /* Client data for xCreate/xConnect */
			void(*xDestroy)(void*)     /* Module destructor function */
		);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_declare_vtab")] // Declare The Schema Of A Virtual Table
		static int SQLite3_declare_vtab(sqlite3*, const char* zSQL);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_vtab_config")] // Virtual Table Interface Configuration
		static int SQLite3_vtab_config(sqlite3*, int op, ...);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_vtab_distinct")] // Determine if a virtual table query is DISTINCT
		static int SQLite3_vtab_distinct(sqlite3_index_info*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_vtab_collation")] // Determine The Collation For a Virtual Table Constraint
		static const char* SQLite3_vtab_collation(sqlite3_index_info*, int);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_vtab_in")] // Identify and handle IN constraints in xBestIndex
		static int SQLite3_vtab_in(sqlite3_index_info*, int iCons, int bHandle);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_vtab_in_first")] // Find all elements on the right-hand side of an IN constraint.
		static int SQLite3_vtab_in_first(sqlite3_value* pVal, sqlite3_value** ppOut);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_vtab_in_next")] // Find all elements on the right-hand side of an IN constraint.
		static int SQLite3_vtab_in_next(sqlite3_value* pVal, sqlite3_value** ppOut);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_vtab_nochange")] // Determine If Virtual Table Column Access Is For UPDATE
		static int SQLite3_vtab_nochange(sqlite3_context*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_vtab_on_conflict")] // Determine The Virtual Table Conflict Policy
		static int SQLite3_vtab_on_conflict(sqlite3*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_vtab_rhs_value")] // Constraint values in xBestIndex()
		static int SQLite3_vtab_rhs_value(sqlite3_index_info*, int, sqlite3_value** ppVal);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_overload_function")] // Overload A Function For A Virtual Table
		static int SQLite3_overload_function(sqlite3*, const char* zFuncName, int nArg);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_drop_modules")] // Remove Unnecessary Virtual Table Implementations
		static int SQLite3_drop_modules(
			sqlite3* db,                /* Remove modules from this connection */
			const char** azKeep         /* Except, do not remove the ones named here */
		);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_value_subtype")] // Finding The Subtype Of SQL Values
		static unsigned int SQLite3_value_subtype(sqlite3_value*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_libversion")] // Run-Time Library Version Numbers
		static const char* SQLite3_libversion(void);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_sourceid")] // Run-Time Library Version Numbers
		static const char* SQLite3_sourceid(void);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_libversion_number")] // Run-Time Library Version Numbers
		static int SQLite3_libversion_number(void);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_initialize")] // Initialize The SQLite Library
		static int SQLite3_initialize(void);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_shutdown")] // Initialize The SQLite Library
		static int SQLite3_shutdown(void);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_os_init")] // Initialize The SQLite Library
		static int SQLite3_os_init(void);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_os_end")] // Initialize The SQLite Library
		static int SQLite3_os_end(void);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_data_count")] // Number of columns in a result set
		static int SQLite3_data_count(sqlite3_stmt* pStmt);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_get_autocommit")] // Test For Auto-Commit Mode
		static int SQLite3_get_autocommit(sqlite3*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_keyword_check")] // checks to see whether or not the L-byte UTF8 identifier that Z points to is a keyword, returning non-zero if it is and zero if not.
		static int SQLite3_keyword_check(const char*, int);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_mprintf")] // Formatted String Printing Functions
		static char* SQLite3_mprintf(const char*, ...);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_vmprintf")] // Formatted String Printing Functions
		static char* SQLite3_vmprintf(const char*, va_list);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_snprintf")] // Formatted String Printing Functions
		static char* SQLite3_snprintf(int, char*, const char*, ...);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_vsnprintf")] // Formatted String Printing Functions
		static char* SQLite3_vsnprintf(int, char*, const char*, va_list);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_randomness")] // Pseudo-Random Number Generator
		static void SQLite3_randomness(int N, void* P);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_release_memory")] // Attempt To Free Heap Memory
		static int SQLite3_release_memory(int);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_result_subtype")] // Setting The Subtype Of An SQL Function
		static void SQLite3_result_subtype(sqlite3_context*, unsigned int);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_reset_auto_extension")] // Reset Automatic Extension Loading
		static void SQLite3_reset_auto_extension(void);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_sleep")] // Suspend Execution For A Short Time
		static int SQLite3_sleep(int);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_status")] // SQLite Runtime Status
		static int SQLite3_status(int op, int* pCurrent, int* pHighwater, int resetFlag);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_status64")] // SQLite Runtime Status
		static int SQLite3_status64(
			int op,
			sqlite3_int64* pCurrent,
			sqlite3_int64* pHighwater,
			int resetFlag
		);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_stmt_status")] // Prepared Statement Status
		static int SQLite3_stmt_status(sqlite3_stmt*, int op, int resetFlg);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_threadsafe")] // Test To See If The Library Is Threadsafe
		static int SQLite3_threadsafe(void);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_total_changes")] // Total Number Of Rows Modified
		static int SQLite3_total_changes(sqlite3*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_total_changes64")] // Total Number Of Rows Modified
		static sqlite3_int64 SQLite3_total_changes64(sqlite3*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_trace_v2")] // SQL Trace Hook
		static int SQLite3_trace_v2(
			sqlite3*,
			unsigned uMask,
			int(*xCallback)(unsigned, void*, void*, void*),
			void* pCtx
		);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_user_data")] // User Data For Functions
		static void* SQLite3_user_data(sqlite3_context*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_value_dup")] // Copy And Free SQL Values
		static sqlite3_value* SQLite3_value_dup(const sqlite3_value*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_value_free")] // Copy And Free SQL Values
		static void SQLite3_value_free(sqlite3_value*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_value_encoding")] // Report the internal text encoding state of an SQLite3_value object
		static int SQLite3_value_encoding(sqlite3_value*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_changes")] // Count The Number Of Rows Modified
		static int SQLite3_changes(sqlite3*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_changes64")] // Count The Number Of Rows Modified
		static sqlite3_int64 SQLite3_changes64(sqlite3*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_backup_init")] // The backup API copies the content of one database into another. It is useful either for creating backups of databases or for copying in-memory databases to or from persistent files.
		static sqlite3_backup* SQLite3_backup_init(
			sqlite3* pDest,                        /* Destination database handle */
			const char* zDestName,                 /* Destination database name */
			sqlite3* pSource,                      /* Source database handle */
			const char* zSourceName                /* Source database name */
		);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_backup_step")] // backup API'S
		static int SQLite3_backup_step(sqlite3_backup* p, int nPage);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_backup_finish")] // backup API'S
		static int SQLite3_backup_finish(sqlite3_backup* p);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_backup_remaining")] // backup API'S
		static int SQLite3_backup_remaining(sqlite3_backup* p);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_backup_pagecount")] // backup API'S
		static int SQLite3_backup_pagecount(sqlite3_backup* p);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_mutex_alloc")] // Mutex api'S
		static sqlite3_mutex* SQLite3_mutex_alloc(int);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_mutex_free")] // Mutex api'S
		static void SQLite3_mutex_free(sqlite3_mutex*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_mutex_enter")] // Mutex api'S
		static void SQLite3_mutex_enter(sqlite3_mutex*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_mutex_try")] // Mutex api'S
		static int SQLite3_mutex_try(sqlite3_mutex*);

	[DllImport("sqlite3.dll", EntryPoint = "sqlite3_mutex_leave")] // Mutex api'S
		static void SQLite3_mutex_leave(sqlite3_mutex*);
}; 

#endif  // __SQLITEDLLCONNECT_H

