#pragma once
#include "IControl.h"
enum
{
	STATUS_NORMAL = 0,
	STATUS_HOVERED,
	STATUS_PRESSED,
	STATUS_DISABLED,
};
class CButtonCtrl :public CControlBase
{
public:
	CButtonCtrl();
	~CButtonCtrl(void);
	BOOL Create(HWND& hWnd,CRect& rct,const CString& szName,ICtrlCallback*pCallback,int nStatusCnts = 4,BOOL bIsAuotSize = TRUE);
	virtual void __stdcall OnDraw(HDC hdc);
	virtual void __stdcall OnMouseHover(UINT nFlags, CPoint point);
	virtual void __stdcall OnMouseLeave();
	virtual void __stdcall OnLButtonDown(UINT nFlags, CPoint point);
	virtual void __stdcall OnLButtonUp(UINT nFlags, CPoint point);
private:
	Bitmap* m_pBkgbmp;
	int m_nBkgWidth;
	int m_nBkgHeight;
	int m_nBtnStatus;
	int m_nStatusCnts;
	BOOL m_bPress;
	ICtrlCallback* m_pCtrlCallback;
};
