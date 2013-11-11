#include "StdAfx.h"
#include "Common.h"

BOOL CCommon::SnapWnd( HWND hWnd ,HBITMAP& hBmp)
{
	if(!IsWindowVisible(hWnd)) return FALSE;

	RECT rct;
	GetClientRect(hWnd,&rct);
	HDC hDesktopDc = GetDC(GetDesktopWindow());
	HDC hMemDc = CreateCompatibleDC(hDesktopDc);
	HBITMAP hMemBmp = CreateCompatibleBitmap(hDesktopDc,RECT_WIDTH(rct),RECT_HEIGHT(rct));
	if(NULL == hDesktopDc || NULL == hMemDc || NULL == hMemBmp) return FALSE;

	HBITMAP hOldBmp = (HBITMAP)SelectObject(hMemDc,hMemBmp);
	SendMessage(hWnd, WM_PRINTCLIENT, (WPARAM)hMemDc, PRF_CLIENT|PRF_ERASEBKGND|PRF_NONCLIENT|PRF_CHILDREN); 
	//BOOL bIsPrinted = PrintWindow(hWnd,hMemDc,PW_CLIENTONLY);
#if 1
	CCommon::SavePicture(hMemBmp,L"image/bmp",L"C:\\c.bmp");
#endif
	//hBmp = (HBITMAP)SelectObject(hMemDc,hOldBmp);
	hMemBmp = hBmp;
	DeleteDC(hDesktopDc);
	DeleteDC(hMemDc);
	DeleteObject(hMemBmp);
	DeleteObject(hOldBmp);

	return TRUE;
}

BOOL CCommon::GetEncoderClsid( const WCHAR* format, CLSID* pClsid )
{
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes

	ImageCodecInfo* pImageCodecInfo = NULL;

	GetImageEncodersSize(&num, &size);
	if(size == 0)
		return FALSE;  // Failure

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if(pImageCodecInfo == NULL)
		return FALSE;  // Failure

	GetImageEncoders(num, size, pImageCodecInfo);

	for(UINT j = 0; j < num; ++j)
	{
		if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return TRUE;  // Success
		}    
	}

	free(pImageCodecInfo);
	return FALSE;  // Failure 
}

BOOL CCommon::SavePicture( const HBITMAP& hbmp,LPCTSTR lpszType,LPCTSTR lpszFileName )
{
	if(NULL == hbmp || lpszType ==  NULL || lpszFileName == NULL) return FALSE;

	CLSID bmpClsid;
	if(!GetEncoderClsid(lpszType,&bmpClsid)) return FALSE;
	Bitmap bitmap(hbmp,NULL);
	int nStatus = bitmap.Save(lpszFileName,&bmpClsid,NULL);

	return nStatus == 0;
}

 