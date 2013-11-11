#pragma once
#include "stdafx.h"
class CResMgr: public CSingletonT<CResMgr>
{
public:
	SINGLETON(CResMgr);
	CString GetImgPath(const CString& strRelativePath);
private:
	CResMgr();
private:
	CString m_strImgPath;
};
#define GetImgPathEx(strPath) CResMgr::GetInstance()->GetImgPath(strPath)
