#ifndef _AFXDISP_H_
#define _AFXDISP_H_
#include <afx.h>
#include <afxwin.h>
class COleDateTime : public CObject {
public:
    enum DateTimeStatus { valid=0, invalid=1, null=2 };
    COleDateTime() {}
    COleDateTime(const COleDateTime&) {}
    COleDateTime(time_t) {}
    COleDateTime(int,int,int,int,int,int) {}
    BOOL GetAsSystemTime(SYSTEMTIME&) const { return FALSE; }
    DateTimeStatus GetStatus() const { return valid; }
    int GetDay() const { return 1; }
    int GetMonth() const { return 1; }
    int GetYear() const { return 2024; }
    int GetHour() const { return 0; }
    int GetMinute() const { return 0; }
    int GetSecond() const { return 0; }
    CString Format(LPCTSTR = nullptr) const { return CString(); }
    CString Format(UINT) const { return CString(); }
};
class COleDateTimeSpan {
public:
    COleDateTimeSpan() {}
    double GetTotalDays() const { return 0; }
};
#endif