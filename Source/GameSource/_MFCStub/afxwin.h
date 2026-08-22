#ifndef _AFXWIN_H__
#define _AFXWIN_H__
#include <afx.h>
#include <tchar.h>
#include <time.h>
#include <commctrl.h>

struct AFX_MSGMAP_ENTRY;
struct AFX_MSGMAP;

class CWnd {
public:
    HWND  m_hWnd;
    BOOL  Create(LPCTSTR, LPCTSTR, DWORD, const RECT&, CWnd*, UINT, class CCreateContext*);
    template<typename... Args> BOOL CreateEx(Args&&... ) { return TRUE; }
    BOOL  DestroyWindow();
    void  CenterWindow(CWnd* = nullptr) {}
    CWnd* GetDlgItem(int);
    HWND  GetSafeHwnd() const;
    BOOL  Invalidate(BOOL);
    BOOL  UpdateWindow();
    BOOL  ShowWindow(int);
    BOOL  SetWindowText(LPCTSTR);
    BOOL  SetTimer(UINT, UINT, void*);
    BOOL  KillTimer(UINT);
    virtual void OnPaint();
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    LRESULT WindowProc(UINT, WPARAM, LPARAM);
    BOOL    OnCommand(WPARAM, LPARAM);
    LPCTSTR GetWinText() const;
    DECLARE_MESSAGE_MAP()
};

class CFrameWnd : public CWnd {};
class CDialog   : public CWnd { public: virtual int DoModal() { return 0; } };
class CDialogEx : public CDialog {};
class CWinThread : public CObject {};
class CWinApp    : public CWinThread {};
class CDC { public: HDC m_hDC; };
class CPaintDC  : public CDC {};
class CClientDC : public CDC { public: CClientDC(CWnd* = nullptr) {} CClientDC(HWND) {} };
class CGdiObject : public CObject {};
class CBitmap   : public CGdiObject { public:
#pragma push_macro("GetObject")
#undef GetObject
    int GetObject(int, void*) { return 0; }
    int GetObjectA(int, void*) { return 0; }
    BOOL Attach(HBITMAP) { return TRUE; }
    HBITMAP Detach() { return nullptr; }
#pragma pop_macro("GetObject")
};
class CBrush    : public CGdiObject {};
class CPen      : public CGdiObject {};
class CFont     : public CGdiObject {};
class CImageList : public CObject {};
class CPalette : public CGdiObject { public: BOOL CreatePalette(void*) { return TRUE; } BOOL CreateHalftonePalette(HDC) { return TRUE; } };
class CMenu    : public CObject {};
class CListBox    : public CWnd {};
class CComboBox   : public CWnd {};
class CEdit       : public CWnd {};
class CStatic     : public CWnd {};
class CButton     : public CWnd {};
class CListCtrl   : public CWnd {};
class CTreeCtrl   : public CWnd {};
class CTabCtrl    : public CWnd {};
class CToolTipCtrl: public CWnd {};
class CPropertySheet  : public CWnd {};
class CPropertyPage   : public CWnd {};

