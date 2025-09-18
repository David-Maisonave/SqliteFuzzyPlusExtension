#include <windows.h>
#include "SQLiteDLLConnect.h"
#include <cassert>
#include <string>
#include <system_error>


namespace SQLite_DLL
{
	template<typename TProc>
	inline bool GetProcAddressChecked(HINSTANCE hINSTANCE, const std::string& procName, TProc& typeFunc)
	{
		if (hINSTANCE == NULL)
			return false;
		PROC ret = GetProcAddress(hINSTANCE, procName.c_str());
		if (!ret)
			throw std::system_error(GetLastError(), std::system_category(), "GetProcAddress failed");
		typeFunc = reinterpret_cast<TProc>(ret);
		return true;
	}
	static HINSTANCE HinstanceSqliteDll = NULL;

	typedef int (WINAPI* SQLITE3_CONFIG)(int, ...);
	static SQLITE3_CONFIG SQLite3_config;

	typedef char* (WINAPI* SQLITE3_MPRINTF)(const char*, ...);
	static SQLITE3_MPRINTF SQLite3_mprintf;

	typedef char* (WINAPI* SQLITE3_SNPRINTF)(int, char*, const char*, ...);
	static SQLITE3_SNPRINTF SQLite3_snprintf;

	typedef int (WINAPI* SQLITE3_DB_CONFIG)(sqlite3*, int op, ...);
	static SQLITE3_DB_CONFIG SQLite3_db_config;

	typedef void (WINAPI* SQLITE3_LOG)(int iErrCode, const char* zFormat, ...);
	static SQLITE3_LOG SQLite3_log;

	typedef int (WINAPI* SQLITE3_VTAB_CONFIG)(sqlite3*, int op, ...);
	static SQLITE3_VTAB_CONFIG SQLite3_vtab_config;


	RunTimeConnect::RunTimeConnect(std::string DllFileName)
	{
		HinstanceSqliteDll = LoadLibraryA(DllFileName.c_str());
		assert(GetProcAddressChecked(HinstanceSqliteDll, "sqlite3_config", SQLite3_config));
		assert(GetProcAddressChecked(HinstanceSqliteDll, "sqlite3_mprintf", SQLite3_mprintf));
		assert(GetProcAddressChecked(HinstanceSqliteDll, "sqlite3_snprintf", SQLite3_snprintf));
		assert(GetProcAddressChecked(HinstanceSqliteDll, "sqlite3_db_config", SQLite3_db_config));
		assert(GetProcAddressChecked(HinstanceSqliteDll, "sqlite3_log", SQLite3_log));
		assert(GetProcAddressChecked(HinstanceSqliteDll, "sqlite3_vtab_config", SQLite3_vtab_config));
	}

#pragma warning (disable : 4793)
	int RunTimeConnect::sqlite3_config(int arg, ...)
	{
		va_list ap;
		va_start(ap, arg);
		int r = SQLite3_config(arg, ap);
		va_end(ap);
		return r;
	}

	char* RunTimeConnect::sqlite3_mprintf(const char* arg, ...)
	{
		va_list ap;
		va_start(ap, arg);
		char* r = SQLite3_mprintf(arg, ap);
		va_end(ap);
		return r;
	}

	char* RunTimeConnect::sqlite3_snprintf(int i, char* arg, const char* arg2, ...)
	{
		va_list ap;
		va_start(ap, arg2);
		char* r = SQLite3_snprintf(i, arg, arg2, ap);
		va_end(ap);
		return r;
	}

	int RunTimeConnect::sqlite3_db_config(sqlite3* db, int arg, ...)
	{
		va_list ap;
		va_start(ap, arg);
		int r = SQLite3_db_config(db, arg, ap);
		va_end(ap);
		return r;
	}

	void RunTimeConnect::sqlite3_log(int iErrCode, const char* arg, ...)
	{
		va_list ap;
		va_start(ap, arg);
		SQLite3_log(iErrCode, arg, ap);
		va_end(ap);
	}

	int RunTimeConnect::sqlite3_vtab_config(sqlite3* db, int  arg, ...)
	{
		va_list ap;
		va_start(ap, arg);
		int r = SQLite3_vtab_config(db, arg, ap);
		va_end(ap);
		return r;
	}
}