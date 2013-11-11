#include "StdAfx.h"
#include "ControlTimer.h"
#include "GenerateCtrlID.h"
CControlTimer* CControlTimer::m_pThis = NULL;

CControlTimer::CControlTimer(void):m_hWnd(NULL)
{
}

CControlTimer::~CControlTimer(void)
{
    KillAllTimer();
}


UINT CControlTimer::SetControlTimer( CObjBase* pCtrl, UINT uElapse )
{
    if(pCtrl == NULL) return 0;

    if(m_pThis == NULL)
    {
        m_pThis = this;
    }

    UINT uId = GetEventIDEx();  
	m_ctrlMap.insert(pair<UINT, _TimerParams>(uId, _TimerParams(pCtrl,uElapse)));	
    return uId;
}

void CControlTimer::OnTimer( UINT_PTR nIDEvent )
{
    _ItControl it = m_ctrlMap.find(nIDEvent);
    if( it == m_ctrlMap.end()) return;

    _TimerParams timerParams = it->second;
    if(timerParams._pObj){
        timerParams._pObj->OnTimer(nIDEvent);
    }
}

BOOL CControlTimer::KillTimer( UINT_PTR nIDEvent )
{
    _ItControl it = m_ctrlMap.find(nIDEvent);
    if( it != m_ctrlMap.end()){
        m_ctrlMap.erase(nIDEvent);
    }
    return ::KillTimer(NULL, nIDEvent);
}

void CControlTimer::KillAllTimer()
{
	_ItControl iter1 = m_ctrlMap.begin();
	_ItControl iter2 = m_ctrlMap.end();
	while(iter1 != iter2)
	{
		::KillTimer(NULL, iter1->first);
		++iter1;
	}
	m_ctrlMap.clear();
}

CControlTimer* CControlTimer::GetInstance( void )
{
    static CControlTimer g_ctrlTimer;
    return &g_ctrlTimer;
}

VOID _stdcall CControlTimer::TimerProc( HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime )
{
    if(m_pThis){
        m_pThis->OnTimer(idEvent);
    }
}

BOOL CControlTimer::Start( UINT uEventId )
{
	_ItControl itr = m_ctrlMap.find(uEventId);

	if(itr != m_ctrlMap.end())
	{
		_TimerParams timerParmas(itr->second);
		::SetTimer(m_hWnd, uEventId,timerParmas._uElapse, TimerProc);
		return TRUE;
	}

	return FALSE;
}

BOOL CControlTimer::Stop( UINT uEventId )
{
	return KillTimer(uEventId);
}
