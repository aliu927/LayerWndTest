#include "StdAfx.h"
#include "IControl.h"
#include "GenerateCtrlID.h"


CControlBase::CControlBase():
m_bEnable(TRUE),
m_bVisble(TRUE)
{

}

void __stdcall CControlBase::OnMouseHover( UINT nFlags, CPoint point )
{
	return;
}

void __stdcall CControlBase::OnDraw( HDC hdc )
{
	return;
}

BOOL __stdcall CControlBase::PtInClient( CPoint point )
{
	return m_rctClient.PtInRect(point);
}

void CControlBase::SetClientRct( CRect& rct )
{
	m_rctClient = rct;
}

void __stdcall CControlBase::OnMouseLeave( void )
{
	return;
}

void __stdcall CControlBase::OnLButtonDown( UINT nFlags, CPoint point )
{
	return ;
}

void __stdcall CControlBase::OnLButtonUp( UINT nFlags, CPoint point )
{
	return;
}

void CControlBase::OnCreate()
{
	m_uCtrlId = GetCtrlIDEx();
}

unsigned long CControlBase::GetCtrlID()
{
	return m_uCtrlId;
}

BOOL __stdcall CControlBase::IsEnableWindow()
{
	return m_bEnable;
}

BOOL __stdcall CControlBase::IsShowWindow()
{
	return m_bVisble;
}

void __stdcall CControlBase::SetWindowText( LPCTSTR lpszText )
{
	
}

void __stdcall CControlBase::ShowWindow( BOOL bShow, BOOL bRedraw /*= FALSE*/ )
{
	m_bVisble = bShow;
	if(bRedraw)
	{
		PostMessage(m_hParentWnd,WM_PAINT,NULL,NULL);
	}
}

void __stdcall CControlBase::EnableWindow( BOOL bEnable, BOOL bRedraw /*= FALSE*/ )
{
	m_bEnable = bEnable;

	if(bRedraw)
	{
		PostMessage(m_hParentWnd,WM_PAINT,NULL,NULL);
	}
}

void __stdcall CControlBase::OnTimer( UINT uEventId )
{

}

HWND __stdcall CControlBase::GetHWnd()
{
	return m_hParentWnd;
}
	