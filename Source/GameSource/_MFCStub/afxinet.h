#ifndef _AFXINET_H__
#define _AFXINET_H__
#include "afxwin.h"

class CException : public CObject { public: virtual BOOL GetErrorMessage(LPTSTR, UINT, UINT* = nullptr) { return FALSE; } void Delete() { delete this; } };
class CInternetException : public CException {
public:
    DWORD m_dwError = 0;
    BOOL GetErrorMessage(LPTSTR s, UINT n, UINT* = nullptr) { if(s&&n) s[0]=0; return FALSE; }
};

#ifndef INTERNET_INVALID_PORT_NUMBER
#define INTERNET_INVALID_PORT_NUMBER 0
#endif
typedef WORD INTERNET_PORT;

class CHttpFile;

class CHttpConnection : public CObject {
public:
    enum { HTTP_VERB_POST = 1, HTTP_VERB_GET = 0 };
    CHttpFile* OpenRequest(int, LPCTSTR, LPCTSTR = nullptr, DWORD = 0, LPCTSTR* = nullptr, LPCTSTR = nullptr, DWORD = 0) { return nullptr; }
    CHttpFile* OpenRequest(LPCTSTR, LPCTSTR, LPCTSTR = nullptr, DWORD = 0, LPCTSTR* = nullptr, LPCTSTR = nullptr, DWORD = 0) { return nullptr; }
    void Close() {}
};

class CHttpFile : public CObject {
public:
    BOOL SendRequest(LPCTSTR = nullptr, DWORD = 0, LPVOID = nullptr, DWORD = 0) { return FALSE; }
    BOOL SendRequest(LPCTSTR, LPVOID, DWORD) { return FALSE; }
    BOOL SendRequestEx(DWORD, DWORD) { return FALSE; }
    DWORD GetLength() { return 0; }
    UINT Read(void*, UINT n) { return 0; }
    UINT ReadHuge(void*, UINT n) { return 0; }
    void Close() {}
};

class CInternetSession : public CObject {
public:
    CInternetSession(LPCTSTR = nullptr, int = 0, DWORD = 0, LPCTSTR = nullptr, LPCTSTR = nullptr, DWORD = 0) {}
    CHttpConnection* GetHttpConnection(LPCTSTR, INTERNET_PORT = 80, LPCTSTR = nullptr, LPCTSTR = nullptr) { return nullptr; }
    CHttpConnection* GetHttpConnection(LPCTSTR, DWORD, LPCTSTR, LPCTSTR) { return nullptr; }
    void Close() {}
};

#endif
