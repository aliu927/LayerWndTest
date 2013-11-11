#pragma once

class CCacheDC : public CDC
{
public:
	CCacheDC(HDC hDC, RECT& rcPaint);
	~CCacheDC(void);
	 operator HDC();
private:
	HDC m_hOriginal;
	RECT m_rcPaint;
	CBitmap m_hCanvasBmp;
	HBITMAP m_hOldBmp;
};