class CString {
public:
    CString() : s_() {}
    CString(LPCTSTR s) : s_(s ? s : _T("")) {}
    CString(LPCTSTR s, int nLen) : s_(s ? std::basic_string<TCHAR>(s, nLen) : _T("")) {}
    CString(TCHAR ch, int nRepeat) : s_(nRepeat>0 ? std::basic_string<TCHAR>(nRepeat, ch) : _T("")) {}
    CString(const unsigned char* s) : s_() { if(s){ int n=(int)strlen((const char*)s); s_.assign(n,0); for(int i=0;i<n;i++) s_[i]=(TCHAR)(unsigned char)s[i]; } }
    CString(LPCWSTR ws) : s_() { if(ws){ int n=(int)wcslen(ws); s_.assign(n,0); for(int i=0;i<n;i++) s_[i]=(TCHAR)ws[i]; } }
    CString(const CString& o) : s_(o.s_) {}
    CString(const CString& o, int nLen) : s_(o.s_.substr(0,nLen)) {}
    CString(TCHAR ch) : s_(1,ch) {}
    CString& operator=(LPCTSTR s_) { s_ = s_ ? s_ : _T(""); return *this; }
    CString& operator=(TCHAR ch) { s_.assign(1,ch); return *this; }
    CString& operator=(const CString& o) { s_ = o.s_; return *this; }
    CString& operator+=(LPCTSTR s) { if(s) s_+=s; return *this; }
    CString& operator+=(TCHAR c) { s_+=c; return *this; }
    CString& operator+=(const CString& o) { s_+=o.s_; return *this; }
    friend CString operator+(const CString& a, const CString& b) { return CString((a.s_+b.s_).c_str()); }
    friend CString operator+(const CString& a, LPCTSTR b) { return CString((a.s_+(b?b:_T(""))).c_str()); }
    friend CString operator+(LPCTSTR a, const CString& b) { return CString(((a?a:_T(""))+b.s_).c_str()); }
    friend CString operator+(const CString& a, TCHAR b) { CString r=a; r.s_+=b; return r; }
    friend CString operator+(TCHAR a, const CString& b) { CString r; r.s_+=a; r.s_+=b.s_; return r; }
    BOOL operator==(LPCTSTR s) const { return s_==(s?s:_T("")); }
    BOOL operator==(const CString& o) const { return s_==o.s_; }
    BOOL operator==(TCHAR c) const { return s_.length()==1 && s_[0]==c; }
    BOOL operator!=(LPCTSTR s) const { return s_!=(s?s:_T("")); }
    BOOL operator!=(TCHAR c) const { return !(*this==c); }
    void Empty() { s_.clear(); }
    operator LPCTSTR() const { return s_.c_str(); }
    int   GetLength() const    { return (int)s_.length(); }
    TCHAR GetAt(int) const     { return 0; }
    void  SetAt(int n, TCHAR c) { if(n>=0 && n<(int)s_.size()) s_[n]=c; }
    void  ReleaseBuffer()      {}
    CString Mid(int, int=0) const { return CString(); }
    int    Find(TCHAR ch) const   { auto p=s_.find(ch); return p==std::basic_string<TCHAR>::npos?-1:(int)p; }
    int    Find(TCHAR ch, int nStart) const { if(nStart<0) nStart=0; auto p=s_.find(ch,(size_t)nStart); return p==std::basic_string<TCHAR>::npos?-1:(int)p; }
    int    Find(LPCTSTR sub) const { if(!sub) return -1; auto p=s_.find(sub); return p==std::basic_string<TCHAR>::npos?-1:(int)p; }
    int    Find(LPCTSTR sub, int nStart) const { if(!sub) return -1; if(nStart<0) nStart=0; auto p=s_.find(sub,(size_t)nStart); return p==std::basic_string<TCHAR>::npos?-1:(int)p; }
    int    Compare(LPCTSTR) const { return 0; }
    CString& MakeLower() { return *this; }
    CString& MakeUpper() { return *this; }
    LPCTSTR   GetString() const { return s_.c_str(); }
    BOOL      IsEmpty()   const { return s_.empty(); }
    LPTSTR    LockBuffer() { return s_.empty()?nullptr:&s_[0]; }
    void      UnlockBuffer() {}
    LPTSTR    GetBuffer(int nMin) { s_.resize(nMin); return s_.empty()?nullptr:&s_[0]; }
    void      ReleaseBuffer(int = -1) {}
    void      Append(LPCTSTR s) { if(s) s_+=s; }
    void      Append(const CString& s) { s_+=s.s_; }
    void      FormatV(LPCTSTR, va_list) {}
    void      Format(LPCTSTR, ...) {}
    CString   Left(int n)  const { return n > 0 ? CString(s_.substr(0, n).c_str()) : CString(); }
    CString   Right(int n) const { int l = (int)s_.length(); return n > 0 ? CString(s_.substr(l - n, n).c_str()) : CString(); }
    int       Delete(int n, int c=1) { if(n>=0 && n<(int)s_.size()) s_.erase(n,c); return (int)s_.size(); }
    int       Insert(int n, TCHAR ch) { if(n<0) n=0; if(n>(int)s_.size()) n=(int)s_.size(); s_.insert(s_.begin()+n,ch); return (int)s_.size(); }
    int       Insert(int n, LPCTSTR p) { if(!p) return (int)s_.size(); if(n<0) n=0; if(n>(int)s_.size()) n=(int)s_.size(); s_.insert(n,p); return (int)s_.size(); }
    int       Remove(TCHAR) { return 0; }
    int       Replace(LPCTSTR from, LPCTSTR to) { if(!from||!to) return 0; int cnt=0; size_t p=0; size_t fl=_tcslen(from); size_t tl=_tcslen(to); while((p=s_.find(from,p))!=std::basic_string<TCHAR>::npos){ s_.replace(p,fl,to); p+=tl; cnt++; } return cnt; }
    int       Replace(TCHAR from, TCHAR to) { int cnt=0; for(auto& c:s_) if(c==from){c=to; cnt++;} return cnt; }
    void      TrimLeft() { s_.erase(s_.begin(), std::find_if(s_.begin(), s_.end(), [](TCHAR c){return c!=' '&&c!='\t'&&c!='\n'&&c!='\r';})); }
    void      TrimLeft(TCHAR ch) { while(!s_.empty() && s_.front()==ch) s_.erase(s_.begin()); }
    void      TrimLeft(LPCTSTR chars) { if(!chars) return; while(!s_.empty() && _tcschr(chars,s_.front())) s_.erase(s_.begin()); }
    void      TrimRight() { s_.erase(std::find_if(s_.rbegin(), s_.rend(), [](TCHAR c){return c!=' '&&c!='\t'&&c!='\n'&&c!='\r';}).base(), s_.end()); }
    void      TrimRight(TCHAR ch) { while(!s_.empty() && s_.back()==ch) s_.pop_back(); }
    void      TrimRight(LPCTSTR chars) { if(!chars) return; while(!s_.empty() && _tcschr(chars,s_.back())) s_.pop_back(); }
    void      Trim() { TrimRight(); TrimLeft(); }
    void      Trim(TCHAR ch) { TrimLeft(ch); TrimRight(ch); }
    CString   SpanExcluding(LPCTSTR) const { return *this; }
    CString   SpanIncluding(LPCTSTR)  const { return *this; }
private:
    std::basic_string<TCHAR> s_;
};

