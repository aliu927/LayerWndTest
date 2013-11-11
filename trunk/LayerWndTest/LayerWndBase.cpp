#include "StdAfx.h"
#include "LayerWndBase.h"
#include "RenderUtility.h"
#include "ResMgr.h"
#include "StaticCtrl.h"
CLayerWndBase::CLayerWndBase(void):
m_pbackgrdDc(NULL),
m_bTrack(FALSE),
m_pLastHoverCtrl(NULL),
m_pDrawCacheDc(NULL),
m_pCloseCtrl(NULL)
{
}

CLayerWndBase::~CLayerWndBase(void)
{
	if(m_pbackgrdDc)
	{
		delete m_pbackgrdDc;
		m_pbackgrdDc = NULL;
	}
}

LRESULT CLayerWndBase::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// TODO: Add your message handler code here and/or call default
	DWORD dwExStyle = GetWindowLong(GWL_EXSTYLE);
	dwExStyle = dwExStyle|WS_EX_LAYERED;
	SetWindowLong(GWL_EXSTYLE, dwExStyle);
	DWORD dwStyle = GetWindowLong(GWL_STYLE);
	dwStyle |= WS_MINIMIZEBOX;
	SetWindowLong(GWL_STYLE,dwStyle);
	//SetMsgHandled(FALSE);
	//////////////////////////////////////////////////////////////////////////
	CPaintDC dc(m_hWnd);
	RECT rct;
	GetClientRect(&rct);
	m_pbackgrdDc = new CCacheDC(dc.m_hDC,rct);
	m_pDrawCacheDc = new CCacheDC(dc.m_hDC,rct);
	ATLASSERT(m_pbackgrdDc != NULL);
	ATLASSERT(m_pDrawCacheDc != NULL);

	InitBkg(rct);
	InitUI(rct);	
	CenterWindow();
	
	PostMessage(WM_PAINT);

	SIZE size = {RECT_WIDTH(rct),RECT_HEIGHT(rct)};
	CRenderUtility::UpdateLayerWnd(m_hWnd,m_pbackgrdDc->m_hDC,size);

	return TRUE;
}

LRESULT CLayerWndBase::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// TODO: Add your message handler code here and/or call default
	return 0;
}

LRESULT CLayerWndBase::OnLButtonDown(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
	// TODO: Add your message handler code here and/or call default
	BOOL bHandleFlag = FALSE;
	for (_ReverseCtrlIterator it = m_arrCtrl.rbegin(); it != m_arrCtrl.rend(); ++ it)
	{
		IControl* pCtrl = (*it).second;
		CPoint point(LOWORD(lParam),HIWORD(lParam));
		if(pCtrl && pCtrl->PtInClient(point))
		{
			pCtrl->OnLButtonDown(wParam,point);
			bHandleFlag = TRUE;
			break;
		}
	}
	if(!bHandleFlag)
	{
		SendMessage(WM_SYSCOMMAND,0xF012,0);
	}
	return 0;
}

LRESULT CLayerWndBase::OnLButtonUp(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
	// TODO: Add your message handler code here and/or call default
	for (_ReverseCtrlIterator it = m_arrCtrl.rbegin(); it != m_arrCtrl.rend(); ++ it)
	{
		IControl* pCtrl = (*it).second;
		CPoint point(LOWORD(lParam),HIWORD(lParam));
		if(pCtrl && pCtrl->PtInClient(point))
		{
			pCtrl->OnLButtonUp(wParam,point);
			break;
		}
	}
	return 0;
}

