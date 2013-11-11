#include "StdAfx.h"
#include "GdiplusInstance.h"

CGdiplusInstance::CGdiplusInstance(void)
{
	GdiplusStartupInput gdiplusStartupInput = NULL;
	GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);
}

CGdiplusInstance::~CGdiplusInstance(void)
{
	GdiplusShutdown(m_gdiplusToken);
	m_gdiplusToken = NULL;
}
