#include "StdAfx.h"
#include "StaticCtrl.h"

CStaticCtrl::CStaticCtrl(void):
m_hDc(NULL),
m_uStcState(STATUS_STC_NORMAL),
m_bPress(FALSE),
m_pCallback(NULL)
{
}

CStaticCtrl::~CStaticCtrl(void)
{
}

void __stdcall CStaticCtrl::SetWindowText( LPCTSTR lpszText )
{
	m_strWndText = lpszText;
}

void __stdcall CStaticCtrl::OnDraw( HDC hdc )
{
	if(m_strWndText.IsEmpty()) return;
	
	switch (m_uStcState)
	{
	case STATUS_STC_NORMAL:
		{
			CRenderUtility::DrawText(hdc,m_strWndText,m_rctClient);
		}
		break;
	case STATUS_STC_HOVER:
		{
			CRenderUtility::DrawText(hdc,m_strWndText,m_rctClient,RGB(105,105,255));
		}
		break;
	}
}

BOOL CStaticCtrl::Create( HWND& hWnd,RECT& rct,LPCTSTR lpszText,ICtrlCallback*pCallback /*= FALSE*/,BOOL bIsAutoSize/* = TRUE*/ )
{
	if(NULL == hWnd) return FALSE;
	CControlBase::OnCreate();

	m_hParentWnd = hWnd;
	m_pCallback = pCallback;
	if(bIsAutoSize)
	{
		m_rctClient = rct;
		m_hDc = GetDC(hWnd);
		CSize size = CRenderUtility::GetTextSize(m_hDc,lpszText);
		ReleaseDC(hWnd,m_hDc);
		m_rctClient.right = m_rctClient.left + size.cx;
		m_rctClient.bottom = m_rctClient.top + size.cy;
	}
	else
	{
		m_rctClient = rct;
	}
	m_strWndText = lpszText;

	return TRUE;
}

void __stdcall CStaticCtrl::OnMouseHover( UINT nFlags, CPoint point )
{
	SetCursor(LoadCursor(NULL, IDC_HAND));
	m_uStcState = STATUS_STC_HOVER;
	PostMessage(m_hParentWnd,WM_PAINT,NULL,NULL);
}

void __stdcall CStaticCtrl::OnMouseLeave()
{
	SetCursor(LoadCursor(NULL, IDC_ARROW));
	m_uStcState = STATUS_STC_NORMAL;
	PostMessage(m_hParentWnd,WM_PAINT,NULL,NULL);
}

void __stdcall CStaticCtrl::OnLButtonDown( UINT nFlags, CPoint point )
{
	m_bPress = TRUE;
}

void __stdcall CStaticCtrl::OnLButtonUp( UINT nFlags, CPoint point )
{
	if(!m_bPress || NULL == m_pCallback) return;
	m_bPress = FALSE;
	m_pCallback->OnStcClicked(m_uCtrlId);	
}
