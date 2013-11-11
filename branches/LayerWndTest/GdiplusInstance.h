#pragma once

class CGdiplusInstance
{
public:
	CGdiplusInstance(void);
	~CGdiplusInstance(void);
private:
	ULONG_PTR m_gdiplusToken;
};