LRESULT CLayerWndBase::OnMouseMove(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
	// TODO: Add your message handler code here and/or call default
	if(!m_bTrack)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.dwFlags = TME_LEAVE|TME_HOVER;
		tme.hwndTrack = m_hWnd;
		_TrackMouseEvent(&tme);
		m_bTrack = TRUE;
	}
	BOOL bHovered = FALSE;

	for (_ReverseCtrlIterator it = m_arrCtrl.rbegin(); it != m_arrCtrl.rend(); ++ it)
	{
		CPoint pt(LOWORD(lParam),HIWORD(lParam));
		IControl *pc = (*it).second;
		if(pc && pc->PtInClient(pt))
		{
			if(pc != m_pLastHoverCtrl)
			{
				if(m_pLastHoverCtrl)
					m_pLastHoverCtrl->OnMouseLeave();
				m_pLastHoverCtrl = pc;
			}
			else
			{
				pc->OnMouseHover(wParam,pt);
			}
			bHovered = TRUE;
			break;
		}
	}
	//让Hover的子控件失去焦点
	if(!bHovered && m_pLastHoverCtrl) 
	{
		m_pLastHoverCtrl->OnMouseLeave();
	}
	return 0;
}

LRESULT CLayerWndBase::OnMouseLeave( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	m_bTrack = FALSE;
	if(m_pLastHoverCtrl){
		m_pLastHoverCtrl->OnMouseLeave();
	}
	return 0;
}

LRESULT CLayerWndBase::OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// TODO: Add your message handler code here and/or call default
	EndDialog(0);
	return 0;
}

LRESULT CLayerWndBase::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// TODO: Add your message handler code here and/or call default
 	RECT rct;
 	GetClientRect(&rct);
// 
// 	_ControlIterator itr = m_arrCtrl.begin();
// 	_ControlIterator itrEnd = m_arrCtrl.end();
// 	//先绘制背景图
// 	::BitBlt(m_pDrawCacheDc->m_hDC,0,0, RECT_WIDTH(rct),RECT_HEIGHT(rct),m_pbackgrdDc->m_hDC,0,0,SRCCOPY);
// 	while (itr != itrEnd)
// 	{
// 		IControl* pCtrl = itr->second;
// 		if(pCtrl)
// 		{
// 			pCtrl->OnDraw(m_pDrawCacheDc->m_hDC);
// 		}
// 
// 		itr++;
// 	}
	VirtualDraw()	;
	SIZE size = { RECT_WIDTH(rct),RECT_HEIGHT(rct)};
	CRenderUtility::UpdateLayerWnd(m_hWnd,m_pDrawCacheDc->m_hDC,size);
	
#if 0
	HDC hDesktopDc = ::GetDC(GetDesktopWindow());
	BitBlt(hDesktopDc,0,0,size.cx,size.cy,m_pDrawCacheDc->m_hDC,0,0,SRCCOPY);
	BitBlt(hDesktopDc,0,size.cy,size.cx,size.cy,m_pbackgrdDc->m_hDC,0,0,SRCCOPY);
#endif

	return 0;
}

BOOL CLayerWndBase::InitBkg(RECT& rct)
{
	Bitmap bmp(GetImgPathEx(L"bk.png"));
	SetWindowPos(m_hWnd,NULL,0,0,bmp.GetWidth(),bmp.GetHeight());
	CRenderUtility::DrawImage(m_pbackgrdDc->m_hDC,&bmp,rct,rct);

	return TRUE;
}

