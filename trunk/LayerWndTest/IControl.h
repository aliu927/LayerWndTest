#pragma once
#include "RenderUtility.h"
class CObjBase
{
public:
	virtual HWND __stdcall GetHWnd()
	{
		return NULL;
	}
	virtual void __stdcall OnTimer(UINT uEventId)
	{

	}
};
class IControl
{
public:

	//
	virtual void __stdcall OnMouseHover(UINT nFlags, CPoint point) = 0;
	virtual void __stdcall OnMouseLeave(void) = 0;
	virtual void __stdcall OnLButtonDown(UINT nFlags, CPoint point) = 0;
	virtual void __stdcall OnLButtonUp(UINT nFlags, CPoint point) = 0;
	virtual void __stdcall OnDraw(HDC hdc) = 0;
	//
	virtual BOOL __stdcall PtInClient(CPoint point) = 0;
	virtual void __stdcall ShowWindow( BOOL bShow, BOOL bRedraw = FALSE) = 0;
	virtual void __stdcall EnableWindow(BOOL bEnable,  BOOL bRedraw = FALSE) = 0;
	virtual BOOL __stdcall IsEnableWindow() = 0;
	virtual BOOL __stdcall IsShowWindow() = 0;
	virtual void __stdcall SetWindowText(LPCTSTR lpszText) = 0;
	virtual void __stdcall OnTimer(UINT uEventId) = 0;
};

class ICtrlCallback
{
public:
	virtual void __stdcall OnBtnClicked(UINT uCtrlId) = 0;
	virtual void __stdcall OnStcClicked(UINT uCtrlId) = 0;
};
class CCtrlCallback : public ICtrlCallback
{
	virtual void __stdcall OnBtnClicked(UINT uCtrlId)
	{
		return;
	}
	virtual void __stdcall OnStcClicked(UINT uCtrlId)
	{
		return;
	}
};

class CControlBase:
	public IControl,
	public CObjBase
{
public:
	CControlBase();
	virtual void __stdcall OnMouseHover(UINT nFlags, CPoint point);
	virtual void __stdcall OnMouseLeave(void);
	virtual void __stdcall OnLButtonDown(UINT nFlags, CPoint point);
	virtual void __stdcall OnLButtonUp(UINT nFlags, CPoint point);
	virtual void __stdcall OnDraw(HDC hdc);
	virtual BOOL __stdcall PtInClient(CPoint point);
	virtual void __stdcall ShowWindow( BOOL bShow, BOOL bRedraw = FALSE);
	virtual void __stdcall EnableWindow(BOOL bEnable,  BOOL bRedraw = FALSE);
	virtual BOOL __stdcall IsEnableWindow();
	virtual BOOL __stdcall IsShowWindow();
	virtual void __stdcall SetWindowText(LPCTSTR lpszText);
	virtual void __stdcall OnTimer(UINT uEventId);

	HWND __stdcall GetHWnd();
	//
	void SetClientRct(CRect& rct);
	void OnCreate();
	unsigned long GetCtrlID();
protected:
	CRect m_rctClient;
	HWND m_hParentWnd;
	unsigned long m_uCtrlId;
	BOOL m_bEnable;
	BOOL m_bVisble;
};
