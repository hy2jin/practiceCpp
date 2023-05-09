
// ValueServer.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
//

#include "stdafx.h"
#include "ValueServer.h"
#include "ValueServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CValueServerApp

BEGIN_MESSAGE_MAP(CValueServerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CValueServerApp 생성

CValueServerApp::CValueServerApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CValueServerApp 개체입니다.

CValueServerApp theApp;


// CValueServerApp 초기화

BOOL CValueServerApp::InitInstance()
{
	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	CValueServerDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}

