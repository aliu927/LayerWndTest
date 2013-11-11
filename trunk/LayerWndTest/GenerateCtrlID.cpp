#include "StdAfx.h"
#include "GenerateCtrlID.h"

CMyLock::CMyLock()
{
	InitializeCriticalSection(&m_critialSec);
}

CMyLock::~CMyLock()
{
	DeleteCriticalSection(&m_critialSec);
}

void CMyLock::Unlock()
{
	LeaveCriticalSection(&m_critialSec);
}

void CMyLock::Lock()
{
	EnterCriticalSection(&m_critialSec);
}

CMyAutoLock::CMyAutoLock()
{
	Lock();
}

CMyAutoLock::~CMyAutoLock()
{
	Unlock();
}

unsigned long CGenerateID::m_ulCtrlId = 0;
UINT CGenerateID::m_uEventId = 0;

unsigned long CGenerateID::GetCtrlID()
{
	CMyAutoLock autoLock;
	return ++m_ulCtrlId;
}

UINT CGenerateID::GetEventID()
{
	CMyAutoLock autoLock;
	return ++m_uEventId;
}
