#ifndef __ATLBASE_H__
#define __ATLBASE_H__
#include <windows.h>
#include <winuser.h>
// Minimal ATL base stub — only enough to satisfy atlmfc transitives
// NOTE: CoInitialize/CoUninitialize deliberately NOT redefined here - already in combaseapi.h via windows.h
class CComModule {};
class CRegKey { public: LONG Open(HKEY, LPCTSTR, REGSAM=0) { return ERROR_SUCCESS; } LONG QueryValue(TCHAR*, LPCTSTR, DWORD*) { return ERROR_SUCCESS; } LONG Close() { return ERROR_SUCCESS; } };
class CComVariant { public: CComVariant() {} CComVariant(LPCTSTR) {} };
#define _ATL_APARTMENT_THREADED 1
#define ATLASSERT(x) assert(x)
struct _AtlAptCreateObjData { HRESULT hRes; void* pfnCreateInstance; void* piid; void* pStream; };
#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(x) (void)(x)
#endif
#endif