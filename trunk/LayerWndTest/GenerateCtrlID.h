#pragma once
#include "StdAfx.h"
//////////////////////////////////////////////////////////////////////////
class CMyLock
{
public:
	CMyLock();
	~CMyLock();
	void Unlock();
	void Lock();
protected:
	CRITICAL_SECTION m_critialSec;
};

class CMyAutoLock: public CMyLock
{
public:
	CMyAutoLock();
	~CMyAutoLock();
};
//////////////////////////////////////////////////////////////////////////
class CGenerateID :public CSingletonT<CGenerateID>
{
public:
	SINGLETON(CGenerateID);
	unsigned long GetCtrlID();
	UINT GetEventID();
private:
	static unsigned long m_ulCtrlId;
	static UINT m_uEventId;
};
#define GetCtrlIDEx() CGenerateID::GetInstance()->GetCtrlID()
#define GetEventIDEx() CGenerateID::GetInstance()->GetEventID()