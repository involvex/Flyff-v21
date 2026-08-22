#ifndef _AFXTEMPL_H_
#define _AFXTEMPL_H_
#include <afx.h>
#include <list>
#include <map>
#include <vector>

template <class T, class U> class CArray {
public:
    int   GetSize() const              { return 0; }
    int   GetCount() const             { return 0; }
    void  RemoveAll()                  {}
    void  RemoveAt(int, int=1)         {}
    void  InsertAt(int, const U&, int=1) {}
    void  Append(const CArray& )       {}
    void  Copy(const CArray& )         {}
    void  Add(const U&)                {}
    U&    ElementAt(int)               { static U u; return u; }
    U&    GetAt(int)                   { static U u; return u; }
    const U& GetAt(int) const          { static U u; return u; }
    U&    operator[](int)              { static U u; return u; }
    const U& operator[](int) const     { static U u; return u; }
    U*    GetData()                    { return nullptr; }
    int   GetUpperBound() const        { return -1; }
    void  SetSize(int, int=0)          {}
    void  SetAt(int, const U&)         {}
    void  SetAtGrow(int, const U&)     {}
};

template <class T, class U> class CList {
public:
    int     GetCount() const           { return 0; }
    void    RemoveAll()                {}
    POSITION AddHead(const U&)         { return nullptr; }
    POSITION AddTail(const U&)         { return nullptr; }
    U&      GetNext(POSITION&) const   { static U u; return u; }
    U&      GetPrev(POSITION&) const   { static U u; return u; }
    U&      GetAt(POSITION) const      { static U u; return u; }
    void    RemoveAt(POSITION)         {}
    POSITION GetHeadPosition() const   { return nullptr; }
    POSITION GetTailPosition() const   { return nullptr; }
    U       GetHead() const            { static U u; return u; }
    U       GetTail() const            { static U u; return u; }
    void    AddTail(const CList<U,U>&) {}
    POSITION Find(const U&) const      { return nullptr; }
};

template <class K, class AK, class V, class AV> class CMapT {
public:
    int     GetCount() const           { return 0; }
    void    RemoveAll()                {}
    BOOL    Lookup(AK, V&) const { return FALSE; }
    POSITION GetStartPosition() const  { return nullptr; }
    void    GetNextAssoc(POSITION&, K&, V&) const {}
    void    SetAt(AK, const V&)  {}
    BOOL    RemoveKey(AK)        { return FALSE; }
    V& operator[](AK k) { static V v; (void)k; return v; }
};
template<class... Args> struct CMapHelper;
template<class K, class V> struct CMapHelper<K, V> { using type = CMapT<K, const K&, V, V&>; };
template<class K, class AK, class V, class AV> struct CMapHelper<K, AK, V, AV> { using type = CMapT<K, AK, V, AV>; };
template<class... Args> using CMap = typename CMapHelper<Args...>::type;

typedef CMap<CString, LPCTSTR, void*, void*> CMapStringToPtr;
typedef CMap<CString, LPCTSTR, CString, CString&> CMapStringToString;
typedef CMap<WORD, WORD, void*, void*> CMapWordToPtr;
typedef CMap<DWORD, DWORD, void*, void*> CMapDWordToPtr;
typedef CMap<void*, void*, void*, void*> CMapPtrToPtr;
typedef CMap<UINT, UINT, void*, void*> CMapUIntToPtr;

template <class T> class CTypedPtrList    : public CList<T*, T*>  {};
template <class T> class CTypedPtrArray   : public CArray<T*, T*> {};
template <class T> class CTypedPtrDwordArray { public: DWORD GetAt(int) const { return 0; } void SetAt(int,DWORD) {} };

class CObList  : public CObject { public: CObList() : head(nullptr), tail(nullptr) {} POSITION head, tail; };
class CPtrList : public CObject { public: CPtrList() : head(nullptr), tail(nullptr) {} POSITION head, tail; };
class CObArray : public CArray<CObject*, CObject*> {};
class CStringArray : public CArray<CString, CString> {
public:
    void SetAtGrow(int n, const CString& v) { if(n>=GetSize()) SetSize(n+1); SetAt(n, v); }
};
class CWordArray   : public CArray<WORD, WORD> {
public:
    void SetAtGrow(int n, WORD v) { if(n>=GetSize()) SetSize(n+1); SetAt(n, v); }
};
class CDWordArray  : public CArray<DWORD, DWORD> {
public:
    void SetAtGrow(int n, DWORD v) { if(n>=GetSize()) SetSize(n+1); SetAt(n, v); }
};
class CPtrArray    : public CArray<void*, void*> { public: void* operator[](int n) const { return nullptr; } };
class CUIntArray   : public CArray<UINT, UINT> {
public:
    void SetAtGrow(int n, UINT v) { if(n>=GetSize()) SetSize(n+1); SetAt(n, v); }
};
class CByteArray : public CObject {
public:
    int GetSize() const { return (int)data.size(); }
    void RemoveAll() { data.clear(); }
    void RemoveAt(int, int=1) {}
    void InsertAt(int, BYTE, int=1) {}
    void Append(const CByteArray& ) {}
    void SetAtGrow(int n, BYTE v) { if(n>= (int)data.size()) data.resize(n+1); data[n]=v; }
    void Add(BYTE b) { data.push_back(b); }
    void SetSize(int n, int = -1) { data.resize(n); }
    BYTE GetAt(int i) const { return data[i]; }
    void SetAt(int i, BYTE b) { data[i]=b; }
    BYTE& ElementAt(int i) { return data[i]; }
    BYTE& operator[](int i) { static BYTE b=0; if(i>=0 && i<(int)data.size()) return data[i]; return b; }
    const BYTE& operator[](int i) const { static BYTE b=0; if(i>=0 && i<(int)data.size()) return data[i]; return b; }
    BYTE* GetData() { return data.empty()?nullptr:&data[0]; }
    int GetCount() const { return (int)data.size(); }
private:
    std::vector<BYTE> data;
};
#endif