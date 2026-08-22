#ifndef _AFX_H_
#define _AFX_H_
#include <windows.h>
#include <winuser.h>
#include <shellapi.h>
#include <cstdlib>
#include <assert.h>
#include <string>
#include <stdio.h>
#include <algorithm>

namespace ATL {
    inline size_t _mbstowcsz(wchar_t* w, const char* m, size_t n) {
        if (!m || !w || !n) return 0;
        size_t r = 0;
        for (; r < n - 1 && m[r]; ++r) w[r] = (wchar_t)(unsigned char)m[r];
        w[r] = 0;
        return r;
    }
}

class CObject {};
typedef void* POSITION;

struct AFX_MSGMAP_ENTRY { unsigned nMessage; unsigned nSig; };
struct AFX_MSGMAP      { const AFX_MSGMAP* pBaseMap; const AFX_MSGMAP_ENTRY* lpEntries; };
#define DECLARE_DYNAMIC(c)      public:
#define IMPLEMENT_DYNAMIC(c,b)
#define DECLARE_DYNCREATE(c)     public:
#define IMPLEMENT_DYNCREATE(c,b)
#define DECLARE_MESSAGE_MAP()    public: virtual const AFX_MSGMAP* GetMessageMap() const;
#define BEGIN_MESSAGE_MAP(c,b)
#define END_MESSAGE_MAP()
#define ON_COMMAND(id,fn)
#define ON_BN_CLICKED(id,fn)  ON_COMMAND(id,fn)
#define ON_WM_PAINT()
#define ON_WM_TIMER()
#define ON_WM_DESTROY()
#define ON_WM_CLOSE()
#define ON_WM_COMMAND()
#define afx_msg
#define TRACE(...)  do {} while(0)
#define TRACE0(x) do {} while(0)
#define TRACE1(x,a) do {} while(0)
#define TRACE2(x,a,b) do {} while(0)
#define TRACE3(x,a,b,c) do {} while(0)
#ifndef UNUSED_ALWAYS
#define UNUSED_ALWAYS(x) (void)(x)
#endif
#ifndef PROGDLG_NORMAL
#define PROGDLG_NORMAL 0
#endif
#define ASSERT(x)   assert(x)
#define VERIFY(x)   ((void)(x))
inline HINSTANCE AfxGetInstanceHandle() { return (HINSTANCE)GetModuleHandle(NULL); }
inline int       AfxMessageBox(LPCTSTR, UINT=0, UINT=0) { return 0; }
inline class CWinApp*  AfxGetApp()     { return nullptr; }
inline class CWnd*     AfxGetMainWnd() { return nullptr; }
inline LPCTSTR AfxRegisterWndClass(UINT, HCURSOR = nullptr, HBRUSH = nullptr, HICON = nullptr) { return TEXT(""); }
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

// NOTE: D3DFORMAT intentionally not defined here - ServerDesc.h and vutil.h
// now include <d3d9types.h> directly to get the real enum, avoiding
// typedef-vs-enum redefinition with ThirdParty/WindowsSDK headers.
// D3DVECTOR/D3DXVECTOR3 are intentionally NOT defined here to avoid
// collision with ThirdParty\directX headers (CoreServer/Neuz include them).
// ServerDesc.h now handles the fallback directly.
#endif