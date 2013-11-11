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
class CGenerateCtrlID :public CSingletonT<CGenerateCtrlID>
{
public:
	SINGLETON(CGenerateCtrlID);
	unsigned long GetCtrlID();
private:
	static unsigned long m_ulCtrlId;
};
#define GetCtrlIDEx() CGenerateCtrlID::GetInstance()->GetCtrlID();