class CTimeSpan : public CObject {
public:
    CTimeSpan() : m_span(0) {}
    CTimeSpan(long d,int h,int m,int s) : m_span((long long)d*86400+h*3600+m*60+s) {}
    CTimeSpan(long long s) : m_span(s) {}
    long long GetTotalSeconds() const { return m_span; }
    long long GetTotalMinutes() const { return m_span/60; }
    long long GetTotalHours() const { return m_span/3600; }
    CString Format(LPCTSTR) const { return CString(); }
    int GetDays() const { return (int)(m_span/86400); }
    int GetHours() const { return (int)((m_span%86400)/3600); }
    int GetMinutes() const { return (int)((m_span%3600)/60); }
    int GetSeconds() const { return (int)(m_span%60); }
    CTimeSpan& operator+=(const CTimeSpan& o){ m_span+=o.m_span; return *this; }
    CTimeSpan& operator-=(const CTimeSpan& o){ m_span-=o.m_span; return *this; }
    BOOL operator<=(const CTimeSpan& o) const { return m_span<=o.m_span; }
    BOOL operator>=(const CTimeSpan& o) const { return m_span>=o.m_span; }
    BOOL operator<(const CTimeSpan& o) const { return m_span<o.m_span; }
    BOOL operator>(const CTimeSpan& o) const { return m_span>o.m_span; }
    BOOL operator==(const CTimeSpan& o) const { return m_span==o.m_span; }
private:
    long long m_span;
};

