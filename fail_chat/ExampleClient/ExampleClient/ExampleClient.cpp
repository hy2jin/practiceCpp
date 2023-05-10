
// ExampleClient.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
//

#include "stdafx.h"
#include "ExampleClient.h"
#include "ExampleClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExampleClientApp

BEGIN_MESSAGE_MAP(CExampleClientApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CExampleClientApp 생성

CExampleClientApp::CExampleClientApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CExampleClientApp 개체입니다.

CExampleClientApp theApp;


// CExampleClientApp 초기화

BOOL CExampleClientApp::InitInstance()
{
	CWinApp::InitInstance();
	WSADATA temp;
	WSAStartup(0x0202, &temp);	// 소켓 쓰겠다고 선언

	CExampleClientDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	WSACleanup();

	return FALSE;
}

