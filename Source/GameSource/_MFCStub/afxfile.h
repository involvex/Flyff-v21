#ifndef _AFXFILE_H__
#define _AFXFILE_H__
#include "afxwin.h"
struct CFileStatus { CTime m_ctime; CTime m_mtime; CTime m_atime; LONG m_size; BYTE m_szFullName[MAX_PATH]; };
class CFileException : public CObject { public: void GetErrorMessage(LPTSTR, UINT) {} };
class CFile : public CObject {
public:
    enum OpenFlags {
        modeRead = 0x0000, modeWrite = 0x0001, modeReadWrite = 0x0002,
        shareCompat = 0x0000, shareExclusive = 0x0010, shareDenyWrite = 0x0020, shareDenyRead = 0x0030, shareDenyNone = 0x0040, shareDenyNoTruncate = 0x0080,
        modeCreate = 0x1000, modeNoTruncate = 0x2000, typeText = 0x4000, typeBinary = 0x8000
    };
    enum SeekPosition { begin = 0, current = 1, end = 2 };
    HANDLE m_hFile;
    CFile() : m_hFile(INVALID_HANDLE_VALUE) {}
    CFile(LPCTSTR, UINT) : m_hFile(INVALID_HANDLE_VALUE) {}
    virtual BOOL Open(LPCTSTR, UINT, void* = nullptr) { return FALSE; }
    virtual UINT Read(void*, UINT) { return 0; }
    virtual void Write(const void*, UINT) {}
    virtual void Close() {}
    virtual void Flush() {}
    virtual DWORD GetLength() const { return 0; }
    virtual DWORD GetPosition() const { return 0; }
    virtual ULONGLONG GetLength64() const { return 0; }
    virtual LONG Seek(LONG, UINT) { return 0; }
    static BOOL GetStatus(LPCTSTR, CFileStatus&) { return FALSE; }
    static BOOL GetStatus(LPCTSTR, CFileStatus&, void*) { return FALSE; }
};
class CStdioFile : public CFile {};
class CMemFile : public CFile {
public:
    CMemFile(UINT = 0) {}
    void Attach(BYTE*, UINT) {}
    BYTE* Detach() { return nullptr; }
};
class CArchive : public CObject {
public:
    enum Mode { store = 0, load = 1, bNoFlushOnDelete = 2 };
    CArchive(CFile*, UINT, int = 4096, void* = nullptr) {}
    BOOL IsLoading() const { return FALSE; }
    BOOL IsStoring() const { return FALSE; }
    CArchive& operator<<(DWORD) { return *this; }
    CArchive& operator>>(DWORD&) { return *this; }
    CArchive& operator<<(int) { return *this; }
    CArchive& operator>>(int&) { return *this; }
    void Read(void*, UINT) {}
    void Write(const void*, UINT) {}
    void Flush() {}
    void Close() {}
};
#endif
