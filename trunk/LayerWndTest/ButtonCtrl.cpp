#include "StdAfx.h"
#include "ButtonCtrl.h"
CButtonCtrl::CButtonCtrl():
m_nBkgWidth(0),
m_nBkgHeight(0),
m_pBkgbmp(NULL),
m_nStatusCnts(0)
{
	
}

CButtonCtrl::~CButtonCtrl(void)
{
}

void __stdcall CButtonCtrl::OnDraw( HDC hdc )
{
	if(!m_bVisble || NULL == hdc || m_pBkgbmp == NULL) return ;

	if(!m_bEnable) m_nBtnStatus = STATUS_DISABLED;

	const int nCurWidth = m_nBkgWidth/m_nStatusCnts;
	CRect rctSrc(0,0,nCurWidth,m_nBkgHeight);
	rctSrc.OffsetRect(m_nBtnStatus * nCurWidth,0);

	CRenderUtility::DrawImage(hdc,m_pBkgbmp,m_rctClient,rctSrc);
}

BOOL CButtonCtrl::Create( HWND& hWnd,CRect& rct,const CString& szName,ICtrlCallback*pCallback,int nStatusCnts /*= 4*/,BOOL bIsAuotSize )
{
	if(NULL == hWnd || rct.IsRectNull()|| szName.IsEmpty() || nStatusCnts <= 0) return FALSE;
	CControlBase::OnCreate();

	m_hParentWnd = hWnd;
	m_pBkgbmp = new Bitmap(szName);

	if(bIsAuotSize && m_pBkgbmp)
	{
		m_rctClient = rct;
		m_rctClient.right = m_rctClient.left + m_pBkgbmp->GetWidth()/nStatusCnts;
		m_rctClient.bottom = m_rctClient.top + m_pBkgbmp->GetHeight();
	}
	else
	{
		m_rctClient = rct;
	}

	m_nBtnStatus = STATUS_NORMAL;
	m_nStatusCnts = nStatusCnts;
	if(NULL == m_pBkgbmp || NULL == pCallback) return FALSE;
	
	m_pCtrlCallback = pCallback;
	m_nBkgWidth = m_pBkgbmp->GetWidth();
	m_nBkgHeight = m_pBkgbmp->GetHeight();
	
	return TRUE;
}

void __stdcall CButtonCtrl::OnMouseHover( UINT nFlags, CPoint point )
{
	m_nBtnStatus = STATUS_HOVERED;
	::PostMessage(m_hParentWnd,WM_PAINT,0,0);
}

void __stdcall CButtonCtrl::OnMouseLeave()
{
	m_nBtnStatus = STATUS_NORMAL;
	::PostMessage(m_hParentWnd,WM_PAINT,0,0);
}

void __stdcall CButtonCtrl::OnLButtonDown( UINT nFlags, CPoint point )
{
	if(!m_bEnable) return;

	m_bPress = TRUE;
	m_nBtnStatus = STATUS_PRESSED;
	::PostMessage(m_hParentWnd,WM_PAINT,0,0);
}

void __stdcall CButtonCtrl::OnLButtonUp( UINT nFlags, CPoint point )
{
	if(!m_bEnable || !m_bPress || NULL == m_pCtrlCallback) return;

	m_nBtnStatus = STATUS_NORMAL;
	m_bPress = FALSE;
	::PostMessage(m_hParentWnd,WM_PAINT,0,0);
	//点击事件：可以以消息方式简单处理；或者是回调；
	m_pCtrlCallback->OnBtnClicked(m_uCtrlId);
	//	
}
