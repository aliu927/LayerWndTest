#include "StdAfx.h"
#include "ResMgr.h"

CResMgr::CResMgr(void)
{
	m_strImgPath = L"E:\\code\\MySource\\SVN_Client\\LayerWndTest\\trunk\\LayerWndTest\\res\\";
}

CString CResMgr::GetImgPath(const CString& strRelativePath)
{
	if(!::PathIsRelative(strRelativePath) || strRelativePath.IsEmpty()) 
	{
		return m_strImgPath;
	}

	return m_strImgPath + strRelativePath;	
}
