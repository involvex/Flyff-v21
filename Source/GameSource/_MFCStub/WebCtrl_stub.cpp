#include <windows.h>
#include "..\Neuz\WebCtrl.h"
// Stub implementations for ReleaseDll build where WebCtrl.cpp is excluded (IE WebBrowser control not needed)
CWebCtrl::CWebCtrl(HWND h) : m_hWnd(h), m_cxScroll(0), m_cyScroll(0), m_pContainer(nullptr), m_pweb(nullptr), m_cxWidth(0), m_cxHeight(0) { memset(&m_Va,0,sizeof(m_Va)); }
void CWebCtrl::Navigate(char*, char*, char*) {}
void CWebCtrl::ShowScroll(BOOL) {}
bool WINAPI InitWebCtrl() { return true; }
bool WINAPI UninitWebCtrl() { return true; }
LRESULT CALLBACK WebCtrlProc(HWND, UINT, WPARAM, LPARAM) { return 0; }
LRESULT CWebCtrl::WebCtrlProc(UINT, WPARAM, LPARAM) { return 0; }
