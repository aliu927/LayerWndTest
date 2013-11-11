#pragma once
#include "icontrol.h"
enum
{
	STATUS_STC_NORMAL,
	STATUS_STC_HOVER
};
class CStaticCtrl :
	public CControlBase
{
public:
	CStaticCtrl(void);
	~CStaticCtrl(void);
	virtual void __stdcall SetWindowText(LPCTSTR lpszText);
	virtual void __stdcall OnDraw(HDC hdc);
	virtual void __stdcall OnMouseHover(UINT nFlags, CPoint point);
	virtual void __stdcall OnMouseLeave();

	virtual void __stdcall OnLButtonDown(UINT nFlags, CPoint point);
	virtual void __stdcall OnLButtonUp(UINT nFlags, CPoint point);
	BOOL Create(HWND& hWnd,RECT& rct,LPCTSTR lpszText,ICtrlCallback*pCallback = FALSE,BOOL bIsAutoSize = TRUE);
private:
	CString m_strWndText;
	HDC m_hDc;
	UINT m_uStcState;
	BOOL m_bPress;
	ICtrlCallback* m_pCallback;
};
