// stdafx.cpp : source file that includes just the standard includes
//	LayerWndTest.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include "GdiplusInstance.h"

CGdiplusInstance g_GdiplusInit;
#if (_ATL_VER < 0x0700)
#include <atlimpl.cpp>
#endif //(_ATL_VER < 0x0700)