#ifdef GetCurrentTime
#undef GetCurrentTime
#endif
#ifdef GetTickCount
#undef GetTickCount
#endif
inline DWORD GetCurrentTime() { return ::GetTickCount(); }
class CTime     : public CObject {
public:
    CTime() : t_(0) {}
    CTime(ULONG t) : t_(t) {}
    CTime(int, int, int, int, int, int) : t_(0) {}
    CTime(const SYSTEMTIME& st) : t_(0) { (void)st; }
    CTime(SYSTEMTIME* pst) : t_(0) { (void)pst; }
    CTime(const CTime& o) : t_(o.t_) {}
    CTime& operator=(const CTime& o) { t_ = o.t_; return *this; }
    time_t GetTime() const { return t_; }
    static DWORD GetTickCount() { return (DWORD)::GetTickCount(); }
    static CTime GetCurrentTime() { return CTime((ULONG)time(nullptr)); }
    int    GetYear()   const { return 2024; }
    int    GetMonth()  const { return 1; }
    int    GetDay()    const { return 1; }
    int    GetHour()   const { return 0; }
    int    GetMinute() const { return 0; }
    int    GetSecond() const { return 0; }
    int    GetDayOfWeek() const { return 1; }
    struct tm* GetLocalTm(struct tm* ptm) const { if(ptm){ memset(ptm,0,sizeof(*ptm)); } return ptm; }
    CString Format(LPCTSTR) const { return CString(); }
    CString Format(UINT) const { return CString(); }
    CTime& operator+=(CTimeSpan span) { t_ += (time_t)span.GetTotalSeconds(); return *this; }
    CTime& operator-=(CTimeSpan span) { t_ -= (time_t)span.GetTotalSeconds(); return *this; }
    CTime& operator=(time_t v) { t_=v; return *this; }
    CTime& operator=(int v) { t_=v; return *this; }
    BOOL operator==(const CTime& o) const { return t_ == o.t_; }
    BOOL operator!=(const CTime& o) const { return t_ != o.t_; }
    BOOL operator<(const CTime& o)  const { return t_ < o.t_; }
    BOOL operator>(const CTime& o)  const { return t_ > o.t_; }
    BOOL operator<=(const CTime& o) const { return t_ <= o.t_; }
    BOOL operator>=(const CTime& o) const { return t_ >= o.t_; }
private:
    time_t t_;
    friend CTimeSpan operator-(const CTime& a, const CTime& b);
    friend CTime operator+(const CTime& a, const CTimeSpan& s);
    friend CTime operator-(const CTime& a, const CTimeSpan& s);
};
inline CTimeSpan operator-(const CTime& a, const CTime& b){ return CTimeSpan((long long)a.GetTime()-(long long)b.GetTime()); }
inline CTime operator+(const CTime& a, const CTimeSpan& s){ return CTime((ULONG)(a.GetTime()+s.GetTotalSeconds())); }
inline CTime operator-(const CTime& a, const CTimeSpan& s){ return CTime((ULONG)(a.GetTime()-s.GetTotalSeconds())); }
class CPoint    : public POINT  {
public:
    CPoint() { x=y=0; }
    CPoint(int n) { x=y=n; }
    CPoint(int _x,int _y) { x=_x; y=_y; }
    CPoint(POINT pt) { x=pt.x; y=pt.y; }
    CPoint(SIZE sz) { x=sz.cx; y=sz.cy; }
    void SetPoint(int _x,int _y) { x=_x; y=_y; }
    CPoint operator+(POINT p) const { CPoint r; r.x=x+p.x; r.y=y+p.y; return r; }
    CPoint operator-(POINT p) const { CPoint r; r.x=x-p.x; r.y=y-p.y; return r; }
    CPoint operator-() const { CPoint r; r.x=-x; r.y=-y; return r; }
    CPoint& operator+=(POINT p) { x+=p.x; y+=p.y; return *this; }
    CPoint& operator-=(POINT p) { x-=p.x; y-=p.y; return *this; }
    CPoint& operator+=(SIZE s) { x+=s.cx; y+=s.cy; return *this; }
    CPoint& operator-=(SIZE s) { x-=s.cx; y-=s.cy; return *this; }
    BOOL operator==(POINT p) const { return x==p.x && y==p.y; }
    BOOL operator!=(POINT p) const { return x!=p.x || y!=p.y; }
};
class CSize     : public SIZE   {
public:
    CSize() { cx=cy=0; }
    CSize(int _cx,int _cy) { cx=_cx; cy=_cy; }
    CSize(SIZE sz) { cx=sz.cx; cy=sz.cy; }
    CSize(POINT pt) { cx=pt.x; cy=pt.y; }
    CSize(RECT rc) { cx=rc.right-rc.left; cy=rc.bottom-rc.top; }
    BOOL operator==(SIZE s) const { return cx==s.cx && cy==s.cy; }
    BOOL operator!=(SIZE s) const { return cx!=s.cx || cy!=s.cy; }
    CSize operator+(SIZE s) const { CSize r; r.cx=cx+s.cx; r.cy=cy+s.cy; return r; }
    CSize operator-(SIZE s) const { CSize r; r.cx=cx-s.cx; r.cy=cy-s.cy; return r; }
};
class CRect     : public RECT   {
public:
    CRect() { left = top = right = bottom = 0; }
    CRect(int l,int t,int r,int b) { left=l; top=t; right=r; bottom=b; }
    CRect(const RECT& rc) { left=rc.left; top=rc.top; right=rc.right; bottom=rc.bottom; }
    CRect(LPCRECT p) { if(p){left=p->left; top=p->top; right=p->right; bottom=p->bottom;} else left=top=right=bottom=0; }
    CRect(POINT pt, SIZE sz) { left=pt.x; top=pt.y; right=left+sz.cx; bottom=top+sz.cy; }
    CRect(POINT p1, POINT p2) { left=p1.x; top=p1.y; right=p2.x; bottom=p2.y; }
    void SetRect(int l,int t,int r,int b) { left=l; top=t; right=r; bottom=b; }
    void SetRectEmpty() { left=top=right=bottom=0; }
    void CopyRect(const RECT* p) { if(p){left=p->left; top=p->top; right=p->right; bottom=p->bottom;} }
    void CopyRect(const RECT& rc) { left=rc.left; top=rc.top; right=rc.right; bottom=rc.bottom; }
    BOOL IsRectEmpty() const { return left>=right || top>=bottom; }
    CPoint CenterPoint() const { return CPoint((left+right)/2, (top+bottom)/2); }
    void NormalizeRect() { if(left>right) std::swap(left,right); if(top>bottom) std::swap(top,bottom); }
    CPoint& TopLeft() { return *(CPoint*)&left; }
    const CPoint& TopLeft() const { return *(const CPoint*)&left; }
    CPoint& BottomRight() { return *(CPoint*)&right; }
    const CPoint& BottomRight() const { return *(const CPoint*)&right; }
    void SetRect(POINT p1, POINT p2) { left=p1.x; top=p1.y; right=p2.x; bottom=p2.y; }
    void InflateRect(int dx, int dy) { left-=dx; top-=dy; right+=dx; bottom+=dy; }
    void DeflateRect(int dx, int dy) { left+=dx; top+=dy; right-=dx; bottom-=dy; }
    void OffsetRect(int dx,int dy) { left+=dx; top+=dy; right+=dx; bottom+=dy; }
    void OffsetRect(POINT pt) { left+=pt.x; top+=pt.y; right+=pt.x; bottom+=pt.y; }
    void OffsetRect(SIZE sz) { left+=sz.cx; top+=sz.cy; right+=sz.cx; bottom+=sz.cy; }
    void DeflateRect(int l,int t,int r,int b) { left+=l; top+=t; right-=r; bottom-=b; }
    void DeflateRect(LPCRECT rc) { if(rc){ left+=rc->left; top+=rc->top; right-=rc->right; bottom-=rc->bottom; } }
    CRect& operator+=(POINT pt) { OffsetRect(pt); return *this; }
    CRect& operator-=(POINT pt) { OffsetRect(-pt.x,-pt.y); return *this; }
    CRect& operator+=(SIZE sz) { OffsetRect(sz); return *this; }
    CRect& operator-=(SIZE sz) { OffsetRect(-sz.cx,-sz.cy); return *this; }
    CRect& operator+=(const RECT& rc) { left+=rc.left; top+=rc.top; right+=rc.right; bottom+=rc.bottom; return *this; }
    CRect& operator-=(const RECT& rc) { left-=rc.left; top-=rc.top; right-=rc.right; bottom-=rc.bottom; return *this; }
    CRect operator+(POINT pt) const { CRect r(*this); r.OffsetRect(pt); return r; }
    CRect operator+(SIZE sz) const { CRect r(*this); r.OffsetRect(sz); return r; }
    CRect operator+(const RECT& rc) const { CRect r; r.left=left+rc.left; r.top=top+rc.top; r.right=right+rc.right; r.bottom=bottom+rc.bottom; return r; }
    CRect operator-(POINT pt) const { CRect r(*this); r.OffsetRect(-pt.x,-pt.y); return r; }
    BOOL operator==(const RECT& rc) const { return left==rc.left && top==rc.top && right==rc.right && bottom==rc.bottom; }
    BOOL operator!=(const RECT& rc) const { return !(*this==rc); }
    operator LPRECT() { return this; }
    operator LPCRECT() const { return this; }
    BOOL PtInRect(POINT pt) const { return pt.x>=left && pt.x<right && pt.y>=top && pt.y<bottom; }
    int  Width() const { return right-left; }
    int  Height() const { return bottom-top; }
    CSize Size() const { CSize s; s.cx=right-left; s.cy=bottom-top; return s; }
};

typedef LPCTSTR PCXSTR;
#include <afxtempl.h>
#include <afxfile.h>

// Keep GetMessage macro (maps to GetMessageW/A via windows.h) for client code like d3dapp.cpp

inline BOOL AfxExtractSubString(CString& rString, LPCTSTR lpszFullString, int nSubString, TCHAR chSep = '\n') { rString.Empty(); if(!lpszFullString) return FALSE; CString s(lpszFullString); int start=0; int idx=0; for(int i=0;i<=(int)s.GetLength();i++){ if(i==(int)s.GetLength() || s.GetString()[i]==chSep){ if(idx==nSubString){ rString = s.Mid(start,i-start); return TRUE; } idx++; start=i+1; } } return FALSE; }
#define MB_OK 0
#define MB_ICONERROR 0x10
#define SW_HIDE 0
#define SW_SHOW 5
#define SW_RESTORE 9
#define WM_PAINT 0x000F
#define WM_COMMAND 0x0111
#define WM_CLOSE 0x0010
#define WM_USER 0x0400
#define WM_DESTROY 0x0002
#define MF_BYCOMMAND 0
#define MF_POPUP 0x0010
#define MF_STRING 0
#endif
