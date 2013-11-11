#include "StdAfx.h"
#include "IWndAnimate.h"
#include "GenerateCtrlID.h"
#include "ControlTimer.h"
#include "RenderUtility.h"
#include "LayerWndBase.h"
#include "Common/Common.h"
//////////////////////////////////////////////////////////////////////////
CWndAnimate::CWndAnimate():
m_pImage(NULL)
{

}

UINT __stdcall CWndAnimate::CreateWndAnimate( HWND hWnd ,UINT uElapse,CLayerWndBase*pthis)
{
	if(NULL == hWnd || 0 >= uElapse) return 0;
	
	UINT uAnimateId = GetEventIDEx();
	GetTimerMgr()->SetHWnd(hWnd);
	UINT uTimerId = GetTimerMgr()->SetControlTimer(this,uElapse);

	_animate_map[uAnimateId] = _AnimParams(hWnd,uTimerId,uElapse);
 	m_pLayerWnd = pthis;

	//НиЭМ
	HBITMAP hSnapBmp = NULL;
	CCommon::SnapWnd(hWnd,hSnapBmp);
// 	m_pImage = new Bitmap(hSnapBmp,NULL);
// 	
// 	CLSID bmpClsid;
// 	CCommon::GetEncoderClsid(L"image/bmp",&bmpClsid);
// 	int nRet = m_pImage->Save(L"C:\\b.bmp",&bmpClsid);
#if 1
	CCommon::SavePicture(hSnapBmp,L"image/bmp",L"C:\\b.bmp");
#endif
	return uAnimateId;
}

BOOL __stdcall CWndAnimate::Start( UINT uAnimateId )
{
	animate_iter itr = _animate_map.find(uAnimateId);
	
	if(itr != _animate_map.end())
	{
		return GetTimerMgr()->Start(itr->second._uTimerId);
	}
	return FALSE;
}

void __stdcall CWndAnimate::Stop( UINT uAnimateId )
{
	animate_iter itr = _animate_map.find(uAnimateId);

	if(itr != _animate_map.end())
	{
		GetTimerMgr()->Stop(itr->second._uTimerId);
	}
}

void __stdcall CWndAnimate::OnTimer( UINT uTimerId )
{
	animate_iter itr = _animate_map.begin();
	animate_iter itrEnd = _animate_map.end();

	while(itrEnd != itr)
	{
		if(itr->second._uTimerId == uTimerId)
		{
			break;
		}
		itr++;
	}

	if(itr == itrEnd) return;

	_AnimParams tmpParams = itr->second;
	CRect rctOfWnd;
	HWND hWnd = tmpParams._hWnd;
	GetClientRect(hWnd,&rctOfWnd);
	int nWidth = rctOfWnd.Width();
	int nHeight = rctOfWnd.Height();

	if(nWidth <=0 || nHeight <=0 ) GetTimerMgr()->Stop(uTimerId);

	static float fScalefactor = 1;

	fScalefactor -= 0.001f;

	int nCenterX = nWidth/2;
	int nCenterY = nHeight/2;

	int nfWidth = (int)(nWidth * fScalefactor);
	int nfHeight = (int)(nHeight * fScalefactor);

	HDC hDc = ::GetDC(hWnd);
	CPaintDC dc(hWnd);

	HDC hSrcDc = CreateCompatibleDC(hDc);
	HBITMAP hBmp = CreateCompatibleBitmap(hDc,nWidth,nHeight);
	SelectObject(hSrcDc,(HBITMAP)hBmp);

	Graphics grahics(hSrcDc);
	Rect rcDst(nCenterX - (int)nfWidth/2,nCenterY - (int)nfHeight/2,nfWidth,nfHeight);
	grahics.DrawImage(m_pImage,rcDst,0,0,nWidth,nHeight,UnitPixel);
	//m_pLayerWnd->VirtualDraw(hSrcDc);
	//PrintWindow(hWnd,hSrcDc,0);

	//StretchBlt(hSrcDc,nCenterX - (int)nfWidth/2,nCenterY - (int)nfHeight/2,nfWidth,nfHeight,hSrcDc,0,0,nWidth,nHeight,SRCCOPY);
#if 0
	HDC hDesktopDc = GetDC(GetDesktopWindow());
	BitBlt(hDesktopDc,0,0,nWidth,nHeight,hSrcDc,0,0,SRCCOPY);
#endif
	SIZE size;
	size.cx = nfWidth;//rctOfWnd.Width();
	size.cy = nfHeight;//rctOfWnd.Height();
	CRenderUtility::UpdateLayerWnd(hWnd,hSrcDc,size);
	::ReleaseDC(hWnd,hDc);
	::DeleteDC(hDc);
	::DeleteDC(hSrcDc);
	//DeleteDC(hDesktopDc);
	::DeleteObject(hBmp);
}
