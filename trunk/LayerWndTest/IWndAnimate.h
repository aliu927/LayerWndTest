#pragma once
#include "IControl.h"
#include <map>
class CLayerWndBase;
using namespace std;
class IWndAnimate
{
public:
	virtual UINT __stdcall CreateWndAnimate(HWND hWnd,UINT uElapse,CLayerWndBase* pthis) = 0;
	virtual BOOL __stdcall Start(UINT uAnimateId) = 0;
	virtual void __stdcall Stop(UINT uAnimateId) = 0;
};

class CWndAnimate:
	public IWndAnimate,
	public CObjBase
{
public:
	CWndAnimate();
	virtual UINT __stdcall CreateWndAnimate(HWND hWnd,UINT uElapse,CLayerWndBase*pthis);
	virtual BOOL __stdcall Start(UINT uAnimateId);
	virtual void __stdcall Stop(UINT uAnimateId);
	void __stdcall OnTimer(UINT uEventId);
private:
	struct _AnimParams
	{
		_AnimParams():_hWnd(NULL),_uTimerId(0),_uElapse(0)
		{

		}
		_AnimParams(HWND hWnd,UINT uId,UINT uElapse):_hWnd(hWnd),_uTimerId(uId),_uElapse(uElapse)
		{

		}
		HWND _hWnd;
		UINT _uTimerId;
		UINT _uElapse;
	};
	typedef map<UINT,_AnimParams> animate_map;
	typedef animate_map::iterator animate_iter;
	animate_map _animate_map;
	CLayerWndBase* m_pLayerWnd;
	Image* m_pImage;
};