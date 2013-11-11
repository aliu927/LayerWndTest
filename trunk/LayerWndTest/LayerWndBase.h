#pragma once
#include "resource.h"
#include "CacheDC.h"
#include "ButtonCtrl.h"
#include "IWndAnimate.h"
#include <map>

using namespace std;

typedef map<UINT, IControl *>             _ControlCollection;
typedef _ControlCollection::iterator   _ControlIterator;
typedef _ControlCollection::reverse_iterator _ReverseCtrlIterator;

#define  Filter_Msg(uFltMsg) \
	{\
		if(uMsg == uFltMsg)\
		{\
		::MessageBox(NULL,L"Filter ok!",L"Tip",MB_OK);\
		}\
	}
class CLayerWndBase : 
	public CDialogImpl<CLayerWndBase>,
	public CCtrlCallback
{
public:
	CLayerWndBase(void);
	~CLayerWndBase(void);
	enum {IDD = IDD_MAINDLG};

	BEGIN_MSG_MAP(CLayerWndBase)
		MESSAGE_HANDLER(WM_SYSCOMMAND,OnSysCommand)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_MOUSELEAVE,OnMouseLeave)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_PRINTCLIENT,OnPrintWindow)
	END_MSG_MAP()
	LRESULT OnSysCommand(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnMouseLeave(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnPrintWindow(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//
	void __stdcall  OnBtnClicked(UINT uCtrlId);
	void __stdcall  OnStcClicked(UINT uCtrlId);
	void VirtualDraw(HDC hdc = NULL);
private:
	BOOL InitBkg(RECT& rct);
	BOOL InitUI(RECT& rct);
	IControl* GetCtrlByID(unsigned long ulCtrlId);
private:
	CCacheDC* m_pbackgrdDc;
	CCacheDC* m_pDrawCacheDc;
	CButtonCtrl* m_pCloseCtrl;
	CButtonCtrl* m_pMinCtrl;
	IControl* m_pLastHoverCtrl;
	_ControlCollection	m_arrCtrl;
	BOOL	m_bTrack;
	CWndAnimate m_wndAnimate;
};
