#pragma once
#include "IControl.h"
#include "stdafx.h"
#include <map>
struct _TimerParams
{
	_TimerParams():_pObj(NULL),_uElapse(0)
	{

	}
	_TimerParams(CObjBase*pObj,UINT uElapse):_pObj(pObj),_uElapse(uElapse)
	{

	}
	CObjBase* _pObj;
	UINT _uElapse;
};
typedef std::map<UINT, _TimerParams>           _ControlMap;
typedef std::map<UINT, _TimerParams>::iterator _ItControl;

class CControlTimer:
	public CSingletonT<CControlTimer>
{
private:
    CControlTimer(void);
    ~CControlTimer(void);

    void OnTimer(UINT_PTR nIDEvent);
public:
	SINGLETON(CControlTimer);
    UINT SetControlTimer(CObjBase* pCtrl, UINT uElapse);
	BOOL Start(UINT uEventId);
	void SetHWnd(HWND hWnd){m_hWnd = hWnd;}
	BOOL Stop(UINT uEventId);
    BOOL KillTimer(UINT_PTR nIDEvent);

    static VOID _stdcall TimerProc( HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime );
    static CControlTimer* m_pThis;
    static CControlTimer* GetInstance(void);
private:
	void KillAllTimer();

private:
    _ControlMap  m_ctrlMap;
	HWND m_hWnd;
};

#define GetTimerMgr() CControlTimer::GetInstance()
