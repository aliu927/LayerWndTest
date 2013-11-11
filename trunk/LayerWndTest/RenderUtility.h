#pragma once

class CRenderUtility
{
public:
	static void DrawImage(HDC hDC, Image* pImage, RECT &rctDst, RECT&rctSrc, int nAlpha = 255 );
	//
	static void DrawText(HDC hDC,LPCTSTR lpszText,RECT& rctSrc,COLORREF color= RGB(0,0,0),
		LPCTSTR lpszFontFamily =L"Î¢ÈíÑÅºÚ",int nFontSize = 12,DWORD dwAlignStyle = SS_CENTER,DWORD dwFontStyle = FontStyleRegular, int nAlpha = 255);
	static CSize GetTextSize( HDC hDC, LPCTSTR lpszText);
	static void UpdateLayerWnd(HWND& hWnd,HDC& hSrcDc,SIZE& size);
};