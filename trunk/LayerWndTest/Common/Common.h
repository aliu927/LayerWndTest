#pragma once

class CCommon
{
public:
	static BOOL SnapWnd(HWND hWnd,HBITMAP& hBmp);
	/* format È¡ÖµÎª£ºimage/bmp image/jpeg image/gif image/tiff image/png */
	static BOOL GetEncoderClsid( const WCHAR* format, CLSID* pClsid );
	static BOOL SavePicture(const HBITMAP& hbmp, LPCTSTR lpszType,LPCTSTR lpszFileName);
};
