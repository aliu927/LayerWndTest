#include "StdAfx.h"
#include "CacheDC.h"

CCacheDC::CCacheDC(HDC hDC, RECT& rcPaint):
m_hOriginal(hDC),
m_rcPaint(rcPaint)
{
	CreateCompatibleDC(m_hOriginal);
	ATLASSERT(m_hDC != NULL);

	HBITMAP hBmp = CreateCompatibleBitmap(hDC,RECT_WIDTH(rcPaint),RECT_HEIGHT(rcPaint));
	m_hCanvasBmp.Attach(hBmp);
	ATLASSERT(m_hCanvasBmp.m_hBitmap != NULL);

	m_hOldBmp = SelectBitmap(m_hCanvasBmp);
}

CCacheDC::~CCacheDC(void)
{
	::BitBlt(m_hOriginal,m_rcPaint.left,m_rcPaint.top,RECT_WIDTH(m_rcPaint),RECT_HEIGHT(m_rcPaint),m_hDC,m_rcPaint.left,m_rcPaint.top,SRCCOPY);
	SelectBitmap(m_hOldBmp);
}

CCacheDC::operator HDC()
{
	return m_hDC;
}
