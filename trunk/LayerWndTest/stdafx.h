// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#pragma once

// Change these values to use different versions
#define WINVER		0x0500
#define _WIN32_WINNT	0x0501
#define _WIN32_IE	0x0501
#define _RICHEDIT_VER	0x0200

#include <atlbase.h>
#include <atlapp.h>
#include <atlmisc.h>
extern CAppModule _Module;

#include <atlwin.h>
#include <utility>
#include <Gdiplus.h>
using namespace Gdiplus;
using namespace std;
#pragma comment(lib, "Gdiplus.lib")

#define RECT_WIDTH(rct) (rct.right - rct.left)
#define RECT_HEIGHT(rct) (rct.bottom - rct.top)
#if defined _M_IX86
  #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
  #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
  #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
  #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
template<class T>
class CSingletonT
{
public:
	static T* GetInstance()
	{
		static T g_Instance;
		return &g_Instance;	
	}
protected:
	CSingletonT(){}
private:
	CSingletonT(const T& rhs);
	CSingletonT& operator =(const T& rhs);
};
#define SINGLETON(T) friend CSingletonT<T>