BOOL CLayerWndBase::InitUI( RECT& rct )
{
	CRect rctClose(rct);
	rctClose.right -= 50;
	rctClose.left = rctClose.right - 27;
	rctClose.bottom = rctClose.top + 26;
	CRect rctOfMin(rctClose);
	rctOfMin.OffsetRect(-27,0);

	m_pCloseCtrl = new CButtonCtrl;
	m_pMinCtrl	 = new CButtonCtrl;
	if(m_pCloseCtrl == NULL || NULL == m_pMinCtrl) return FALSE;

#if 1
	//测试按钮
	CRect rctTstBtn(RECT_WIDTH(rct)/2,RECT_HEIGHT(rct)/2,RECT_WIDTH(rct)/2 + 140,RECT_HEIGHT(rct)/2 + 46);
	CRect rctTstBtn2(rctTstBtn);
	rctTstBtn2.OffsetRect(-50,25);
	CButtonCtrl* pTstBtn = new CButtonCtrl;
	pTstBtn->Create(m_hWnd,rctTstBtn,GetImgPathEx(L"getMedal.png"),this);

	CButtonCtrl* pTstBtn2 = new CButtonCtrl;
	pTstBtn2->Create(m_hWnd,rctTstBtn2,GetImgPathEx(L"getMedal.png"),this);
	m_arrCtrl[pTstBtn->GetCtrlID()] = pTstBtn;
	m_arrCtrl[pTstBtn2->GetCtrlID()] = pTstBtn2;

	//测试文本控件
	CStaticCtrl* pStcCtrl = new CStaticCtrl;
	CRect rctStc(rct);
	rctStc.OffsetRect(RECT_WIDTH(rct)/2 - 300,RECT_HEIGHT(rct)/2 + 100);//
	pStcCtrl->Create(m_hWnd,rctStc,L"测试文本控件",this);
	m_arrCtrl[pStcCtrl->GetCtrlID()] = pStcCtrl;

#endif

	m_pCloseCtrl->Create(m_hWnd,rctClose,GetImgPathEx(L"sys_button_close.png"),this);
	m_pMinCtrl->Create(m_hWnd,rctOfMin,GetImgPathEx(L"sys_button_min.png"),this);
	ATLASSERT(m_pCloseCtrl != NULL && m_pMinCtrl != NULL);

#if 0
	m_pMinCtrl->EnableWindow(FALSE,FALSE);
#endif
	m_arrCtrl[m_pCloseCtrl->GetCtrlID()] = m_pCloseCtrl;
	m_arrCtrl[m_pMinCtrl->GetCtrlID()] = m_pMinCtrl;

	return TRUE;
}

LRESULT CLayerWndBase::OnSysCommand( UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
{
	bHandled = FALSE;
	switch(wParam)
	{
	case SC_RESTORE:
		{
			PostMessage(WM_PAINT);
		}
		break;
	}
	return 0;
}

IControl* CLayerWndBase::GetCtrlByID( unsigned long ulCtrlId )
{
	_ControlIterator itr = m_arrCtrl.find(ulCtrlId);
	if(itr != m_arrCtrl.end()) return itr->second;

	return NULL;
}

void __stdcall CLayerWndBase::OnBtnClicked( UINT uCtrlId )
{
	if(uCtrlId == m_pMinCtrl->GetCtrlID())
	{
		//MessageBox(L"m_pMiniCtrl clicked.");
		m_wndAnimate.Start(m_wndAnimate.CreateWndAnimate(m_hWnd,50,this));
#if 0
		WINDOWPLACEMENT lwndpl;
		GetWindowPlacement(&lwndpl);
		lwndpl.showCmd=SW_SHOWMINIMIZED;
		SetWindowPlacement(&lwndpl);
#endif
	}
	else if(uCtrlId == m_pCloseCtrl->GetCtrlID())
	{
		EndDialog(0);
	}
	else
	{
		IControl* pCtrl = GetCtrlByID(uCtrlId);
		if(NULL == pCtrl) return;
		//pCtrl->ShowWindow(FALSE,TRUE);
	}
}

void __stdcall CLayerWndBase::OnStcClicked( UINT uCtrlId )
{
	CString szInfo;
	szInfo.Format(L"点击 %ld 文本控件",uCtrlId);
	MessageBox(szInfo);
}

void CLayerWndBase::VirtualDraw( HDC hdc )
{
	RECT rct;
	GetClientRect(&rct);

	_ControlIterator itr = m_arrCtrl.begin();
	_ControlIterator itrEnd = m_arrCtrl.end();
	//先绘制背景图
	::BitBlt(hdc?hdc:m_pDrawCacheDc->m_hDC,0,0, RECT_WIDTH(rct),RECT_HEIGHT(rct),m_pbackgrdDc->m_hDC,0,0,SRCCOPY);
	while (itr != itrEnd)
	{
		IControl* pCtrl = itr->second;
		if(pCtrl)
		{
			pCtrl->OnDraw(hdc?hdc:m_pDrawCacheDc->m_hDC);
		}
		itr++;
	}
}

LRESULT CLayerWndBase::OnPrintWindow( UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	VirtualDraw(HDC(wParam));
	return S_OK;
}
