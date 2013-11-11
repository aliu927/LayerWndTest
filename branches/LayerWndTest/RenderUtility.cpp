#include "StdAfx.h"
#include "RenderUtility.h"

void CRenderUtility::DrawImage( HDC hDC, Image* pImage, RECT &rctDst, RECT&rctSrc, int nAlpha /*= 255*/ )
{
	if(pImage == NULL || nAlpha == 0) return;

	float fAlpha = (float)nAlpha / 255.0f;
	Graphics	graph(hDC);
	ColorMatrix colorMatrix={1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, fAlpha, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

	ImageAttributes imgAtt;
	imgAtt.SetColorMatrix(&colorMatrix);

	Rect rcDst(rctDst.left, rctDst.top, RECT_WIDTH(rctDst), RECT_HEIGHT(rctDst));
	graph.DrawImage(pImage, rcDst, rctSrc.left, rctSrc.top, RECT_WIDTH(rctSrc), RECT_HEIGHT(rctSrc), UnitPixel, &imgAtt);
}

void CRenderUtility::UpdateLayerWnd( HWND& hWnd,HDC& hSrcDc,SIZE& size )
{
	if(NULL == hWnd || !::IsWindow(hWnd)) return;

	BLENDFUNCTION blend = { 0 };  
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.AlphaFormat = AC_SRC_ALPHA;
	blend.SourceConstantAlpha = 255;

	POINT ptSrc = { 0 };
	POINT ptDest = { 0 };
	HDC hDstDc = ::GetDC(hWnd);


	RECT rtWindowRect = { 0 };
	::GetWindowRect(hWnd,&rtWindowRect);
	ptDest.x = rtWindowRect.left;
	ptDest.y = rtWindowRect.top;

	//SIZE size = { RECT_WIDTH(rct),RECT_HEIGHT(rct)};
	UpdateLayeredWindow(hWnd,hDstDc,&ptDest,&size,hSrcDc,&ptSrc,NULL,&blend,ULW_ALPHA);
	::DeleteDC(hDstDc);
}

void CRenderUtility::DrawText( HDC hDC,LPCTSTR lpszText,RECT& rctSrc,COLORREF color/*= RGB(0,0,0)*/, LPCTSTR lpszFontFamily /*=L"Î¢ÈíÑÅºÚ"*/,int nFontSize /*= 12*/,DWORD dwAlignStyle /*= SS_CENTER*/,DWORD dwFontStyle /*= FontStyleRegular*/, int nAlpha /*= 255*/ )
{
	if(0 == nAlpha || NULL == lpszText) return;

	Graphics graphics(hDC);
	FontFamily fontFamily(lpszFontFamily);
	FontStyle fontStyle = (FontStyle)dwFontStyle;

	Gdiplus::Font font(&fontFamily,(float)nFontSize,fontStyle,UnitPixel);
	RectF rcText((float)rctSrc.left,(float)rctSrc.top,(float)RECT_WIDTH(rctSrc),(float)RECT_HEIGHT(rctSrc));
	SolidBrush brush(Color(nAlpha,GetRValue(color),GetGValue(color),GetBValue(color)));
	StringFormat txtFormat;
	if(dwAlignStyle & SS_CENTERIMAGE)
	{
		txtFormat.SetLineAlignment(StringAlignmentCenter);
	}
	if(dwAlignStyle & SS_CENTER){
		txtFormat.SetAlignment(StringAlignmentCenter);
	}
	else if(dwAlignStyle & SS_RIGHT){
		txtFormat.SetFormatFlags(StringFormatFlagsDirectionRightToLeft);
		txtFormat.SetAlignment(StringAlignmentNear);
	}

	graphics.DrawString(lpszText,-1,&font,rcText,&txtFormat,&brush);
}

CSize CRenderUtility::GetTextSize( HDC hDC, LPCTSTR lpszText )
{
	Graphics	graph(hDC);
	FontFamily	fontFamily(L"Î¢ÈíÑÅºÚ");
	FontStyle fontStyle = FontStyleRegular;
	
	Gdiplus::Font		font(&fontFamily, 12, fontStyle, UnitPixel);

	StringFormat textFormat;
	PointF pt(0.0f, 0.0f);
	RectF  rcSize;
	CSize  szRet;
	graph.MeasureString(lpszText, -1, &font, pt, &textFormat, &rcSize);


	szRet.cx = static_cast<int>(rcSize.Width) + 1;
	szRet.cy = static_cast<int>(rcSize.Height) + 1;

	return szRet;
}
